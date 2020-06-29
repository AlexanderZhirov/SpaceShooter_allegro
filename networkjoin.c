#include "common.h"
#include "networkjoin.h"

/************************************************************
 * HANDLING
 ***********************************************************/

void networkjoin_handling(CLIENT_DATA* data)
{
    if(data->event.current.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (data->event.current.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
            {
                if(!data->keys[ESCAPE])
                {
                    data->keys[ESCAPE] = true;
                    cl_change_state(data, NETWORKMODE);
                }
                break;
            }
            case ALLEGRO_KEY_LEFT:
                data->keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                data->keys[RIGHT] = true;
                break;
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
                networkjoin_push_button(data);
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                networkjoin_push_button(data);
                break;
            case ALLEGRO_KEY_TAB:
                networkjoin_change_selected(data);
                break;
            default:
                cl_print_field(data);
        }
    }
    else if(data->event.current.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch (data->event.current.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
                data->keys[ESCAPE] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                data->keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                data->keys[RIGHT] = false;
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
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        cl_update_button(data);
        cl_update_field(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        networkjoin_push_button(data);
        cl_enter_field(data);
    }
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

void networkjoin_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG2);
    cl_draw_header(data);
    cl_draw_button(data);
    
    cl_draw_field(data);
}

/************************************************************
 * FIELD
 ***********************************************************/

void networkjoin_init_field(CLIENT_DATA* data, int key_field, int key_font, const char* description)
{
    if(data->pairing.interface[NETWORKJOIN]->field_size > key_field)
    {
        CLIENT_FONT* font = data->media.fonts[key_font];
        int block_size = data->screen.height / 8;
        
        cl_add_interface_field(
                data->pairing.interface[NETWORKJOIN]->field[key_field],
                font->al_font, font->size, description,
                (data->screen.width / 2) - al_get_text_width(font->al_font, description),
                (block_size * (key_field + 3) - font->size / 2),
                (data->screen.width / 2),
                (block_size * (key_field + 3) - font->size / 2),
                (data->screen.width / 2),
                (block_size * (key_field + 3) + font->size / 2)
        );
    }
}

/************************************************************
 * BUTTON
 ***********************************************************/

void networkjoin_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text)
{
    if(data->pairing.interface[NETWORKJOIN]->button_size > key_button)
    {
        CLIENT_FONT* font = data->media.fonts[key_font];
        int block_size = data->screen.height / 8;
        
        cl_add_interface_button(
                data->pairing.interface[NETWORKJOIN]->button[key_button],
                font->al_font, text, data->screen.width / 2,
                (block_size * (key_button + 5)) + (block_size / 4) + (block_size / 2) - font->size,
                (data->screen.width / 2) - (750 * data->screen.scale_factor) / 2,
                block_size * (key_button + 5) + (block_size / 4),
                (data->screen.width / 2) + (750 * data->screen.scale_factor) / 2,
                block_size * (key_button + 5) + block_size);
    }
}

static void networkjoin_push_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];

    if(interface->selected == SELECTED_BUTTON)
    {
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->al_font && interface->button[i]->selected)
            {
                cl_play_sound(data, SAMPLE_ENTER);
            
                switch(i)
                {
                    case BUTTON_NETWORKJOIN_CREATE:
                        interface->button[i]->selected = false;
                        if(networkjoin_check_field(data))
                            cl_change_state(data, NETWORKLIST);
                        break;
                    case BUTTON_NETWORKJOIN_OUT:
                        interface->button[i]->selected = false;
                        cl_change_state(data, NETWORKMODE);
                        break;
                }
            }
    }
    else if(interface->selected == SELECTED_FIELD)
    {
        for(int i = 0; i < interface->field_size; i++)
            if(interface->field[i]->selected)
                switch(i)
                {
                    case FIELD_NETWORKJOIN_NICKNAME:
                        interface->field[i]->enter = true;
                        break;
                }
    }
}

static void networkjoin_change_selected(CLIENT_DATA* data)
{
    cl_change_selected(data->pairing.interface[data->state]);
}

static bool networkjoin_check_field(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[data->state];
    int field_size = interface->field_size;
    int field_filled_size = 0;
    
    for(int i = 0; i < field_size; i++)
        if(interface->field[i]->char_number > 0)
            field_filled_size++;
    
    return field_size == field_filled_size;
}
