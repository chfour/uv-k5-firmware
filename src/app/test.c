#include "app/test.h"
#include "app/main.h"
#include "driver/keyboard.h"
#include "ui/text.h"
#include "ui/fb.h"

void App_Test_Main() {
    Framebuffer_Clear();
    Text_DrawText(0, 4, "012345678901234567890"); // 3 pixels of empty space to the right i think
    Framebuffer_UpdateScreen();

    uint8_t state = 0;
    uint8_t state2 = 0;
    while (1) {
        //Framebuffer_Clear();
        //Keyboard_Poll();
        if (gKeyboardKeypress == KEY_SIDE1) {
            state ^= 1;
        }
        if (gKeyboardKeypress == KEY_MENU) {
            break;
        }
        gKeyboardKeypress = KEY_NONE;

        state2 ^= 1;

        uint8_t x = 0;
        x += Text_DrawChar(x, 5, Keyboard_ToChar(gKeyboardCurrentKey));
        x += Text_DrawChar(x, 5, gKeyboardPttState ? '1' : '0');
        x += Text_DrawText(x, 5, " state:");
        x += Text_DrawChar(x, 5, '0' + state);
        x += Text_DrawChar(x, 5, '0' + state2);
        FB_MARKDIRTY(5);
        Framebuffer_UpdateScreen();
        App_Wait();
    }
}
