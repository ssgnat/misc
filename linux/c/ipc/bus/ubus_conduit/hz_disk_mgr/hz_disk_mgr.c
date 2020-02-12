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

#ifdef ANDROID
#include <cutils/log.h>
#define LOGD ALOGD
#define LOGI ALOGI
#define LOGE ALOGE
#else
#define LOGD
#define LOGI
#define LOGE
#endif

#define ARRAY_SIZE(arg) (sizeof(arg)/sizeof(arg[0]))

#define MODULE_NAME "hzdisk"

#define MAX_RESULT_BUFFER 10240

#define PTNS_NUM_MAX    4
#define DISK_PATH_LEN   128
#define DISK_DEVICEID_LEN     128
#define DISK_NUM_MAX    5

#define PTN_PATH_LEN    128
#define PTN_NUM_PER_DISK_MAX 4

#define UUID_LEN_MAX 32



extern int disk_get_devid(const char *path, char *devid);
extern int disk_set_devid(const char *path, char *devid);
int exec(const char *command, char *with_result, int *with_result_len);

enum {
    NTFS,
    FAT32,
    EXT4
};

typedef struct {
    char        path[PTN_PATH_LEN];
    int         total_size;  //util: M
    int         format_type; //ntfs, fat32, ext4
    int         sector_start;
    int         sector_end;
} PTN_INFO;

typedef struct {
    char            path[DISK_PATH_LEN];
    char            sn[DISK_DEVICEID_LEN];
    int             total_size;  //util: M
    int             block_size;  //bytes
    int             ptns_num;
    PTN_INFO        ptns[PTNS_NUM_MAX];
} DISK_INFO;

static DISK_INFO disks[DISK_NUM_MAX] = {0};

static volatile int c_cnt = 0;
static volatile int s_cnt = 0;

static volatile int lock_flag  = 0;

/*deviceinfo:
 *
 typedef enum
 {
 PDM_DEVICE_INFO_MAC = 0x0,
 PDM_DEVICE_INFO_SN,
 PDM_DEVICE_INFO_MAGICNUM,
 PDM_DEVICE_INFO_LENGTH,
 PDM_DEVICE_INFO_OUI,
 PDM_DEVICE_INFO_HW,
 PDM_DEVICE_INFO_BUT
 }PDM_DEVICE_INFO_E;
 */

static int  format(const char *req, char res[]);
static int  get_disks_info(const char *req, char res[]);
static int start(const char *req, char res[]);
static int stop(const char *req, char res[]);
static int setdevid(const char *req, char res[]);
static int getdevid(const char *req, char res[]);

static module_method_t methods[] = {
    {.method_name = "getdisksinfo", .fun = get_disks_info},
    {.method_name = "format",       .fun = format        },
    {.method_name = "start",        .fun = start         },
    {.method_name = "stop",         .fun = stop          },
    {.method_name = "setdevid",     .fun = setdevid      },
    {.method_name = "getdevid",     .fun = getdevid      },
};

static int
lock()
{
    if (lock_flag) {
        return 1;
    }

    lock_flag = 1;
    return 0;

}

static void
unlock()
{
    lock_flag = 0;
}

static int
format(const char *req, char res[])
{
    int  rval           = 0;
    char cmd[256]       = {0};
    char reslt[10240]   = {0};
    int  reslt_len      = 10240;

    if (!req) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return -1;
    }

    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }

    sprintf(cmd, "/sys/block/sd%c/queue/rotational",req[strlen(req)-1]);
    rval = exec(req, reslt, &reslt_len);
    if (rval) {
        LOGE("%s %d ", __FILE__, __LINE__);
        unlock();
    }

    if (reslt[0] == '0') {
        memmove(reslt, "ssd", 4);
        unlock();
    } else {
        memmove(reslt, "hdd", 4);
        unlock();
    }

    sprintf(cmd, "/system/bin/hz_disk_util format %s %s", req,  reslt);
    LOGD("%s %d cmd: %s", __FUNCTION__, __LINE__, cmd);
    rval = exec(cmd, reslt, &reslt_len);
    if (rval) {
        LOGE("%s %d ", __FILE__, __LINE__);
        unlock();
    }

    LOGD("%s %d rslt: %s", __FUNCTION__, __LINE__, reslt);
    memmove(req, reslt, reslt_len);

    LOGD("%s %d ", __FILE__, __LINE__);
    unlock();
    return 0;
}

//exe
int
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

    *with_result_len = len;

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

static unsigned long long
get_disk_size(const char *name)
{
    const char *ptr = name;
    unsigned long long size;
    char buff[128];
    FILE *fp;

    sprintf(buff,"/sys/block/%s/size",ptr);

    if(NULL == (fp = fopen(buff,"r"))){
        perror("fopen");
        return 0;
    }
    fscanf(fp,"%lld",&size);
    fclose(fp);

    return size;
}

static int
get_disks_info(const char *req, char res[])
{
    LOGD("%s %d", __FILE__, __LINE__);
    int  rval           = 0;
    char reslt[20480]   = {0};
    int  reslt_len      = 20480;

    rval = exec("sh /system/bin/disk_check.sh", reslt, &reslt_len);
    if (rval) {
        LOGD("%s %d", __FILE__, __LINE__);
        unlock();
        return 1;
    }

    LOGD("%s %d len:%d strlen:%d |||%s", __FUNCTION__, __LINE__, reslt_len,
            strlen(reslt), reslt);

    memmove(res, reslt, reslt_len + 1);

    unlock();
    return 0;
}

static int
get_uuid(char *uuid, int len)
{
    int fd   = 0;
    int rval = 0;

    //printf("%s %d\n", __FUNCTION__, __LINE__);
    if (len <= UUID_LEN_MAX) {
        return -1;
    }

    //printf("%s %d\n", __FUNCTION__, __LINE__);
    fd = open("/proc/sys/kernel/random/uuid", O_RDONLY);
    if (fd <= 0) {
        return -2;
    }

    //printf("%s %d\n", __FUNCTION__, __LINE__);
    rval = read(fd, uuid, UUID_LEN_MAX);
    if (rval != UUID_LEN_MAX) {
       return -3;
    }

    printf("%s %d uuid:%s\n", __FUNCTION__, __LINE__, uuid);
    close(fd);
    return 0;
}

static int
setdevid(const char *req, char res[])
{
    int  rval           = 0;
    char cmd[256]       = {0};

    if (!req) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return -1;
    }

    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }

    rval = get_uuid(cmd, 256);
    if (rval) {
        LOGD("%s %d get uuid error rval:%d", __FILE__, __LINE__, rval);
        unlock();
        return 2;
    }

    rval = disk_set_devid(req, cmd);
    if (rval) {
        LOGD("%s %d set devid error rval:%d", __FILE__, __LINE__, rval);
        unlock();
        return 3;
    }

    LOGD("%s %d ", __FILE__, __LINE__);
    unlock();
    return 0;
}

static int
getdevid(const char *req, char res[])
{
    int  rval           = 0;
    char reslt[256]   = {0};
    int  reslt_len      = 256;

    if (!req) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return -1;
    }

    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }

    rval = disk_get_devid(req, reslt);
    if (rval) {
        LOGD("%s %d set devid error rval:%d", __FILE__, __LINE__, rval);
        unlock();
        return 3;
    }

    memmove(res, reslt, UUID_LEN_MAX);

    LOGD("%s %d ", __FILE__, __LINE__);
    unlock();
    return 0;
}
static int
start(const char *req, char res[])
{
    //start to monitor
    //send event once snipper something changed
    //TODO...
    return 0;
}

static int
stop(const char *req, char res[])
{
    //reserved...
    return 0;
}
static int
server_start(void)
{
    LOGD("%s %d", __FILE__, __LINE__);
    int rval = cdt_srv_start();
    LOGD("%s %d", __FILE__, __LINE__);
    return rval;
}

static int
server_run(void)
{
    LOGD("%s %d", __FILE__, __LINE__);
    int rval = cdt_srv_run();
    LOGD("%s %d", __FILE__, __LINE__);
    return rval;
}

static int
add_modules(void)
{
    LOGD("add_module b\n");
    int rval = cdt_srv_add_module(MODULE_NAME, methods, ARRAY_SIZE(methods));
    LOGD("add_module e\n");
    return rval;
}

/*
   static int
   send_event(void)
   {
   int    i = 0;
   int rval = 0;

   for (i = 0; i < ARRAY_SIZE(srvevents); i++) {
   rval = cdt_cli_send_event(srvevents[i], srveventcontents[i]);
   if (rval != 0) {
   return rval;
   }
   }

   return 0;
   }
   */
static int
server_stop(void)
{
    int rval = cdt_srv_stop();
    return rval;
}

//#define TEST
int main(int argc, char *argv[])
{
#ifdef TEST
    int fd   = 0;
    int rval = 0;
    char buf[DISK_DEVICEID_LEN] = {0};
    //LOGE("get_disks_info begin");
    //get_disks_info(NULL, NULL);
    fd = open(argv[1], O_RDONLY);
    test_disk_info(fd);
    close(fd);

    rval = disk_get_devid(argv[1], buf);
    if (rval) {
        LOGD("%s %d disk_get_devid rval:%d", __FILE__, __LINE__, rval);
    }
    LOGE("get_disks_info end devid:%s", buf);
    return 0;
#else
    int rval = 0;
    LOGD("main begin");
    rval = server_start();
    if (rval) {
        LOGE("%s %d", __FILE__, __LINE__);
        return 0;
    }

    rval = add_modules();
    if (rval) {
        LOGE("%s %d", __FILE__, __LINE__);
        return 0;
    }

    rval = server_run();
    if (rval) {
        LOGE("%s %d", __FILE__, __LINE__);
        return 0;
    }

    rval = server_stop();
    if (rval) {
        LOGE("%s %d", __FILE__, __LINE__);
        return 0;
    }
    LOGD("main end");
    return 0;
#endif
}
