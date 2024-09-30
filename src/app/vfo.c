#include "app/vfo.h"
#include "app/main.h"
#include "driver/keyboard.h"
#include "ui/fb.h"
#include "ui/text.h"

void App_Vfo_Main() {
    while (1) {
        if (gKeyboardKeypress == KEY_MENU) {
            break;
        }
        gKeyboardKeypress = KEY_NONE;
        Framebuffer_Clear();
        Text_DrawText(0, 2, "hello from vfo.c!");
        Framebuffer_UpdateScreen();
        App_Wait();
    }
}
