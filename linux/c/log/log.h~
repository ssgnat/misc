/*
 * LOG UTILITY , ONLY LOG TO STDOUT
 * MACRO SWITCH - DEBUG
 * author: tangss
 * date  : 31/09/2019
 */
#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#ifndef DEBUG

    #ifndef LOGI
    #define LOGI(fmt, args...)              \
        do {                                \
            printf("[INF] %s %s %d " fmt "\n", __FILE__, __FUNCTION__, __LINE__,\
                ##args);                    \
        } while (0)
    #endif

    #ifndef LOGD
    #define LOGD(fmt, args...)              \
        do {                                \
            printf("[DBG] %s %s %d " fmt "\n", __FILE__, __FUNCTION__, __LINE__,\
                ##args);                    \
        } while (0)
    #endif

    #ifndef LOGE
    #define LOGE(fmt, args...)              \
        do {                                \
            printf("[ERR] %s %s %d " fmt "\n", __FILE__, __FUNCTION__, __LINE__,\
                ##args);                    \
        } while (0)
    #endif

#else

    #ifndef LOGI
    #define LOGI
    #endif

    #ifndef LOGD
    #define LOGD
    #endif

    #ifndef LOGE
    #define LOGE
    #endif

#endif


#endif //_LOG_H_
