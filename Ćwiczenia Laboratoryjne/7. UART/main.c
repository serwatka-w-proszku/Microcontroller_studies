#include <LPC21xx.H>
#include "uart.h"
#include "servo.h"
#include "keyboard.h"
#include "led.h"

#define LED0_bm 0x1<<16
#define LED1_bm 0x1<<17
#define LED2_bm 0x1<<18
#define LED3_bm 0x1<<19

//Global variables

extern char cOdebranyZnak;
unsigned int uiDesiredPosition = 0;


int main(void){
	
	Servo_Init(400);
	KeyboardInit();
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
			default:
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
	}
}

/*
------------CWICZENIE 2-------------	
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

*/

/* 
------------CWICZENIE 3-------------

	Servo_Init(2500);
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

	Servo_Init(2500);
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
