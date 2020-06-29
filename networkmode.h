/* 
 * File:   network.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.11
 */

#ifndef client_networkmode
#define client_networkmode

enum networkmode_buttons
{
    BUTTON_NETWORKMODE_CREATE,
    BUTTON_NETWORKMODE_JOIN,
    BUTTON_NETWORKMODE_OUT
};

void networkmode_handling(CLIENT_DATA* data);
void networkmode_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void networkmode_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void networkmode_push_button(CLIENT_DATA* data);

#endif



