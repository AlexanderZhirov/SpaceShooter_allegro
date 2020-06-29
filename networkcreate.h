/* 
 * File:   network_create.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.12
 */

#ifndef client_networkcreate
#define client_networkcreate

enum networkcreate_buttons
{
    BUTTON_NETWORKCREATE_CREATE,
    BUTTON_NETWORKCREATE_OUT
};

enum networkcreate_field
{
    FIELD_NETWORKCREATE_NICKNAME,
    FIELD_NETWORKCREATE_GAMENAME
};

void networkcreate_handling(CLIENT_DATA* data);
void networkcreate_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void networkcreate_init_field(CLIENT_DATA* data, int key_field, int key_font, const char* description);
void networkcreate_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void networkcreate_push_button(CLIENT_DATA* data);
static void networkcreate_change_selected(CLIENT_DATA* data);
static bool networkcreate_check_field(CLIENT_DATA* data);

#endif

