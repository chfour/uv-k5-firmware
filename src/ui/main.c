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

#include "driver/st7565.h"
#include "ui/main.h"
#include "ui/text.h"
#include <string.h>
#include <stdint.h>

void UI_DisplayMain(void) {
	memset(gFrameBuffer[6], 0xAA, 127);
	for (uint8_t i = 0; i < 128; i++) {
		gFrameBuffer[6][i] = (i & 2) ? 0x33 : 0xCC; // checkerboard pattern
	}
	Text_DrawText(0, 3, "test TEST 123 !\"#~");

	ST7565_BlitFullScreen();
}