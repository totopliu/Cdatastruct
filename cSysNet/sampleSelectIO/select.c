#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUFF_SIZE 30

int main()
{
    char buff[BUFF_SIZE];
    //set fileno filescop timeout
    fd_set reads,temp;
    FD_ZERO(&reads);
    FD_SET(0,&reads);
    struct timeval timeout;
    while (1)
    {
        temp = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        int result = select(1,&temp,0,0,&timeout);
        if(result==-1)
        {
            puts("select error\n");
        }
        else if(result==0){
            puts("select timeout\n");
        }else{
            if(FD_ISSET(0,&temp))
            {
                int str_len = read(0,buff,BUFF_SIZE);
                buff[str_len] =0;
                printf("message is %s",buff);
            }
        }
    }
    
    return 0;
}

