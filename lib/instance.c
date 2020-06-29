#include "instance.h"
#include "message.h"

CLIENT_SOUND* cl_create_sound(CLIENT_SOUND* sound, int instance_size)
{
    if(!sound)
    {
        sound = (CLIENT_SOUND*)malloc(sizeof(CLIENT_SOUND));
        show_message_error(sound, "Failed to allocate space for CLIENT_SOUND");
    }
    
    sound->instance_size = instance_size;
    sound->current_instance = -1;
    
    sound->instance = (CLIENT_SAMPLE_INSTANCE**)malloc(sizeof(CLIENT_SAMPLE_INSTANCE*) * instance_size);
    show_message_error(sound->instance, "Failed to allocate space for CLIENT_SAMPLE_INSTANCE collection");
    
    for(int i = 0; i < instance_size; i++)
    {
        sound->instance[i] = (CLIENT_SAMPLE_INSTANCE*)malloc(sizeof(CLIENT_SAMPLE_INSTANCE));
        show_message_error(sound->instance[i], "Failed to allocate space for CLIENT_SAMPLE_INSTANCE");
        
        sound->instance[i]->al_instance = NULL;
        sound->instance[i]->al_sample = NULL;
    }
    
    return sound;
}

void cl_free_sound(CLIENT_SOUND* sound)
{
    cl_destroy_sound(sound);
    free(sound);
}

void cl_destroy_sound(CLIENT_SOUND* sound)
{
    for(int i = 0; i < sound->instance_size; i++)
    {
        if(sound->instance[i]->al_instance)
            al_destroy_sample_instance(sound->instance[i]->al_instance);
        free(sound->instance[i]);
    }
    free(sound->instance);
}

void cl_add_instance(CLIENT_SAMPLE_INSTANCE* instance, ALLEGRO_SAMPLE* sample, ALLEGRO_PLAYMODE playmode, float gain)
{
    instance->playmode = playmode;
    instance->gain = gain;
    instance->al_sample = sample;
    instance->al_instance = al_create_sample_instance(instance->al_sample);
    al_set_sample_instance_playmode(instance->al_instance, instance->playmode);
    al_set_sample_instance_gain(instance->al_instance, instance->gain);
    al_attach_sample_instance_to_mixer(instance->al_instance, al_get_default_mixer());    
}