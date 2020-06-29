#include <allegro5/allegro_native_dialog.h>
#include "message.h"

void show_message_error(bool result, const char* message)
{
    if(!result)
    {
        al_show_native_message_box(NULL, "Сообщение об ошибке", "Произошла ошибка",
                message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(EXIT_FAILURE);
    }
}
