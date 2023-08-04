
# EEPROM library for STM32

This library is for saving data into the internal flash of STM32 microcontrollers. Writing data is quite easy. You can find an example (main.c) to show how to use it. In this version of the library, every time you want to save data, you should all previous data. So it is better to have a structure for all data you want to write in Flash and pass it as a pointer to this library.