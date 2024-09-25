#include <stdint.h>
#include <string.h>
#include "ui/font/font_terminus.h"
#include "driver/st7565.h"

void Text_DrawChar(uint8_t x, uint8_t row, char chr) {
    if (chr == ' ') return;
    memcpy(gFrameBuffer[row] + x, Font_Terminus + ((chr - '!') * 5), 5);
}

uint8_t Text_DrawText(uint8_t x, uint8_t row, char* str) {
    while (*str != '\0') {
        Text_DrawChar(x, row, *str);
        x += 5 + 1; // advance x by char width + 1px
        str++; // advance char*
    }
    return x;
}
