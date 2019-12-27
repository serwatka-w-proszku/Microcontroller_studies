#include "timer.h"
#include "led.h"

int main(void)
{
	unsigned int uiLoopCounter;
	Led_Init();
	
	InitTimer0Match0(500000);
	for(uiLoopCounter = 0; uiLoopCounter < 100; uiLoopCounter++) {
		WaitOnTimer0Match0();
	}
	
	return 0;
}
