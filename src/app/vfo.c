#include "app/vfo.h"
#include "app/main.h"
#include "bsp/dp32g030/gpio.h"
#include "driver/bk4819-regs.h"
#include "driver/bk4819.h"
#include "driver/gpio.h"
#include "driver/keyboard.h"
#include "external/printf/printf.h"
#include "radio.h"
#include "ui/fb.h"
#include "ui/text.h"
#include <string.h>

void App_Vfo_Main() {
    uint32_t frequency = 14550000; // in 10Hz
    char buf[32];
    uint8_t state = 0;
    uint16_t step = 625;
    uint8_t vfo_changed = 1;
    SquelchInfo_t sqlinfo;
    while (1) {
        Framebuffer_Clear();
        uint16_t interrupts;
        uint8_t int_pin_state = GPIO_CheckBit(&GPIOB->DATA, GPIOB_PIN_BK4819_INT);
        while ((interrupts = BK4819_GetInterrupts())) {
            if (interrupts & BK4819_REG_02_SQUELCH_FOUND) { // im goingto kill somebody over those _SHIFT whatever names
                BK4819_GpioSet(BK4819_GPIO6_PIN2_GREEN, 1);
                GPIO_SetBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
            }
            if (interrupts & BK4819_REG_02_SQUELCH_LOST) {
                BK4819_GpioSet(BK4819_GPIO6_PIN2_GREEN, 0);
                GPIO_ClearBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
            }
            snprintf(buf, sizeof(buf), "%04x", interrupts);
            Text_DrawText(0, 1, buf);
        }
        if (gKeyboardKeypress == KEY_MENU) {
            break;
        }
        if (gKeyboardKeypress == KEY_STAR) {
            if (GPIO_CheckBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH)) {
                GPIO_ClearBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
            } else {
                GPIO_SetBit(&GPIOC->DATA, GPIOC_PIN_AUDIO_PATH);
            }
        }
        if (gKeyboardKeypress == KEY_F) {
            // 250, 500, 625, 1000, 1250, 2500
            switch (step) {
                case 250:
                    step = 500; break;
                case 500:
                    step = 625; break;
                case 625:
                    step = 1000; break;
                case 1000:
                    step = 1250; break;
                case 2500:
                default:
                    step = 250; break;
            }
        }
        if (gKeyboardKeypress == KEY_UP) {
            frequency += step;
            vfo_changed = 1;
        }
        if (gKeyboardKeypress == KEY_DOWN) {
            frequency -= step;
            vfo_changed = 1;
        }
        if (vfo_changed) {
            BK4819_SetFrequency(frequency);
            BK4819_SelectFilter(frequency);
            Radio_GetSquelchData(frequency, 1, &sqlinfo);
            BK4819_SetupSquelch(&sqlinfo);
            BK4819_SetFilterBandwidth(BK4819_FILTER_BW_NARROW);
            BK4819_SetAGC(1);
            BK4819_RX_TurnOn();
            BK4819_SetAF(BK4819_AF_OPEN);
            vfo_changed = 0;
        }
        gKeyboardKeypress = KEY_NONE;
        snprintf(buf, sizeof(buf), "%9ld", frequency);
        memmove(buf+5, buf+4, 6); // move everything but the first 4 chars ahead one byte
        buf[4] = '.'; // add a dot between the two parts
        uint8_t last_x = Text_DrawText(0, 2, buf);
        
        snprintf(buf, sizeof(buf), " st: %4d", step);
        Text_DrawText(last_x, 2, buf);

        snprintf(buf, sizeof(buf), "%02x %02x", sqlinfo.SquelchOpenRSSI, sqlinfo.SquelchCloseRSSI);
        Text_DrawText(0, 3, buf);

        state ^= 1;
        snprintf(buf, sizeof(buf), "s:%c int:%c", state + '0', int_pin_state + '0');
        Text_DrawText(0, 4, buf);
        
        snprintf(buf, sizeof(buf), "rssi: %d", BK4819_GetRSSI());
        Text_DrawText(0, 5, buf);
        
        Framebuffer_UpdateScreen();
        App_Wait();
    }
}
