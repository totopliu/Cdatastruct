#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
//#include <sys/time.h>
#include <event.h>

void signal_cb(int fd,short event,void* argc)
{
    struct event_base *base = (struct event_base*)argc;
    struct timeval delay ={2,0};
    printf("caught an interrupt signal,clean 2 sencond..\n");
    event_base_loopexit(base,&delay);
}

void timeout_cb(int fd,short event,void* argc)
{
    printf("time out cb call\n");
}

int main()
{
    struct event_base* base = event_init();

    struct event* signal_event = evsignal_new(base,SIGINT,signal_cb,base);
    event_add(signal_event,NULL);

    struct timeval tv= {1,0};
    struct event* timeout_event = evtimer_new(base,timeout_cb,NULL);
    event_add(timeout_event,&tv);
    
    event_base_dispatch(base);

    event_free(timeout_event);
    event_free(signal_event);
    event_base_free(base);

    return 0;
}