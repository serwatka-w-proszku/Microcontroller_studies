#include <LPC21xx.H>
#include "led.h"

#define mLED0 0x1<<16
#define mLED1 0x1<<17
#define mLED2 0x1<<18
#define mLED3 0x1<<19

void Led_Init(void)
{
	IO1DIR |= (mLED0 | mLED1 | mLED2 | mLED3);
	IO1CLR = (mLED0 | mLED1 | mLED2 | mLED3);
	IO1SET = mLED0;
}

void Led_On(unsigned char ucNumerDiody)
{
	IO1DIR |= (mLED0 | mLED1 | mLED2 | mLED3);
	IO1CLR = (mLED0 | mLED1 | mLED2 | mLED3);

	switch (ucNumerDiody)
	{
		case 0:
				IO1SET = mLED0;
				break;		
		case 1:
				IO1SET = mLED1;
				break;		
		case 2:
				IO1SET = mLED2;
				break;		
		case 3:
				IO1SET = mLED3;
				break;
	}
}

void Led_Step(enum LedState eLedState)
{
	static unsigned int uiLedState = 0;
	
	if(eLedState == LED_LEFT)
	{
			uiLedState++;
			Led_On((uiLedState%4));
	}
	else
	{
			uiLedState--;
			Led_On((uiLedState%4));
	}
}

void Led_StepLeft(void)
{
	Led_Step(LED_LEFT);
}

void Led_StepRight(void)
{
	Led_Step(LED_RIGHT);
}
