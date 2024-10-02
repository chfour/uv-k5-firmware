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

#include "app/main.h"
#include "driver/keyboard.h"
#include "driver/bk4819.h"
#include <stdint.h>

static volatile uint32_t gSystickCount;

void Sched_SystickHandler() { // every 10ms
	gSystickCount++;
	if ((gSystickCount % 50) == 0) { // every 500ms
		gAppShouldUpdate = 1;
	}

	uint8_t keys_changed = Keyboard_Poll();
	// if the pressed keys have changed, there's an unhandled key event or the ptt state changed
	if (keys_changed || gKeyboardKeypress != KEY_NONE || Keyboard_CheckPTT()) {
		gAppShouldUpdate = 1;
	}

	// we have an interrupt from the bk4819
	if (BK4819_CheckForInterrupts()) {
		gAppShouldUpdate = 1;
	}

	if ((gSystickCount % 10) == 0) { // every 100ms
		// fire key autorepeat events
		if (gKeyboardIsAutorepeating) {
			gKeyboardKeypress = gKeyboardCurrentKey;
			gAppShouldUpdate = 1;
		}
	}
}
