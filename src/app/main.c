#include "app/main.h"
#include "app/listmenu.h"
#include "app/test.h"
#include "app/vfo.h"
#include "driver/keyboard.h"
#include <stdint.h>

volatile uint8_t gAppShouldUpdate = 1;

char* gAppList[APP_COUNT] = {
	"VFO",
	"test"
};

void App_Wait() {
	while (gAppShouldUpdate == 0) {} // wait
	// now gAppShouldUpdate != 0
	gAppShouldUpdate = 0; // reset it back to 0
}

void App_Main() {
	App_t current_app = APP_VFO;
	while (1) {
		switch (current_app) {
			case APP_VFO:
				App_Vfo_Main();
				break;
			case APP_TEST:
				App_Test_Main();
				break;
		}
		gKeyboardKeypress = KEY_NONE;
		App_Listmenu_Main(gAppList, APP_COUNT, &current_app);
	}
}
