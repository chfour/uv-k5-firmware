/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include "ui/main.h"
#include "driver/systick.h"
#include "ui/fb.h"
#include "ui/text.h"
#include <stdint.h>

void UI_DisplayMain(void) {
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
}
