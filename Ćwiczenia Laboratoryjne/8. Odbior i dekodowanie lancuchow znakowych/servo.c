#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm 1<<10

/**********enum declaration***********/

enum KeyboardRead {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

/**********structure declaration***********/

struct Servo{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

struct Servo sServo;

/**********function declaration***********/

void DetectorInit(void){
	IO0DIR &= ~(DETECTOR_bm);
}


enum KeyboardRead eKeyboardRead(void){
	if ((DETECTOR_bm & IO0PIN) == 0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
};

void ServoControll(void){
	switch(sServo.eState){		
		case CALLIB: 
				if(ACTIVE == eKeyboardRead()){
					sServo.uiDesiredPosition = 0;
					sServo.uiCurrentPosition = 0;
					sServo.eState = IDLE;
				}
				else{
					Led_StepLeft();
					sServo.eState = CALLIB;
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
				
		case IN_PROGRESS: 
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					sServo.uiCurrentPosition ++;
					Led_StepRight();
					sServo.eState = IN_PROGRESS;
				}
				else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					sServo.uiCurrentPosition --;
					Led_StepLeft();
					sServo.eState = IN_PROGRESS;
				}
				else{
					sServo.eState = IDLE;
		}
				break;
	}
};

void Servo_Init(unsigned int uiServoFrequency){
	DetectorInit();
	Led_Init();
	sServo.eState = CALLIB;
	Timer0Interrupts_Init(1000000/uiServoFrequency, ServoControll); //zamiana okresu na czestotliwosc 
};

void Servo_Callib(void){
	sServo.eState = CALLIB;
};

void Servo_GoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
};
