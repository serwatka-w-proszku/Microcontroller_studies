#include <LPC21xx.H>
#include "uart.h"
#include "servo.h"
#include "keyboard.h"
#include "led.h"

//Global variables

extern char cOdebranyZnak;
unsigned int uiDesiredPosition = 0;


int main(void){
	
	
/*
------------CWICZENIE 2-------------
	
	UART_InitWithInt(9600);
	Led_Init();
	
	while(1){	
	
		switch(cOdebranyZnak){
			
			case 'c':
				IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
				cOdebranyZnak = 0;
				break;
	
			case '0':
				Led_On(0);
				cOdebranyZnak = 0;
				break;			
			
			case '1':
				Led_On(1);
				cOdebranyZnak = 0;
				break;
				
			case '2':
				Led_On(2);
				cOdebranyZnak = 0;
				break;
			
			case '3':
				Led_On(3);
				cOdebranyZnak = 0;
				break;			
		}
	}
*/




/* 
------------CWICZENIE 3-------------

	Servo_Init(500);
	Keyboard_Init();
	UART_InitWithInt(9600);
	
	while(1){
		
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
		}
		
		switch(cOdebranyZnak){
			case 'c':
				Servo_Callib();
				cOdebranyZnak = 0;
				break;			
			
			case '1':
				Servo_GoTo(50);
				cOdebranyZnak = 0;
				break;
				
			case '2':
				Servo_GoTo(100);
				cOdebranyZnak = 0;
				break;
			
			case '3':
				Servo_GoTo(150);
				cOdebranyZnak = 0;
				break;		
		}
	
*/

/*
------------CWICZENIE 4-------------

	Servo_Init(500);
	Keyboard_Init();
	UART_InitWithInt(9600);
	
	while(1){
		
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
		}
		
		switch(cOdebranyZnak){
			case 'c':

				Servo_Callib();
				uiDesiredPosition = 0;
				cOdebranyZnak = 0;
				break;
			
			case '1':
				uiDesiredPosition = uiDesiredPosition + 50; 
				Servo_GoTo(uiDesiredPosition);
				cOdebranyZnak = 0;
				break;	
		}


*/

}
