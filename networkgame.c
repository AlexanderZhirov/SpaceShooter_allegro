#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "common.h"
#include "networkgame.h"

/************************************************************
 * HANDLING
 ***********************************************************/

void networkgame_handling(CLIENT_DATA* data)
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
                    al_show_mouse_cursor(data->screen.display);
                    cl_change_state(data, NETWORKOUT);
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
//                cl_select_button(data);
                break;
            case ALLEGRO_KEY_DOWN:
                data->keys[DOWN] = true;
//                cl_select_button(data);
                break;
            case ALLEGRO_KEY_ENTER:
                data->keys[ENTER] = true;
//                networkparty_push_button(data);
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                networkgame_fire_bullet(data);
                break;
            case ALLEGRO_KEY_TAB:
//                networkparty_change_selected(data);
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
//        cl_update_list(data);
//        cl_update_button(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
//        networkparty_push_button(data);
    }
    else if(data->event.current.type == ALLEGRO_EVENT_TIMER)
    {
        data->render = true;
        
        if(data->keys[UP])
            networkgame_move_ship_up(data);
        else if(data->keys[DOWN])
            networkgame_move_ship_down(data);
        else
            networkgame_reset_ship_animation(data, 1);

        if(data->keys[LEFT])
            networkgame_move_ship_left(data);
        else if(data->keys[RIGHT])
            networkgame_move_ship_right(data);
        else
            networkgame_reset_ship_animation(data, 2);
        
        networkgame_update_explosions(data);
        networkgame_update_comet(data);
        
        cl_update_background(data, BG1);
        cl_update_background(data, BG3);
        cl_update_background(data, BG2);
    }
    
    networkgame_enet_receive(data);
}

/************************************************************
 * DRAW
 ***********************************************************/

void networkgame_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG3);
    cl_draw_background(data, BG2);
    
    networkgame_draw_ship(data);
    networkgame_draw_bullet(data);
    networkgame_draw_comet(data);
    networkgame_draw_explosions(data);
    networkgame_draw_statistic(data);
    
    networkgame_send_move_ship(data);
}

/************************************************************
 * PROCESSING
 ***********************************************************/

void networkgame_create_objects(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    int iterator = 0;
    
    cl_create_objects(objects, data->network.count_connected, 5 * data->network.count_connected, 15, 5 * data->network.count_connected);
    
    for(int i = 0; i < objects->ship_size; i++)
    {
        cl_init_ships(objects, iterator, data->network.users[i].id, 3, 1, 1, 10, 12, 0, 0, 50, 41, 46, data->media.bitmaps[SHIP_R + i]->al_bitmap, 3, 3, 0, 0, 0, 0);
        
        for(int j = iterator++ * 5; j < iterator * 5; j++)
                cl_init_bullets(objects, j, data->network.users[i].id, 10, 0, 0);
    }

    for(int i = 0; i < objects->comet_size; i++)
        cl_init_comets(objects, i, 0, 21, rand() % 2 ? 1 : -1, 35, 35, 0, 0, 2, 96, 96, data->media.bitmaps[COMET]->al_bitmap, 143, 5, 0, 0);
    
    for(int i = 0; i < objects->explosion_size; i++)
        cl_init_explosions(objects, i, 8, 1, 0, 0, 1, 128, 128, data->media.bitmaps[EXPLOSION]->al_bitmap, 31, 0, 0);
}

void networkgame_enet_receive(CLIENT_DATA* data)
{
    ENetEvent event;
    CLIENT_MESSAGE_UPDATE* message;
    
    while(enet_host_service(data->enet.client, &event, 0) > 0)
        if(event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            message = (CLIENT_MESSAGE_UPDATE*)event.packet->data;
            
            for(int i = 0; i < data->objects.ship_size; i++)
            {
                CLIENT_SHIP* ship = data->objects.ships[i];
                
                for(int j = 0; j < 3; j++)
                    if(ship->ID == message->ship[j].ID)
                    {
                        ship->x = message->ship[j].x;
                        ship->y = message->ship[j].y;
                        ship->lives = message->ship[j].lives;
                        ship->score = message->ship[j].score;
                        ship->active = message->ship[j].active;
                        
                        for(int k = 0; k < 3; k++)
                        {
                            CLIENT_USER* user = &data->network.users[k];
                            
                            if(user->id == ship->ID)
                            {
                                user->command.dx = message->ship[j].dx;
                                user->command.dy = message->ship[j].dy;
                            }
                        }
                        
                        break;
                    }
            }
            
            for(int i = 0; i < data->objects.bullet_size; i++)
            {
                CLIENT_BULLET* bullet = data->objects.bullets[i];
                
                if(message->bullet[i].live && !bullet->live)
                    cl_play_sound(data, SAMPLE_SHOT);
                
                bullet->ID = message->bullet[i].ID;
                bullet->active = message->bullet[i].active;
                bullet->live = message->bullet[i].live;
                bullet->x = message->bullet[i].x;
                bullet->y = message->bullet[i].y;
            }
            
            for(int i = 0; i < data->objects.comet_size; i++)
            {
                CLIENT_COMET* comet = data->objects.comets[i];
                
                comet->live = message->comet[i].live;
                comet->x = message->comet[i].x;
                comet->y = message->comet[i].y;
            }
            
            for(int i = 0; i < data->objects.explosion_size; i++)
            {
                CLIENT_EXPLOSION* explosion = data->objects.explosions[i];
                
                if(message->explosion[i].live)
                {
                    if(message->explosion[i].live && !explosion->live)
                        cl_play_sound(data, SAMPLE_BOOM);
                    
                    explosion->live = message->explosion[i].live;
                    explosion->x = message->explosion[i].x;
                    explosion->y = message->explosion[i].y;
                }
            }
            
            enet_packet_destroy(event.packet);
        }
}

static void networkgame_send_move_ship(CLIENT_DATA* data)
{
    if(data->network.command.send)
    {
        CLIENT_GAME_COMMAND command = data->network.command;
        
        command.send = false;
        
        ENetPacket *packet;
        CLIENT_MESSAGE_GAME message;
        
        message.dx = command.dx;
        message.dy = command.dy;
        message.fire = command.fire;
        message.state = STATE_GAME;
        
        data->network.command.fire = false;
        
        packet = enet_packet_create(&message, sizeof(message), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(data->enet.server, 0, packet);
    }
}

/************************************************************
 * SHIP
 ***********************************************************/

static void networkgame_draw_ship(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(!ship->active) continue;
        
        for(int j = 0; j < data->objects.ship_size; j++)
        {
            CLIENT_USER* user = &data->network.users[j];
            
            if(user->id == ship->ID)
            {
                if(user->command.dy == -1)
                    ship->animation_row = 0;
                else if(user->command.dy == 1)
                    ship->animation_row = 2;
                else
                    ship->animation_row = 1;
                    
                if(user->command.dx == -1)
                    ship->cur_frame = 2;
                else if(user->command.dx == 1)
                    ship->cur_frame = 1;
                else
                    ship->cur_frame = 0;
            }
        }
        
        int fx = (ship->cur_frame % ship->animation_columns) * ship->frame_width;
        int fy = ship->animation_row * ship->frame_height;

        al_draw_bitmap_region(ship->image, fx, fy, ship->frame_width, ship->frame_height,
                ship->x - ship->frame_width / 2, ship->y - ship->frame_height / 2, 0);
    }
}

static void networkgame_move_ship_up(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id)
        {
            ship->animation_row = 0;
            data->network.command.dy = -1;
            data->network.command.send = true;
        }        
    }
}

static void networkgame_move_ship_down(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id)
        {
            ship->animation_row = 2;
            data->network.command.dy = 1;
            data->network.command.send = true;
        }        
    }
}

static void networkgame_move_ship_left(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id)
        {
            ship->cur_frame = 2;
            data->network.command.dx = -1;
            data->network.command.send = true;
        }        
    }
}

static void networkgame_move_ship_right(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id)
        {
            ship->cur_frame = 1;
            data->network.command.dx = 1;
            data->network.command.send = true;
        }        
    }
}

static void networkgame_reset_ship_animation(CLIENT_DATA* data, int position)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id)
        {
            if(position == 1)
            {
                ship->animation_row = 1;
                data->network.command.dy = 0;
            }
            else
            {
                ship->cur_frame = 0;
                data->network.command.dx = 0;
            }

            data->network.command.send = true;
        }        
    }
}

static bool networkgame_dead_ship(CLIENT_DATA* data)
{
    return data->objects.ships[0]->lives <= 0;
}

/************************************************************
 * BULLET
 ***********************************************************/

static void networkgame_fire_bullet(CLIENT_DATA* data)
{
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        
        if(ship->ID == data->network.user_id && ship->active)
            data->network.command.fire = true;
    }
}

static void networkgame_draw_bullet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->bullet_size; i++)
    {
        CLIENT_BULLET* bullet = objects->bullets[i];
        
        if(bullet->live)
            al_draw_filled_circle(bullet->x, bullet->y, 2, al_map_rgb(255, 255, 255));
    }
}

/************************************************************
 * COMET
 ***********************************************************/

static void networkgame_draw_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->comet_size; i++)
    {
        CLIENT_COMET* comet = objects->comets[i];
        
        if(comet->live)
        {            
            int fx = (comet->cur_frame % comet->animation_columns) * comet->frame_width;
            int fy = (comet->cur_frame / comet->animation_columns) * comet->frame_height;

            al_draw_bitmap_region(comet->image, fx, fy, comet->frame_width, comet->frame_height,
                    comet->x - comet->frame_width / 2, comet->y - comet->frame_height / 2, 0);            
        }
    }
}

void networkgame_update_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->comet_size; i++)
    {
        CLIENT_COMET* comet = objects->comets[i];
        
        if(comet->live)
        {            
            if(++comet->frame_count >= comet->frame_delay)
            {
                comet->cur_frame += comet->animation_direction;
                if(comet->cur_frame >= comet->max_frame)
                    comet->cur_frame = 0;
                else if(comet->cur_frame <= 0)
                    comet->cur_frame = comet->max_frame - 1;
                
                comet->frame_count = 0;
            }
        }
    }
}

/************************************************************
 * EXPLOSION
 ***********************************************************/

static void networkgame_draw_explosions(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->explosion_size; i++)
    {
        CLIENT_EXPLOSION* explosion = objects->explosions[i];
        
        if(explosion->live)
        {
            int fx = (explosion->cur_frame % explosion->animation_columns) * explosion->frame_width;
            int fy = (explosion->cur_frame / explosion->animation_columns) * explosion->frame_height;
            
            al_draw_bitmap_region(explosion->image, fx, fy, explosion->frame_width, explosion->frame_height,
                    explosion->x - explosion->frame_width / 2, explosion->y - explosion->frame_height / 2, 0);
        }
    }
}

void networkgame_update_explosions(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->explosion_size; i++)
    {
        CLIENT_EXPLOSION* explosion = objects->explosions[i];
        
        if(explosion->live)
            if(++explosion->frame_count >= explosion->frame_delay)
            {
                explosion->cur_frame += explosion->animation_direction;
                if(explosion->cur_frame >= explosion->max_frame)
                {
                    explosion->cur_frame = 0;
                    explosion->live = false;
                }
                
                explosion->frame_count = 0;
            }
    }
}

/************************************************************
 * STATISTIC
 ***********************************************************/

static void networkgame_draw_statistic(CLIENT_DATA* data)
{
    ALLEGRO_COLOR color;
    ALLEGRO_COLOR color_text = al_map_rgba_f(0.5, 0.5, 0.5, 0.2);
    ALLEGRO_FONT* font = data->media.fonts[FONT_PS2P30]->al_font;
    
    char text[200] = {' ', '\0'};
    char num[5] = {'\0'};
    
    for(int i = 0; i < data->objects.ship_size; i++)
    {
        CLIENT_SHIP* ship = data->objects.ships[i];
        CLIENT_USER user;
        
        switch(i)
        {
            case 0:
                color = al_map_rgba_f(0.5, 0.0, 0.0, 0.2);
                break;
            case 1:
                color = al_map_rgba_f(0.0, 0.5, 0.0, 0.2);
                break;
            case 2:
                color = al_map_rgba_f(0.5, 0.5, 0.0, 0.2);
                break;
        }
        
        for(int j = 0; j < 3; j++)
            if(data->network.users[j].id == ship->ID)
            {
                user = data->network.users[j];
                break;
            }
        
        al_draw_text(font, color, al_get_text_width(font, text), 5, 0, user.nickname);
        strcat(text, user.nickname);
        al_draw_text(font, color, al_get_text_width(font, text), 5, 0, " - Ж:");
        strcat(text, " - Ж:");
        al_draw_textf(font, color_text, al_get_text_width(font, text), 5, 0, "%d", ship->lives);
        sprintf(num, "%d", ship->lives);
        strcat(text, num);
        al_draw_text(font, color, al_get_text_width(font, text), 5, 0, " К:");
        strcat(text, " К:");
        al_draw_textf(font, color_text, al_get_text_width(font, text), 5, 0, "%d", ship->score);
        sprintf(num, "%d ", ship->score);
        strcat(text, num);
    }
}

