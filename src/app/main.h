#ifndef APP_MAIN_H
#define APP_MAIN_H

#include <stdint.h>

// non-zero if the app should update
extern volatile uint8_t gAppShouldUpdate;

// wait for any new events
void App_Wait();

// app manager main loop
void App_Main();

#endif
