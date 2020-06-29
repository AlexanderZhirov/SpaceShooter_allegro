#include "common.h"
#include "networkparty.h"
#include "networkcreate.h"

#include <stdio.h>
#include <allegro5/allegro_primitives.h>

/************************************************************
 * HANDLING
 ***********************************************************/

void networkparty_handling(CLIENT_DATA* data)
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
                    if(data->network.is_creator)
                        cl_change_state(data, NETWORKMODE);
                    else
                        networkparty_send_exit(data);
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
                networkparty_push_button(data);
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                networkparty_push_button(data);
                break;
            case ALLEGRO_KEY_TAB:
                networkparty_change_selected(data);
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
        cl_update_list(data);
        cl_update_button(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        networkparty_push_button(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_TIMER)
    {
        data->render = true;
        
        cl_update_background(data, BG1);
        cl_update_background(data, BG2);
    }
    
    networkparty_enet_receive(data);
}

/************************************************************
 * DRAW
 ***********************************************************/

void networkparty_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG2);
    cl_draw_header(data);
    networkparty_draw_button(data);
    networkparty_draw_list(data);
}

/************************************************************
 * BUTTON
 ***********************************************************/

void networkparty_init_button(CLIENT_DATA* data, int key_button, int key_font, const char* text)
{
    if(data->pairing.interface[NETWORKPARTY]->button_size > key_button)
    {
        CLIENT_FONT* font = data->media.fonts[key_font];
        int block_size = data->screen.height / 8;
        int index = 0;
        
        if(key_button == BUTTON_NETWORKPARTY_OUT)
            index = 1;
        
        cl_add_interface_button(
                data->pairing.interface[NETWORKPARTY]->button[key_button],
                font->al_font, text,
                data->screen.width - (750 * data->screen.scale_factor + 60) / 2,
                block_size * (index + 5) + (block_size / 4) + (block_size / 2) - font->size,
                data->screen.width - (750 * data->screen.scale_factor) - 30,
                block_size * (index + 5) + (block_size / 4),
                data->screen.width - 30,
                block_size * (index + 5) + block_size);
    }
}

static void networkparty_draw_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[NETWORKPARTY];
    
    for(int i = 0; i < interface->button_size; i++)
        if(interface->button[i]->al_font)
        {
            CLIENT_BUTTON* btn = interface->button[i];
            
            if(data->network.is_creator)
            {
                if(i == BUTTON_NETWORKPARTY_READY || i == BUTTON_NETWORKPARTY_UNREADY)
                {
                    btn->active = false;
                    continue;
                }
            }
            else if(data->network.is_ready)
            {
                if(i == BUTTON_NETWORKPARTY_READY || i == BUTTON_NETWORKPARTY_START)
                {
                    btn->active = false;
                    continue;
                }
            }
            else
            {
                if(i == BUTTON_NETWORKPARTY_UNREADY || i == BUTTON_NETWORKPARTY_START)
                {
                    btn->active = false;
                    continue;
                }
            }
            
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
 * LIST
 ***********************************************************/

void networkparty_init_list(CLIENT_DATA* data, int key_font)
{
    CLIENT_LIST* list = &data->pairing.interface[NETWORKPARTY]->list;
    
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

static void networkparty_draw_list(CLIENT_DATA* data)
{
    CLIENT_LIST* list = &data->pairing.interface[NETWORKPARTY]->list;
    ALLEGRO_COLOR clr;
       
    al_draw_rectangle(list->sx, list->sy, list->dx, list->dy, al_map_rgba_f(0.2, 0.2, 0.2, 0.2), 3);
    
    for(int i = 0; i < 3; i++)
    {
        if(i < data->network.count_connected)
        {
            list->item[i].active = true;
            
            CLIENT_LIST_ITEM item = list->item[i];
            
            if(item.selected)
                clr = al_map_rgba_f(0.4, 0.4, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.2, 0.2, 0.2, 0.2);

            al_draw_filled_rectangle(item.sx_item, item.sy_item, item.dx_item, item.dy_item, clr);
            al_draw_text(list->al_font, al_map_rgb(255, 255, 255), item.x_h, item.y_h, 0, data->network.users[i].nickname);

            if(data->network.users[i].is_ready)
                clr = al_map_rgba_f(0.0, 0.5, 0.0, 0.2);
            else
                clr = al_map_rgba_f(0.5, 0.0, 0.0, 0.2);

            al_draw_filled_circle(item.x_status, item.y_status, item.r_status, clr);
        }
        else
            list->item[i].active = false;
    }
}

/************************************************************
 * PROCESSING
 ***********************************************************/

static void networkparty_enet_receive(CLIENT_DATA* data)
{
    ENetEvent event;
    CLIENT_MESSAGE_PARTY* message;
    
    while(enet_host_service(data->enet.client, &event, 0) > 0)
        if(event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            message = (CLIENT_MESSAGE_PARTY*)event.packet->data;
            
            if(message->state == STATE_LIST)
            {
                cl_change_state(data, NETWORKLIST);
                break;
            }
            else if(message->state == STATE_GAME)
            {
                cl_change_state(data, NETWORKGAME);
                break;
            }
            
            CLIENT_NETWORK* network = &data->network;
            
            network->active = message->active;
            network->count_connected = message->count_connected;
            network->game_started = message->game_started;
            strncpy(network->game_name, message->game_name, 40);
            network->is_creator = message->is_creator;
            network->is_ready = message->is_ready;            
            network->game_id = message->game_id;
            network->user_id = message->user_id;
            
            for(int i = 0; i < network->count_connected; i++)
            {
                network->users[i].id = message->users[i].id;
                network->users[i].is_ready = message->users[i].is_ready;
                strncpy(network->users[i].nickname, message->users[i].nickname, 40);
            }
            
            enet_packet_destroy(event.packet);
        }
}

static void networkparty_push_button(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[NETWORKPARTY];

    if(interface->selected == SELECTED_BUTTON)
    {        
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->selected)
            {
                cl_play_sound(data, SAMPLE_ENTER);
                
                interface->button[i]->selected = false;
                
                switch(i)
                {
                    case BUTTON_NETWORKPARTY_START:
                        if(networkparty_check_users(data))
                            networkparty_send_start(data);
                        break;
                    case BUTTON_NETWORKPARTY_READY:
                    case BUTTON_NETWORKPARTY_UNREADY:
                        networkparty_send_ready(data);
                        break;
                    case BUTTON_NETWORKPARTY_OUT:
                        if(data->network.is_creator)
                            cl_change_state(data, NETWORKMODE);
                        else
                            networkparty_send_exit(data);
                        break;
                }
            }
    }
    else if(interface->selected == SELECTED_LIST)
    {
        if(data->network.is_creator)
        {
            CLIENT_LIST* list = &interface->list;
        
            for(int i = 0; i < 3; i++)
                if(list->item[i].selected && data->network.users[i].id != data->network.user_id)
                {
                    list->item[i].selected = false;
                    
                    networkparty_send_kick(data, data->network.users[i].id);

                    break;
                }
        }
    }
}

static void networkparty_change_selected(CLIENT_DATA* data)
{
    CLIENT_INTERFACE* interface = data->pairing.interface[NETWORKPARTY];
    
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

static bool networkparty_check_users(CLIENT_DATA* data)
{
    bool ready = true;
    
    for(int i = 0; i < data->network.count_connected; i++)
        if(!data->network.users[i].is_ready)
        {
            ready = false;
            break;
        }
    
    return ready;
}

static void networkparty_send_exit(CLIENT_DATA* data)
{
    CLIENT_MESSAGE_SENDPARTY message;
    
    message.state = STATE_LIST;
    message.kick_user = false;

    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(data->enet.server, 0, packet);
}

static void networkparty_send_ready(CLIENT_DATA* data)
{
    CLIENT_MESSAGE_SENDPARTY message;
    
    message.state = STATE_PARTY;
    message.is_ready = !data->network.is_ready;

    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(data->enet.server, 0, packet);
}

static void networkparty_send_kick(CLIENT_DATA* data, int user_id)
{
    CLIENT_MESSAGE_SENDPARTY message;
    
    message.state = STATE_LIST;
    message.kick_user = true;
    message.user_id = user_id;

    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(data->enet.server, 0, packet);
}

static void networkparty_send_start(CLIENT_DATA* data)
{
    CLIENT_MESSAGE_SENDPARTY message;
    
    message.state = STATE_GAME;

    ENetPacket *packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(data->enet.server, 0, packet);
}
