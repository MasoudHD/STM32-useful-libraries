#include "main.h"
#include "string.h"
#include "eeprom.h"


int main(void)
{
	int buffer[5] = {0};
 
	char checksum = 0;
	checksum = ReadFlash(60, &buffer, sizeof(buffer));

	for(int i=0; i<5; i++)
  {
    buffer[i] = i*3;
  }

	if(!WriteFlash(60, &buffer, sizeof(buffer)))
  {
    printf("Error in writing data on flash")
  }
  
  while (1)
  {
    
  }
 
}