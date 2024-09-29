/* Copyright 2023 Manuel Jinger
 * Copyright 2023 Dual Tachyon
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

#include "bsp/dp32g030/gpio.h"
#include "driver/gpio.h"
#include "driver/keyboard.h"
#include "driver/systick.h"

Keycode_t gKeyboardCurrentKey = KEY_NONE;
Keycode_t gKeyboardKeypress = KEY_NONE;

uint8_t gKeyboardPttState = 0;

uint8_t Keyboard_CheckPTT() {
	uint8_t last = gKeyboardPttState;
	gKeyboardPttState = !GPIO_CheckBit(&GPIOC->DATA, GPIOC_PIN_PTT);

	return last != gKeyboardPttState;
}

uint8_t Keyboard_Poll() {
	Keycode_t prev_key = gKeyboardCurrentKey;
	gKeyboardCurrentKey = KEY_NONE;

	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_5);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_6);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_7);
	Systick_DelayUs(1);

	// Keys connected to gnd
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_0)) {
		gKeyboardCurrentKey = KEY_SIDE1;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_1)) {
		gKeyboardCurrentKey = KEY_SIDE2;
		goto Bye;
	}
	// Original doesn't do PTT

	// First row
	GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	Systick_DelayUs(1);

	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_0)) {
		gKeyboardCurrentKey = KEY_MENU;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_1)) {
		gKeyboardCurrentKey = KEY_1;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_2)) {
		gKeyboardCurrentKey = KEY_4;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_3)) {
		gKeyboardCurrentKey = KEY_7;
		goto Bye;
	}

	// Second row
	GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_5);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	Systick_DelayUs(1);

	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_0)) {
		gKeyboardCurrentKey = KEY_UP;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_1)) {
		gKeyboardCurrentKey = KEY_2;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_2)) {
		gKeyboardCurrentKey = KEY_5;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_3)) {
		gKeyboardCurrentKey = KEY_8;
		goto Bye;
	}

	// Third row
	GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_5);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_6);
	Systick_DelayUs(1);

	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_0)) {
		gKeyboardCurrentKey = KEY_DOWN;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_1)) {
		gKeyboardCurrentKey = KEY_3;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_2)) {
		gKeyboardCurrentKey = KEY_6;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_3)) {
		gKeyboardCurrentKey = KEY_9;
		goto Bye;
	}

	// Fourth row
	GPIO_ClearBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_7);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_6);
	Systick_DelayUs(1);

	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_0)) {
		gKeyboardCurrentKey = KEY_EXIT;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_1)) {
		gKeyboardCurrentKey = KEY_STAR;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_2)) {
		gKeyboardCurrentKey = KEY_0;
		goto Bye;
	}
	if (!GPIO_CheckBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_3)) {
		gKeyboardCurrentKey = KEY_F;
		goto Bye;
	}

Bye:
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_4);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_5);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_6);
	GPIO_SetBit(&GPIOA->DATA, GPIOA_PIN_KEYBOARD_7);

	if (prev_key != gKeyboardCurrentKey && gKeyboardCurrentKey != KEY_NONE) {
		gKeyboardKeypress = gKeyboardCurrentKey;
	}

	return prev_key != gKeyboardCurrentKey;
}

char Keyboard_ToChar(Keycode_t keycode) {
	switch (keycode) {
		case KEY_0: case KEY_1:
		case KEY_2: case KEY_3:
		case KEY_4: case KEY_5:
		case KEY_6: case KEY_7:
		case KEY_8: case KEY_9:
			return '0' + keycode;
		case KEY_MENU: case KEY_UP:
		case KEY_DOWN: case KEY_EXIT:
			return 'A' + keycode - KEY_MENU;
		case KEY_STAR:  return '*'; break;
		case KEY_F:     return 'F'; break;
		case KEY_SIDE1: return '-'; break;
		case KEY_SIDE2: return '='; break;
		default:
			return '.';
	}
}
