/* 
 * File:   networkout.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.27
 */

#ifndef client_networkout
#define client_networkout

enum networkout_buttons
{
    BUTTON_NETWORKOUT_BACK,
    BUTTON_NETWORKOUT_MENU
};

void networkout_handling(CLIENT_DATA* data);
void networkout_draw(CLIENT_DATA* data);

void networkout_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void networkout_push_button(CLIENT_DATA* data);

#endif



