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

#include "ARMCM0.h"
#include "driver/systick.h"
#include "misc.h"

// 0x20000324
static uint32_t gTickMultiplier;

void Systick_Init() {
	SysTick_Config(480000);
	gTickMultiplier = 48;
}

void Systick_DelayUs(uint32_t delay) {
	uint32_t i;
	uint32_t start;
	uint32_t previous;
	uint32_t current;
	uint32_t delta;

	i = 0;
	start = SysTick->LOAD;
	previous = SysTick->VAL;
	do {
		do {
			current = SysTick->VAL;
		} while (current == previous);
		if (current < previous) {
			delta = -current;
		} else {
			delta = start - current;
		}
		i += delta + previous;
		previous = current;
	} while (i < delay * gTickMultiplier);
}

void Systick_DelayMs(uint32_t delay) {
	Systick_DelayUs(delay * 1000);
}
