#ifndef APP_LISTMENU_H
#define APP_LISTMENU_H

#include <stdint.h>

// a scrolling list menu. items is a list of strings to choose from, count is the number of items in that list,
// cursor is a pointer to the variable storing the selection.
// returns 0 and restores the previous selection if KEY_EXIT or PTT was pressed, 1 if KEY_MENU was used
uint8_t App_Listmenu_Main(char** items, uint8_t count, uint8_t* cursor);

#endif
