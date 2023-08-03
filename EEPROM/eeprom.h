#ifndef EEPROM_H
#define EEPROM_H

// Change these two includes based on your STM32 microcontroller
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash.h"

#include "stdint.h"
#include "stdbool.h"

/**
 * @brief                   Read data from flash page
 * 
 * @param pageStartAddr     Page address based on STM32 uC you use. ex: for 64KB MCU => 60 (page 60 will be used for EEPROM) 
 * @param dest              Pointer to copy the data from flash 
 * @param len               Length of the dest 
 * @return uint8_t          Checksum of the read data (8-XOR) 
 */
uint8_t ReadFlash(uint32_t pageStartAddr, void *dest, int len);


/**
 * @brief                   Write data on flash page            
 * 
 * @param pageStartAddr     Page address based on STM32 uC you use. ex: for 64KB MCU => 60 (page 60 will be used for EEPROM)  
 * @param src               The pointer to the data you want to write on flash 
 * @param len 
 * @return true             If data write without any error 
 * @return false            If there is a problem in writing process 
 */
bool WriteFlash(uint32_t pageStartAddr, void *src, int len);

#endif /* EEPROM_H */
