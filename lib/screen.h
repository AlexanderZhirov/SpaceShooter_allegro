/* 
 * File:   screen.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messenger): @alexanderzhirov
 *
 * Created on 27 мая 2020 г., 17:17
 */

#ifndef client_screen
#define client_screen

#include <allegro5/allegro5.h>
#include <stdbool.h>

typedef struct cl_screen
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* buffer;
    int monitor_width;
    int monitor_height;
    int display_width;
    int display_height;
    int buffer_width;
    int buffer_height;
    int width; // main width (== buffer width)
    int height; // main height (== buffer height)
    float display_diagonal;
    float buffer_diagonal;
    bool own_diagonal; // use own diagonal (if own diagonal >)
    float scale_factor;
    float scale_factor_x;
    float scale_factor_y;
    int FPS;
    bool fullscreen;
    int pos_x; // display output buffer position x
    int pos_y; // display output buffer position y
} CLIENT_SCREEN;

typedef struct cl_adapter
{
    int width;
    int height;
} CLIENT_ADAPTER;

CLIENT_SCREEN* cl_create_screen(CLIENT_SCREEN* screen, float scale_factor, bool fullscreen, bool resolution, int w, int h, int FPS, int num_adapter);

static CLIENT_ADAPTER cl_get_info_adapter(int num_adapter);

void cl_free_screen(CLIENT_SCREEN* screen);
void cl_destroy_screen(CLIENT_SCREEN* screen);

void cl_pre_draw();

void cl_post_draw();

CLIENT_SCREEN cl_get_screen(CLIENT_SCREEN* screen);

#endif
