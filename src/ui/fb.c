#include "ui/fb.h"
#include <stdint.h>
#include "driver/st7565.h"

uint8_t gFramebuffer[8][128];
uint8_t gFramebufferAreas = 0;

void Framebuffer_UpdateScreen() {
    uint8_t i = 0;
    // while gFramebufferAreas != 0 - so while there's still stuff to update
    while (gFramebufferAreas != 0) {
        // if the current bit is set
        if (gFramebufferAreas & 1) {
            ST7565_DrawLine(0, i, gFramebuffer[i], 128);
        }
        i++;
        gFramebufferAreas >>= 1;
    }
}
