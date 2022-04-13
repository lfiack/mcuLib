/*
 * STM32L432_EEPROM.c
 *
 *  Created on: Apr 13, 2022
 *      Author: laurentf
 */

#include "STM32L432_EEPROM.h"

#include "stm32l4xx_hal.h"

uint8_t STM32L432_EEPROMWrite(uint8_t * pData, uint16_t Size) {
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.Page = 127;
	EraseInitStruct.NbPages = 1;

	HAL_FLASH_Unlock();

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
		HAL_FLASH_Lock();
		return 255;
	}

	uint64_t Data = 0;
	uint8_t * ptr = (uint8_t *) &Data;

	int itFlash = 0;
	int itData = 0;
	int itInput = 0;

	while(itInput < Size) {
		// Put 8 bytes in 64 bits variable
		ptr[itData++] = pData[itInput++];

		// As soon as 8 bytes are put together, we write them to the flash
		if (itData == 8) {
			itData = 0;

			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, EEPROM_ADDRESS+itFlash*8, Data) != HAL_OK) {
				HAL_FLASH_Lock();
				return 255;
			}
			itFlash++;
			Data = 0;
		}
	}

	// Write remaining bytes if its not a multiple of 8
	if (itData != 0) {
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, EEPROM_ADDRESS+itFlash*8, Data) != HAL_OK) {
			HAL_FLASH_Lock();
			return 255;
		}
	}

	HAL_FLASH_Lock();

	return 0;
}

uint8_t STM32L432_EEPROMRead(uint8_t * pData, uint16_t Size) {

	for (int i = 0 ; i < Size ; i++) {
		pData[i] = * (__IO uint8_t *)(EEPROM_ADDRESS+i);
	}

	return 0;
}
