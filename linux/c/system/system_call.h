/*****************************************************
 * utility to run script or command
 * autor:       tangss
 * date :       19/08/2018
 *****************************************************/
#ifndef _SYSTEM_CALL_H_
#define _SYSTEM_CALL_H_

#include <stdio.h>

#define MAX_RESULT_BUFFER 10240
#ifdef __cplusplus
extern "C"{
#endif
/*
 * execute an command , return the output of (command stdout and stderr)
 * @with_result: run command with result
 * @with_result_len: in/out , in: max len of with result, out: real len of with result
 * return: 0:run ok, other else failed ,see error/error.h
 */
int exec(const char *command, char *with_result, int *with_result_len);

/*
 * execute an command , return the output of command stdout
 *
 */
int exec_noredirect(const char *command, char *with_result,
        int *with_result_len);


#ifdef __cplusplus
}
#endif
#endif
