/* 
 * File:   networklist.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.21
 */

#ifndef client_network_list
#define client_network_list

enum networkparty_buttons
{
    BUTTON_NETWORKLIST_OUT
};

void networklist_handling(CLIENT_DATA* data);
void networklist_draw(CLIENT_DATA* data);

void networklist_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);

void networklist_init_list(CLIENT_DATA* data, int key_font);
static void networklist_draw_list(CLIENT_DATA* data);

static void networklist_enet_receive(CLIENT_DATA* data);
static void networklist_push_button(CLIENT_DATA* data);

void networklist_change_selected(CLIENT_DATA* data);

#endif



