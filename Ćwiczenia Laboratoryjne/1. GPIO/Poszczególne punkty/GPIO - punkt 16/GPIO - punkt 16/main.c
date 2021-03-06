// program zrobiony do podpunktu 16 wlacznie

#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define LEDAll_bm 0x000F0000
#define BUTT1_bm 0x00000010


void Delay(int iDelayTime)
{
	int iDelayCounter;
	int iDelayCounterMaxValue;
	
	iDelayCounterMaxValue=((iDelayTime)*(12000000/1000)); 	
	for (iDelayCounter=0; iDelayCounter < iDelayCounterMaxValue; iDelayCounter++)
	{
	}
}

void LedInit()
{
	IO1DIR = IO1DIR|LEDAll_bm;
	//znak '|' reprezentuje 'or' czyli dodawanie
  IO1SET = LED0_bm;
}


void Led_On (unsigned char ucLedIndeks)
{
  switch(ucLedIndeks)
	{
		case 0:
						IO1CLR = LEDAll_bm;
						IO1SET = LED0_bm;
						break;
		case 1:
						IO1CLR = LEDAll_bm;
						IO1SET = LED1_bm;
						break;
		case 2:
						IO1CLR = LEDAll_bm;
						IO1SET = LED2_bm;
						break;
		case 3:
						IO1CLR = LEDAll_bm;
						IO1SET = LED3_bm;
						break;
		default: 
						break;
	}
}


enum ButtonState{RELASED, PRESSED};


//Button to: P0.04
enum ButtonState ReadButton1()
{
	if ((IO0PIN&BUTT1_bm)==0)
//jakby w warunku bylo 0x03FFFFFF to nie zadziala	('bo czyta tylko pierwsze(?) cztery bity')	
	{
		return PRESSED;
	}
	else
	{
		return RELASED;
	}
}



int main()
{
	
LedInit();

while(1)
{
	if (ReadButton1()==PRESSED)
	{
		Led_On (1);
	}
	else
	{
		Led_On (0);
	}
};

}
