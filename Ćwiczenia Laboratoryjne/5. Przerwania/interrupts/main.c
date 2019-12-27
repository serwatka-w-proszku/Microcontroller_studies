#include "timer_interrupts.h"
#include "keyboard.h"
#include "led.h"

void Automat(void){
	enum ServoState { STOP, MOVE_LEFT, MOVE_RIGHT };
	static enum ServoState eServoState = STOP;
	
	switch(eServoState){
		case STOP :
			if(BUTTON_1 == eKeyboard_Read()){
				eServoState = MOVE_LEFT;
			}
			else if(BUTTON_3 == eKeyboard_Read()){
				eServoState = MOVE_RIGHT;
			}
			else {
				eServoState = STOP;
			}
				break;
			
		case MOVE_LEFT :
			if(BUTTON_2 == eKeyboard_Read()){
				eServoState = STOP;
			}
			else{
				Led_StepLeft();
			}
			break;		
			
		case MOVE_RIGHT :
			if(BUTTON_2 == eKeyboard_Read()){
				eServoState = STOP;
			}
			else{
				Led_StepRight();
			}
			break;
	}
}

int main (void){
	unsigned int uiMainLoopCtr;
	Timer0Interrupts_Init(100000, &Automat);

	while(1){
	 	uiMainLoopCtr++;
	}
}
