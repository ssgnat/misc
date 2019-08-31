/*************************
 * autor:       tangss
 * date:        19/08/2018
 * description: check legal info of input
 ************************/
#ifndef _PUBLIC_CHECK_H_
#define _PUBLIC_CHECK_H_

#ifndef CHECK_NULL_OF_POINTER
#define CHECK_NULL_OF_POINTER(POINTER, ERROR)   \
{                                               \
    if(NULL == POINTER)                         \
        return ERROR;                           \
}
#endif

#ifndef CHECK_EMPTY_OF_STRING
#define CHECK_EMPTY_OF_STRING(POINTER, ERROR)   \
{                                               \
    if(NULL == POINTER)                         \
        return ERROR;                           \
    if(*POINTER == 0)                           \
        return ERROR;                           \
}
#endif

#endif
