/* 
 * File:   gameover.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.11
 */

#ifndef client_gameover
#define client_gameover

enum gameover_buttons
{
    BUTTON_GAMEOVER_OUT
};

void gameover_handling(CLIENT_DATA* data);
void gameover_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void gameover_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void gameover_push_button(CLIENT_DATA* data);
static void gameover_draw_statistic(CLIENT_DATA* data);

#endif



