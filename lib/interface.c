#include "interface.h"
#include "message.h"

CLIENT_PAIRING* cl_create_pairing(CLIENT_PAIRING* pairing, int interface_size)
{
    if(!pairing)
    {
        pairing = (CLIENT_PAIRING*)malloc(sizeof(CLIENT_PAIRING));
        show_message_error(pairing, "Failed to allocate space for CLIENT_PAIRING");
    }
    
    pairing->interface_size = interface_size;
    
    if(interface_size)
    {
        pairing->interface = (CLIENT_INTERFACE**)malloc(sizeof(CLIENT_INTERFACE*) * interface_size);
        show_message_error(pairing->interface, "Failed to allocate space for CLIENT_INTERFACE collection");
        
        for(int i = 0; i < interface_size; i++)
            pairing->interface[i] = NULL;
    }
    else
        pairing->interface = NULL;
    
    return pairing;
}

CLIENT_INTERFACE* cl_create_interface(int background_size, int button_size, int field_size)
{
    CLIENT_INTERFACE* interface = (CLIENT_INTERFACE*)malloc(sizeof(CLIENT_INTERFACE));
    show_message_error(interface, "Failed to allocate space for CLIENT_INTERFACE");
    
    interface->header.al_font = NULL;
    interface->background_size = background_size;
    interface->button_size = button_size;
    interface->field_size = field_size;
    interface->selected = SELECTED_BUTTON;
    interface->list.al_font = NULL;
    
    if(background_size)
        interface->background = cl_create_background_pages(background_size);
    else
        interface->background = NULL;
    
    if(button_size)
        interface->button = cl_create_buttons(button_size);
    else
        interface->button = NULL;
    
    if(field_size)
        interface->field = cl_create_fields(field_size);
    else
        interface->field = NULL;

    return interface;
}

static CLIENT_BACKGROUND_PAGE** cl_create_background_pages(int size)
{
    CLIENT_BACKGROUND_PAGE** background = (CLIENT_BACKGROUND_PAGE**)malloc(sizeof(CLIENT_BACKGROUND_PAGE*) * size);
    show_message_error(background, "Failed to allocate space for CLIENT_BACKGROUND_PAGE collection");
    
    for(int i = 0; i < size; i++)
    {
        background[i] = (CLIENT_BACKGROUND_PAGE*)malloc(sizeof(CLIENT_BACKGROUND_PAGE));
        show_message_error(background[i], "Failed to allocate space for CLIENT_BACKGROUND_PAGE");
    }
    
    return background;
}

static CLIENT_BUTTON** cl_create_buttons(int size)
{
    CLIENT_BUTTON** buttons = (CLIENT_BUTTON**)malloc(sizeof(CLIENT_BUTTON*) * size);
    show_message_error(buttons, "Failed to allocate space for CLIENT_BUTTON collection");
    
    for(int i = 0; i < size; i++)
    {
        buttons[i] = (CLIENT_BUTTON*)malloc(sizeof(CLIENT_BUTTON));
        show_message_error(buttons[i], "Failed to allocate space for CLIENT_BUTTON");
        buttons[i]->al_font = NULL;
    }
    
    return buttons;
}

static CLIENT_FIELD** cl_create_fields(int size)
{
    CLIENT_FIELD** fields = (CLIENT_FIELD**)malloc(sizeof(CLIENT_FIELD*) * size);
    show_message_error(fields, "Failed to allocate space for CLIENT_FIELD collection");
    
    for(int i = 0; i < size; i++)
    {
        fields[i] = (CLIENT_FIELD*)malloc(sizeof(CLIENT_FIELD));
        show_message_error(fields[i], "Failed to allocate space for CLIENT_FIELD");
        fields[i]->al_font = NULL;
    }
    
    return fields;
}

void cl_change_selected(CLIENT_INTERFACE* interface)
{
    if(interface->selected == SELECTED_BUTTON)
    {
        interface->selected = SELECTED_FIELD;
        for(int i = 0; i < interface->button_size; i++)
            if(interface->button[i]->selected)
                interface->button[i]->selected = false;
    }
    else if(interface->selected == SELECTED_FIELD)
    {
        interface->selected = SELECTED_BUTTON;
        for(int i = 0; i < interface->field_size; i++)
            if(interface->field[i]->selected)
            {
                interface->field[i]->selected = false;
                interface->field[i]->enter = false;
            }
    }
}

void cl_free_pairing(CLIENT_PAIRING* pairing)
{
    cl_destroy_pairing(pairing);
    free(pairing);
}

void cl_destroy_pairing(CLIENT_PAIRING* pairing)
{
    for(int i = 0; i < pairing->interface_size; i++)
    {
        if(pairing->interface[i])
        {
            cl_destroy_interface(pairing->interface[i]);
        }
    }
    
    free(pairing->interface);
}

static void cl_destroy_interface(CLIENT_INTERFACE* interface)
{
    if(interface->background_size > 0)
    {
        for(int i = 0; i < interface->background_size; i++)
            free(interface->background[i]);
        free(interface->background);
    }
    
    if(interface->button_size)
    {
        for(int i = 0; i < interface->button_size; i++)
            free(interface->button[i]);
        free(interface->button);
    }
    
    if(interface->field_size)
    {
        for(int i = 0; i < interface->field_size; i++)
            free(interface->field[i]);
        free(interface->field);
    }
    
    free(interface);
}


void cl_add_interface_header(CLIENT_HEADER* header, ALLEGRO_FONT* font, int x, int y, const char* text)
{
    header->al_font = font;
    header->size = al_get_text_width(font, text);
    strncpy(header->text, text, 100);
    header->x = x;
    header->y = y;
}

void cl_add_interface_background(CLIENT_BACKGROUND_PAGE* background, CLIENT_BITMAP* bitmap, int dir_x, int dir_y, int vel_x, int vel_y, int x, int y)
{
    background->bitmap = bitmap;
    background->dir_x = dir_x;
    background->dir_y = dir_y;
    background->vel_x = vel_x;
    background->vel_y = vel_y;
    background->x = x;
    background->y = y;
}

void cl_add_interface_button(CLIENT_BUTTON* button, ALLEGRO_FONT* font, const char* text, int t_x, int t_y, int b_sx, int b_sy, int b_dx, int b_dy)
{
    button->al_font = font;
    strncpy(button->text, text, 100);
    button->t_size = al_get_text_width(font, text);
    button->t_x = t_x;
    button->t_y = t_y;
    button->selected = false;
    button->active = false;
    button->b_sx = b_sx;
    button->b_sy = b_sy;
    button->b_dx = b_dx;
    button->b_dy = b_dy;
}

void cl_add_interface_field(CLIENT_FIELD* field, ALLEGRO_FONT* font, int font_height, const char* description, int d_x, int d_y, int f_sx, int f_sy, int f_dx, int f_dy)
{
    field->al_font = font;
    strncpy(field->description, description, 100);
    field->char_size = al_get_text_width(font, "_");
    field->char_number = 0;
    field->d_x = d_x;
    field->d_y = d_y;
    field->f_sx = f_sx;
    field->f_sy = f_sy - font_height * 0.4;
    field->f_dx = f_dx + al_get_text_width(font, "_") * 20;
    field->f_dy = f_dy + font_height * 0.4;
    field->ft_x = f_sx + al_get_text_width(font, "_") * 0.4;
    field->ft_y = f_sy;
    field->selected = false;
    field->enter = false;
}

void cl_add_list_item(CLIENT_LIST_ITEM* item, int sx_item, int sy_item, int dx_item, int dy_item, int x_h, int y_h, int x_status, int y_status, int r_status)
{
    item->sx_item = sx_item;
    item->sy_item = sy_item;
    item->dx_item = dx_item;
    item->dy_item = dy_item;
    item->x_h = x_h;
    item->y_h = y_h;    
    item->x_status = x_status;
    item->y_status = y_status;
    item->r_status = r_status;
    item->selected = false;
    item->active = false;
}
