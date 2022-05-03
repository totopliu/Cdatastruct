#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFF_SIZE 1024
void error_handling(char *message);
int main(int argc,char* argv[])
{
    struct sockaddr_in sev_addr;
    int sev_sock = socket(PF_INET,SOCK_STREAM,0);
    if(sev_sock==-1)
        error_handling("socket error");
    
    memset(&sev_addr,0,sizeof(sev_sock));
    sev_addr.sin_family = PF_INET;
    sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sev_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sev_sock,(struct sockaddr *)&sev_addr,sizeof(sev_addr))==-1)
        error_handling("bind error");
    
    if(listen(sev_sock,5)==-1)
        error_handling("listen error");
    
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    int str_len;
    char message[30];
    //int i=0;
    for(int i=0;i<5;i++){
        int clnt_sock = accept(sev_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_len);
        if(clnt_sock==-1)
            error_handling("accept error");
        else
            printf("connect client %d \n",i+1);
        
        while ( (str_len = read(clnt_sock,message,BUFF_SIZE))!=-1 )
        {
            write(clnt_sock,message,str_len);
        }
        close(clnt_sock);
    }
    close(sev_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    putc('\n',stderr);
    exit(1);
}