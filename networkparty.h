/* 
 * File:   network_party.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.12
 */

#ifndef client_network_party
#define client_network_party

enum networklist_buttons
{
    BUTTON_NETWORKPARTY_START,
    BUTTON_NETWORKPARTY_READY,
    BUTTON_NETWORKPARTY_UNREADY,
    BUTTON_NETWORKPARTY_OUT
};

void networkparty_handling(CLIENT_DATA* data);
void networkparty_draw(CLIENT_DATA* data);

static void networkparty_enet_receive(CLIENT_DATA* data);
void networkparty_init_list(CLIENT_DATA* data, int key_font);

static void networkparty_draw_list(CLIENT_DATA* data);
void networkparty_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void networkparty_draw_button(CLIENT_DATA* data);
static void networkparty_push_button(CLIENT_DATA* data);
static void networkparty_change_selected(CLIENT_DATA* data);

static bool networkparty_check_users(CLIENT_DATA* data);

static void networkparty_send_exit(CLIENT_DATA* data);
static void networkparty_send_ready(CLIENT_DATA* data);
static void networkparty_send_kick(CLIENT_DATA* data, int user_id);
static void networkparty_send_start(CLIENT_DATA* data);

#endif



