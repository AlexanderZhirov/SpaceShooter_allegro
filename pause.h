/* 
 * File:   pause.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.11
 */

#ifndef client_pause
#define client_pause

enum pause_buttons
{
    BUTTON_PAUSE_BACK,
    BUTTON_PAUSE_MENU
};

void pause_handling(CLIENT_DATA* data);
void pause_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void pause_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void pause_push_button(CLIENT_DATA* data);

#endif



