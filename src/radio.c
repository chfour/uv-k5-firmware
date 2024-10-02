#include "radio.h"
#include "driver/eeprom.h"
#include <stdint.h>

void Radio_GetSquelchData(uint32_t freq, uint8_t squelch_level, SquelchInfo_t* sqlinfo) {
	if (squelch_level == 0) {
		sqlinfo->SquelchOpenRSSI = 0x00;
		sqlinfo->SquelchOpenNoise = 0x7F;
		sqlinfo->SquelchCloseGlitch = 0xFF;
		sqlinfo->SquelchCloseRSSI = 0x00;
		sqlinfo->SquelchCloseNoise = 0x7F;
		sqlinfo->SquelchOpenGlitch = 0xFF;
	} else {
	    uint16_t base_addr = freq < 17400000 ? 0x1E60 : 0x1E00;
		base_addr += squelch_level;
		EEPROM_ReadBuffer(base_addr + 0x00, &sqlinfo->SquelchOpenRSSI, 1);
		EEPROM_ReadBuffer(base_addr + 0x10, &sqlinfo->SquelchCloseRSSI, 1);
		EEPROM_ReadBuffer(base_addr + 0x20, &sqlinfo->SquelchOpenNoise, 1);
		EEPROM_ReadBuffer(base_addr + 0x30, &sqlinfo->SquelchCloseNoise, 1);
		EEPROM_ReadBuffer(base_addr + 0x40, &sqlinfo->SquelchCloseGlitch, 1);
		EEPROM_ReadBuffer(base_addr + 0x50, &sqlinfo->SquelchOpenGlitch, 1);
		if (sqlinfo->SquelchOpenNoise >= 0x80) {
			sqlinfo->SquelchOpenNoise = 0x7F;
		}
		if (sqlinfo->SquelchCloseNoise >= 0x80) {
			sqlinfo->SquelchCloseNoise = 0x7F;
		}
	}
}
