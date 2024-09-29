#include <stdint.h>
#include <string.h>
#include "ui/font/font_terminus.h"
#include "ui/fb.h"

uint8_t Text_DrawChar(uint8_t x, uint8_t row, char chr) {
    if (chr != ' ') {
        memcpy(gFramebuffer[row] + x, Font_Terminus + ((chr - '!') * 5), 5);
    }

    return 5 + 1; // char width + 1px
}

uint8_t Text_DrawText(uint8_t x, uint8_t row, char* str) {
    while (*str != '\0') {
        x += Text_DrawChar(x, row, *str); // advance x by char width
        str++; // advance char*
    }
    FB_MARKDIRTY(row);
    return x;
}
