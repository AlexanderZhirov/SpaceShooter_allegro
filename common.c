#include "common.h"
#include "menu.h"
#include "single.h"
#include "networkmode.h"
#include "networkcreate.h"
#include "networkjoin.h"
#include "networklist.h"
#include "networkparty.h"
#include "networkgame.h"
#include "networkout.h"
#include "autors.h"
#include "pause.h"
#include "gameover.h"

#include <allegro5/allegro_primitives.h>
#include <stdio.h>

void cl_init_interfaces(CLIENT_PAIRING* pairing)
{
    pairing->interface[MENU] = cl_create_interface(2, 5, 0);
    pairing->interface[SINGLE] = cl_create_interface(3, 0, 0);
    pairing->interface[NETWORKMODE] = cl_create_interface(0, 3, 0);
    pairing->interface[NETWORKCREATE] = cl_create_interface(0, 2, 2);
    pairing->interface[NETWORKJOIN] = cl_create_interface(0, 2, 1);
    pairing->interface[NETWORKLIST] = cl_create_interface(0, 1, 0);
    pairing->interface[NETWORKPARTY] = cl_create_interface(0, 4, 0);
    pairing->interface[NETWORKGAME] = cl_create_interface(3, 0, 0);
    pairing->interface[NETWORKOUT] = cl_create_interface(0, 2, 0);
    pairing->interface[SETTINGS] = cl_create_interface(0, 0, 0);
    pairing->interface[AUTORS] = cl_create_interface(0, 1, 0); // 0 background size (background copies)
    pairing->interface[PAUSE] = cl_create_interface(0, 2, 0); // 0 background size (background copies)
    pairing->interface[GAMEOVER] = cl_create_interface(0, 1, 0); // 0 background size (background copies)
}

void cl_load_media(CLIENT_MEDIA* media)
{
    cl_load_bitmap(media, BG1, "data/bitmaps/starBG.png");
    cl_load_bitmap(media, BG2, "data/bitmaps/starFG.png");
    cl_load_bitmap(media, BG3, "data/bitmaps/starMG.png");
    cl_load_bitmap(media, SHIP_R, "data/bitmaps/ship_red.png");
    al_convert_mask_to_alpha(media->bitmaps[SHIP_R]->al_bitmap, al_map_rgb(255, 0, 255));
    cl_load_bitmap(media, SHIP_G, "data/bitmaps/ship_green.png");
    al_convert_mask_to_alpha(media->bitmaps[SHIP_G]->al_bitmap, al_map_rgb(255, 0, 255));
    cl_load_bitmap(media, SHIP_Y, "data/bitmaps/ship_yellow.png");
    al_convert_mask_to_alpha(media->bitmaps[SHIP_Y]->al_bitmap, al_map_rgb(255, 0, 255));
    cl_load_bitmap(media, COMET, "data/bitmaps/comet.png");
    cl_load_bitmap(media, EXPLOSION, "data/bitmaps/explosion.png");
    cl_load_font(media, FONT_SAC60, "data/fonts/space_age_cyrillic.ttf", 60);
    cl_load_font(media, FONT_SAC80, "data/fonts/space_age_cyrillic.ttf", 80);
    cl_load_font(media, FONT_PS2P30, "data/fonts/Press_Start_2P.ttf", 30);
    cl_load_font(media, FONT_PS2P40, "data/fonts/Press_Start_2P.ttf", 40);
    cl_load_sample(media, SAMPLE_BOOM, "data/samples/boom.ogg");
    cl_load_sample(media, SAMPLE_SHOT, "data/samples/shot.ogg");
    cl_load_sample(media, SAMPLE_MENU, "data/samples/menu.ogg");
    cl_load_sample(media, SAMPLE_GAME, "data/samples/game.ogg");
    cl_load_sample(media, SAMPLE_BUTTON, "data/samples/button.ogg");
    cl_load_sample(media, SAMPLE_ENTER, "data/samples/enter.ogg");
}

void cl_init_media(CLIENT_DATA* data)
{
    cl_init_sample_instance(data, INSTANCE_MENU, SAMPLE_MENU);
    cl_init_sample_instance(data, INSTANCE_GAME, SAMPLE_GAME);
    /************************************************************
    * MENU
    ***********************************************************/
    cl_init_background(data, MENU, BG1, 0, 0, 1, 0, -1, 1);
    cl_init_background(data, MENU, BG2, 0, 0, 5, 0, -1, 1);
    cl_init_header(data, MENU, FONT_SAC80, "Космический шутер");
    menu_init_button(data, BUTTON_MENU_SINGLE, FONT_SAC60, "Одиночная игра");
    menu_init_button(data, BUTTON_MENU_NETWORK, FONT_SAC60, "Сетевая игра");
    menu_init_button(data, BUTTON_MENU_SETTINGS, FONT_SAC60, "Настройки");
    menu_init_button(data, BUTTON_MENU_AUTORS, FONT_SAC60, "Авторы");
    menu_init_button(data, BUTTON_MENU_OUT, FONT_SAC60, "Выход");
    /************************************************************
    * NETWORK
    ***********************************************************/
    cl_copy_background(data, NETWORKMODE, MENU);
    cl_init_header(data, NETWORKMODE, FONT_SAC80, "Сетевая игра");
    networkmode_init_button(data, BUTTON_NETWORKMODE_CREATE, FONT_SAC60, "Создать");
    networkmode_init_button(data, BUTTON_NETWORKMODE_JOIN, FONT_SAC60, "Присоединиться");
    networkmode_init_button(data, BUTTON_NETWORKMODE_OUT, FONT_SAC60, "Назад в меню");
    /************************************************************
    * NETWORK CREATE
    ***********************************************************/
    cl_copy_background(data, NETWORKCREATE, MENU);
    cl_init_header(data, NETWORKCREATE, FONT_SAC80, "Создание сетевой игры");
    networkcreate_init_field(data, FIELD_NETWORKCREATE_NICKNAME, FONT_PS2P40, "Никнейм:");
    networkcreate_init_field(data, FIELD_NETWORKCREATE_GAMENAME, FONT_PS2P40, "Название игры:");
    networkcreate_init_button(data, BUTTON_NETWORKCREATE_CREATE, FONT_SAC60, "Создать игру");
    networkcreate_init_button(data, BUTTON_NETWORKCREATE_OUT, FONT_SAC60, "Назад");
    /************************************************************
    * NETWORK JOIN
    ***********************************************************/
    cl_copy_background(data, NETWORKJOIN, MENU);
    cl_init_header(data, NETWORKJOIN, FONT_SAC80, "Присоединиться к игре");
    networkjoin_init_field(data, FIELD_NETWORKJOIN_NICKNAME, FONT_PS2P40, "Никнейм:");
    networkjoin_init_button(data, BUTTON_NETWORKJOIN_CREATE, FONT_SAC60, "Найти игру");
    networkjoin_init_button(data, BUTTON_NETWORKJOIN_OUT, FONT_SAC60, "Назад");
    /************************************************************
    * NETWORK LIST
    ***********************************************************/
    cl_copy_background(data, NETWORKLIST, MENU);
    cl_init_header(data, NETWORKLIST, FONT_SAC80, "Список серверов");
    networklist_init_button(data, BUTTON_NETWORKLIST_OUT, FONT_SAC60, "Назад");
    networklist_init_list(data, FONT_PS2P40);
    /************************************************************
    * AUTORS
    ***********************************************************/
    cl_copy_background(data, AUTORS, MENU);
    cl_init_header(data, AUTORS, FONT_SAC80, "Авторы");
    autors_init_button(data, BUTTON_AUTORS_OUT, FONT_SAC60, "Назад в меню");
    /************************************************************
    * NETWORK PARTY
    ***********************************************************/
    cl_copy_background(data, NETWORKPARTY, MENU);
    cl_init_header(data, NETWORKPARTY, FONT_SAC80, "Новая игра");
    networkparty_init_button(data, BUTTON_NETWORKPARTY_START, FONT_SAC60, "Начать");
    networkparty_init_button(data, BUTTON_NETWORKPARTY_READY, FONT_SAC60, "Готов");
    networkparty_init_button(data, BUTTON_NETWORKPARTY_UNREADY, FONT_SAC60, "Не готов");
    networkparty_init_button(data, BUTTON_NETWORKPARTY_OUT, FONT_SAC60, "Назад");
    networkparty_init_list(data, FONT_PS2P40);
    /************************************************************
    * NETWORK OUT
    ***********************************************************/
    cl_copy_background(data, NETWORKOUT, NETWORKGAME);
    cl_init_header(data, NETWORKOUT, FONT_SAC80, "Режим сетевой игры");
    networkout_init_button(data, BUTTON_NETWORKOUT_BACK, FONT_SAC60, "Продолжить");
    networkout_init_button(data, BUTTON_NETWORKOUT_MENU, FONT_SAC60, "Выйти в меню");
    /************************************************************
    * PAUSE
    ***********************************************************/
    cl_copy_background(data, PAUSE, MENU);
    cl_init_header(data, PAUSE, FONT_SAC80, "Пауза");
    pause_init_button(data, BUTTON_PAUSE_BACK, FONT_SAC60, "Продолжить");
    pause_init_button(data, BUTTON_PAUSE_MENU, FONT_SAC60, "Выйти в меню");
    /************************************************************
    * GAMEOVER
    ***********************************************************/
    cl_copy_background(data, GAMEOVER, MENU);
    cl_init_header(data, GAMEOVER, FONT_SAC80, "Конец игры");
    gameover_init_button(data, BUTTON_GAMEOVER_OUT, FONT_SAC60, "Выйти в меню");
}

void cl_change_state(CLIENT_DATA* data, int state)
{
    if(data->state == MENU && state == SINGLE)
    {
        /************************************************************
        * CREATE GAME OBJECTS
        ***********************************************************/
        cl_init_background(data, SINGLE, BG1, 0, 0, 1, 0, -1, 1);
        cl_init_background(data, SINGLE, BG2, 0, 0, 5, 0, -1, 1);
        cl_init_background(data, SINGLE, BG3, 0, 0, 3, 0, -1, 1);
        
        cl_init_objects(data);
    }
    else if((data->state == PAUSE || data->state == GAMEOVER) && state == MENU)
        /************************************************************
        * DESTROY GAME OBJECTS
        ***********************************************************/
        cl_destroy_objects(&data->objects);
    else if(data->state == NETWORKCREATE && state == NETWORKPARTY)
    {
        cl_create_enet(&data->enet);
        if(data->enet.connect)
            cl_send_message_create(data);
        else
            state = NETWORKCREATE;
    }
    else if(data->state == NETWORKJOIN && state == NETWORKLIST)
    {
        cl_create_enet(&data->enet);
        if(data->enet.connect)
            cl_send_message_join(data);
        else
            state = NETWORKJOIN;
    }
    else if((data->state == NETWORKPARTY && state == NETWORKMODE) ||
            (data->state == NETWORKLIST && state == NETWORKMODE))
    {
        cl_disconnect_enet(&data->enet);
    }
    else if(data->state == NETWORKOUT && state == NETWORKMODE)
    {
        cl_disconnect_enet(&data->enet);
        cl_destroy_objects(&data->objects);
    }
    else if(data->state == NETWORKPARTY && state == NETWORKGAME)
    {
        /************************************************************
        * CREATE GAME OBJECTS
        ***********************************************************/
        cl_init_background(data, NETWORKGAME, BG1, 0, 0, 1, 0, -1, 1);
        cl_init_background(data, NETWORKGAME, BG2, 0, 0, 5, 0, -1, 1);
        cl_init_background(data, NETWORKGAME, BG3, 0, 0, 3, 0, -1, 1);
        
        networkgame_create_objects(data);
    }
    
    
    data->state = state;
    
    cl_change_sample_instance(data, state);
}

/************************************************************
 * SAMPLE INSTANCE
 ***********************************************************/

static void cl_init_sample_instance(CLIENT_DATA* data, int key_instance, int key_sample)
{
    cl_add_instance(
            data->sound.instance[key_instance],
            data->media.samples[key_sample]->al_sapmle,
            ALLEGRO_PLAYMODE_LOOP,
            data->settings.music_gain);
}

static void cl_change_sample_instance(CLIENT_DATA* data, int state)
{
    switch(state)
    {
        case MENU:
        case NETWORKMODE:
        case NETWORKCREATE:
        case NETWORKJOIN:
        case NETWORKLIST:
        case NETWORKPARTY:
        case SETTINGS:
        case AUTORS:
            if(data->sound.current_instance != INSTANCE_MENU)
            {
                al_stop_sample_instance(data->sound.instance[INSTANCE_GAME]->al_instance);
                al_play_sample_instance(data->sound.instance[INSTANCE_MENU]->al_instance);
            }
            break;
        case SINGLE:
        case NETWORKGAME:
        case NETWORKOUT:
        case PAUSE:
        case GAMEOVER:
            if(data->sound.current_instance != INSTANCE_GAME)
            {
                al_stop_sample_instance(data->sound.instance[INSTANCE_MENU]->al_instance);
                al_play_sample_instance(data->sound.instance[INSTANCE_GAME]->al_instance);
            }
            break;
    }
}

void cl_play_sound(CLIENT_DATA* data, int key_sample)
{
    al_play_sample(data->media.samples[key_sample]->al_sapmle, data->settings.effects_gain, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}

/************************************************************
 * BACKGROUND
 ***********************************************************/

static void cl_init_background(CLIENT_DATA* data, int key_state, int key_bitmap, float x, float y, float vel_x, float vel_y, int dir_x, int dir_y)
{
    if(data->pairing.interface[key_state]->background_size > key_bitmap)
        cl_add_interface_background(
                data->pairing.interface[key_state]->background[key_bitmap],
                data->media.bitmaps[key_bitmap],
                dir_x, dir_y, vel_x, vel_y, x, y);
}

static void cl_copy_background(CLIENT_DATA* data, int dir_key_state, int src_key_state)
{
    data->pairing.interface[dir_key_state]->background = data->pairing.interface[src_key_state]->background;
}

void cl_draw_background(CLIENT_DATA* data, int key_bitmap)
{
    CLIENT_BACKGROUND_PAGE* bg = data->pairing.interface[data->state]->background[key_bitmap];
    
    al_draw_bitmap(bg->bitmap->al_bitmap, bg->x, bg->y, 0);
    al_draw_bitmap(bg->bitmap->al_bitmap, bg->x + bg->bitmap->width, bg->y, 0);
    
    if(bg->x + bg->bitmap->width + bg->bitmap->width < data->screen.width)
        al_draw_bitmap(bg->bitmap->al_bitmap, bg->x + bg->bitmap->width + bg->bitmap->width, bg->y, 0);
}

void cl_update_background(CLIENT_DATA* data, int key_bitmap)
{
    CLIENT_BACKGROUND_PAGE* bg = data->pairing.interface[data->state]->background[key_bitmap];
    
    bg->x += bg->vel_x * bg->dir_x;
    if(bg->x + bg->bitmap->width < 0)
        bg->x = 0;
}

/************************************************************
 * HEADER
 ***********************************************************/

static void cl_init_header(CLIENT_DATA* data, int key_state, int key_font, const char* text)
{
    int block_size = data->screen.height / 8;
    
    cl_add_interface_header(
            &data->pairing.interface[key_state]->header,
            data->media.fonts[key_font]->al_font,
            data->screen.width / 2,
            block_size - data->media.fonts[key_font]->size / 2,
            text);
}

void cl_draw_header(CLIENT_DATA* data)
{
    CLIENT_HEADER header = data->pairing.interface[data->state]->header;
    
    al_draw_text(header.al_font, al_map_rgb(255, 255, 255), header.x, header.y, ALLEGRO_ALIGN_CENTRE, header.text);
}

/************************************************************
 * BUTTON
 ***********************************************************/
// use with mouse event
void cl_update_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    int mx, my;

    if(data->screen.fullscreen)
    {
        mx = data->event.current.mouse.x / data->screen.scale_factor_x - data->screen.pos_x;
        my = data->event.current.mouse.y / data->screen.scale_factor_y - data->screen.pos_y;
    }
    else
    {
        mx = data->event.current.mouse.x;
        my = data->event.current.mouse.y;
    }

    for(int i = 0; i < interface->button_size; i++)
    {
        CLIENT_BUTTON* btn = interface->button[i];
        
        if(!btn->active) continue;

        if(btn->b_sx < mx && btn->b_dx > mx && btn->b_sy < my && btn->b_dy > my)
        {
            if(!btn->selected)
                cl_play_sound(data, SAMPLE_BUTTON);
            
            btn->selected = true;
            interface->selected = SELECTED_BUTTON;
        }
        else
            btn->selected = false;
    }
}
// use with key
void cl_select_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    bool is_selected = false;
    
    if(interface->selected == SELECTED_BUTTON)
    {
        int count_active_button = 0;
        
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->active)
                count_active_button++;
        
        if(count_active_button)
        {
            CLIENT_BUTTON* button[count_active_button];
            int iterator = 0;
            
            for(int i = 0; i < interface->button_size; i++)
                if(interface->button[i]->active)
                    button[iterator++] = interface->button[i];
            
            for(int i = 0; i < count_active_button; i++)
                if(button[i]->selected)
                {
                    if(data->keys[UP] && !data->keys[DOWN])
                    {
                        button[i]->selected = false;

                        if(i != 0)
                            button[i - 1]->selected = true;
                        else
                            button[count_active_button - 1]->selected = true;
                    }
                    else if(data->keys[DOWN] && !data->keys[UP])
                    {
                        button[i]->selected = false;

                        if(i == count_active_button - 1)
                            button[0]->selected = true;
                        else
                            button[i + 1]->selected = true;
                    }

                    is_selected = true;            
                    break;
                }
            
            if(!is_selected)
                if(data->keys[UP] && !data->keys[DOWN])
                    button[count_active_button - 1]->selected = true;
                else if(data->keys[DOWN] && !data->keys[UP])
                    button[0]->selected = true;
                
            cl_play_sound(data, SAMPLE_BUTTON);
        }
    }
    else if(interface->selected == SELECTED_FIELD)
    {
        for(int i = 0; i < interface->field_size; i++)
            if(interface->field[i]->selected)
            {
                interface->field[i]->enter = false;
                
                if(data->keys[UP] && !data->keys[DOWN])
                {
                    interface->field[i]->selected = false;

                    if(i != 0)
                        interface->field[i - 1]->selected = true;
                    else
                        interface->field[interface->field_size - 1]->selected = true;
                }
                else if(data->keys[DOWN] && !data->keys[UP])
                {
                    interface->field[i]->selected = false;

                    if(i == interface->field_size - 1)
                        interface->field[0]->selected = true;
                    else
                        interface->field[i + 1]->selected = true;
                }

                is_selected = true;            
                break;
            }
        
        if(!is_selected)
            if(data->keys[UP] && !data->keys[DOWN])
                interface->field[interface->field_size - 1]->selected = true;
            else if(data->keys[DOWN] && !data->keys[UP])
                interface->field[0]->selected = true;
            
        cl_play_sound(data, SAMPLE_BUTTON);
    }
    else if(interface->selected == SELECTED_LIST)
    {
        int count_active_item = 0;
        
        for(int i = 0; i < 3; i++)
            if(interface->list.item[i].active)
                count_active_item++;
        
        if(count_active_item)
        {
            CLIENT_LIST_ITEM* item[count_active_item];
            int iterator = 0;
            
            for(int i = 0; i < 3; i++)
                if(interface->list.item[i].active)
                    item[iterator++] = &interface->list.item[i];
            
            for(int i = 0; i < count_active_item; i++)
                if(item[i]->selected)
                {
                    if(data->keys[UP] && !data->keys[DOWN])
                    {
                        item[i]->selected = false;

                        if(i != 0)
                            item[i - 1]->selected = true;
                        else
                            item[count_active_item - 1]->selected = true;
                    }
                    else if(data->keys[DOWN] && !data->keys[UP])
                    {
                        item[i]->selected = false;

                        if(i == count_active_item - 1)
                            item[0]->selected = true;
                        else
                            item[i + 1]->selected = true;
                    }

                    is_selected = true;            
                    break;
                }
            
            if(!is_selected)
                if(data->keys[UP] && !data->keys[DOWN])
                    item[count_active_item - 1]->selected = true;
                else if(data->keys[DOWN] && !data->keys[UP])
                    item[0]->selected = true;
                
            cl_play_sound(data, SAMPLE_BUTTON);
        }
    }
}

void cl_draw_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    
    for(int i = 0; i < interface->button_size; i++)
        if(interface->button[i]->al_font)
        {
            CLIENT_BUTTON* btn = interface->button[i];
            ALLEGRO_COLOR clr;
            
            btn->active = true;
            
            if(btn->selected)
                clr = al_map_rgba_f(0.4, 0.4, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);
            
            al_draw_filled_rectangle(btn->b_sx, btn->b_sy, btn->b_dx, btn->b_dy, clr);
            al_draw_text(btn->al_font, al_map_rgb(255, 255, 255), btn->t_x, btn->t_y, ALLEGRO_ALIGN_CENTRE, btn->text);
        }
}

/************************************************************
 * FIELD
 ***********************************************************/

void cl_draw_field(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    
    for(int i = 0; i < interface->field_size; i++)
    {
        CLIENT_FIELD* field = interface->field[i];
        ALLEGRO_COLOR clr;
        
        if(field->selected)
                clr = al_map_rgba_f(0.4, 0.4, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);

        al_draw_text(field->al_font, al_map_rgb(255, 255, 255), field->d_x, field->d_y, 0, field->description);
        al_draw_rectangle(field->f_sx, field->f_sy, field->f_dx, field->f_dy, clr, 2);
        al_draw_text(field->al_font, al_map_rgb(255, 255, 255), field->ft_x, field->ft_y, 0, field->field_text);
        
        if(field->enter)
            al_draw_text(field->al_font, al_map_rgb(255, 255, 255), field->ft_x + field->char_number * field->char_size, field->ft_y, 0, "_");
    }
}

void cl_update_field(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    int mx, my;

    if(data->screen.fullscreen)
    {
        mx = data->event.current.mouse.x / data->screen.scale_factor_x - data->screen.pos_x;
        my = data->event.current.mouse.y / data->screen.scale_factor_y - data->screen.pos_y;
    }
    else
    {
        mx = data->event.current.mouse.x;
        my = data->event.current.mouse.y;
    }

    for(int i = 0; i < interface->field_size; i++)
    {
        CLIENT_FIELD* field = interface->field[i];

        if(field->f_sx < mx && field->f_dx > mx && field->f_sy < my && field->f_dy > my)
        {
            if(!field->selected)
                cl_play_sound(data, SAMPLE_BUTTON);
            
            field->selected = true;
            interface->selected = SELECTED_FIELD;
        }
        else if(field->enter)
            field->selected = true;
        else
            field->selected = false;
    }
}

void cl_enter_field(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    int mx, my;

    if(data->screen.fullscreen)
    {
        mx = data->event.current.mouse.x / data->screen.scale_factor_x - data->screen.pos_x;
        my = data->event.current.mouse.y / data->screen.scale_factor_y - data->screen.pos_y;
    }
    else
    {
        mx = data->event.current.mouse.x;
        my = data->event.current.mouse.y;
    }

    for(int i = 0; i < interface->field_size; i++)
    {
        CLIENT_FIELD* field = interface->field[i];

        if(field->f_sx < mx && field->f_dx > mx && field->f_sy < my && field->f_dy > my)
            field->enter = true;
        else
        {
            field->enter = false;
            field->selected = false;
        }
    }
}

void cl_print_field(CLIENT_DATA* data)
{
    bool backspace = false;
    char symbol = '\0';
    
    switch(data->event.current.keyboard.keycode)
    {
        case ALLEGRO_KEY_A:
            symbol = 'A';
            break;
        case ALLEGRO_KEY_B:
            symbol = 'B';
            break;
        case ALLEGRO_KEY_C:
            symbol = 'C';
            break;
        case ALLEGRO_KEY_D:
            symbol = 'D';
            break;
        case ALLEGRO_KEY_E:
            symbol = 'E';
            break;
        case ALLEGRO_KEY_F:
            symbol = 'F';
            break;
        case ALLEGRO_KEY_G:
            symbol = 'G';
            break;
        case ALLEGRO_KEY_H:
            symbol = 'H';
            break;
        case ALLEGRO_KEY_I:
            symbol = 'I';
            break;
        case ALLEGRO_KEY_J:
            symbol = 'J';
            break;
        case ALLEGRO_KEY_K:
            symbol = 'K';
            break;
        case ALLEGRO_KEY_L:
            symbol = 'L';
            break;
        case ALLEGRO_KEY_M:
            symbol = 'M';
            break;
        case ALLEGRO_KEY_N:
            symbol = 'N';
            break;
        case ALLEGRO_KEY_O:
            symbol = 'O';
            break;
        case ALLEGRO_KEY_P:
            symbol = 'P';
            break;
        case ALLEGRO_KEY_Q:
            symbol = 'Q';
            break;
        case ALLEGRO_KEY_R:
            symbol = 'R';
            break;
        case ALLEGRO_KEY_S:
            symbol = 'S';
            break;
        case ALLEGRO_KEY_T:
            symbol = 'T';
            break;
        case ALLEGRO_KEY_U:
            symbol = 'U';
            break;
        case ALLEGRO_KEY_V:
            symbol = 'V';
            break;
        case ALLEGRO_KEY_W:
            symbol = 'W';
            break;
        case ALLEGRO_KEY_X:
            symbol = 'X';
            break;
        case ALLEGRO_KEY_Y:
            symbol = 'Y';
            break;
        case ALLEGRO_KEY_Z:
            symbol = 'Z';
            break;
        case ALLEGRO_KEY_BACKSPACE:
            backspace = true;
            break;
    }

    if(symbol != '\0')
    {
        CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
        
        for(int i = 0; i < interface->field_size; i++)
        {
            CLIENT_FIELD* field = interface->field[i];

            if(field->enter && field->char_number < 18)
            {
                field->field_text[field->char_number] = symbol;
                ++field->char_number;
                field->field_text[field->char_number] = '\0';
                break;
            }
        }
    }
    else if(backspace)
    {
        CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
        
        for(int i = 0; i < interface->field_size; i++)
        {
            CLIENT_FIELD* field = interface->field[i];

            if(field->enter && field->char_number > 0)
            {
                --field->char_number;
                field->field_text[field->char_number] = symbol;
                break;
            }
        }
    }
}

/************************************************************
 * LIST
 ***********************************************************/

void cl_draw_list(CLIENT_DATA* data)
{
    CLIENT_LIST* list = &data->pairing.interface[data->state]->list;
    
//    if(btn->selected)
//                clr = al_map_rgba_f(0.4, 0.4, 0.0, 0.2);
//            else
//                clr = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);
    
    al_draw_rectangle(list->sx, list->sy, list->dx, list->dy, al_map_rgba_f(0.2, 0.2, 0.2, 0.2), 3);
}

void cl_update_list(CLIENT_DATA* data)
{
    CLIENT_LIST* list = &data->pairing.interface[data->state]->list;
    int mx, my;

    if(data->screen.fullscreen)
    {
        mx = data->event.current.mouse.x / data->screen.scale_factor_x - data->screen.pos_x;
        my = data->event.current.mouse.y / data->screen.scale_factor_y - data->screen.pos_y;
    }
    else
    {
        mx = data->event.current.mouse.x;
        my = data->event.current.mouse.y;
    }

    for(int i = 0; i < 3; i++)
    {
        if(!list->item[i].active) continue;
        
        CLIENT_LIST_ITEM* item = &list->item[i];

        if(item->sx_item < mx && item->dx_item > mx && item->sy_item < my && item->dy_item > my)
        {
            item->selected = true;
            data->pairing.interface[data->state]->selected = SELECTED_LIST;
        }
        else
            item->selected = false;
    }
}

/************************************************************
 * NETWORK
 ***********************************************************/

void cl_send_message_create(CLIENT_DATA* data)
{
    CLIENT_MESSAGE_NONE message;
    
    CLIENT_FIELD** field = data->pairing.interface[data->state]->field;
    
    message.display_height = data->screen.display_height;
    message.display_width = data->screen.display_width;
    message.scale_factor = data->screen.scale_factor;
    strncpy(message.game_name, field[FIELD_NETWORKCREATE_GAMENAME]->field_text, 40);
    strncpy(message.nickname, field[FIELD_NETWORKCREATE_NICKNAME]->field_text, 40);
    message.is_creator = true;
    message.is_ready = true;
    message.state = STATE_PARTY;
    
    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);

    enet_peer_send(data->enet.server, 0, packet);
}

void cl_send_message_join(CLIENT_DATA* data)
{
    CLIENT_MESSAGE_NONE message;
    
    CLIENT_FIELD** field = data->pairing.interface[data->state]->field;
    
    message.display_height = data->screen.display_height;
    message.display_width = data->screen.display_width;
    message.scale_factor = data->screen.scale_factor;
    strncpy(message.nickname, field[FIELD_NETWORKJOIN_NICKNAME]->field_text, 40);
    message.is_creator = false;
    message.is_ready = false;
    message.state = STATE_LIST;
    
    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);

    enet_peer_send(data->enet.server, 0, packet);
}
