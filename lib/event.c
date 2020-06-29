#include "event.h"
#include "message.h"
#include "screen.h"

CLIENT_EVENT* cl_create_event(CLIENT_EVENT* event, CLIENT_TIMER* timer, CLIENT_SCREEN* screen)
{
    if(!event)
    {
        event = (CLIENT_EVENT*)malloc(sizeof(CLIENT_EVENT));
        show_message_error(event, "Failed to allocate space for CLIENT_EVENT");
    }
    
    event->queue = al_create_event_queue();
    show_message_error(event->queue, "Failed to create Allegro event");
    
    al_register_event_source(event->queue, al_get_keyboard_event_source());
    al_register_event_source(event->queue, al_get_mouse_event_source());
    if(screen)
        al_register_event_source(event->queue, al_get_display_event_source(screen->display));
    if(timer)
        al_register_event_source(event->queue, al_get_timer_event_source(timer->al_timer));
    
    return event;
}

void cl_free_event(CLIENT_EVENT* event)
{
    cl_destroy_event(event);
    free(event);
};

void cl_destroy_event(CLIENT_EVENT* event)
{
    al_destroy_event_queue(event->queue);
}
