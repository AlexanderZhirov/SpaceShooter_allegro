#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "common.h"
#include "message.h"

void cl_load_allegro_resources()
{
    show_message_error(al_init(), "Failed to initialize Allegro");
    show_message_error(al_init_primitives_addon(), "Failed to initialize addon primitives");
    show_message_error(al_init_image_addon(), "Failed to initialize addon image");
    show_message_error(al_install_keyboard(), "Failed to install keyboard");
    show_message_error(al_install_mouse(), "Failed to install mouse");
    show_message_error(al_init_font_addon(), "Failed to initialize addon font");
    show_message_error(al_init_ttf_addon(), "Failed to initialize addon ttf");
    show_message_error(al_install_audio(), "Failed to install audio");
    show_message_error(al_init_acodec_addon(), "Failed to initialize addon acodec");
    al_reserve_samples(20);
}

CLIENT_RESOURCE* cl_create_resource(CLIENT_RESOURCE* res, CLIENT_PARAMETRS parametrs)
{
    if(!res)
    {
        res = (CLIENT_RESOURCE*)malloc(sizeof(CLIENT_RESOURCE));
        show_message_error(res, "Failed to allocate space for CLIENT_RESOURCE");
    }
    
    cl_create_screen(&res->screen, parametrs.scale_factor, parametrs.fullscreen, parametrs.resolution, parametrs.width, parametrs.height, parametrs.FPS, parametrs.num_adapter);
    cl_create_timer(&res->timer, parametrs.FPS); 
    cl_create_event(&res->event, &res->timer, &res->screen);
    cl_create_media(&res->media, parametrs.bitmaps_size, parametrs.fonts_size, parametrs.samples_size);
    cl_create_pairing(&res->pairing, parametrs.pairing_size);
    cl_create_sound(&res->sound, parametrs.sound_size);
    
    return res;
}

void cl_destroy_resource(CLIENT_RESOURCE* res)
{
    cl_destroy_media(&res->media);
    cl_destroy_event(&res->event);
    cl_destroy_timer(&res->timer);
    cl_destroy_screen(&res->screen);
    cl_destroy_pairing(&res->pairing);
    cl_destroy_sound(&res->sound);
    free(res);
}

