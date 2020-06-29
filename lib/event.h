/* 
 * File:   event.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.02
 */

#ifndef client_event
#define client_event

#include <allegro5/allegro5.h>
#include "timer.h"
#include "screen.h"

typedef struct cl_event
{
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT current;
} CLIENT_EVENT;

CLIENT_EVENT* cl_create_event(CLIENT_EVENT* event, CLIENT_TIMER* timer, CLIENT_SCREEN* screen);
void cl_free_event(CLIENT_EVENT* event);
void cl_destroy_event(CLIENT_EVENT* event);

#endif
