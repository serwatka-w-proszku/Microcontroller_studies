#include <LPC21xx.H>
#include "keyboard.h"

#define mBUTTON1 0x1<<4
#define mBUTTON2 0x1<<5
#define mBUTTON3 0x1<<6
#define mBUTTON4 0x1<<7

void KeyboardInit(void)
{
	IO0DIR &= ~(mBUTTON1 | mBUTTON2 | mBUTTON3 | mBUTTON4);
}

enum KeyboardState eKeyboard_Read(void)
{
	if((IO0PIN & mBUTTON1) == 0) {
			return BUTTON_1;
	}	
	else if((IO0PIN & mBUTTON2) == 0) {
			return BUTTON_2;
	}	
	else if((IO0PIN & mBUTTON3) == 0) {
			return BUTTON_3;
	}	
	else if((IO0PIN & mBUTTON4) == 0) {
			return BUTTON_4;
	}	
	else {
			return RELEASED;
	}
}
