/* 
 * File:   interface.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.04
 */

#ifndef client_interface
#define client_interface

#include <allegro5/allegro_font.h>
#include "media.h"

enum cl_selceted
{
    SELECTED_NONE,
    SELECTED_BUTTON,
    SELECTED_FIELD,
    SELECTED_LIST
};

typedef struct cl_background_page
{
    CLIENT_BITMAP* bitmap;
    float x;
    float y;
    float vel_x;
    float vel_y;
    int dir_x;
    int dir_y;
} CLIENT_BACKGROUND_PAGE;

typedef struct cl_button
{
    int b_sx;
    int b_sy;
    int b_dx;
    int b_dy;
    char text[100];
    int t_size;
    ALLEGRO_FONT* al_font;
    int t_x;
    int t_y;
    bool selected;
    bool active;
} CLIENT_BUTTON;

typedef struct cl_field
{
    ALLEGRO_FONT* al_font;
    char description[100];
    char field_text[40];
    int char_size;
    int char_number;
    int d_x; // description x position
    int d_y; // description y position
    int f_sx; // field sx position
    int f_sy; // field sy position
    int f_dx; // field dx position
    int f_dy; // field dy position
    int ft_x; // field text x position
    int ft_y; // field text y position
    bool selected;
    bool enter;
} CLIENT_FIELD;

typedef struct cl_header
{
    int x;
    int y;
    char text[100];
    int size; // text size
    ALLEGRO_FONT* al_font;
} CLIENT_HEADER;

typedef struct cl_list_item
{
    int sx_item;
    int sy_item;
    int dx_item;
    int dy_item;
    int x_h;
    int y_h;
    int x_status;
    int y_status;
    int r_status;
    bool selected;
    bool active;
} CLIENT_LIST_ITEM;

typedef struct cl_list
{
    int sx;
    int sy;
    int dx;
    int dy;
    CLIENT_LIST_ITEM item[3];
    ALLEGRO_FONT* al_font;
} CLIENT_LIST;

typedef struct cl_interface
{
    CLIENT_HEADER header;
    CLIENT_BACKGROUND_PAGE** background;
    CLIENT_BUTTON** button;
    CLIENT_FIELD** field;
    CLIENT_LIST list;
    int background_size;
    int button_size;
    int field_size;
    int selected; // selceted current control (none/button/field)
} CLIENT_INTERFACE;

typedef struct cl_pairing
{
    CLIENT_INTERFACE** interface;
    int interface_size;
} CLIENT_PAIRING;

CLIENT_PAIRING* cl_create_pairing(CLIENT_PAIRING* pairing, int interface_size);
void cl_free_pairing(CLIENT_PAIRING* pairing);
void cl_destroy_pairing(CLIENT_PAIRING* pairing);
CLIENT_INTERFACE* cl_create_interface(int background_size, int button_size, int field_size);
static void cl_destroy_interface(CLIENT_INTERFACE* interface);

static CLIENT_BACKGROUND_PAGE** cl_create_background_pages(int size);
static CLIENT_BUTTON** cl_create_buttons(int size);
static CLIENT_FIELD** cl_create_fields(int size);

void cl_change_selected(CLIENT_INTERFACE* interface);

void cl_add_interface_header(CLIENT_HEADER* header, ALLEGRO_FONT* font, int x, int y, const char* text);
void cl_add_interface_background(CLIENT_BACKGROUND_PAGE* background, CLIENT_BITMAP* bitmap, int dir_x, int dir_y, int vel_x, int vel_y, int x, int y);
void cl_add_interface_button(CLIENT_BUTTON* button, ALLEGRO_FONT* font, const char* text, int t_x, int t_y, int b_sx, int b_sy, int b_dx, int b_dy);
void cl_add_interface_field(CLIENT_FIELD* field, ALLEGRO_FONT* font, int font_height, const char* description, int d_x, int d_y, int f_sx, int f_sy, int f_dx, int f_dy);

// ITEMS
void cl_add_list_item(CLIENT_LIST_ITEM* item, int sx_item, int sy_item, int dx_item, int dy_item, int x_h, int y_h, int x_status, int y_status, int r_status);

#endif
