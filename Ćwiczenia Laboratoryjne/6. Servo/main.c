#include <LPC21xx.H>
#include "keyboard.h"
#include "led.h"
#include "servo.h"


int main (void){
	
	KeyboardInit();
	Servo_Init(1000);
	
	switch(eKeyboard_Read()){
		case BUTTON_1:
			Servo_Callib();
			break;
		case BUTTON_2:
			Servo_GoTo(50);
			break;
		case BUTTON_3:
			Servo_GoTo(100);
			break;
		case BUTTON_4:
			Servo_GoTo(150);
			break;
		default:
			break;

	}
}
