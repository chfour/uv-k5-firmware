#include "app/test.h"
#include "app/main.h"
#include "driver/keyboard.h"
#include "ui/text.h"
#include "ui/fb.h"
#include "app/listmenu.h"
#include "external/printf/printf.h"

void App_Test_Main() {
    Framebuffer_Clear();
    //Text_DrawText(0, 4, "012345678901234567890"); // 3 pixels of empty space to the right i think
    //Framebuffer_UpdateScreen();

    uint8_t state1 = 0;
    uint8_t state2 = 0;
    uint8_t menu_cursor = 0;
    uint8_t menu_return = 0;
    char buf[32];
    uint8_t x;
    while (1) {
        //Framebuffer_Clear();
        //Keyboard_Poll();
        if (gKeyboardKeypress == KEY_SIDE1) {
            state1 ^= 1;
        }
        if (gKeyboardKeypress == KEY_MENU) {
            break;
        }
        if (gKeyboardKeypress == KEY_EXIT) {
            char* items[] = {
                "0", "1", "2", "3", "4",
                "5", "6", "7", "8", "9",
                "10", "11", "12", "13", "14",
                "15"
            };
            gKeyboardKeypress = 0;
            menu_return = App_Listmenu_Main(items, 16, &menu_cursor);
            continue;
        }
        gKeyboardKeypress = KEY_NONE;

        state2 ^= 1;

        snprintf(buf, sizeof(buf), "menu: c:%2d ->%2d", menu_cursor, menu_return);
        Text_DrawText(0, 3, buf);
        snprintf(buf, sizeof(buf), "pressedfor: %3d", gKeyboardPressedFor);
        Text_DrawText(0, 4, buf);

        x = 0;
        x += Text_DrawChar(x, 5, Keyboard_ToChar(gKeyboardCurrentKey));
        x += Text_DrawChar(x, 5, gKeyboardPttState ? '1' : '0');
        x += Text_DrawText(x, 5, " state:");
        x += Text_DrawChar(x, 5, '0' + state1);
        x += Text_DrawChar(x, 5, '0' + state2);
        //FB_MARKDIRTY(5);

        Text_DrawText(0, 6, "EXIT goes into menu");
        Text_DrawText(0, 7, "SIDE1 toggles state1");

        Framebuffer_UpdateScreen();
        App_Wait();
    }
}
