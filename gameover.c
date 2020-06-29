#include "common.h"
#include "gameover.h"

/************************************************************
 * HANDLING
 ***********************************************************/

void gameover_handling(CLIENT_DATA* data)
{
    if(data->event.current.type == ALLEGRO_EVENT_KEY_DOWN)
        switch (data->event.current.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
            {
                if(!data->keys[ESCAPE])
                {
                    data->keys[ESCAPE] = true;
                    cl_change_state(data, MENU);
                }
                break;
            }
            case ALLEGRO_KEY_UP:
                data->keys[UP] = true;
                cl_select_button(data);
                break;
            case ALLEGRO_KEY_DOWN:
                data->keys[DOWN] = true;
                cl_select_button(data);
                break;
            case ALLEGRO_KEY_ENTER:
                data->keys[ENTER] = true;
                gameover_push_button(data);
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                gameover_push_button(data);
                break;
        }
    else if(data->event.current.type == ALLEGRO_EVENT_KEY_UP)
        switch (data->event.current.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
                data->keys[ESCAPE] = false;
                break;
            case ALLEGRO_KEY_UP:
                data->keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                data->keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_ENTER:
                data->keys[ENTER] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = false;
                break;
        }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_AXES)
        cl_update_button(data);
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        gameover_push_button(data);
    else if(data->event.current.type == ALLEGRO_EVENT_TIMER)
    {
        data->render = true;
        
        cl_update_background(data, BG1);
        cl_update_background(data, BG2);
    }
}

/************************************************************
 * DRAW
 ***********************************************************/

void gameover_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG2);
    cl_draw_header(data);
    cl_draw_button(data);
    gameover_draw_statistic(data);
}

/************************************************************
 * PROCESSING
 ***********************************************************/

void gameover_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text)
{
    if(data->pairing.interface[GAMEOVER]->button_size > key_button)
    {
        CLIENT_FONT* font = data->media.fonts[key_font];
        int block_size = data->screen.height / 8;
        
        cl_add_interface_button(
                data->pairing.interface[GAMEOVER]->button[key_button],
                font->al_font, text, data->screen.width / 2,
                (block_size * (key_button + 6)) + (block_size / 4) + (block_size / 2) - font->size,
                (data->screen.width / 2) - (750 * data->screen.scale_factor) / 2,
                block_size * (key_button + 6) + (block_size / 4),
                (data->screen.width / 2) + (750 * data->screen.scale_factor) / 2,
                block_size * (key_button + 6) + block_size);
    }
}

static void gameover_push_button(CLIENT_DATA* data)
{    
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];

    for(int i = 0; i < interface->button_size; i++)
        if(interface->button[i]->al_font && interface->button[i]->selected)
        {
            cl_play_sound(data, SAMPLE_ENTER);
            
            switch(i)
            {
                case BUTTON_GAMEOVER_OUT:
                    interface->button[i]->selected = false;
                    cl_change_state(data, MENU);
                    break;
            }
        }
}

static void gameover_draw_statistic(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    ALLEGRO_FONT* font = data->media.fonts[FONT_PS2P40]->al_font;
    ALLEGRO_COLOR color = al_map_rgba_f(1.0, 0.0, 0.0, 0.2);
    ALLEGRO_COLOR color_text = al_map_rgba_f(1.0, 1.0, 1.0, 0.2);
    
    al_draw_text(
            font, color,
            (data->screen.width / 2) - al_get_text_width(font, "УНИЧТОЖЕНО:") / 2,
            data->screen.height / 2, 0, "УНИЧТОЖЕНО:");
    al_draw_textf(
            font, color_text,
            (data->screen.width / 2) + al_get_text_width(font, "УНИЧТОЖЕНО:") / 2,
            data->screen.height / 2, 0, "%d", ship->score);
}
