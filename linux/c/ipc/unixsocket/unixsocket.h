/*
 *@brief:   unixsocket header files
 *@auther:  tangss
 *@date:    20/09/2019
 */

#ifndef _UNIXSOCKET_H_
#define _UNIXSOCKET_H_


//unix server
typedef int (*unixsock_server_receiver)(int client_fd,
        const char *clientpath, const char *request_buffer,
        int *request_buffer_len);

/*
 *@brief: open and bind, listen unix_path
 *@param: unix_path, unix path
 *        reciver, process function on recive request
 *@return: >0 file descriptor of unix path opened, else error
 *@modify:
 *
 */
int unixsocket_server_start(const char *unix_path,
    unixsock_server_receiver receiver);
int unixsocket_server_stop(void);


//unix client
int unixsocket_client_connect(const char *unix_path, const char *clientid);
int unixsocket_client_send(int sockfd, const char *to_send_buffer,
    int to_send_buffer_len);
int unixsocket_client_recv(int sockfd, char *recv_buffer, int recv_buffer_len);
int unixsocket_client_disconnect(int sockfd);

#endif
