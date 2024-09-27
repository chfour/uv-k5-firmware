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

#ifndef DRIVER_ST7565_H
#define DRIVER_ST7565_H

#include <stdbool.h>
#include <stdint.h>

// fill a row with data
void ST7565_DrawLine(uint8_t x, uint8_t row, const uint8_t *data, uint8_t size);

// initialize the display
void ST7565_Init();

// hardware reset the display
void ST7565_HardwareReset();

// select the column and line
void ST7565_SelectColumnAndLine(uint8_t Column, uint8_t Line);

// write a byte over SPI (and wait)
void ST7565_WriteByte(uint8_t Value);

// set A0 to command or data
void ST7565_A0Mode(uint8_t mode);

#define ST7565_CMD 0
#define ST7565_DATA 1

#endif

