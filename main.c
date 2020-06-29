#include <stdio.h>
#include "game.h"

int main(int argc, char** argv)
{
    cl_load_allegro_resources();
    
    CLIENT_PARAMETRS parametrs =
    {
        // screen
        .num_adapter = 0,
        .scale_factor = 0.5,
        .fullscreen = false,
        .resolution = true,
        .width = 1280,
        .height = 540,
        .FPS = 60,
        // media
        .bitmaps_size = 8,
        .fonts_size = 4,
        .samples_size = 6,
        // interface
        .pairing_size = 13,
        .sound_size = 2,
        // network
        .enet_port = 9234,
        .enet_host = "127.0.0.1",
        // sound
        .effects_gain = 0.1,
        .music_gain = 0.1
    };
    
    CLIENT_DATA* data = cl_create_data(NULL, parametrs);

    cl_init_interfaces(&data->pairing);
    cl_load_media(&data->media);
    cl_init_media(data);
    
    al_start_timer(data->timer.al_timer);
    data->timer.time = al_current_time();
    
    srand(time(NULL));
    
    cl_change_state(data, MENU);
    
    while(!data->done)
    {
        al_wait_for_event(data->event.queue, &data->event.current);
        
        if(data->state == MENU)
            menu_handling(data);
        if(data->state == AUTORS)
            autors_handling(data);
        if(data->state == SINGLE)
            single_handling(data);
        if(data->state == NETWORKMODE)
            networkmode_handling(data);
        if(data->state == NETWORKCREATE)
            networkcreate_handling(data);
        if(data->state == NETWORKJOIN)
            networkjoin_handling(data);
        if(data->state == NETWORKPARTY)
            networkparty_handling(data);
        if(data->state == NETWORKLIST)
            networklist_handling(data);
        if(data->state == NETWORKGAME)
            networkgame_handling(data);
        if(data->state == NETWORKOUT)
            networkout_handling(data);
        if(data->state == PAUSE)
            pause_handling(data);
        if(data->state == GAMEOVER)
            gameover_handling(data);

        if(data->render && al_is_event_queue_empty(data->event.queue))
        {
            data->render = false;
            cl_pre_draw();
            
            if(data->state == MENU)
                menu_draw(data);
            if(data->state == AUTORS)
                autors_draw(data);
            if(data->state == SINGLE)
                single_draw(data);
            if(data->state == NETWORKMODE)
                networkmode_draw(data);
            if(data->state == NETWORKCREATE)
                networkcreate_draw(data);
            if(data->state == NETWORKJOIN)
                networkjoin_draw(data);
            if(data->state == NETWORKPARTY)
                networkparty_draw(data);
            if(data->state == NETWORKLIST)
                networklist_draw(data);
            if(data->state == NETWORKGAME)
                networkgame_draw(data);
            if(data->state == NETWORKOUT)
                networkout_draw(data);
            if(data->state == PAUSE)
                pause_draw(data);
            if(data->state == GAMEOVER)
                gameover_draw(data);
            
            cl_post_draw();
        }
    }
    
    cl_destroy_data(data);
    
    return EXIT_SUCCESS;
}
