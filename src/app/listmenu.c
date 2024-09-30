#include "app/main.h"
#include "driver/keyboard.h"
#include "ui/fb.h"
#include "ui/text.h"
#include "ui/font/font_terminus.h"
#include "external/printf/printf.h"
#include <stdint.h>

uint8_t App_Listmenu_Main(char** items, uint8_t count, uint8_t* cursor) {
    uint8_t prev_cursor = *cursor;
    uint8_t per_screen = count < 7 ? count : 7;
    uint8_t scroll_offset = 0;
    char buf[16];
    while (1) {
        switch (gKeyboardKeypress) {
            case KEY_UP:
                if (*cursor == 0) *cursor = count - 1;
                else (*cursor)--;
                break;
            case KEY_DOWN:
                if (*cursor >= count - 1) *cursor = 0;
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
        // move scroll_offset if necessary
        if (count > 7) {
            // scrolling down
            if (*cursor >= scroll_offset + per_screen - 1 && scroll_offset < count - per_screen) {
                if (*cursor >= count - 1) scroll_offset = count - per_screen;
                else scroll_offset = *cursor - per_screen + 2;
                //scroll_offset++;
            }
            // scrolling up
            if (*cursor < scroll_offset + 1 && scroll_offset > 0) {
                if (*cursor < 2) scroll_offset = 0;
                else scroll_offset = *cursor - 1;
                //scroll_offset--;
            }
        }
        snprintf(buf, sizeof(buf), "% 2d/% 2d", (*cursor) + 1, count);
        Text_DrawText(0, 0, buf);
        // draw list
        uint8_t real_i;
        for (uint8_t i = 0; i < per_screen; i++) {
            real_i = i + scroll_offset;
            Text_DrawChar(0, i+1, real_i == *cursor ? FONT_SYM_ARROWR : ' ');
            Text_DrawText(6, i+1, items[real_i]);
        }
        // show there's more above/below
        if (scroll_offset > 0)
            Text_DrawChar(127-5, 0, FONT_SYM_ARROWU);
        if (count > 7 && scroll_offset < count - per_screen) {
            Text_DrawChar(127-5, 7, FONT_SYM_ARROWD);
            FB_MARKDIRTY(7);
        }
        Framebuffer_UpdateScreen();
        App_Wait();
    }
}