#ifndef APP_MAIN_H
#define APP_MAIN_H

#include <stdint.h>

#define APP_COUNT 2

// list of "apps"
typedef enum App_t {
    APP_VFO = 0,
    APP_TEST = 1
} App_t;

// a list of app names
extern char* gAppList[APP_COUNT];

// non-zero if the app should update
extern volatile uint8_t gAppShouldUpdate;

// wait for any new events
void App_Wait();

// app manager main loop
void App_Main();

#endif
