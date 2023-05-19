/**
 * @file        alcd.h
 * @author      Masoud Heidari (github.com/MasoudHD, linkedin.com/in/heidarimasoud, masoud-heidari.com, me@masoud-heidari.com)
 * @brief       This library is for using Alphanumeric LCD with any kind of microcontroller. You can print single character, 
 *              string and custom character on LCD using this library. Before anything, you need to iniialize this file definitions 
 *              (like pins you connected to LCD and some functions)
 * @version     0.1
 * @date        2023-05-19
 * 
 * @copyright   Copyright (c) 2023
 * 
 */

#ifndef alcd_h
#define alcd_h

/// Change this "include" based on your microcontroller
#include "stm32f1xx_hal.h"

/**
 * @brief       Declare the colomns and the rows of the LCD you want to use in this project
 * 
 */
#define ALCD_ROWS                       2
#define ALCD_COLUMNS                    16

/**
 * @brief       Declare the PORTs and the PINs which you want to connect to LCD
 * 
 */
#define ALCD_RS_PORT                    GPIOA   
#define ALCD_RS_PIN                     GPIO_PIN_9

#define ALCD_EN_PORT                    GPIOA   
#define ALCD_EN_PIN                     GPIO_PIN_10 

#define ALCD_D4_PORT                    GPIOA   
#define ALCD_D4_PIN                     GPIO_PIN_11 

#define ALCD_D5_PORT                    GPIOA   
#define ALCD_D5_PIN                     GPIO_PIN_12 

#define ALCD_D6_PORT                    GPIOA   
#define ALCD_D6_PIN                     GPIO_PIN_15

#define ALCD_D7_PORT                    GPIOB 
#define ALCD_D7_PIN                     GPIO_PIN_0

/**
 * @brief       Declare the SET and RESET functions to chanage the state of the pins
 * 
 */
#define ALCD_PIN_SET(PORT, PIN)         HAL_GPIO_WritePin(PORT, PIN, 1)
#define ALCD_PIN_RESET(PORT, PIN)       HAL_GPIO_WritePin(PORT, PIN, 0)        

/**
 * @brief       Declare the delay function which you are using in you project (in milli-second)
 * 
 */
#define ALCD_DELAY(ms)                  HAL_Delay(ms)



#define ALCD_CLEAR                      1
#define ALCD_NO_CLEAR                   0

extern const uint8_t CC_BatteryFull[8];
extern const uint8_t CC_Battery50[8];
extern const uint8_t CC_WifiFull[8];
extern const uint8_t CC_Wifi50[8];
extern const uint8_t CC_AntennaFull[8];
extern const uint8_t CC_Antenna50[8];
extern const uint8_t CC_Speaker[8];
extern const uint8_t CC_ElectricPlug[8];
extern const uint8_t CC_Lock[8];
extern const uint8_t CC_UnLock[8];
extern const uint8_t CC_Success[8];
extern const uint8_t CC_Info[8];
extern const uint8_t CC_Warning[8];

void ALcdInit(void);
void ALcdPrintChar(int clear, uint8_t data, int x, int y);
void ALcdClear(void);
void ALcdCursor(uint8_t x, uint8_t y);
void ALcdPrintString(int clear, char *a, int x, int y);
void ALcdPrintCC(int clear, int x, int y, uint8_t address);
void ALcdLoadCC(const uint8_t *arr, uint8_t address);
void ALcdLoadAndPrintCC(const uint8_t *arr, int x, int y, uint8_t address);

#endif