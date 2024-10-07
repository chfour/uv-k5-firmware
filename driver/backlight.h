#ifndef DRIVER_BACKLIGHT_H
#define DRIVER_BACKLIGHT_H

#include <stdint.h>

extern volatile uint8_t gBacklightTimer;

// turn backlight on
void Backlight_On();

// backlight scheduler task to be run every 100ms
void Backlight_SchedTask();

#endif
