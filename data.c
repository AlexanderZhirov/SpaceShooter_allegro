#include "common.h"
#include "lib/message.h"

CLIENT_DATA* cl_create_data(CLIENT_DATA* data, CLIENT_PARAMETRS parametrs)
{
    if(!data)
    {
        data = (CLIENT_DATA*)malloc(sizeof(CLIENT_DATA));
        show_message_error(data, "Failed to allocate space for CLIENT_DATA");
    }
    
    cl_create_screen(&data->screen, parametrs.scale_factor, parametrs.fullscreen, parametrs.resolution, parametrs.width, parametrs.height, parametrs.FPS, parametrs.num_adapter);
    cl_create_timer(&data->timer, parametrs.FPS); 
    cl_create_event(&data->event, &data->timer, &data->screen);
    cl_create_media(&data->media, parametrs.bitmaps_size, parametrs.fonts_size, parametrs.samples_size);
    cl_create_pairing(&data->pairing, parametrs.pairing_size);
    cl_create_sound(&data->sound, parametrs.sound_size);
    
    for(int i = 0; i < 7; i++)
    {
        data->keys[i] = false;
    }
    
    data->pause = false;
    data->done = false;
    data->render = false;
    data->state = 0;
    data->enet.port = parametrs.enet_port;
    strncpy(data->enet.host, parametrs.enet_host, 20);
    data->settings.effects_gain = parametrs.effects_gain;
    data->settings.music_gain = parametrs.music_gain;
    
    return data;
}

void cl_destroy_data(CLIENT_DATA* data)
{
    cl_destroy_media(&data->media);
    cl_destroy_event(&data->event);
    cl_destroy_timer(&data->timer);
    cl_destroy_screen(&data->screen);
    cl_destroy_pairing(&data->pairing);
    cl_destroy_sound(&data->sound);
    free(data);
}