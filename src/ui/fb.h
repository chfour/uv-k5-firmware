#ifndef FB_H
#define FB_H

#include <stdint.h>

// helper macro to mark a row as dirty
#define FB_MARKDIRTY(row) do { gFramebufferAreas |= 1 << row; } while (0)

// the framebuffer. the dualtachyon source stored the
// first line (the "status line") as a separate array which caused me A Headache
extern uint8_t gFramebuffer[8][128];

// which rows are "dirty" and need to be updated, one bit per row
extern uint8_t gFramebufferAreas;

// write rows that need updating to the screen
void Framebuffer_UpdateScreen();

#endif
