#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig == SIGALRM)
       puts("Time out");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig==SIGINT)
    {
        puts("CTRL+C press");
    }
}

int main()
{
    int i;
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);
    for(int i=0;i<3;i++)
    {
        puts("wait...");
        sleep(1000*10);
    }
    return 0;
}