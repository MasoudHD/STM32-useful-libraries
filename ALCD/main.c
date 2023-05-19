#include "alcd.h"

int main()
{
	ALcdInit();	/// First you need to initilize the LCD
	ALcdLoadCC(CC_Success, 0);	/// Load a custom character into LCD CGRAM
	ALcdLoadCC(CC_Info, 1);		/// Load another custom character into LCD CGRAM
	ALcdPrintCC(ALCD_CLEAR, 0, 0, 0);	/// Clear the LCD and print the first custom character
	ALcdPrintString(ALCD_NO_CLEAR, "ALCD library", 1, 0);	/// Print a string without clearing the LCD in the first row and second column (counting from zero including the zero)
	ALcdPrintCC(ALCD_NO_CLEAR, 0, 1, 1);	/// Print the second custom character in second row and second column	
	ALcdPrintString(ALCD_NO_CLEAR, "Test For STM32", 1, 1);	/// Print a string without clearing the LCD in the second row and second column (counting from zero including the zero)

	while(1)
	{

	}
}