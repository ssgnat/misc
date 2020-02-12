/*************************************************
  Copyright (C), 2019-2099, Horzon Info. Co.,Ltd.
  File name:      hz_disk_mgr.c
Author:         tangss
Version:        1.0
Date:           2019-11-02
Description:
Others:
 **************************************************/

#include <stdarg.h>
#include <stddef.h>
//#include <setjmp.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cJSON.h"

#include <sys/ioctl.h> //ioctl
#include <sys/mount.h> //BLKSSZGET  //BLKGETSIZE
#include <linux/fd.h>  //struct floppy_struct //FDGETPRM
#include <linux/hdreg.h>

#include "conduit_client.h"
#include "conduit_server.h"

#define ARRAY_SIZE(arg) (sizeof(arg)/sizeof(arg[0]))

#define MODULE_NAME "hzdisk"

#define MAX_RESULT_BUFFER 10240

#define PTNS_NUM_MAX    4
#define DISK_PATH_LEN   128
#define DISK_DEVICEID_LEN     128
#define DISK_NUM_MAX    5

#define PTN_PATH_LEN    128
#define PTN_NUM_PER_DISK_MAX 4

#define CMD_LEN_MAX     128


extern int disk_get_devid(const char *path, char *devid);
extern int disk_set_devid(const char *path, char *devid);


static int
get_device_id_ssd(const char *path, char *buf)
{
    int fd = open(path, O_RDONLY);
    struct hd_driveid hd;
    if (ioctl(fd, HDIO_GET_IDENTITY, &hd) >= 0) {
        memmove(buf, hd.serial_no, DISK_DEVICEID_LEN);
        close(fd);
        return 0;
    }
    //printf("err:%s\n", strerror(errno));

    close(fd);
    return 1;
}

static int
get_device_cap(const char *path, unsigned long *cap)
{
    int fd = open(path, O_RDONLY);
    unsigned long long bytes = 0;

    *cap = 0;
    //cap
    if (ioctl(fd, BLKGETSIZE64, &bytes) >= 0) {
        *cap = bytes >> 20;
        return 0;
    }
    //printf("err:%s\n", strerror(errno));
    close(fd);
    return 1;
}

static int
get_device_sector_size(const char *path, unsigned long *ssize)
{
    int fd = open(path, O_RDONLY);
    //sector size
    if (ioctl(fd, BLKSSZGET, ssize) >= 0) {
        return 0;
    }
    //printf("err:%s\n", strerror(errno));
    close(fd);
    return 1;
}

static int
get_device_type(const char *path, char *buf)
{
    char filepath[128] = {0};
    int  fd = 0;
    int  len = 0;

    if (strlen(path) <= 0) {
        return 1;
    }

    sprintf(filepath, "/sys/block/sd%c/queue/rotational", path[strlen(path)-1]);
    //printf("%s\n", filepath);

    fd = open(filepath, O_RDONLY);

    len = read(fd, buf, 128);
    if (len <= 0) {
        return 2;
    }

    close(fd);
    return 0;
}

//exe
static int
exec(const char *command, char *with_result, int *with_result_len)
{

    char *cmd = NULL;
    int   len = 0;
    int   max_result = 0;
    FILE *fp = NULL;

    char  read_buf[MAX_RESULT_BUFFER]={0};

    max_result = *with_result_len;

    len = strlen(command) + 20;
    cmd = (char*)malloc(len);
    memset(cmd, 0, len);
    memmove(cmd, command, strlen(command));

    strcat(cmd," 1>&1 2>&1");

    fp = popen(cmd, "r");

    if( fp <=0 )
    {
        free(cmd);
        return 1;
    }

    len = 0;
    while (fgets(read_buf, sizeof(read_buf), fp) > 0) {
        len += strlen(read_buf);
        if (len >= max_result - 1) {
            continue;
        }
        strcat(with_result, read_buf);
    }

    with_result_len = len;

    pclose(fp);
    free(cmd);

    return 0;
}

//file read
static int
file_read(const char *path, char *buf, int len)
{
    int rval = 0;
    int fd = open(path, O_RDONLY);

    if (fd <= 0) {
        return -1;
    }

    rval = read(fd, buf, len);
    if (rval <= 0) {
        return -2;
    }

    close(fd);

    rval = remove(path);
    if (rval) {
        return -3;
    }

    return 0;
}

/*
static int
get_disks_info(const char *req, char res[])
{
    LOGD("%s %d", __FILE__, __LINE__);
    int  i, j          = 0;
    int  rval          = 0;
    char devid[128]    ={0};
    char reslt[1024]   ={0};
    int  reslt_len     =1024;

    char *cmd_ls_fmt   = "ls /dev/block/sd[a-z]";
    char  cmd_ls[128]  = {0};

    char *sz_tmp            = NULL;
    char *sz_tmp_1          = NULL;

    if (lock()) {
        return 1;
    }

    for (i = 0; i < DISK_NUM_MAX; i++) {
        memset(disks[i].ptns, 0, PTNS_NUM_MAX * sizeof(PTN_INFO));
    }

    //get all disk nodes
    if (exec(cmd_ls_fmt, reslt, &reslt_len)) {
        LOGE("%s %d exec cmd:%s\n", __FILE__, __LINE__, cmd_ls);
        unlock();
    }

    //sz_tmp = reslt; while (sz_tmp) { LOGE("%2x ", sz_tmp[0]); sz_tmp++; }
    sz_tmp = reslt;
    i = 0;
    while (sz_tmp_1 = strstr(sz_tmp,"\r\n")) {
        memmove(disks[i].path, sz_tmp, sz_tmp_1 - sz_tmp);
        i = i + 1;
        sz_tmp = sz_tmp_1 + 1;
        LOGD("sz_tmp:%s\n", sz_tmp);
    }
    LOGD("%s %d exec cmd:%s rlt:%s\n", __FILE__, __LINE__, cmd_ls, reslt);

    for (i = 0; i < DISK_NUM_MAX; i++) {
        //get device id
        rval = disk_get_devid(disks[i].path, sz_tmp);

        //total size
        //block size

        //ptns info
    }

    unlock();
    return 0;
}

*/
static void
usage(const char *name)
{
    //LOGD("usage: %s getdeviceid <device path> <device type>", name);
}


int main(int argc, char *argv[])
{
    int     fd   = 0;
    int     rval = 0;
    char    buf[DISK_DEVICEID_LEN] = {0};
    int     buf_len = DISK_DEVICEID_LEN;

    char    cmd[CMD_LEN_MAX] = {0};

    int     sector_size;
    unsigned long ul_tmp;

    if (argc < 2) {
        printf("ERROR %d\n", argc);
        return 1;
    }

    if (!strcmp(argv[1], "getdeviceid")) {
        if (!strcmp(argv[3], "ssd")) {
            rval = get_device_id_ssd(argv[2], buf);
            if (rval) {
                printf("ERROR rval:%d", rval);
            } else {
                printf("%s", buf);
            }
        } else {
            rval = disk_get_devid(argv[2], buf);
            if (rval) {
                printf("ERROR: %s %d disk_get_devid rval:%d\n", __FILE__, __LINE__, rval);
            } else {
                printf("%s", buf);
            }
        }
    } else if (!strcmp(argv[1], "setdeviceid")) {
        if (!strcmp(argv[3], "ssd")) {
            printf("ERROR: SSD CANN'T SET\n");
        } else {
            rval = disk_set_devid(argv[2], buf);
            if (rval) {
                printf("ERROR: %s %d disk_set_devid rval:%d\n", __FILE__, __LINE__, rval);
            } else {
                printf("%s", buf);
            }
        }
    } else if (!strcmp(argv[1], "format")) {
        sprintf(buf, "/system/bin/hzformat %s %s", argv[2], argv[3]);
        system(buf);
        printf("PLEASE RESTART TO CHECK\n");
    } else if (!strcmp(argv[1], "getcap")) {
        rval = get_device_cap(argv[2], &ul_tmp);
        if (rval) {
                //printf("ERROR: %s %d get_device_cap rval:%d\n", __FILE__, __LINE__, rval);
        } else {
            printf("%u",ul_tmp);
        }
    } else if (!strcmp(argv[1], "getsectorsize")) {
        rval = get_device_sector_size(argv[2], &ul_tmp);
        if (rval) {
                //printf("ERROR: %s %d get_device_sector_size rval:%d\n",
                //        __FILE__, __LINE__, rval);
        } else {
            printf("%u",ul_tmp);
        }
    } else if (!strcmp(argv[1], "getdevicetype")) {
        rval = get_device_type(argv[2], buf);
        if (rval) {
                //printf("ERROR: %s %d get_device_sector_size rval:%d\n",
                //        __FILE__, __LINE__, rval);
        } else {
            if (buf[0] == '0') {
                printf("ssd");
            } else {
                printf("hdd");
            }
        }
    } else if (!strcmp(argv[1], "getfree")) {
        sprintf(cmd, "df | grep %s | busybox awk '{print $4}'", argv[2]);
        rval = exec(cmd, buf, &buf_len);
        if (rval) {
            //printf("ERROR: %s %d getfree rval:%d\n", __FILE__, __LINE__, rval);
        } else {
            printf("%s",buf);
        }

    } else {
        printf("ERROR: SUPPORT CMD: \n \
                getdeviceid \n \
                setdeviceid \n \
                format \n \
                getcap \n \
                getfree \n \
                getsectorsize \n \
                getdevicetype\n \
                \n \
            hz_disk_util <CMD> /dev/block/sda  [ssd|hdd] \n \
              \n \
            note: getdevicetype no need add [ssd|hdd] \n \
             \n");
    }

    return 0;
}
