/* 
 * File:   network_join.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.12
 */

#ifndef client_network_join
#define client_network_join

enum networkjoin_buttons
{
    BUTTON_NETWORKJOIN_CREATE,
    BUTTON_NETWORKJOIN_OUT
};

enum networkjoin_field
{
    FIELD_NETWORKJOIN_NICKNAME
};

void networkjoin_handling(CLIENT_DATA* data);
void networkjoin_draw(CLIENT_DATA* data);

void networkjoin_init_field(CLIENT_DATA* data, int key_field, int key_font, const char* description);
void networkjoin_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);

static void networkjoin_push_button(CLIENT_DATA* data);
static void networkjoin_change_selected(CLIENT_DATA* data);
static bool networkjoin_check_field(CLIENT_DATA* data);

#endif



