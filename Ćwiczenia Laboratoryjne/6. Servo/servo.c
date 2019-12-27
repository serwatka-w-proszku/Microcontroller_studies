#include <LPC21xx.H>
#include "led.h"
#include "servo.h"
#include "timer_interrupts.h"

#define mDetector 0x00000400 //1<<10

//cwiczenie 1

void DetectorInit(void){
	IO0DIR &= ~(mDetector);  //ustawienie pinu detektora jako wejsciowego (aktywowany zerem)
}

enum DetectorState eReadDetector(void){
	if((IO0PIN&mDetector)==0){
		return INACTIVE;
	}
	else{
		return ACTIVE;
	}
} 

//cwiczenie 2

struct Servo sServo;

//cwiczenie 3

void Servo_Callib(void){
	sServo.eState = CALLIB;
}

void Servo_GoTO(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
}

void Automat(void){
	switch(sServo.eState){
		case IN_PROGRESS: 
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					Led_StepLeft();
					sServo.uiCurrentPosition ++;
					sServo.eState = IN_PROGRESS;
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					Led_StepRight();
					sServo.uiCurrentPosition --;
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
				}
				break;
				
		case CALLIB: 
				if(INACTIVE == eReadDetector()){
					Led_StepRight();
					sServo.eState = CALLIB;
				}
				else{
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				}
				break;
		
		case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
				}
				break;
	}
}

void Servo_Init(unsigned int uiServoFrequency){
	sServo.eState = CALLIB;
	DetectorInit();
	Led_Init();
	Timer0Interrupts_Init(uiServoFrequency, Automat);
}
