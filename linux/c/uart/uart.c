#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "uart.h"
#include "./log/log.h"

#ifndef MAX_READ_BUF_LEN
#define MAX_READ_BUF_LEN 40
#endif

#ifndef MIN_BAUT_SUPPORT
#define MIN_BAUT_SUPPORT 1200
#endif


int read_uart_flag = 1;

int
uart_open(const char *device_path)
{
    int fd = -1;

    fd = open(device_path, O_RDWR|O_NOCTTY|O_NONBLOCK);
    if (fd <= 0) {
        LOGE("Serial Port uart_open Failed!");
        return fd;
    }

    if (!isatty(fd)) {
        LOGE("NOT a tty");
        return -1;
    }

    return fd;
}


int
uart_close(int fd)
{
    int rval = -1;

    rval = close(fd);

    if (rval < 0) {
        LOGE("uart_close Serial Fialed!");
    }
    return rval;
}

int
uart_set_baudrate(int fd, int s)
{
    int i = 0;
    int rval = 0;
    int ba[] = { 115200, 57600, 38400, 19200, 9600};
    int bba[] = {B115200,B57600,B38400,B19200,B9600};

    struct termios attr;

    for (i = 0; i < sizeof(ba) / sizeof(int); i++) {
        if (ba[i] == s) {
            break;
        }
    }

    rval = tcgetattr(fd, &attr);

    if (rval < 0) {
        LOGE("get attr failed!");
        return rval;
    }

    rval = cfsetspeed(&attr, bba[i]);
    if (rval < 0) {
        LOGE("set speed failed!");
        return rval;
    }
    tcflush(fd, TCIOFLUSH);
    rval = tcsetattr(fd, TCSANOW, &attr);
    if (rval < 0) {
        LOGE("set attr failed!");
        return rval;
    }
    return 0;
}

int
uart_set_attrs(int fd, int databits, int stopbits, int parity, int flowctrl)
{
    struct termios attr;
    int rval = tcgetattr(fd,&attr);
    if (rval < 0) {
        LOGE("get attr failed!");
        return rval;
    }


    attr.c_cflag &= ~CRTSCTS; // clear flags
    attr.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);
    attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    attr.c_oflag &= ~(INLCR|IGNCR|ICRNL);
    attr.c_oflag &= ~(ONLCR|OCRNL);

    switch (databits) {
    case 5:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS5;
        break;
    case 6:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS6;
        break;
    case 7:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS7;
        break;
    case 8:
        attr.c_cflag &= ~CSIZE;
        attr.c_cflag |= CS8;
        break;
    default:
        LOGI("Unsupported argument!\n");
    }

    switch (stopbits) {
    case 1:
        attr.c_cflag &= ~CSTOPB;
        break;
    case 2:
        attr.c_cflag |= CSTOPB;
        break;
    default:
        LOGI("Unsupported argument!\n");
    }


    switch (flowctrl) {
        case 'n':
        case 'N':
            break;

        case 'h':
        case 'H':
            attr.c_cflag |= CRTSCTS;
            break;

        case 's':
        case 'S':
            attr.c_iflag |= IXON|IXOFF;
            break;
        default:
            break;
    }


    switch (parity) {
    case 'n':
    case 'N':
        attr.c_iflag &= ~INPCK;
        attr.c_cflag &= ~PARENB;
        break;
    case 'E':
    case 'e':
        attr.c_iflag |= INPCK;
        attr.c_cflag |= PARENB;
        attr.c_cflag &= ~PARODD;
        break;
    case 'O':
    case 'o':
        attr.c_iflag |= INPCK;
        attr.c_cflag |= PARENB;
        attr.c_cflag |= PARODD;
        break;
    default:
        LOGI("Unsupported argument!\n");
    }

    tcflush(fd,TCIOFLUSH);
    rval = tcsetattr(fd,TCSANOW,&attr);
    if (rval < 0) {
        LOGE("set attr failed!");
        return rval;
    }

    return 0;
}

int
set_uart_recv_cond_maxtime_minbytes(int fd, int timeout /*ms*/ ,
        int reciver_min)
{
    struct termios attr;
    int rval = tcgetattr(fd,&attr);
    if (rval < 0) {
        LOGE("get attr failed!");
        return rval;
    }
    attr.c_cc[VTIME] = timeout / 100;
    attr.c_cc[VMIN] = reciver_min;
    tcflush(fd,TCIOFLUSH);
    rval = tcsetattr(fd, TCSANOW, &attr);
    if (rval < 0) {
        LOGE("set attr failed!");
        return rval;
    }
    return 0;
}

int
uart_read(int fd, unsigned char *buf, int len)
{
    int read_len = 0;
    int rval = 0;
    while ((rval = read(fd,buf,len)) == -1) {
        if (errno != EINTR) {
            LOGE("read serial error!");
            return 0;
        }
        read_len += rval;
    }
    return read_len;
}

int
uart_write(int fd, const unsigned char *buf, int len)
{
    int i = 0;
    int rval;

    if ((rval = write(fd, buf, len)) == -1) {
        if (errno != EINTR) {
            LOGE("write serial error!");
            return rval;
        }

        LOGI("write serial error! %d\n",errno);
        return rval;
    }

    return 0;
}

/*
 *@brief: loop read one interigrity frame whose follows from uart fd
 *@param:
 *   ptimeout:           read timeout
 *   fd:                 uart file descriptor
 *   callback
*@author: tangss
*@date: 25/08/2019
*/

int
uart_read_one_frame(struct timeval *ptimeout, int fd, int one_frame_len,
       is_proto_compliance _is_proto_compliance,
       receive_one_frame callback)
{
    int     rval, i, j;
    int     tmp_cmp_len = 0;
    int     proto_len = one_frame_len;
    int     timeout_wait_fill_us = 10000;

    char    tmp_buf = 0;
    char    one_frm_payload_buf[MAX_READ_BUF_LEN] = {0};

    struct timeval timeout;

    LOGI("");
    memmove(&timeout, ptimeout, sizeof(struct timeval));
    LOGI("");

    fd_set  fs_read;

    FD_ZERO(&fs_read);

    //1.get start pos
    //2.walk length byte of protol
    //2.1 if get start flag -- jump to 1
    //2.2 if get end flag --jump to 1
    //3.get end flag at tart pos + walk length - end flag length
    //4.call back
    //5.if there is still content in buffer, jump to 1

    while (read_uart_flag) {

       FD_ZERO(&fs_read);
       FD_SET(fd, &fs_read);

 //   LOGI("fd:%d", fd);
       rval = select(fd+1, &fs_read, NULL, NULL, &timeout);
 //   LOGI("");
       if (rval > 0) {

       } else if ( rval == 0) {
          // LOGD("select return == 0 timeout\n");
           continue;
       } else {

           LOGE("select return < 0, errno:%d\n", errno);
           return -1;
       }

       rval = recv(fd, one_frm_payload_buf, proto_len, MSG_PEEK);
       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
           continue;
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
           return -2;
       }

       if (rval != one_frame_len) {
            LOGI("not enough length\n");
            usleep(timeout_wait_fill_us);
            continue;
       }

       rval = _is_proto_compliance(one_frm_payload_buf, proto_len);
       if (rval) {
           goto TICK_ONE_BYTE;
       }

       rval = callback(one_frm_payload_buf, proto_len);

       rval = recv(fd, one_frm_payload_buf, proto_len, 0);

       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
       }

       continue;

TICK_ONE_BYTE:
       rval = recv(fd, &tmp_buf, 1, 0);
       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
       }
    }

}

/*
 *@brief: loop read one interigrity frame whose follows frame_protocol from uart fd
 *@param:
 *   frame_protocol:    frame protocol who defines the start flag and end flag
 *      of frame.
 *   timeout:           read timeout
 *   fd:                uart file descriptor
 *   buf:               output buffer from uart
 *   buf_len:           length of buf
*@author: tangss
*@date: 25/08/2019
*/

int
uart_read_one_frame_with_(frm_proto_t *pfrm_proto, struct timeval *ptimeout,
        int fd, receive_one_frame callback)
{
    int     rval, i, j;
    int     payload_len = 0;
    int     flag_e_pos = 0;
    int     tmp_s_pos = 0;
    int     tmp_d_pos = 0;
    int     tmp_cmp_len = 0;
    int     timeout_wait_fill_us = 10000;

    char    tmp_buf = 0;
    char    one_frm_payload_buf[MAX_READ_BUF_LEN] = {0};

    frm_proto_t frm_proto;

    struct timeval timeout;

    LOGI("");
    memmove(&frm_proto, pfrm_proto, sizeof(frm_proto));
    memmove(&timeout, ptimeout, sizeof(struct timeval));
    LOGI("");

    fd_set  fs_read;

    FD_ZERO(&fs_read);

    LOGI("");
    payload_len =  frm_proto.proto_len -  frm_proto.flag_s_len -
        frm_proto.flag_e_len;
    flag_e_pos =  frm_proto.proto_len - frm_proto.flag_e_len;

    LOGI("");
    //1.get start pos
    //2.walk length byte of protol
    //2.1 if get start flag -- jump to 1
    //2.2 if get end flag --jump to 1
    //3.get end flag at tart pos + walk length - end flag length
    //4.call back
    //5.if there is still content in buffer, jump to 1

    while (read_uart_flag) {

       FD_ZERO(&fs_read);
       FD_SET(fd, &fs_read);

 //   LOGI("fd:%d", fd);
       rval = select(fd+1, &fs_read, NULL, NULL, &timeout);
 //   LOGI("");
       if (rval > 0) {

       } else if ( rval == 0) {
          // LOGD("select return == 0 timeout\n");
           continue;
       } else {

           LOGE("select return < 0, errno:%d\n", errno);
           return -1;
       }

       rval = recv(fd, one_frm_payload_buf, frm_proto.proto_len, MSG_PEEK);
       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
           continue;
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
           return -2;
       }

       if (rval != frm_proto.proto_len) {
            LOGI("not enough length\n");
            usleep(timeout_wait_fill_us);
            continue;
       }

       for (i = 0; i < frm_proto.flag_s_len; i++) {

           if (one_frm_payload_buf[i] != frm_proto.flag_s[i]) {
                LOGI("s skip\n");
                goto TICK_ONE_BYTE;
           }
       }

       for (i = 0; i < frm_proto.flag_e_len; i++) {
           if (one_frm_payload_buf[flag_e_pos + i] != frm_proto.flag_e[i]) {
                LOGI("e skip\n");
                goto TICK_ONE_BYTE;
           }
       }

       for (i = 0; i < payload_len; i++) {

           tmp_s_pos = one_frm_payload_buf + frm_proto.flag_s_len + i;
           tmp_d_pos = frm_proto.flag_s;
           tmp_cmp_len = frm_proto.flag_s_len;

           if (memcmp((void *)tmp_s_pos, (void *)tmp_d_pos, tmp_cmp_len)) {
               LOGI("payload s skip\n");
               goto TICK_ONE_BYTE;
           }

           tmp_s_pos = one_frm_payload_buf + frm_proto.flag_e_len + i;
           tmp_d_pos = frm_proto.flag_e;
           tmp_cmp_len = frm_proto.flag_e_len;

           if (memcmp((void *)tmp_s_pos, (void *)tmp_d_pos, tmp_cmp_len)) {
               LOGI("payload e skip\n");
               goto TICK_ONE_BYTE;
           }

       }

       rval = callback(one_frm_payload_buf, frm_proto.proto_len);

       rval = recv(fd, one_frm_payload_buf, frm_proto.proto_len, 0);

       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
       }

       continue;

TICK_ONE_BYTE:
       rval = recv(fd, &tmp_buf, 1, 0);
       if (rval > 0) {

       } else if (rval == 0) {

           LOGD("recv return == 0, client close connection\n");
       } else {
           LOGE("recv return < 0, errno:%d\n", errno);
       }
    }

}

void
stop_read_uart(void)
{
    read_uart_flag = 0;
    return;
}

