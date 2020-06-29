/* 
 * File:   objects.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.03
 */

#ifndef client_objects
#define client_objects

#include <stdbool.h>
#include <allegro5/allegro.h>

typedef struct cl_ship
{
    int ID;
    int x;
    int y;
    int lives;
    int speed;
    int boundx;
    int boundy;
    int score;
    bool active;
    
    int max_frame;
    int cur_frame;
    int frame_count;
    int frame_delay;
    int frame_width;
    int frame_height;
    int animation_columns;
    int animation_direction;
    
    int animation_row;
    
    ALLEGRO_BITMAP *image;
} CLIENT_SHIP;

typedef struct cl_bullet
{
    int ID;
    int x;
    int y;
    bool live;
    int speed;
    bool active;
} CLIENT_BULLET;

typedef struct cl_comet
{
    int ID;
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;
    
    int max_frame;
    int cur_frame;
    int frame_count;
    int frame_delay;
    int frame_width;
    int frame_height;
    int animation_columns;
    int animation_direction;
    
    ALLEGRO_BITMAP *image;
} CLIENT_COMET;

typedef struct cl_explosion
{
    int x;
    int y;
    bool live;
    
    int max_frame;
    int cur_frame;
    int frame_count;
    int frame_delay;
    int frame_width;
    int frame_height;
    int animation_columns;
    int animation_direction;
    
    ALLEGRO_BITMAP *image;
} CLIENT_EXPLOSION;

typedef struct cl_objects
{
    CLIENT_SHIP** ships;
    int ship_size;
    CLIENT_BULLET** bullets;
    int bullet_size;
    CLIENT_COMET** comets;
    int comet_size;
    CLIENT_EXPLOSION** explosions;
    int explosion_size;
} CLIENT_OBJECTS;

CLIENT_OBJECTS* cl_create_objects(CLIENT_OBJECTS* data, int ship_size, int bullet_size, int comet_size, int explosion_size);
void cl_free_objects(CLIENT_OBJECTS* objects);
void cl_destroy_objects(CLIENT_OBJECTS* objects);

static CLIENT_SHIP** cl_create_ships(int size);
static CLIENT_BULLET** cl_create_bullets(int size);
static CLIENT_COMET** cl_create_comets(int size);
static CLIENT_EXPLOSION** cl_create_explosions(int size);

void cl_init_ships(CLIENT_OBJECTS* objects, int key_ship, int ID, int animation_columns, int animation_direction, int animation_row, int boundx, int boundy, int cur_frame,
        int frame_count, int frame_delay, int frame_height, int frame_width, ALLEGRO_BITMAP* image, int lives, int max_frame, int score, int speed, int x, int y);
void cl_init_bullets(CLIENT_OBJECTS* objects, int key_bullet, int ID, int speed, int x, int y);
void cl_init_comets(CLIENT_OBJECTS* objects, int key_comet, int ID, int animation_columns, int animation_direction, int boundx, int boundy, int cur_frame,
        int frame_count, int frame_delay, int frame_height, int frame_width, ALLEGRO_BITMAP* image, int max_frame, int speed, int x, int y);
void cl_init_explosions(CLIENT_OBJECTS* objects, int key_explosion, int animation_columns, int animation_direction, int cur_frame,
        int frame_count, int frame_delay, int frame_height, int frame_width, ALLEGRO_BITMAP* image, int max_frame, int x, int y);

#endif
