#include "app/main.h"
#include "driver/keyboard.h"
#include "driver/systick.h"
#include "ui/fb.h"
#include "ui/text.h"
#include <stdint.h>

void App_Main(void) {
	for (uint8_t i = 0; i < 128; i++) {
		gFramebuffer[6][i] = (i & 2) ? 0x33 : 0xCC; // checkerboard pattern
	}
	FB_MARKDIRTY(6);

	Text_DrawText(0, 0, "row 0");
	Text_DrawText(5, 1, "row 1");
	Text_DrawText(0, 3, "test TEST 123 !\"#~");
	Text_DrawText(0, 7, "row 7");
	Framebuffer_UpdateScreen();
	Systick_DelayMs(2000);
	Text_DrawText(0, 4, "012345678901234567890"); // 3 pixels of empty space to the right i think
	Framebuffer_UpdateScreen();

	KEY_Code_t keycode;
	while (1) {
		//Framebuffer_Clear();
		keycode = Keyboard_Poll();
		Text_DrawChar(0, 5, Keyboard_ToChar(keycode));
		Text_DrawChar(6, 5, Keyboard_CheckPTT() ? '1' : '0');
		FB_MARKDIRTY(5);
		Framebuffer_UpdateScreen();
		Systick_DelayMs(100);
	}
}
