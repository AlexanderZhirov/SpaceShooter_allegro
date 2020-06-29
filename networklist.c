#include "common.h"
#include "networklist.h"

#include <stdio.h>
#include <allegro5/allegro_primitives.h>

/************************************************************
 * HANDLING
 ***********************************************************/

void networklist_handling(CLIENT_DATA* data)
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
                networklist_push_button(data);
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                networklist_push_button(data);
                break;
            case ALLEGRO_KEY_TAB:
                networklist_change_selected(data);
                break;
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
        cl_update_list(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        networklist_push_button(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_TIMER)
    {
        data->render = true;
        
        cl_update_background(data, BG1);
        cl_update_background(data, BG2);
    }
    
    networklist_enet_receive(data);
}

/************************************************************
 * DRAW
 ***********************************************************/

void networklist_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG2);
    cl_draw_header(data);
    cl_draw_button(data);
    networklist_draw_list(data);
}

/************************************************************
 * BUTTON
 ***********************************************************/

void networklist_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text)
{
    if(data->pairing.interface[NETWORKLIST]->button_size > key_button)
    {
        CLIENT_FONT* font = data->media.fonts[key_font];
        int block_size = data->screen.height / 8;
        int index = 0;
        
        cl_add_interface_button(
                data->pairing.interface[NETWORKLIST]->button[key_button],
                font->al_font, text,
                data->screen.width - (750 * data->screen.scale_factor + 60) / 2,
                block_size * (index + 6) + (block_size / 4) + (block_size / 2) - font->size,
                data->screen.width - (750 * data->screen.scale_factor) - 30,
                block_size * (index + 6) + (block_size / 4),
                data->screen.width - 30,
                block_size * (index + 6) + block_size);
    }
}

/************************************************************
 * LIST
 ***********************************************************/

void networklist_init_list(CLIENT_DATA* data, int key_font)
{
    CLIENT_LIST* list = &data->pairing.interface[NETWORKLIST]->list;
    
    CLIENT_FONT* font = data->media.fonts[key_font];
    int block_size = data->screen.height / 8;
    int item_height = ((data->screen.height - 15) - block_size * 2) / 3;
    
    list->sx = 15;
    list->sy = block_size * 2;
    list->dx = data->screen.width - (750 * data->screen.scale_factor) - 60;
    list->dy = data->screen.height - 15;
    list->al_font = font->al_font;
    
    for(int i = 0; i < 3; i++)
        cl_add_list_item(
                &list->item[i],
                list->sx,
                list->sy + (item_height * i),
                list->dx,
                list->sy + item_height + (item_height * i),
                list->sx + 30,
                (list->sy + (item_height * i)) + ((item_height / 2) - (font->size / 2)),
                list->dx - font->size - 30,
                list->sy + (item_height * i) + (item_height / 2),
                font->size);
}

static void networklist_draw_list(CLIENT_DATA* data)
{
    CLIENT_LIST* list = &data->pairing.interface[NETWORKLIST]->list;
    ALLEGRO_COLOR clr;
       
    al_draw_rectangle(list->sx, list->sy, list->dx, list->dy, al_map_rgba_f(0.2, 0.2, 0.2, 0.2), 3);
    
    for(int i = 0; i < 3; i++)
    {
        if(i < data->network.count_game)
        {
            list->item[i].active = true;
            
            CLIENT_LIST_ITEM item = list->item[i];
            
            if(item.selected)
                clr = al_map_rgba_f(0.4, 0.4, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);

            al_draw_filled_rectangle(item.sx_item, item.sy_item, item.dx_item, item.dy_item, clr);
            al_draw_text(list->al_font, al_map_rgb(255, 255, 255), item.x_h, item.y_h, 0, data->network.games[i].game_name);
            
            if(data->network.games[i].count_connected == 3)
                clr = al_map_rgba_f(0.5, 0.0, 0.0, 0.2);
            else if(data->network.games[i].count_connected == 2)
                clr = al_map_rgba_f(0.5, 0.5, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.0, 0.5, 0.0, 0.2);

            al_draw_filled_circle(item.x_status, item.y_status, item.r_status, clr);
        }
        else
            list->item[i].active = false;
    }
}

/************************************************************
 * PROCESSING
 ***********************************************************/

static void networklist_enet_receive(CLIENT_DATA* data)
{
    ENetEvent event;
    CLIENT_MESSAGE_LIST* message;
    CLIENT_MESSAGE_PARTY* messages;
    
    while(enet_host_service(data->enet.client, &event, 0) > 0)
        if(event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            message = (CLIENT_MESSAGE_LIST*)event.packet->data;
            
            if(message->state == STATE_PARTY)
            {
                cl_change_state(data, NETWORKPARTY);
                break;
            }
            
            CLIENT_NETWORK* network = &data->network;

            for(int i = 0; i < 3; i++)
            {
                network->games[i].id = message->games[i].id;
                network->games[i].count_connected = message->games[i].count_connected;
                strncpy(network->games[i].game_name, message->games[i].game_name, 40);
            }

            network->count_game = message->count_game;
            
            enet_packet_destroy(event.packet);
        }
}

static void networklist_push_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[NETWORKLIST];
    
    ENetPacket *packet;
    CLIENT_MESSAGE_JOINGAME message;
    
    if(interface->selected == SELECTED_LIST)
    {
        CLIENT_LIST* list = &interface->list;
        
        for(int i = 0; i < 3; i++)
            if(list->item[i].selected && data->network.games[i].count_connected < 3)
            {
                list->item[i].selected = false;

                message.id = data->network.games[i].id;
                message.state = STATE_PARTY;
                packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(data->enet.server, 0, packet);

                break;
            }
    }
    else if(interface->selected == SELECTED_BUTTON)
    {
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->al_font && interface->button[i]->selected)
            {
                cl_play_sound(data, SAMPLE_ENTER);
                
                switch(i)
                {
                    case BUTTON_NETWORKLIST_OUT:
                        interface->button[i]->selected = false;
                        cl_change_state(data, NETWORKMODE);
                        break;
                }
            }
    }
}

void networklist_change_selected(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[NETWORKLIST];
    
    if(interface->selected == SELECTED_BUTTON)
    {
        interface->selected = SELECTED_LIST;
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->selected)
                interface->button[i]->selected = false;
    }
    else if(interface->selected == SELECTED_LIST)
    {
        interface->selected = SELECTED_BUTTON;
        for(int i = 0; i < 3; i++)
            if(interface->list.item[i].selected)
               interface->list.item[i].selected = false;
    }
}

