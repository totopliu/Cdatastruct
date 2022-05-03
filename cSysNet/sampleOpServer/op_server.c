#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum, int opds[], char operate);
int main(int argc, char *argv[])
{
    int sev_sock, clnt_sock;
    struct sockaddr_in sev_addr,clnt_addr;
    char optinfo[BUFF_SIZE];
    int result,optnum;

    sev_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sev_sock == -1)
        error_handling("socket error");
    
    memset(&sev_addr,0,sizeof(sev_sock));
    sev_addr.sin_family = PF_INET;
    sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sev_addr.sin_port = htons(atoi("9190"));

    if(-1 == bind(sev_sock,(struct sockaddr*)&sev_addr,sizeof(sev_addr)))
        error_handling("socket error");
    if(-1 == listen(sev_sock,5))
        error_handling("socket error");
    
    socklen_t clnt_sck_size = sizeof(clnt_addr);
    int recv_len,recv_cnt;
    for(int i=0;i<5;i++)
    {
        clnt_sock = accept(sev_sock,(struct sockaddr*)&clnt_addr,&clnt_sck_size);
        if(clnt_sock==-1)
            error_handling("accept error");
        else    
            printf("connect client %d \n",i+1);
        
        read(clnt_sock,&optnum,1);
        printf("optnum is %d",optnum);
        recv_len =0;
        while (recv_len<(optnum*OPSZ+1))
        {
            recv_cnt = read(clnt_sock,&optinfo[recv_len],BUFF_SIZE-1);
            recv_len += recv_cnt;
        }
        result = calculate(optnum,(int*)optinfo,optinfo[recv_len-1]);
    
        write(clnt_sock,(char*)&result,sizeof(result));
        close(clnt_sock);
    }
    close(sev_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    putc('\n', stderr);
    exit(1);
}

int calculate(int opnum, int opds[], char operate)
{
    int result =opds[0],i;
    switch (operate)
    {
    case '+':
        for(i=1;i<opnum;i++) result+=opds[i];
        break;
    case '-':
        for( i=1;i<opnum;i++) result-=opds[i];
        break;
    case '*':
        for( i=1;i<opnum;i++) result*=opds[i];
        break;
    default:
        break;
    }
    return result;
}
