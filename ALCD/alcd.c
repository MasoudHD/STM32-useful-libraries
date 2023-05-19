#include "alcd.h"
#include "stdint.h"


/**
 * @brief 			Custom Character arrays. These are some common and ready to use custom character.
 * 
 */
const uint8_t CC_BatteryFull[8] 		= {0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
const uint8_t CC_Battery50[8] 			= {0x0E, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F};
const uint8_t CC_WifiFull[8]			= {0x00, 0x0E, 0x11, 0x04, 0x0A, 0x00, 0x04, 0x00};
const uint8_t CC_Wifi50[8]				= {0x00, 0x00, 0x00, 0x04, 0x0A, 0x00, 0x04, 0x00};
const uint8_t CC_AntennaFull[8] 		= {0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F};
const uint8_t CC_Antenna50[8]			= {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, 0x1C};
const uint8_t CC_Speaker[8]				= {0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01};
const uint8_t CC_ElectricPlug[8] 		= {0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04};
const uint8_t CC_Lock[8]				= {0x00, 0x0E, 0x11, 0x11, 0x1F, 0x1B, 0x1B, 0x1F};
const uint8_t CC_UnLock[8]				= {0x00, 0x0E, 0x10, 0x10, 0x1F, 0x1B, 0x1B, 0x1F};
const uint8_t CC_Success[8]				= {0x00, 0x00, 0x01, 0x03, 0x16, 0x1C, 0x08, 0x00};
const uint8_t CC_Info[8]				= {0x1F, 0x11, 0x15, 0x11, 0x15, 0x15, 0x15, 0x1F};
const uint8_t CC_Warning[8]				= {0x1F, 0x11, 0x15, 0x15, 0x15, 0x11, 0x15, 0x1F};

static void enPulse(void);
static void ALcdData(uint8_t data_bit);
static void ALcdCmd(uint8_t cmd);
static void ALcdWriteByte(uint8_t byte);

/**
 * @brief 			Init LCD. This function must be called before using other ALCD functions and after
 * 					initilizing the GPIO and Clock settings.
 * 
 */
void ALcdInit(void)
{	 
	ALcdData(0x00);
	ALCD_DELAY(1);
  	ALcdCmd(0x03);
	ALCD_DELAY(5);	
  	ALcdCmd(0x03);
	ALCD_DELAY(1);
  	ALcdCmd(0x03);
	ALCD_DELAY(1);
  	ALcdCmd(0x02);
	ALCD_DELAY(1);
  	ALcdCmd(0x28);
  	ALcdCmd(0x0C);
  	ALcdCmd(0x01);  
}

/**
 * @brief 			This function clear all data from LCD screen.
 * 
 */
void ALcdClear(void)
{
	ALcdCmd(0x00);
  	ALcdCmd(0x01);
}

/**
 * @brief 			Set the cursor position for print on LCD
 * 
 * @param x			X position of the cursor in the range of 0~ALCD_COLUMNS (see ALCD.h) 
 * @param y			Y position of the cursor in the range of 0~ALCD_ROWS (see ALCD.h) 
 */
void ALcdCursor(uint8_t x, uint8_t y)
{
  uint8_t mask;

  mask = x&0x0F;
  if(y==0)
  {
    mask |= (0x80);
    ALcdCmd(mask);
  }
  else
  {
    mask |= (0xc0);
    ALcdCmd(mask);
  }
}

/**
 * @brief			Print a single character on LCD 		
 * 
 * @param clear		You can clear LCD before print on it. Use ALCD_CLEAR to clear the screen
 * 					and ALCD_NO_CLEAR to keep previous data on screen and print the new data. 
 * @param data		Character to print
 * @param x			X position of the cursor in the range of 0~ALCD_COLUMNS (see ALCD.h)
 * @param y			Y position of the cursor in the range of 0~ALCD_ROWS (see ALCD.h)
 */
void ALcdPrintChar(int clear, uint8_t data, int x, int y)
{
   if(clear)
   {	
			ALcdClear();
   }
   ALcdCursor(x, y);
   ALcdWriteByte(data);
}

/**
 * @brief 			Load a single custom character in LCD CGRAM. Before print any custom character 
 * 					you must first store its data in the LCD CGRAM.
 * 
 * @param arr		The array of the custom character (with the length of 8 bytes) 
 * @param address	The address of the LCD CGRAM (in the range of 0~7). 
 */
void ALcdLoadCC(const uint8_t *arr, uint8_t address)
{
	ALcdCmd(0x40+address*8);
  for(int i=0; i<8; i++)
  {
		ALcdWriteByte(arr[i]);
  }
}

/**
 * @brief 			Print the loaded custom character on LCD screen.
 * 
 * @param clear		You can clear LCD before print on it. Use ALCD_CLEAR to clear the screen
 * 					and ALCD_NO_CLEAR to keep previous data on screen and print the new data.  
 * @param x 		X position of the cursor in the range of 0~ALCD_COLUMNS (see ALCD.h)
 * @param y 		Y position of the cursor in the range of 0~ALCD_ROWS (see ALCD.h)
 * @param address 	The address of the LCD CGRAM (in the range of 0~7) where you loaded the intended
 * 					custom character (by using ALcdLoadCC function)
 */
void ALcdPrintCC(int clear, int x, int y, uint8_t address)
{
	ALcdPrintChar(clear, address, x, y);
}

/**
 * @brief			This function combines the ALcdLoadCC and ALcdPrintCC functions so you
 * 					can load the custom character into LCD CGRAM whenever you want to print it.
 * 
 * @param arr		The array of the custom character (with the length of 8 bytes)
 * @param x			X position of the cursor in the range of 0~ALCD_COLUMNS (see ALCD.h)
 * @param y 		Y position of the cursor in the range of 0~ALCD_ROWS (see ALCD.h)
 * @param address	The address of the LCD CGRAM (in the range of 0~7) where you loaded the intended
 * 					custom character (by using ALcdLoadCC function) 
 */
void ALcdLoadAndPrintCC(const uint8_t *arr, int x, int y, uint8_t address)
{
	ALcdCmd(0x40+address*8);
	for(int i=0; i<8; i++)
	{
			ALcdWriteByte(arr[i]);
	}
	ALcdPrintCC(ALCD_NO_CLEAR, x, y, address);
		
}

/**
 * @brief 			Print a string on LCD screen
 * 
 * @param clear		You can clear LCD before print on it. Use ALCD_CLEAR to clear the screen
 * 					and ALCD_NO_CLEAR to keep previous data on screen and print the new data. 
 * @param data		The string you want to print on LCD 
 * @param x 		X position of the cursor in the range of 0~ALCD_COLUMNS (see ALCD.h)
 * @param y 		Y position of the cursor in the range of 0~ALCD_ROWS (see ALCD.h)
 */
void ALcdPrintString(int clear, char *data, int x, int y)
{
	if(clear)
	{	
		ALcdClear();
	}
	ALcdCursor(x, y);
  for(int i=0; data[i]!='\0'; i++)
	{
		ALcdWriteByte(data[i]);
	}
       
}


/**
 * @brief 			Make a single pulse on LCD enable pin
 * 
 */
static void enPulse(void)
{
	ALCD_PIN_SET(ALCD_EN_PORT, ALCD_EN_PIN);
	ALCD_DELAY(1);
	ALCD_PIN_RESET(ALCD_EN_PORT, ALCD_EN_PIN);
	ALCD_DELAY(1);
}

/**
 * @brief 			Load the data on LCD data pins
 * 
 * @param data		The data we want to be loaded on data pins 
 */
static void ALcdData(uint8_t data)
{
	if(data & 1) 
		ALCD_PIN_SET(ALCD_D4_PORT, ALCD_D4_PIN);
	else
		ALCD_PIN_RESET(ALCD_D4_PORT, ALCD_D4_PIN);

	if(data & 2)
		ALCD_PIN_SET(ALCD_D5_PORT, ALCD_D5_PIN);
	else
		ALCD_PIN_RESET(ALCD_D5_PORT, ALCD_D5_PIN);

	if(data & 4)
		ALCD_PIN_SET(ALCD_D6_PORT, ALCD_D6_PIN);
	else
		ALCD_PIN_RESET(ALCD_D6_PORT, ALCD_D6_PIN);

	if(data & 8) 
		ALCD_PIN_SET(ALCD_D7_PORT, ALCD_D7_PIN);
	else
		ALCD_PIN_RESET(ALCD_D7_PORT, ALCD_D7_PIN);
}

/**
 * @brief 			Send a command to LCD
 * 
 * @param cmd		The command we want to be sent  
 */
static void ALcdCmd(uint8_t cmd)
{
	uint8_t lsb,msb;
    
	lsb = cmd&0x0F;
	msb = cmd&0xF0;
	ALCD_PIN_RESET(ALCD_RS_PORT, ALCD_RS_PIN);
	ALcdData(msb>>4);
	enPulse();
	ALcdData(lsb);
	enPulse();
}

/**
 * @brief 			Write a byte on LCD data pins.
 * 
 * @param byte 		Byte to send on LCD data pins.
 */
static void ALcdWriteByte(uint8_t byte)
{
	uint8_t lsb,msb;

	lsb = byte&0x0F;
	msb = byte&0xF0;
	ALCD_PIN_SET(ALCD_RS_PORT, ALCD_RS_PIN);
	ALcdData(msb>>4);
	enPulse();
	ALcdData(lsb);
	enPulse();
}
