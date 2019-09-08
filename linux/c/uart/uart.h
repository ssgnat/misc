/*
 *@brief: serial port utility communication with other devices'
 *@author: tangss
 *@date: created 24/08/2019
 *@modify:
 * 1.
 */
#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define VERSION "1.0.0"


//only adapter with fixed length protocol
typedef  struct {
   char flag_s[4]; //MAX LEN 4
   int  flag_s_len;

   char flag_e[4];
   int  flag_e_len;

   int  proto_len;
   char reverse[0];
}frm_proto_t;

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (* receive_one_frame)(unsigned char *buf, int buf_len);
/*
 * whether the compliance meets the agreement
 * you will get frame buffer if return 0
 * @buf :       a frame
 * @buf_len:    a frame length
 * @return : 0: agreement else disagreement
 */
typedef int (* is_proto_compliance)(unsigned char *buf, int buf_len);


int uart_open(const char * uart_path);
int uart_close(int fd);
int uart_set_baudrate(int fd,int baudrate);
int uart_set_attrs(int fd, int databits, int stopbits, int parity,
        int flowctrl);

int uart_write(int fd, const unsigned char *buf,int len);
/**
* @breif: 设置uart接收的条件（最大的超时时间，最小接收到的字节数)
* @max_time: VTIME
* @min_bytes:VMIN
* @return: 0:ok, else nok
*/
int set_uart_recv_cond_maxtime_minbytes(int fd,int max_time,int min_bytes);



/**
 * @brief 在外循环读取
 **/
int uart_read(int fd,unsigned char *buf,int len);
/**
 * @brief: loop read, callback when get one intergrity frame  by frm_proto
 * @timeout: wait time for select
 **/
int uart_read_one_frame_with_(frm_proto_t *frm_proto, struct timeval *timeout,
        int fd, receive_one_frame callback);

/*
 *@brief: loop read one interigrity frame whose follows from uart fd
 *@param:
 *   ptimeout:           read timeout
 *   fd:                 uart file descriptor
 *   callback
*@author: tangss
*@date: 25/08/2019
*/

int uart_read_one_frame(struct timeval *ptimeout, int fd, int one_frame_len,
       is_proto_compliance _is_proto_compliance,
       receive_one_frame callback);

#ifdef __cplusplus
}
#endif
#endif
