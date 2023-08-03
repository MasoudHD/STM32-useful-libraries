#include "eeprom.h"

extern void    FLASH_PageErase(uint32_t PageAddress);


uint8_t ReadFlash(uint32_t pageStartAddr, void *dest, int len)
{
  uint8_t *ptr = (uint8_t*)dest;
  uint8_t cs = 0;
	
	uint16_t flash_size_kb = *(const uint16_t*)FLASHSIZE_BASE;
	
	if(pageStartAddr > flash_size_kb) return -1;
	
	pageStartAddr = pageStartAddr*0x400 + FLASH_BASE;
	
  HAL_FLASH_Unlock();
  for(int i=0; i<len; i+=2)
  {
    uint16_t *halfWorld;
    halfWorld = (uint16_t*)(pageStartAddr+i);
    uint16_t value = *halfWorld;
    ptr[i] = (value & 0xff00) >> 8;
    ptr[i+1] = value & 0x00ff;
    cs ^= ptr[i] ^ ptr[i+1];
  }
  HAL_FLASH_Lock();
  return cs;
}

bool WriteFlash(uint32_t pageStartAddr, void *src, int len)
{
  uint8_t *ptr = (uint8_t*)src;
	
	uint16_t flash_size_kb = *(const uint16_t*)FLASHSIZE_BASE;
	
	if(pageStartAddr > flash_size_kb) return false;
	
	pageStartAddr = pageStartAddr*0x400 + FLASH_BASE;
	
  HAL_FLASH_Unlock();
  FLASH_PageErase(pageStartAddr);
	while(READ_BIT(FLASH->CR, FLASH_SR_EOP)!=0);
	CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
  for(int i=0; i<len; i+=2)
  {
    uint16_t byteJoin = (ptr[i]<<8) | ptr[i+1];
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, pageStartAddr+i, byteJoin) != HAL_OK)
    {
      return false;
    }
    //HAL_Delay(2);
  }
  HAL_FLASH_Lock();
  return true;
}