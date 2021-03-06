#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig==SIGALRM)
        puts("time out");
    alarm(2);
}

int main()
{
    struct sigaction act;
    //act.__sigaction_handler = timeout;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags =0;
    sigaction(SIGALRM,&act,0);

    alarm(2);
    for(int i=0;i<3;i++)
    {
        puts("wait...");
        sleep(1000*3);
    }
    return 0;
}