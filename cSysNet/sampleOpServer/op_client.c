#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_handling(char* message);
int main(int argc,char* argv[])
{
    /*
    if(argc!=3)
    {
        printf("please use:%s ip port",argv[0]);
        exit(1);
    }
    */
    char* addr = "127.0.0.1";
    char* port = "9190";
    //socket creat
    int sock;
    struct sockaddr_in serv_sock;
    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1)
        error_handling("socket error");
    if(sock==-1)
        error_handling("socket error");

    memset(&serv_sock,0,sizeof(serv_sock));
    serv_sock.sin_family =PF_INET;
    serv_sock.sin_addr.s_addr = inet_addr(addr);
    serv_sock.sin_port = htons(atoi(port));
    //socket connect
    if(-1 == connect(sock,(struct sockaddr *)&serv_sock,sizeof(serv_sock)))
        error_handling("connect error");
    else 
        printf("connect ....");

    char opmsg[BUFF_SIZE];
    char opdebugger[BUFF_SIZE]={0};
    opdebugger[0]='i';
    int opcnt;
    fputs("operand cnt ",stdout);
    scanf("%d",&opcnt);
    opmsg[0] = (char)opcnt;
    for(int i=0;i<opcnt;i++)
    {
        printf("operand %d:",i+1);
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);

        printf("debugger %s \n",opmsg);
    }
    fgetc(stdin);
    fputs("operate is ",stdout);
    scanf("%c",&opmsg[opcnt*OPSZ+1]);
   
    //sock read/write
    int wcnt = write(sock,opmsg,opcnt*OPSZ+2);
    int result;
    read(sock,&result,RLT_SIZE);
    printf("operate result:%d \n",result);
    close(sock);
    return 0;
}
void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}