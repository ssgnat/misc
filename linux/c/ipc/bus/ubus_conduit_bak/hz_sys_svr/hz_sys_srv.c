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

#define MODULE_NAME "hzsys"

#define DEVINFO_NAME "deviceinfo"
#define DEVINFO_PATH "/mnt/mtdinfo"

#define HORZON_MAC_OFFSET    (0)
#define HORZON_MAC_LEN       (18)

#define HORZON_INFO_OFFSET        (1*1024*1024)
#define HORZON_SN_INNER_OFFSET    (0)
#define HORZON_SN_LEN             (20)
#define HORZON_UPURL_INNER_OFFSET (20)
#define HORZON_UPURL_LEN          (256)


#define MAX_RESULT_BUFFER 10240

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
extern int get_flash_info_all(const char *mtdname);
extern int set_flash_info_all(const char *mtdname, const char *mtdinfo);

extern int set_flash_info(const char *mtdname, unsigned long offset,
        unsigned int offlen, const char *mtdinfo);
extern int get_flash_info(const char *mtdname, unsigned long offset,
        unsigned int offlen);

static int  set_devid(const char *req, char res[]);
static int  get_devid(const char *req, char res[]);
static int  set_mac(const char *req, char res[]);
static int  get_mac(const char *req, char res[]);
static int  format(const char *req, char res[]);
static int  set_update_url(const char *req, char res[]);
static int  get_update_url(const char *req, char res[]);
static int  set_light(const char *req, char res[]);
static int  hz_exec(const char *req, char res[]);

static module_method_t methods[] = {
    {.method_name = "setdeviceid", .fun = set_devid     },
    {.method_name = "getdeviceid", .fun = get_devid     },
    {.method_name = "setmac",      .fun = set_mac       },
    {.method_name = "getmac",      .fun = get_mac       },
    {.method_name = "setupurl",    .fun = set_update_url},
    {.method_name = "getupurl",    .fun = get_update_url},
    {.method_name = "format",      .fun = format        },
    {.method_name = "setlight",    .fun = set_light   },
    {.method_name = "exec",        .fun = hz_exec       },
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
      if(len >= max_result - 1)
      {
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
//MAC 0-18

static int
set_mac(const char *req, char res[])
{
    char devid[128] = {0};

    if (lock()) {
        return 1;
    }
    memmove(devid, req, 128);
    set_flash_info(DEVINFO_NAME,  HORZON_MAC_OFFSET, HORZON_MAC_LEN, devid);

    unlock();

    return 0;
}

static int
get_mac(const char *req, char res[])
{

    char mac[128]      ={0};
    int  rval          = 0;

    if (lock()) {
        return 1;
    }

    rval = get_flash_info(DEVINFO_NAME,  HORZON_MAC_OFFSET,
            HORZON_MAC_LEN);
    if (rval) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, errno);
        unlock();
        return -1;
    }

    rval = file_read(DEVINFO_PATH, mac, HORZON_MAC_LEN);
    if (rval < 0) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, rval);
        unlock();
        return -2;
    }

    memmove(res, mac, strlen(mac)+1);
    unlock();

    return 0;
}
//SN:3 *1024 *1024- 25
//
static int
set_devid(const char *req, char res[])
{
    char devid[128] = {0};
    cJSON* obj = NULL;
    cJSON* tmp = NULL;

    if (lock()) {
        return 1;
    }

    if (req == NULL) {
        LOGE("%s %d error", __FILE__, __LINE__);
        unlock();
        return -1;
    }
/*
    obj = cJSON_Parse(req);
    if (obj == NULL) {
        LOGE("%s %d error", __FILE__, __LINE__);
        return -1;
    }
    tmp = cJSON_GetObjectItem(obj, "data");
    if (tmp == NULL) {
        LOGE("%s %d error", __FILE__, __LINE__);
        return -1;
    }
    memcpy(devid, tmp->valuestring,strlen(tmp->valuestring));
    LOGD("%s %d devid:%s", __FILE__, __LINE__, devid);
    cJSON_Delete(obj);
    */
    memmove(devid, req, 128);
    set_flash_info(DEVINFO_NAME, HORZON_INFO_OFFSET + HORZON_SN_INNER_OFFSET,
            HORZON_SN_LEN, devid);

    unlock();
    return 0;
}

static int
get_devid(const char *req, char res[])
{
    LOGD("%s %d", __FILE__, __LINE__);
    char devid[128]    ={0};
    int  rval          = 0;

    if (lock()) {
        return 1;
    }

    rval = get_flash_info(DEVINFO_NAME,  HORZON_INFO_OFFSET + HORZON_SN_INNER_OFFSET, HORZON_SN_LEN);
    if (rval) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, rval);
        unlock();
        return -1;
    }

    LOGD("%s %d", __FILE__, __LINE__);
    rval = file_read(DEVINFO_PATH, devid, HORZON_SN_LEN);
    if (rval < 0) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, rval);
        unlock();
        return -2;
    }

    LOGD("%s %d devid:%s", __FILE__, __LINE__, devid);
    memmove(res, devid, strlen(devid)+1);

    unlock();
    return 0;
}

static int
get_update_url(const char *req, char res[])
{
    char url[256] = {0};
    int  rval          = 0;

    LOGE("%s %d ", __FILE__, __LINE__);
    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }

    rval = get_flash_info(DEVINFO_NAME,
            HORZON_INFO_OFFSET + HORZON_UPURL_INNER_OFFSET,
            HORZON_UPURL_LEN);
    if (rval) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, errno);
        unlock();
        return -1;
    }

    rval = file_read(DEVINFO_PATH, url, HORZON_UPURL_LEN);
    if (rval < 0) {
        LOGE("%s %d error:%d", __FILE__, __LINE__, rval);
        unlock();
        return -2;
    }
    strcpy(res, url);
    unlock();
    LOGE("%s %d ", __FILE__, __LINE__);
    return 0;
}

static int
set_update_url(const char *req, char res[])
{
    char url[256] = {0};

    LOGE("%s %d ", __FILE__, __LINE__);
    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }

    memmove(url, req, 128);
    set_flash_info(DEVINFO_NAME,
            HORZON_INFO_OFFSET + HORZON_UPURL_INNER_OFFSET,
            HORZON_UPURL_LEN, url);

    LOGE("%s %d ", __FILE__, __LINE__);
    unlock();
    return 0;
}

static int
format(const char *req, char res[])
{
    char type[64] = {0};
    char dev[64] = {0};

    LOGE("%s %d NOT IMPLEMENT YET", __FILE__, __LINE__);
    if (!req) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return -1;
    }

    if (lock()) {
        LOGE("%s %d ", __FILE__, __LINE__);
        return 1;
    }



    LOGE("%s %d ", __FILE__, __LINE__);
    unlock();
    return 0;
}

static int
hz_light(const char *req, char res[])
{
    char result[256] = {0};
    int rval = 0;
    int len = 256;

    if (lock()) {
        return 1;
    }

    //fix me tangss
    //light
    //rval = exec(req, result, &len);
    if (rval) {
        LOGE("%s %d rval:%d", __FILE__, __LINE__, rval);
        unlock();
        return -1;
    }

    unlock();
    return 0;
}


static int
set_light(const char *req, char res[])
{
   int  light_num       = 0;
   int  light_stat      = 0;
   int  i               = 0;
   char command[64]     = {0};
   char cmd_fmt[4][64]  =
        {
            "echo %d > /sys/class/gpio/export",
            "echo out > /sys/class/gpio/gpio%d/direction",
            "echo %d > /sys/class/gpio/gpio%d/value",
            "echo %d > /sys/class/gpio/unexport"
        };

   char err_str[1024]       = {"INPUT ERROR"};

   memmove(err_str, err_str, strlen(err_str) + 1);

   if (req == NULL
        || strlen(req) < 3) {
        memmove(res, err_str, strlen(err_str)+1);
        return -1;
   }

   if (strlen(req) == 3) {

        if ((req[1] != '|')
        || !isdigit(req[0])
        || !isdigit(req[2])) {
            memmove(res, err_str, strlen(err_str)+1);
            return -2;
        }

        light_num = req[0] - '0';
        light_stat= req[2] - '0';
   } else if(strlen(req) == 4) {
        if ((req[2] != '|')
        || !isdigit(req[0])
        || !isdigit(req[3])) {
            memmove(res, err_str, strlen(err_str)+1);
            return -3;
        }

        light_num = (req[0] - '0') * 10 + (req[1] - '0');
        light_stat= req[3] - '0';

   } else {
        //memmove(err_str, req,     strlen(req) + 1  );
        memmove(res,     err_str, strlen(err_str)+1);
        return -4;
   }


   switch(light_num) {
       case 1:
           light_num = 40;//GPIO5_0
           break;
       case 2:
           light_num = 41;//GPIO5_1
           break;
       case 3:
           light_num = 42;//GPIO5_2
           break;
       case 4:
           light_num = 48;//GPIO6_0
           break;
       default:
           return -5;
           break;
   }

   for (; i < 4; i++) {
       if (i == 2) {
            sprintf(command, cmd_fmt[i], light_stat, light_num);
       } else {
            sprintf(command, cmd_fmt[i], light_num);
       }

       system(command);
   }

   return 0;
}

static int
hz_exec(const char *req, char res[])
{
    char result[256] = {0};
    int rval = 0;
    int len = 256;

    if (lock()) {
        return 1;
    }

    rval = exec(req, result, &len);
    if (rval) {
        LOGE("%s %d rval:%d", __FILE__, __LINE__, rval);
        unlock();
        return -1;
    }

    unlock();
    return 0;
}

/*
static int
server_send_event(void)
{
    int i = 0;
    int rval = 0;

    for (i = 0; i < ARRAY_SIZE(clievents); i++) {
        rval = cdt_srv_send_event(clievents[i], clieventcontents[i]);
        if (rval != 0) {
            return rval;
        }
    }

    return 0;
}
*/

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

int main(int argc, char *argv[])
{
    int rval = 0;

   if (argc > 1) {

   }

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
}
