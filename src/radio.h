#ifndef RADIO_H
#define RADIO_H

#include <stdint.h>

typedef struct {
    uint8_t SquelchOpenRSSI;
    uint8_t SquelchOpenNoise;
    uint8_t SquelchCloseGlitch;
    uint8_t SquelchCloseRSSI;
    uint8_t SquelchCloseNoise;
    uint8_t SquelchOpenGlitch;
} SquelchInfo_t;

// get squelch data for freq, squelch level, store in sqlinfo
void Radio_GetSquelchData(uint32_t freq, uint8_t squelch_level, SquelchInfo_t* sqlinfo);

#endif
