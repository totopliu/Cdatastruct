#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUFF_SIZE 100

void error_handling(char* message);
int main(int argc,char* argv[])
{
  if(argc!=2)
  {
      puts("arg error");
      exit(1);
  }
  //socket
  int srv_sock,clnt_sock;
  struct sockaddr_in srv_addr,clnt_addr;
  socklen_t clnt_addr_zs;
  //init svr_sock
  memset(&srv_addr,0,sizeof(srv_addr));
  srv_addr.sin_family = PF_INET;
  srv_addr.sin_addr.s_addr =htonl(INADDR_ANY);
  srv_addr.sin_port =htons(atoi(argv[1]));
  srv_sock = socket(PF_INET,SOCK_STREAM,0);
  if(srv_sock==-1)
    error_handling("socket() error");
  if(-1== bind(srv_sock,(struct sockaddr*)&srv_addr,sizeof(srv_addr)))
      error_handling("bind() error");
  if(listen(srv_sock,5)==-1)
      error_handling("listen() error");
  
  //select init
  fd_set reads,cpy_read;
  struct timeval timeout;
  int fdmax,fdnum;
  FD_ZERO(&reads);
  FD_SET(srv_sock,&reads);
  fdmax = srv_sock;

  //msg
  char buff[BUFF_SIZE];
  int str_len;
  while (1)
  {
     //do accept
     cpy_read = reads;
     timeout.tv_sec = 5;
     timeout.tv_usec = 5000;
     fdnum = select(fdmax+1,&cpy_read,0,0,&timeout);
     if(fdnum==-1) break;
     if(fdnum==0) continue;

     //select change
     for(int i=0;i<fdmax+1;i++)
     {
         if(FD_ISSET(i,&cpy_read))
         {
            if(i==srv_sock)
            {
                clnt_addr_zs = sizeof(clnt_addr);
                clnt_sock = accept(srv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_zs);
                FD_SET(clnt_sock,&reads);
                if(fdmax<clnt_sock)
                   fdmax = clnt_sock;
                printf("connect client %d \n",clnt_sock);
            }
            else
            {
              
                //read
                str_len=read(i,buff,BUFF_SIZE);
                if(str_len==0)
                {
                    FD_CLR(i,&reads);
                    close(i);
                    printf("close client %d \n",clnt_sock);
                }else{
                    write(i,buff,str_len);
                }
            }
         }
     }

  }
  close(srv_sock);

  return 0;
}

void error_handling(char* message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}