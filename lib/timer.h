/* 
 * File:   timer.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.02
 */

#ifndef client_timer
#define client_timer

#include <allegro5/allegro5.h>

typedef struct cl_timer
{
    ALLEGRO_TIMER* al_timer;
    float time;
} CLIENT_TIMER;

CLIENT_TIMER* cl_create_timer(CLIENT_TIMER* timer, int FPS);

void cl_free_timer(CLIENT_TIMER* timer);
void cl_destroy_timer(CLIENT_TIMER* timer);

#endif
