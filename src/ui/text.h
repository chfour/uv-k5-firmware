#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <stdint.h>

// draw a single character. caution: this function will NOT mark a fb row as dirty
void Text_DrawChar(uint8_t x, uint8_t row, char chr);

// draw a string
void Text_DrawText(uint8_t x, uint8_t row, char* str);

#endif
