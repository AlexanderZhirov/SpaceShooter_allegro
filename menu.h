/* 
 * File:   menu.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.03
 */

#ifndef client_menu
#define client_menu

enum menu_buttons
{
    BUTTON_MENU_SINGLE, // single play
    BUTTON_MENU_NETWORK, // network play
    BUTTON_MENU_SETTINGS, // settings
    BUTTON_MENU_AUTORS, // autors
    BUTTON_MENU_OUT // output
};

void menu_handling(CLIENT_DATA* data);
void menu_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void menu_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void menu_push_button(CLIENT_DATA* data);

#endif



