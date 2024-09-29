#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <stdint.h>

// draw a single character. returns char width in pixels. caution: this function will NOT mark a fb row as dirty
uint8_t Text_DrawChar(uint8_t x, uint8_t row, char chr);

// draw a string. returns string width in pixels
uint8_t Text_DrawText(uint8_t x, uint8_t row, char* str);

#endif
