#include "media.h"
#include "message.h"
#include "screen.h"

CLIENT_MEDIA* cl_create_media(CLIENT_MEDIA* media, int size_bitmaps, int size_fonts, int size_samples)
{
    if(!media)
    {
        media = (CLIENT_MEDIA*)malloc(sizeof(CLIENT_MEDIA));
        show_message_error(media, "Failed to allocate space for CLIENT_MEDIA");
    }
    
    media->size_bitmaps = size_bitmaps;
    media->size_fonts = size_fonts;
    media->size_samples = size_samples;
    
    media->bitmaps = cl_create_bitmaps(media->size_bitmaps);
    media->fonts = cl_create_fonts(media->size_fonts);
    media->samples = cl_create_samples(media->size_samples);
    
    return media;
}

static CLIENT_BITMAP** cl_create_bitmaps(int size)
{
    CLIENT_BITMAP** bitmaps = (CLIENT_BITMAP**)malloc(sizeof(CLIENT_BITMAP*) * size);
    show_message_error(bitmaps, "Failed to allocate space for CLIENT_BITMAP collection");
    
    for(int i = 0; i < size; i++)
    {
        bitmaps[i] = (CLIENT_BITMAP*)malloc(sizeof(CLIENT_BITMAP));
        show_message_error(bitmaps[i], "Failed to allocate space for CLIENT_BITMAP");
        bitmaps[i]->al_bitmap = NULL;
    }
    
    return bitmaps;
}

static CLIENT_FONT** cl_create_fonts(int size)
{
    CLIENT_FONT** fonts = (CLIENT_FONT**)malloc(sizeof(CLIENT_FONT*) * size);
    show_message_error(fonts, "Failed to allocate space for CLIENT_FONT collection");
    
    for(int i = 0; i < size; i++)
    {
        fonts[i] = (CLIENT_FONT*)malloc(sizeof(CLIENT_FONT));
        show_message_error(fonts[i], "Failed to allocate space for CLIENT_FONT");
        fonts[i]->al_font = NULL;
    }
    
    return fonts;
}

static CLIENT_SAMPLE** cl_create_samples(int size)
{
    CLIENT_SAMPLE** samples = (CLIENT_SAMPLE**)malloc(sizeof(CLIENT_SAMPLE*) * size);
    show_message_error(samples, "Failed to allocate space for CLIENT_SAMPLE collection");
    
    for(int i = 0; i < size; i++)
    {
        samples[i] = (CLIENT_SAMPLE*)malloc(sizeof(CLIENT_SAMPLE));
        show_message_error(samples[i], "Failed to allocate space for CLIENT_SAMPLE");
        samples[i]->al_sapmle = NULL;
    }
    
    return samples;
}

void cl_free_media(CLIENT_MEDIA* media)
{
    cl_destroy_media(media);
    free(media);
}

void cl_destroy_media(CLIENT_MEDIA* media)
{
    for(int i = 0; i < media->size_bitmaps; i++)
    {
        if(media->bitmaps[i]->al_bitmap)
            al_destroy_bitmap(media->bitmaps[i]->al_bitmap);
        free(media->bitmaps[i]);
    }
    free(media->bitmaps);

    for(int i = 0; i < media->size_fonts; i++)
    {
        if(media->fonts[i]->al_font)
            al_destroy_font(media->fonts[i]->al_font);
        free(media->fonts[i]);
    }
    free(media->fonts);

    for(int i = 0; i < media->size_samples; i++)
    {
        if(media->samples[i]->al_sapmle)
            al_destroy_sample(media->samples[i]->al_sapmle);
        free(media->samples[i]);
    }
    free(media->samples);
}

void cl_load_bitmap(CLIENT_MEDIA* media, int key_bitmap, const char* path)
{
    if(media->size_bitmaps > key_bitmap && key_bitmap >= 0)
    {
        if(!media->bitmaps[key_bitmap]->al_bitmap)
        {            
            media->bitmaps[key_bitmap]->al_bitmap = al_load_bitmap(path);
            show_message_error(media->bitmaps[key_bitmap]->al_bitmap, "Failed to load bitmap to collection");
            media->bitmaps[key_bitmap]->width = al_get_bitmap_width(media->bitmaps[key_bitmap]->al_bitmap);
            media->bitmaps[key_bitmap]->height = al_get_bitmap_height(media->bitmaps[key_bitmap]->al_bitmap);
        }
    }
}

void cl_load_font(CLIENT_MEDIA* media, int key_font, const char* path, int size_font)
{
    if(media->size_fonts > key_font && key_font >= 0)
    {
        if(!media->fonts[key_font]->al_font)
        {
            CLIENT_SCREEN screen = cl_get_screen(NULL);

            media->fonts[key_font]->al_font = al_load_font(path, size_font * screen.scale_factor, 0);
            show_message_error(media->fonts[key_font]->al_font, "Failed to load font to collection");
            media->fonts[key_font]->size = size_font * screen.scale_factor;
        }
    }
}

void cl_load_sample(CLIENT_MEDIA* media, int key_sample, const char* path)
{
    if(media->size_samples > key_sample && key_sample >= 0)
    {
        if(!media->samples[key_sample]->al_sapmle)
        {
            media->samples[key_sample]->al_sapmle = al_load_sample(path);
            show_message_error(media->samples[key_sample]->al_sapmle, "Failed to load sample to collection");
        }
    }
}
