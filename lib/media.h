/* 
 * File:   media.h
 * Author: Alexander Zhirov
 * Connection with me (telegram messanger): @alexanderzhirov
 *
 * Created on 2020.06.02
 */

#ifndef client_media
#define client_media

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

typedef struct cl_bitmap
{
    ALLEGRO_BITMAP* al_bitmap;
    int width;
    int height;
} CLIENT_BITMAP;

typedef struct cl_font
{
    ALLEGRO_FONT* al_font;
    int size;
} CLIENT_FONT;

typedef struct cl_sample
{
    ALLEGRO_SAMPLE* al_sapmle;
} CLIENT_SAMPLE;

typedef struct cl_media
{
    CLIENT_BITMAP** bitmaps;
    CLIENT_FONT** fonts;
    CLIENT_SAMPLE** samples;
    int size_bitmaps;
    int size_fonts;
    int size_samples;
} CLIENT_MEDIA;

CLIENT_MEDIA* cl_create_media(CLIENT_MEDIA* media, int size_bitmaps, int size_fonts, int size_samples);
void cl_free_media(CLIENT_MEDIA* media);
void cl_destroy_media(CLIENT_MEDIA* media);

/*
 * Создание коллекции изображений
 */
static CLIENT_BITMAP** cl_create_bitmaps(int size);
/*
 * Создание коллекции шрифтов
 */
static CLIENT_FONT** cl_create_fonts(int size);
/*
 * Создание коллекции аудио
 */
static CLIENT_SAMPLE** cl_create_samples(int size);
/*
 * Загрузка bitmap в коллекцию
 * keyBitmap - the name of the item enumeration in the array
 */
void cl_load_bitmap(CLIENT_MEDIA* media, int key_bitmap, const char* path);
/*
 * Загрузка font в коллекцию
 * keyFont - the name of the item enumeration in the array
 */
void cl_load_font(CLIENT_MEDIA* media, int key_font, const char* path, int size_font);
/*
 * Загрузка sample в коллекцию
 * keySample - the name of the item enumeration in the array
 */
void cl_load_sample(CLIENT_MEDIA* media, int key_sample, const char* path);

#endif
