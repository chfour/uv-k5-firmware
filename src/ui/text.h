#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>

void Text_DrawChar(uint8_t x, uint8_t row, char chr);
void Text_DrawText(uint8_t x, uint8_t row, char* str);

#endif
