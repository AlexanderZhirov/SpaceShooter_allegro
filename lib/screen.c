#include "screen.h"
#include "message.h"

CLIENT_SCREEN* cl_create_screen(CLIENT_SCREEN* screen, float scale_factor, bool fullscreen, bool resolution, int w, int h, int FPS, int num_adapter)
{
    if(!screen)
    {
        screen = (CLIENT_SCREEN*)malloc(sizeof(CLIENT_SCREEN));
        show_message_error(screen, "Failed to allocate space for CLIENT_SCREEN");
    }
    
    CLIENT_ADAPTER adapter = cl_get_info_adapter(num_adapter);
    
    screen->FPS = FPS;
    screen->monitor_width = adapter.width;
    screen->monitor_height = adapter.height;
    screen->display_diagonal = (float)adapter.width / adapter.height;
    screen->fullscreen = fullscreen;
    
    if(resolution)
    {
        if(w < 640 || h < 400 || ((float)w / h) < 1.0)
        {
            screen->width = screen->buffer_width = 640;
            screen->height = screen->buffer_height = 400;
        }
        else
        {
            screen->width = screen->buffer_width = w;
            screen->height = screen->buffer_height = h;
        }
        
        screen->buffer_diagonal = (float)screen->buffer_width / screen->buffer_height;
        
        if(screen->fullscreen)
        {
            if(screen->display_diagonal > screen->buffer_diagonal)
            {
                screen->own_diagonal = true;
                screen->scale_factor = (float)screen->buffer_width / screen->monitor_width;
                screen->display_width = screen->monitor_width * ((float)screen->buffer_height / screen->monitor_height);
                screen->display_height = screen->buffer_height;
                screen->pos_x = (screen->display_width / 2) - (screen->buffer_width / 2);
                screen->pos_y = 0;
            }
            else if(screen->display_diagonal < screen->buffer_diagonal)
            {
                screen->own_diagonal = false;
                screen->scale_factor = (float)screen->buffer_height / screen->monitor_height;
                screen->display_width = screen->buffer_width;
                screen->display_height = screen->monitor_height * ((float)screen->buffer_width / screen->monitor_width);
                screen->pos_x = 0;
                screen->pos_y = (screen->display_height / 2) - (screen->buffer_height / 2);
            }
            else
            {
                screen->own_diagonal = true;
                screen->scale_factor = (float)screen->buffer_width / screen->monitor_width;
                screen->display_width = screen->buffer_width;
                screen->display_height = screen->buffer_height;
                screen->pos_x = 0;
                screen->pos_y = 0;
            }
        }
        else
        {
            if(screen->display_diagonal >= screen->buffer_diagonal)
                screen->scale_factor = (float)screen->buffer_width / screen->monitor_width;
            else if(screen->display_diagonal < screen->buffer_diagonal)
                screen->scale_factor = (float)screen->buffer_height / screen->monitor_height;
            
            screen->own_diagonal = true;
            screen->pos_x = 0;
            screen->pos_y = 0;
            screen->display_width = screen->buffer_width;
            screen->display_height = screen->buffer_height;
        }
    }
    else
    {
        if((float)scale_factor >= 0.1 && (float)scale_factor < 1.0)
            screen->scale_factor = scale_factor;
        else if((float)scale_factor >= 1.0)
        {
            screen->fullscreen = true;
            screen->scale_factor = 1.0;
        }
        else
            screen->scale_factor = 0.5;
        
        screen->own_diagonal = true;
        screen->width = screen->buffer_width = screen->display_width = screen->monitor_width * screen->scale_factor;
        screen->height = screen->buffer_height = screen->display_height = screen->monitor_height * screen->scale_factor;
        screen->pos_x = 0;
        screen->pos_y = 0;
    }
    
    if(screen->fullscreen)
    {
        screen->scale_factor_x = (float)screen->monitor_width / screen->display_width;
        screen->scale_factor_y = (float)screen->monitor_height / screen->display_height;
    }
    
    // Create allegro display
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    
    if(screen->fullscreen)
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    
    screen->display = al_create_display(screen->display_width, screen->display_height);
    show_message_error(screen->display, "Failed to create Allegro display");
    screen->buffer = al_create_bitmap(screen->buffer_width, screen->buffer_height);
    show_message_error(screen->buffer, "Failed to create Allegro buffer");
    
    if(screen->fullscreen)
    {
        ALLEGRO_TRANSFORM t;
        al_identity_transform(&t);
        al_scale_transform(&t, screen->scale_factor_x, screen->scale_factor_y);
        al_use_transform(&t);
    }
    
    cl_get_screen(screen);
    
    return screen;
}

static CLIENT_ADAPTER cl_get_info_adapter(int num_adapter)
{
    CLIENT_ADAPTER adapter;
    const int num_monitor = al_get_num_video_adapters();
    ALLEGRO_MONITOR_INFO m_i;
    int cur_adapter;
    
    show_message_error(num_monitor, "Could not find connected monitors");
    
    if(num_adapter != -1 && num_adapter <= num_monitor - 1)
        cur_adapter = num_adapter;
    else
        cur_adapter = 0;
    
    al_get_monitor_info(cur_adapter, &m_i);
    
    adapter.width = m_i.x2 - m_i.x1;
    adapter.height = m_i.y2 - m_i.y1;
    
    return adapter;
}

void cl_free_screen(CLIENT_SCREEN* screen)
{
    cl_destroy_screen(screen);
    free(screen);
}

void cl_destroy_screen(CLIENT_SCREEN* screen)
{
    al_destroy_bitmap(screen->buffer);
    al_destroy_display(screen->display);
}

CLIENT_SCREEN cl_get_screen(CLIENT_SCREEN* screen)
{
    static CLIENT_SCREEN screen_info;
    
    if(screen)
    {
        screen_info = *screen;
    }
    
    return screen_info;
}

void cl_pre_draw()
{
    CLIENT_SCREEN screen = cl_get_screen(NULL);
    
    al_set_target_bitmap(screen.buffer);
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void cl_post_draw()
{
    CLIENT_SCREEN screen = cl_get_screen(NULL);
    
    al_set_target_backbuffer(screen.display);
    al_draw_scaled_bitmap(screen.buffer, 0, 0, screen.buffer_width, screen.buffer_height, screen.pos_x, screen.pos_y, screen.buffer_width, screen.buffer_height, 0);
    al_flip_display();
}
