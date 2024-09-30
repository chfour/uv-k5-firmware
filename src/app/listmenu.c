#include "app/main.h"
#include "driver/keyboard.h"
#include "ui/fb.h"
#include "ui/text.h"
#include "ui/font/font_terminus.h"
#include <stdint.h>

uint8_t App_Listmenu_Main(char** items, uint8_t count, uint8_t* cursor) {
    uint8_t prev_cursor = *cursor;
    while (1) {
        switch (gKeyboardKeypress) {
            case KEY_UP:
                if (*cursor == 0) *cursor = count - 1;
                else (*cursor)--;
                break;
            case KEY_DOWN:
                if (*cursor > count - 1) *cursor = 0;
                else (*cursor)++;
                break;
            case KEY_EXIT:
                gKeyboardKeypress = KEY_NONE;
            exit_restore:
                // restore old selection
                *cursor = prev_cursor;
                return 0;
            case KEY_MENU:
                gKeyboardKeypress = KEY_NONE;
                return 1;
            default:
                if (gKeyboardPttState) goto exit_restore; // evil goto!!!
                break;
        }
        gKeyboardKeypress = KEY_NONE;
        Framebuffer_Clear();
        for (uint8_t i = 0; i < count; i++) {
            Text_DrawChar(0, i, i == *cursor ? FONT_SYM_SELARROW : ' ');
            Text_DrawText(6, i, items[i]);
        }
        Framebuffer_UpdateScreen();
        App_Wait();
    }
}