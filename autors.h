/* 
 * File:   autors.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.07
 */

#ifndef client_autors
#define client_autors

enum autors_buttons
{
    BUTTON_AUTORS_OUT // output
};

void autors_handling(CLIENT_DATA* data);
void autors_draw(CLIENT_DATA* data);
/************************************************************
 * PROCESSING
 ***********************************************************/
void autors_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text);
static void autors_push_button(CLIENT_DATA* data);

#endif



