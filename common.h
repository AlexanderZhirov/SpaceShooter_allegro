/* 
 * File:   game.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.03
 */

#ifndef client_data
#define client_data

#include "lib/common.h"
#include "objects/objects.h"
#include "network/network.h"

enum bitmaps
{
    BG1,
    BG2,
    BG3,
    SHIP_R,
    SHIP_G,
    SHIP_Y,
    EXPLOSION,
    COMET
};

enum fonts
{
    FONT_SAC60,
    FONT_SAC80,
    FONT_PS2P30,
    FONT_PS2P40
};

enum samples
{
    SAMPLE_BOOM,
    SAMPLE_SHOT,
    SAMPLE_MENU,
    SAMPLE_GAME,
    SAMPLE_BUTTON,
    SAMPLE_ENTER
};

enum instance
{
    INSTANCE_MENU,
    INSTANCE_GAME
};

enum states
{
    MENU,
    SINGLE,
    NETWORKMODE,    
    NETWORKCREATE,
    NETWORKJOIN,
    NETWORKLIST,
    NETWORKPARTY,
    NETWORKGAME,
    NETWORKOUT,
    SETTINGS,
    AUTORS,
    PAUSE,
    GAMEOVER
};

enum keys
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    ESCAPE,
    SPACE
};

typedef struct cl_settings
{
    float effects_gain;
    float music_gain;
} CLIENT_SETTINGS;

typedef struct cl_data
{
    CLIENT_SCREEN screen;
    CLIENT_TIMER timer;
    CLIENT_EVENT event;
    CLIENT_MEDIA media;
    CLIENT_PAIRING pairing;
    CLIENT_OBJECTS objects;
    CLIENT_NETWORK network;
    CLIENT_ENET enet;
    CLIENT_SOUND sound;
    CLIENT_SETTINGS settings;
    bool keys[7];
    bool pause;
    bool done;
    bool render;
    int state;
} CLIENT_DATA;

/************************************************************
 * CREATE DATA PLAYER (MAIN OBJECT)
 ***********************************************************/
CLIENT_DATA* cl_create_data(CLIENT_DATA* data, CLIENT_PARAMETRS parametrs);
void cl_destroy_data(CLIENT_DATA* data);
/************************************************************
 * COMMON FUNCTION
 ***********************************************************/
void cl_init_interfaces(CLIENT_PAIRING* pairing);
void cl_load_media(CLIENT_MEDIA* media);
void cl_init_media(CLIENT_DATA* data);
void cl_change_state(CLIENT_DATA* data, int state);
/************************************************************
 * SAMPLE INSTANCE
 ***********************************************************/
static void cl_init_sample_instance(CLIENT_DATA* data, int key_instance, int key_sample);
static void cl_change_sample_instance(CLIENT_DATA* data, int state);
void cl_play_sound(CLIENT_DATA* data, int key_sample);
/************************************************************
 * BACKGROUND
 ***********************************************************/
static void cl_init_background(CLIENT_DATA* data, int key_state, int key_bitmap, float x, float y, float vel_x, float vel_y, int dir_x, int dir_y);
static void cl_copy_background(CLIENT_DATA* data, int dir_key_state, int src_key_state);
void cl_draw_background(CLIENT_DATA* data, int key_bitmap);
void cl_update_background(CLIENT_DATA* data, int key_bitmap);
/************************************************************
 * HEADER
 ***********************************************************/
static void cl_init_header(CLIENT_DATA* data, int key_state, int key_font, const char* text);
void cl_draw_header(CLIENT_DATA* data);
/************************************************************
 * BUTTON
 ***********************************************************/
void cl_update_button(CLIENT_DATA* data);
void cl_select_button(CLIENT_DATA* data);
void cl_draw_button(CLIENT_DATA* data);
/************************************************************
 * FIELD
 ***********************************************************/
void cl_draw_field(CLIENT_DATA* data);
void cl_update_field(CLIENT_DATA* data);
void cl_enter_field(CLIENT_DATA* data);
void cl_print_field(CLIENT_DATA* data);
/************************************************************
 * LIST
 ***********************************************************/
void cl_draw_list(CLIENT_DATA* data);
void cl_update_list(CLIENT_DATA* data);
/************************************************************
 * NETWORK
 ***********************************************************/
void cl_send_message_create(CLIENT_DATA* data);
void cl_send_message_join(CLIENT_DATA* data);

#endif
