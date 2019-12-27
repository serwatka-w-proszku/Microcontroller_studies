//Program zrobiony do punktu 22 wlacznie. Funkcje StepRight i StepLeft zostal wymazane a ich zawartosc przeniesiona do odpowiednich if'ow 
//w funkcji eLedStep

#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000
#define BUTT1_bm 0x00000010
#define BUTT2_bm 0x00000020
#define BUTT3_bm 0x00000040
#define BUTT4_bm 0x00000080
//Button1 to: P0.04, Button2 to: P0.05, Button3 to: P0.06, Button4 to: P0.07



void Delay(int iDelayTime)
{
	int iDelayCounter;
	int iDelayCounterMaxValue;
	
	iDelayCounterMaxValue=((iDelayTime)*(12000000/1000)); 	
	for (iDelayCounter=0; iDelayCounter < iDelayCounterMaxValue; iDelayCounter++) {}
}


void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1CLR = LED0_bm|LED1_bm|LED2_bm|LED3_bm;
  IO1SET = LED0_bm;
}


void KeyboardInit()
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


enum KeyboardState {RELASED, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};

enum KeyboardState eKeyboard_Read()
{
	if ((IO0PIN&BUTT1_bm)==0) 
	{
		return BUTTON_1;
	}
	else if ((IO0PIN&BUTT2_bm)==0) 
	{
		return BUTTON_2;
	}
	else if ((IO0PIN&BUTT3_bm)==0) 
	{
		return BUTTON_3;
	}
	else if ((IO0PIN&BUTT4_bm)==0) 
	{
		return BUTTON_4;
	}
	else
	{
		return RELASED;
	}
}


enum LedStep {LEFT, RIGHT};


void eLedStep(enum LedStep eStepDirection)
{
	static unsigned int uiStepModulo;
	
	if (eStepDirection==LEFT)
	{
		if (uiStepModulo == 0) 
		{
			uiStepModulo=4;
		}
		uiStepModulo=uiStepModulo-1;
		uiStepModulo=uiStepModulo%4;
		Led_On(uiStepModulo);
	}
	else
	{
		uiStepModulo=uiStepModulo+1;
		uiStepModulo=uiStepModulo%4;
		Led_On(uiStepModulo);;
	}
}


int main()
{
	
LedInit();
KeyboardInit();

while(1)
{
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(LEFT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
	eLedStep(RIGHT);
	Delay(250);
}
}
