#include <LPC21xx.H>
#include "uart.h"
#include "string.h"
#include "servo.h"
#include "watchdog.h"
#include "timer_interrupts.h"
#include "command_decoder.h"
#include "keyboard.h"


char cReceivedString[RECIEVER_SIZE];
char cTransmitString[TRANSMITER_SIZE];
char cSecondsString[7];
char cMinutesString[7];
char cCalcString[7];
unsigned char fCalc;
unsigned char fId;
unsigned char fUnknown;

int main(void){
	UART_InitWithInt(9600);
	Servo_Init(400);
	KeyboardInit();
	Timer0Interrupts_Init(1000000, &WatchUpdate);
		
	while(1){		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cReceivedString);
			DecodeMsg(cReceivedString);
			if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case CALCULATE:
						fCalc = 1;
						break;
					case ID:
						fId = 1;
						break;
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
			else{
				fUnknown = 1;
			}
		}		
		
		if(Transmiter_GetStatus() == FREE){
			if(sWatch.fSecondsValueChanged == 1){
				CopyString("sec ", sTransmiterBuffer.cData);
				AppendUIntToString(sWatch.ucSeconds, sTransmiterBuffer.cData);
				Transmiter_SendString(cTransmitString);
				sWatch.fSecondsValueChanged = 0;
			}
			else if(sWatch.fMinutesValueChanged == 1){
				CopyString("min ", sTransmiterBuffer.cData);
				AppendUIntToString(sWatch.ucMinutes, sTransmiterBuffer.cData);
				Transmiter_SendString(cTransmitString);
				sWatch.fMinutesValueChanged = 0;
			}
			else if(fCalc == 1){
				CopyString("calc ", sTransmiterBuffer.cData);
				AppendUIntToString((asToken[1].uValue.uiNumber*2), sTransmiterBuffer.cData);
				Transmiter_SendString(cTransmitString);
				fCalc = 0;
			}
			else if(fId == 1){
				CopyString("ID 95102503", sTransmiterBuffer.cData);
				Transmiter_SendString(cTransmitString);
				fId = 0;
			}
			else if(fUnknown == 1){
				CopyString("UnknownCommand", sTransmiterBuffer.cData);
				Transmiter_SendString(cTransmitString);
				fUnknown = 0;
			}
		}
	}
}
