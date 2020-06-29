#include "timer.h"
#include "message.h"

CLIENT_TIMER* cl_create_timer(CLIENT_TIMER* timer, int FPS)
{
    if(!timer)
    {
        timer = (CLIENT_TIMER*)malloc(sizeof(CLIENT_TIMER));
        show_message_error(timer, "Failed to allocate space for CLIENT_TIMER");
    }
    
    timer->al_timer = al_create_timer(1.0 / FPS);
    show_message_error(timer->al_timer, "Failed to create Allegro timer");
    
    return timer;
}

void cl_free_timer(CLIENT_TIMER* timer)
{
    cl_destroy_timer(timer);
    free(timer);
}

void cl_destroy_timer(CLIENT_TIMER* timer)
{
    al_destroy_timer(timer->al_timer);
}
