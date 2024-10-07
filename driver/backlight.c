#include "bsp/dp32g030/gpio.h"
#include "driver/backlight.h"
#include "driver/gpio.h"

volatile uint8_t gBacklightTimer;

void Backlight_On() {
	GPIO_SetBit(&GPIOB->DATA, GPIOB_PIN_BACKLIGHT);
	gBacklightTimer = 20;
}

void Backlight_SchedTask() {
	if (gBacklightTimer > 0) {
		gBacklightTimer--;
		if (gBacklightTimer == 0) {
			GPIO_ClearBit(&GPIOB->DATA, GPIOB_PIN_BACKLIGHT);
		}
	}
}
