/*
 * STM32L432_EEPROM.h
 *
 *  Created on: Apr 13, 2022
 *      Author: laurentf
 */

#ifndef MCUDRIVERS_STM32L432_EEPROM_H_
#define MCUDRIVERS_STM32L432_EEPROM_H_

#include <stdint.h>

#define EEPROM_ADDRESS 0x0803F800

uint8_t STM32L432_EEPROMWrite(uint8_t * pData, uint16_t Size);
uint8_t STM32L432_EEPROMRead(uint8_t * pData, uint16_t Size);

#endif /* MCUDRIVERS_STM32L432_EEPROM_H_ */
