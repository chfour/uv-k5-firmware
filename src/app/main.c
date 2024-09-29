#include "app/main.h"
#include "driver/keyboard.h"
#include "driver/systick.h"
#include "ui/fb.h"
#include "ui/text.h"
#include <stdint.h>

volatile uint8_t gAppShouldUpdate = 1;

void App_Wait() {
	while (gAppShouldUpdate == 0) {} // wait
	// now gAppShouldUpdate != 0
	gAppShouldUpdate = 0; // reset it back to 0
}

void App_Main() {
	for (uint8_t i = 0; i < 128; i++) {
		gFramebuffer[6][i] = (i & 2) ? 0x33 : 0xCC; // checkerboard pattern
	}
	FB_MARKDIRTY(6);

	Text_DrawText(0, 0, "row 0");
	Text_DrawText(5, 1, "row 1");
	Text_DrawText(0, 3, "test TEST 123 !\"#~");
	Text_DrawText(0, 7, "row 7");
	Framebuffer_UpdateScreen();
	Systick_DelayMs(1000);
	Text_DrawText(0, 4, "012345678901234567890"); // 3 pixels of empty space to the right i think
	Framebuffer_UpdateScreen();

	uint8_t state = 0;
	uint8_t state2 = 0;
	while (1) {
		//Framebuffer_Clear();
		//Keyboard_Poll();
		if (gKeyboardKeypress == KEY_MENU) {
			state ^= 1;
		}
		gKeyboardKeypress = KEY_NONE;

		state2 ^= 1;

		uint8_t x = 0;
		x += Text_DrawChar(x, 5, Keyboard_ToChar(gKeyboardCurrentKey));
		x += Text_DrawChar(x, 5, gKeyboardPttState ? '1' : '0');
		x += Text_DrawText(x, 5, " state:");
		x += Text_DrawChar(x, 5, '0' + state);
		x += Text_DrawChar(x, 5, '0' + state2);
		FB_MARKDIRTY(5);
		Framebuffer_UpdateScreen();
		App_Wait();
	}
}
