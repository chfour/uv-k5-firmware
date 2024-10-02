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

#ifndef DRIVER_BK4819_h
#define DRIVER_BK4819_h

#include <stdbool.h>
#include <stdint.h>
#include "driver/bk4819-regs.h"
#include "radio.h"

enum BK4819_AF_Type_t {
	BK4819_AF_MUTE = 0U,
	BK4819_AF_OPEN = 1U,
	BK4819_AF_ALAM = 2U,
	BK4819_AF_BEEP = 3U,
	BK4819_AF_CTCO = 6U,
	BK4819_AF_AM   = 7U,
	BK4819_AF_FSKO = 8U,
};

typedef enum BK4819_AF_Type_t BK4819_AF_Type_t;

enum BK4819_FilterBandwidth_t {
	BK4819_FILTER_BW_WIDE   = 0U,
	BK4819_FILTER_BW_NARROW = 1U,
};

typedef enum BK4819_FilterBandwidth_t BK4819_FilterBandwidth_t;

enum BK4819_CssScanResult_t {
	BK4819_CSS_RESULT_NOT_FOUND = 0U,
	BK4819_CSS_RESULT_CTCSS = 1U,
	BK4819_CSS_RESULT_CDCSS = 2U,
};

typedef enum BK4819_CssScanResult_t BK4819_CssScanResult_t;

void BK4819_Init();
uint16_t BK4819_ReadRegister(BK4819_REGISTER_t Register);
void BK4819_WriteRegister(BK4819_REGISTER_t Register, uint16_t Data);
void BK4819_WriteU8(uint8_t Data);
void BK4819_WriteU16(uint16_t Data);

// check the interrupt pin
uint8_t BK4819_CheckForInterrupts();

// get interrupt flags
uint16_t BK4819_GetInterrupts();

void BK4819_SetAGC(uint8_t Value);

// set the state of a gpio pin
void BK4819_GpioSet(BK4819_GPIO_PIN_t pin, uint8_t v);

void BK4819_SetCDCSSCodeWord(uint32_t CodeWord);
void BK4819_SetCTCSSFrequency(uint32_t BaudRate);
void BK4819_Set55HzTailDetection();
void BK4819_EnableVox(uint16_t Vox1Threshold, uint16_t Vox0Threshold);
void BK4819_SetFilterBandwidth(BK4819_FilterBandwidth_t Bandwidth);
void BK4819_SetupPowerAmplifier(uint16_t Bias, uint32_t Frequency);
void BK4819_SetFrequency(uint32_t Frequency);

// set squelch parameters. see radio.c Radio_GetSquelchData()
void BK4819_SetupSquelch(SquelchInfo_t* sqlinfo);

void BK4819_SetAF(BK4819_AF_Type_t AF);
void BK4819_RX_TurnOn();
void BK4819_SelectFilter(uint32_t Frequency);
void BK4819_DisableScramble();
void BK4819_EnableScramble(uint8_t Type);
void BK4819_DisableVox();
void BK4819_DisableDTMF();
void BK4819_EnableDTMF();
void BK4819_PlayTone(uint16_t Frequency, bool bTuningGainSwitch);
void BK4819_EnterTxMute();
void BK4819_ExitTxMute();
void BK4819_Sleep();
void BK4819_TurnsOffTones_TurnsOnRX();
void BK4819_SetupAircopy();
void BK4819_ResetFSK();
void BK4819_Idle();
void BK4819_ExitBypass();
void BK4819_PrepareTransmit();
void BK4819_TxOn_Beep();
void BK4819_ExitSubAu();

void BK4819_EnterDTMF_TX(bool bLocalLoopback);
void BK4819_ExitDTMF_TX(bool bKeep);
void BK4819_EnableTXLink();

void BK4819_PlayDTMF(char Code);
void BK4819_PlayDTMFString(const char *pString, bool bDelayFirst, uint16_t FirstCodePersistTime, uint16_t HashCodePersistTime, uint16_t CodePersistTime, uint16_t CodeInternalTime);

void BK4819_TransmitTone(bool bLocalLoopback, uint32_t Frequency);

void BK4819_GenTail(uint8_t Tail);
void BK4819_EnableCDCSS();
void BK4819_EnableCTCSS();

uint16_t BK4819_GetRSSI();

bool BK4819_GetFrequencyScanResult(uint32_t *pFrequency);
BK4819_CssScanResult_t BK4819_GetCxCSSScanResult(uint32_t *pCdcssFreq, uint16_t *pCtcssFreq);
void BK4819_DisableFrequencyScan();
void BK4819_EnableFrequencyScan();
void BK4819_SetScanFrequency(uint32_t Frequency);

void BK4819_Disable();

void BK4819_StopScan();

uint8_t BK4819_GetDTMF_5TONE_Code();

uint8_t BK4819_GetCDCSSCodeType();
uint8_t BK4819_GetCTCType();

void BK4819_SendFSKData(uint16_t *pData);
void BK4819_PrepareFSKReceive();

void BK4819_PlayRoger();
void BK4819_PlayRogerMDC();

void BK4819_Enable_AfDac_DiscMode_TxDsp();

void BK4819_GetVoxAmp(uint16_t *pResult);
void BK4819_SetScrambleFrequencyControlWord(uint32_t Frequency);
void BK4819_PlayDTMFEx(bool bLocalLoopback, char Code);

#endif
