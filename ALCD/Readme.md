
# Alphanumeric LCD

This library is for using Alphanumeric LCD with any kind of microcontroller. Currently, it is for 4-bit configuration. You can use default custom characters or add your own. For creating custom characters you can use this website:

[Online Custom Character Generator](https://maxpromer.github.io/LCD-Character-Creator)

## Features
- Support 4-bit configuration
- Compatible with all types of microcontrollers
- Default common custom characters
- Add new custom characters  easily

## How to use
 All you need is to change the ```alcd.h``` file based on your uC. Follow these steps:

1. Change the header file based on your uC:

example:
```bash
    #include "stm32f1xx_hal.h"
```
2. Change the Pins and Ports you want to connect the LCD to:
```bash
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
```
3. Change these two line to Set and Reset a pin in your uC:
```bash
    #define ALCD_PIN_SET(PORT, PIN)         HAL_GPIO_WritePin(PORT, PIN, 1)
    #define ALCD_PIN_RESET(PORT, PIN)       HAL_GPIO_WritePin(PORT, PIN, 0)  
```
4. Change this definition to use delay (in milliseconds) in the library:
 ```bash
    #define ALCD_DELAY(ms)                  HAL_Delay(ms)
```

That's all you need to do for setup!

For using functions there is an example in main.c:
```bash
    #include "alcd.h"
    int main()
    {
        ALcdInit();	/// First you need to initialize the LCD
        ALcdLoadCC(CC_Success, 0);	/// Load a custom character into LCD CGRAM
        ALcdLoadCC(CC_Info, 1);		/// Load another custom character into LCD CGRAM
        ALcdPrintCC(ALCD_CLEAR, 0, 0, 0);	/// Clear the LCD and print the first custom character
        ALcdPrintString(ALCD_NO_CLEAR, "ALCD library", 1, 0);	/// Print a string without clearing the LCD in the first row and second column (counting from zero including the zero)
        ALcdPrintCC(ALCD_NO_CLEAR, 0, 1, 1);	/// Print the second custom character in the second row and the second column		
        ALcdPrintString(ALCD_NO_CLEAR, "Test For STM32", 1, 1);	/// Print a string without clearing the LCD in the second row and second column (counting from zero including the zero)

        while(1)
        {

        }
    }
```

## Roadmap
- Support for 8-bit configuration
- Support for serial configuration
- Support for different sizes
