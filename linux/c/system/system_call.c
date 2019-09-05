#include <stdlib.h>
#include <string.h>
#include "system_call.h"
#include "sanity/check.h"

int
exec(const char *command, char *with_result, int *with_result_len)
{

    char *cmd = NULL;
    int   len = 0;
    int   max_result = 0;
    FILE *fp = NULL;

    char  read_buf[MAX_RESULT_BUFFER]={0};

    CHECK_EMPTY_OF_STRING(command, -1);

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

int
exec_noredirect(const char *command, char *with_result, int *with_result_len)
{

    char *cmd = NULL;
    int   len = 0;
    int   max_result = 0;
    FILE *fp = NULL;

    char  read_buf[MAX_RESULT_BUFFER]={0};

    CHECK_EMPTY_OF_STRING(command, -1);

    max_result = *with_result_len;

    len = strlen(command) + 20;
    cmd = (char*)malloc(len);
    memset(cmd, 0, len);
    memmove(cmd, command, strlen(command));

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

    *with_result_len = len;

    pclose(fp);
    free(cmd);

    return 0;
}
