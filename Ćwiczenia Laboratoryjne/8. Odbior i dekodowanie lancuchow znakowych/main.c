#include <LPC21xx.H>
#include "uart.h"
#include "servo.h"
#include "string.h"
#include "command_decoder.h"



char ucReceivedString[RECIEVER_SIZE];

int main(void){
	Servo_Init(400);
	UART_InitWithInt(9600);
	
	while(1){		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(ucReceivedString);
			DecodeMsg(ucReceivedString);
			if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case CALIBRATION:
						Servo_Callib();
						break;
					case GOTO:
						Servo_GoTo(asToken[1].uValue.uiNumber); 
						break;
					default:
						break;
				}
			}
		}
	}
}
