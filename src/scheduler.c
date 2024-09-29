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

#define DECREMENT_AND_TRIGGER(cnt, flag) \
	do { \
		if (cnt) { \
			if (--cnt == 0) { \
				flag = true; \
			} \
		} \
	} while(0)

static volatile uint32_t gSystickCount;

void Sched_SystickHandler() { // every 10ms
	gSystickCount++;
	if ((gSystickCount % 50) == 0) { // every 500ms
		gAppShouldUpdate = 1;
	}
	
	if (Keyboard_Poll() || Keyboard_CheckPTT()) { // if there's been a change in the pressed keys
		gAppShouldUpdate = 1;
	}
}
