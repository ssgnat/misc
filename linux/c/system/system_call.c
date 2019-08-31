#include "system_call.h"
#include "public/check.h"
#include <stdlib.h>

int
exec(const char *command, char *with_result, int *with_result_len)
{

    char *cmd=NULL;
    int   len = 0;
    FILE *fp = NULL;
    char  read_buf[1024]={0};

    CHECK_BUF(with_result);
    CHECK_BUF(command);

    len = sizeof(char) * (command->len + 20);
    cmd = (char*)malloc(len);
    memset(cmd, 0, len);
    memmove(cmd, command->buf, command->len);

    strcat(cmd," 1>&1 2>&1");

    fp = popen(cmd, "r");

    if( fp <=0 )
    {
        free(cmd);
        return HZ_ERROR_APP_FILE_CANNT_OPEN;
    }

    len = 0;
    while(fgets(read_buf, sizeof(read_buf), fp) > 0) 
    {
      len += strlen(read_buf);
      if(len >= with_result->len-1)
      {
          continue;
      }

      strcat(with_result->buf, read_buf);
    }

    pclose(fp);
    free(cmd);

    return HZ_OK;
}

INT hz_exec_noredirect(const T_BUF *command, T_BUF *with_result)
{

    char *cmd=NULL;
    int  len = 0;
    FILE *fp = NULL;
    char read_buf[100]={0};

    CHECK_BUF(with_result);
    CHECK_BUF(command);

    len = sizeof(char) * (command->len + 20);
    cmd = (char*)malloc(len);
    memset(cmd, 0, len);
    memmove(cmd, command->buf, command->len);

    fp = popen(cmd, "r");

    if( fp <=0 )
    {
        free(cmd);
        return HZ_ERROR_APP_FILE_CANNT_OPEN;
    }

    len = 0;
    while(fgets(read_buf, sizeof(read_buf), fp) > 0) 
    {
      len += strlen(read_buf);
      if(len >= with_result->len)
      {
          continue;
      }

      strcat(with_result->buf, read_buf);
    }

    pclose(fp);
    free(cmd);

    return HZ_OK;
}
