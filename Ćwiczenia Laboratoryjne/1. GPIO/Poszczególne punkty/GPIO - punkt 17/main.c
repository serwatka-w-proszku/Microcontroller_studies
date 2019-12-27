// program zrobiony do podpunktu 17 (tylko czy dobrze?)

#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define BUTT1_bm 0x00000010
//Button1 to: P0.04


void Delay(int iDelayTime)
{
	int iDelayCounter;
	int iDelayCounterMaxValue;
	
	iDelayCounterMaxValue=((iDelayTime)*(12000000/1000)); 	
	for (iDelayCounter=0; iDelayCounter < iDelayCounterMaxValue; iDelayCounter++) {}
}


void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm|LED1_bm|LED2_bm|LED3_bm); //znak '|' reprezentuje 'or' czyli dodawanie
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
  IO1SET = LED0_bm;
}


void ButtonInit()
{
	IO0DIR = IO0DIR&(~BUTT1_bm);
}


void Led_On (unsigned char ucLedIndeks)
{
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	
  switch(ucLedIndeks)
	{
		case 0:
						IO1SET = LED0_bm;
						break;
		case 1:
						IO1SET = LED1_bm;
						break;
		case 2:
						IO1SET = LED2_bm;
						break;
		case 3:
						IO1SET = LED3_bm;
						break;
		default: 
						break;
	}
}


enum ButtonState{RELASED, PRESSED};


enum ButtonState ReadButton1()
{
	if ((IO0PIN&BUTT1_bm)==0) //jakby w warunku bylo 0x03FFFFFF to nie zadziala	('bo czyta tylko pierwsze(?) cztery bity')	
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
ButtonInit();

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
