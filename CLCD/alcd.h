#ifndef alcd_h
#define alcd_h

#include "stm32f1xx_hal.h"

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

#define ALCD_PIN_SET(PORT, PIN)         HAL_GPIO_WritePin(PORT, PIN, 1)
#define ALCD_PIN_RESET(PORT, PIN)       HAL_GPIO_WritePin(PORT, PIN, 0)        

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