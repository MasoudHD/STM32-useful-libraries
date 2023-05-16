

int main()
{
    ALcdInit();
	ALcdLoadCC(CC_Success, 0);
	ALcdLoadCC(CC_Info, 1);
	ALcdPrintCC(ALCD_CLEAR, 0, 0, 0);
	ALcdPrintString(ALCD_NO_CLEAR, "ALCD library", 1, 0);
	ALcdPrintCC(ALCD_NO_CLEAR, 0, 1, 1);
	ALcdPrintString(ALCD_NO_CLEAR, "Test For STM32", 1, 1);

    while(1)
    {

    }
}