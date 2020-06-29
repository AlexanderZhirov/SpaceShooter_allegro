#include <stdio.h>
#include <allegro5/allegro_primitives.h>

#include "common.h"
#include "single.h"

/************************************************************
 * HANDLING
 ***********************************************************/

void single_handling(CLIENT_DATA* data)
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
                    cl_change_state(data, PAUSE);
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
                break;
            case ALLEGRO_KEY_DOWN:
                data->keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = true;
                cl_fire_bullet(data);
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
            case ALLEGRO_KEY_SPACE:
                data->keys[SPACE] = false;
                break;
        }
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        
    }
    else if(data->event.current.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        
    }
    else if(data->event.current.type == ALLEGRO_EVENT_TIMER)
    {
        data->render = true;
        
        if(data->keys[UP])
            cl_move_ship_up(data);
        else if(data->keys[DOWN])
            cl_move_ship_down(data);
        else
            cl_reset_ship_animation(data, 1);

        if(data->keys[LEFT])
            cl_move_ship_left(data);
        else if(data->keys[RIGHT])
            cl_move_ship_right(data);
        else
            cl_reset_ship_animation(data, 2);

        cl_update_background(data, BG1);
        cl_update_background(data, BG3);
        cl_update_background(data, BG2);

        cl_update_explosions(data);
        cl_update_bullet(data);
        cl_start_comet(data);
        cl_update_comet(data);
        cl_collide_bullet(data);
        cl_collide_comet(data);
        
        if(cl_dead_ship(data))
        {
            cl_change_state(data, GAMEOVER);
            al_show_mouse_cursor(data->screen.display);
        }
    }
}

/************************************************************
 * DRAW
 ***********************************************************/

void single_draw(CLIENT_DATA* data)
{
    cl_draw_background(data, BG1);
    cl_draw_background(data, BG3);
    cl_draw_background(data, BG2);
    
    cl_draw_ship(data);
    cl_draw_bullet(data);
    cl_draw_comet(data);
    cl_draw_explosions(data);
    
    cl_draw_statistic(data);
}

/************************************************************
 * PROCESSING
 ***********************************************************/

void cl_init_objects(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    cl_create_objects(objects, 1, 5, 10, 5);
    cl_init_ships(objects, 0, 0, 3, 1, 1, 10, 12, 0, 0, 50, 41, 46, data->media.bitmaps[SHIP_R]->al_bitmap, 3, 3, 0, 6, 20, data->screen.height / 2);
    
    for(int i = 0; i < objects->bullet_size; i++)
        cl_init_bullets(objects, i, 0, 10, 0, 0);
    
    for(int i = 0; i < objects->comet_size; i++)
        cl_init_comets(objects, i, 0, 21, rand() % 2 ? 1 : -1, 35, 35, 0, 0, 2, 96, 96, data->media.bitmaps[COMET]->al_bitmap, 143, 5, 0, 0);
    
    for(int i = 0; i < objects->explosion_size; i++)
        cl_init_explosions(objects, i, 8, 1, 0, 0, 1, 128, 128, data->media.bitmaps[EXPLOSION]->al_bitmap, 31, 0, 0);
}

/************************************************************
 * SHIP
 ***********************************************************/

static void cl_draw_ship(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    int fx = (ship->cur_frame % ship->animation_columns) * ship->frame_width;
    int fy = ship->animation_row * ship->frame_height;
    
    al_draw_bitmap_region(ship->image, fx, fy, ship->frame_width, ship->frame_height,
            ship->x - ship->frame_width / 2, ship->y - ship->frame_height / 2, 0);
}

static void cl_move_ship_up(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    ship->animation_row = 0;
    ship->y -= ship->speed;
    if(ship->y < 0)
        ship->y = 0;
}

static void cl_move_ship_down(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    ship->animation_row = 2;
    ship->y += ship->speed;
    if(ship->y > data->screen.height)
        ship->y = data->screen.height;
}

static void cl_move_ship_left(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    ship->cur_frame = 2;
    ship->x -= ship->speed;
    if(ship->x < 0)
        ship->x = 0;
}

static void cl_move_ship_right(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    ship->cur_frame = 1;
    ship->x += ship->speed;
    if(ship->x > 900 * data->screen.scale_factor)
        ship->x = 900 * data->screen.scale_factor;
}

static void cl_reset_ship_animation(CLIENT_DATA* data, int position)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    
    if(position == 1)
        ship->animation_row = 1;
    else
        ship->cur_frame = 0;
}

static bool cl_dead_ship(CLIENT_DATA* data)
{
    return data->objects.ships[0]->lives <= 0;
}

/************************************************************
 * BULLET
 ***********************************************************/

static void cl_draw_bullet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < objects->bullet_size; i++)
        if(objects->bullets[i]->live)
            al_draw_filled_circle(objects->bullets[i]->x, objects->bullets[i]->y, 2, al_map_rgb(255, 255, 255));
}

static void cl_fire_bullet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < data->objects.bullet_size; i++)
        if(!objects->bullets[i]->live)
        {
            objects->bullets[i]->x = objects->ships[0]->x + 17;
            objects->bullets[i]->y = objects->ships[0]->y;
            objects->bullets[i]->live = true;
            
            cl_play_sound(data, SAMPLE_SHOT);
            
            break;
        }
}

static void cl_update_bullet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    
    for(int i = 0; i < data->objects.bullet_size; i++)
        if(objects->bullets[i]->live)
        {
            objects->bullets[i]->x += objects->bullets[i]->speed;
            if(objects->bullets[i]->x > data->screen.width)
                objects->bullets[i]->live = false;
        }
}

static void cl_collide_bullet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_SHIP* ship = objects->ships[0];
    CLIENT_BULLET** bullets = objects->bullets;
    CLIENT_COMET** comets = objects->comets;
    
    for(int i = 0; i < objects->bullet_size; i++)
        if(bullets[i]->live)
        {            
            for(int j = 0; j < objects->comet_size; j++)
                if(comets[j]->live)
                {                    
                    if(bullets[i]->x > (comets[j]->x - comets[j]->boundx) &&
                        bullets[i]->x < (comets[j]->x + comets[j]->boundx) &&
                        bullets[i]->y > (comets[j]->y - comets[j]->boundy) &&
                        bullets[i]->y < (comets[j]->y + comets[j]->boundy))
                    {
                        bullets[i]->live = false;
                        comets[j]->live = false;
                        
                        ship->score++;
                        
                        cl_start_explosions(data, bullets[i]->x, bullets[i]->y);
                        
                        cl_play_sound(data, SAMPLE_BOOM);
                    }
                }
        }
}

/************************************************************
 * COMET
 ***********************************************************/

static void cl_draw_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_COMET** comets = objects->comets;
    
    for(int i = 0; i < objects->comet_size; i++)
        if(comets[i]->live)
        {            
            int fx = (comets[i]->cur_frame % comets[i]->animation_columns) * comets[i]->frame_width;
            int fy = (comets[i]->cur_frame / comets[i]->animation_columns) * comets[i]->frame_height;

            al_draw_bitmap_region(comets[i]->image, fx, fy, comets[i]->frame_width, comets[i]->frame_height,
                    comets[i]->x - comets[i]->frame_width / 2, comets[i]->y - comets[i]->frame_height / 2, 0);            
        }
}

static void cl_start_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_COMET** comets = objects->comets;
    
    for(int i = 0; i < objects->comet_size; i++)
        if(!comets[i]->live)
            if(rand() % 500 == 0)
            {
                comets[i]->live = true;
                comets[i]->x = data->screen.width;
                comets[i]->y = 30 + rand() % (data->screen.height - 60);
                break;
            }
}

static void cl_update_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_COMET** comets = objects->comets;
    
    for(int i = 0; i < objects->comet_size; i++)
        if(comets[i]->live)
        {            
            if(++comets[i]->frame_count >= comets[i]->frame_delay)
            {
                comets[i]->cur_frame += comets[i]->animation_direction;
                if(comets[i]->cur_frame >= comets[i]->max_frame)
                    comets[i]->cur_frame = 0;
                else if(comets[i]->cur_frame <= 0)
                    comets[i]->cur_frame = comets[i]->max_frame - 1;
                
                comets[i]->frame_count = 0;
            }
            
            comets[i]->x -= comets[i]->speed;
        }
}

static void cl_collide_comet(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_SHIP* ship = data->objects.ships[0];
    CLIENT_COMET** comets = objects->comets;
    
    for(int i = 0; i < objects->comet_size; i++)
        if(comets[i]->live)
        {            
            if((comets[i]->x - comets[i]->boundx) < (ship->x + ship->boundx) &&
                (comets[i]->x + comets[i]->boundx) > (ship->x - ship->boundx) &&
                (comets[i]->y - comets[i]->boundy) < (ship->y + ship->boundy) &&
                (comets[i]->y + comets[i]->boundy) > (ship->y - ship->boundy))
            {
                ship->lives--;
                comets[i]->live = false;
                
                cl_start_explosions(data, ship->x, ship->y);
                
                cl_play_sound(data, SAMPLE_BOOM);
            }
            else if(comets[i]->x < 0)
            {
                comets[i]->live = false;
                ship->lives--;
            }
        }
}

/************************************************************
 * EXPLOSION
 ***********************************************************/

static void cl_draw_explosions(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_EXPLOSION** explosions = objects->explosions;
    
    for(int i = 0; i < objects->explosion_size; i++)
        if(explosions[i]->live)
        {
            int fx = (explosions[i]->cur_frame % explosions[i]->animation_columns) * explosions[i]->frame_width;
            int fy = (explosions[i]->cur_frame / explosions[i]->animation_columns) * explosions[i]->frame_height;
            
            al_draw_bitmap_region(explosions[i]->image, fx, fy, explosions[i]->frame_width, explosions[i]->frame_height,
                    explosions[i]->x - explosions[i]->frame_width / 2, explosions[i]->y - explosions[i]->frame_height / 2, 0);
        }
}

static void cl_start_explosions(CLIENT_DATA* data, int x, int y)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_EXPLOSION** explosions = objects->explosions;
    
    for(int i = 0; i < objects->explosion_size; i++)
        if(!explosions[i]->live)
        {
            explosions[i]->live = true;
            explosions[i]->x = x;
            explosions[i]->y = y;
            break;
        }
}

static void cl_update_explosions(CLIENT_DATA* data)
{
    CLIENT_OBJECTS* objects = &data->objects;
    CLIENT_EXPLOSION** explosions = objects->explosions;
    
    for(int i = 0; i < objects->explosion_size; i++)
        if(explosions[i]->live)
            if(++explosions[i]->frame_count >= explosions[i]->frame_delay)
            {
                explosions[i]->cur_frame += explosions[i]->animation_direction;
                if(explosions[i]->cur_frame >= explosions[i]->max_frame)
                {
                    explosions[i]->cur_frame = 0;
                    explosions[i]->live = false;
                }
                
                explosions[i]->frame_count = 0;
            }
}

/************************************************************
 * STATISTIC
 ***********************************************************/

static void cl_draw_statistic(CLIENT_DATA* data)
{
    CLIENT_SHIP* ship = data->objects.ships[0];
    ALLEGRO_COLOR color = al_map_rgba_f(0.5, 0.0, 0.0, 0.2);
    ALLEGRO_COLOR color_text = al_map_rgba_f(0.5, 0.5, 0.5, 0.2);
    ALLEGRO_FONT* font = data->media.fonts[FONT_PS2P30]->al_font;
    
    char text[200] = {' ', '\0'};
    char num[5] = {'\0'};
    
    al_draw_text(font, color, al_get_text_width(font, text), 5, 0, "ЖИЗНИ:");
    strcat(text, "ЖИЗНИ:");
    al_draw_textf(font, color_text, al_get_text_width(font, text), 5, 0, "%d", ship->lives);
    sprintf(num, "%d", ship->lives);
    strcat(text, num);
    al_draw_text(font, color, al_get_text_width(font, text), 5, 0, " КОМЕТЫ:");
    strcat(text, " КОМЕТЫ:");
    al_draw_textf(font, color_text, al_get_text_width(font, text), 5, 0, "%d", ship->score);
}
