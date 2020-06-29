/* 
 * File:   instance.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.28
 */

#ifndef client_instance
#define client_instance

#include <allegro5/allegro_audio.h>


typedef struct cl_sample_instance
{
    ALLEGRO_SAMPLE_INSTANCE* al_instance;
    ALLEGRO_PLAYMODE playmode;
    ALLEGRO_SAMPLE* al_sample;
    float gain;
} CLIENT_SAMPLE_INSTANCE;

typedef struct cl_sound
{
    CLIENT_SAMPLE_INSTANCE** instance;
    int instance_size;
    int current_instance;
} CLIENT_SOUND;

CLIENT_SOUND* cl_create_sound(CLIENT_SOUND* sound, int instance_size);
void cl_free_sound(CLIENT_SOUND* sound);
void cl_destroy_sound(CLIENT_SOUND* sound);

void cl_add_instance(CLIENT_SAMPLE_INSTANCE* instance, ALLEGRO_SAMPLE* sample, ALLEGRO_PLAYMODE playmode, float gain);

#endif



