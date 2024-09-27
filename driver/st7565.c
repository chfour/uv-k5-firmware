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

#include <stdint.h>
#include "bsp/dp32g030/gpio.h"
#include "bsp/dp32g030/spi.h"
#include "driver/gpio.h"
#include "driver/spi.h"
#include "driver/st7565.h"
#include "driver/systick.h"

void ST7565_DrawLine(uint8_t x, uint8_t row, const uint8_t *data, uint8_t size) {
	SPI_ToggleMasterMode(&SPI0->CR, false);
	ST7565_SelectColumnAndLine(x + 4, row);

	ST7565_A0Mode(ST7565_DATA);
	if (data != 0) { // is NULL
		for (uint8_t i = 0; i < size; i++) {
			ST7565_WriteByte(data[i]);
		}
	} else {
		for (uint8_t i = 0; i < size; i++) {
			ST7565_WriteByte(0);
		}
	}

	SPI_WaitForUndocumentedTxFifoStatusBit();
	SPI_ToggleMasterMode(&SPI0->CR, true);
}

void ST7565_Init() {
	SPI0_Init();
	ST7565_HardwareReset();
	SPI_ToggleMasterMode(&SPI0->CR, false);
	ST7565_A0Mode(ST7565_CMD);
	ST7565_WriteByte(0xE2);
	Systick_DelayMs(120);
	ST7565_WriteByte(0xA2);
	ST7565_WriteByte(0xC0);
	ST7565_WriteByte(0xA1);
	ST7565_WriteByte(0xA6);
	ST7565_WriteByte(0xA4);
	ST7565_WriteByte(0x24);
	ST7565_WriteByte(0x81);
	ST7565_WriteByte(0x1F);
	ST7565_WriteByte(0x2B);
	Systick_DelayMs(1);
	ST7565_WriteByte(0x2E);
	Systick_DelayMs(1);
	ST7565_WriteByte(0x2F);
	ST7565_WriteByte(0x2F);
	ST7565_WriteByte(0x2F);
	ST7565_WriteByte(0x2F);
	Systick_DelayMs(40);
	ST7565_WriteByte(0x40);
	ST7565_WriteByte(0xAF);
	SPI_WaitForUndocumentedTxFifoStatusBit();
	SPI_ToggleMasterMode(&SPI0->CR, true);
	//ST7565_FillScreen(0x00);
	for (uint16_t i = 0; i < 8; i++) {
		ST7565_DrawLine(0, i, 0, 128);
	}
}

void ST7565_HardwareReset() {
	GPIO_SetBit(&GPIOB->DATA, GPIOB_PIN_ST7565_RES);
	Systick_DelayMs(1);
	GPIO_ClearBit(&GPIOB->DATA, GPIOB_PIN_ST7565_RES);
	Systick_DelayMs(20);
	GPIO_SetBit(&GPIOB->DATA, GPIOB_PIN_ST7565_RES);
	Systick_DelayMs(120);
}

void ST7565_SelectColumnAndLine(uint8_t x, uint8_t row) {
	ST7565_A0Mode(ST7565_CMD);
	ST7565_WriteByte(row + 0xB0);
	ST7565_WriteByte(((x >> 4) & 0x0F) | 0x10);
	ST7565_WriteByte(((x >> 0) & 0x0F));
	SPI_WaitForUndocumentedTxFifoStatusBit();
}

void ST7565_WriteByte(uint8_t v) {
	while ((SPI0->FIFOST & SPI_FIFOST_TFF_MASK) != SPI_FIFOST_TFF_BITS_NOT_FULL) {}
	SPI0->WDR = v;
}

void ST7565_A0Mode(uint8_t mode) {
	if (mode) { // ST7565_DATA
		GPIO_SetBit(&GPIOB->DATA, GPIOB_PIN_ST7565_A0);
	} else { // ST7565_CMD
		GPIO_ClearBit(&GPIOB->DATA, GPIOB_PIN_ST7565_A0);
	}
}
