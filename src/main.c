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

#include <string.h>
#include "bsp/dp32g030/gpio.h"
#include "bsp/dp32g030/syscon.h"
#include "board.h"
#include "driver/backlight.h"
#include "driver/bk4819.h"
#include "driver/gpio.h"
#include "driver/system.h"
#include "driver/systick.h"
#include "ui/main.h"
#if defined(ENABLE_UART)
#include "driver/uart.h"
#endif
#include "misc.h"

#if defined(ENABLE_UART)
static const char Version[] = "UV-K5 Firmware, Open Edition, OEFW-"GIT_HASH"\r\n";
#endif

void _putchar(char c) {
#if defined(ENABLE_UART)
	UART_Send((uint8_t *)&c, 1);
#endif
}

void Main(void) {
	// Enable clock gating of blocks we need.
	SYSCON_DEV_CLK_GATE = 0
		| SYSCON_DEV_CLK_GATE_GPIOA_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_GPIOB_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_GPIOC_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_UART1_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_SPI0_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_SARADC_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_CRC_BITS_ENABLE
		| SYSCON_DEV_CLK_GATE_AES_BITS_ENABLE;

	SYSTICK_Init();
	BOARD_Init();

#if defined(ENABLE_UART)
	UART_Init();
	UART_Send(Version, sizeof(Version));
#endif

	BK4819_Init();
	//BOARD_ADC_GetBatteryInfo(&gBatteryCurrentVoltage, &gBatteryCurrent);
	//BOARD_EEPROM_Init();
	//BOARD_EEPROM_LoadCalibration();

	/*for (i = 0; i < 4; i++) {
		BOARD_ADC_GetBatteryInfo(&gBatteryVoltages[i], &gBatteryCurrent);
	}
	BATTERY_GetReadings(false);*/

	
	BACKLIGHT_TurnOn();
	UI_DisplayMain();

	while (1) {
		//APP_Update();
		if (gNextTimeslice) {
			//APP_TimeSlice10ms();
			gNextTimeslice = false;
		}
		if (gNextTimeslice500ms) {
			//APP_TimeSlice500ms();
			gNextTimeslice500ms = false;
		}
	}
}

