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

#ifndef DRIVER_KEYBOARD_H
#define DRIVER_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef enum Keycode_t {
	KEY_0 = 0,
	KEY_1 = 1,
	KEY_2 = 2,
	KEY_3 = 3,
	KEY_4 = 4,
	KEY_5 = 5,
	KEY_6 = 6,
	KEY_7 = 7,
	KEY_8 = 8,
	KEY_9 = 9,
	KEY_MENU = 10,
	KEY_UP = 11,
	KEY_DOWN = 12,
	KEY_EXIT = 13,
	KEY_STAR = 14,
	KEY_F = 15,
	// KEY_PTT = 21,
	KEY_SIDE2 = 22,
	KEY_SIDE1 = 23,
	KEY_NONE = 255,
} Keycode_t;

// currently pressed key, or KEY_NONE
extern volatile Keycode_t gKeyboardCurrentKey;

// currently pressed key, but only set on key press and not constantly (so we can reset it)
extern volatile Keycode_t gKeyboardKeypress;

// how long has the key been pressed for, in systicks
extern volatile uint8_t gKeyboardPressedFor;

// whether key autorepeat is happening
extern volatile uint8_t gKeyboardIsAutorepeating;

// current state of the ptt button
extern uint8_t gKeyboardPttState;

// check if the state of the ptt button has changed since the last call
uint8_t Keyboard_CheckPTT();

// poll the keypad, returns 1 if the pressed key changed since the last call
uint8_t Keyboard_Poll();

// convert a keycode to a char
char Keyboard_ToChar(Keycode_t keycode);

#endif
