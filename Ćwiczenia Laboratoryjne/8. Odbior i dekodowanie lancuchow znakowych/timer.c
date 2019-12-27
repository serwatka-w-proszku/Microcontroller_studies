#include <LPC21xx.H>

#define mCOUNTER_ENABLE   0x00000001
#define mCOUNTER_RESET    0x00000002

#define mINTERRUPT_ON_MR0 0x00000001
#define mMR0_INTERRUPT    0x00000001

#define NULL 0
#define CYCLES_IN_uS 15

void InitTimer0(void){
	T0TCR |= mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~mCOUNTER_RESET;
	
	while(uiTime * CYCLES_IN_uS > T0TC){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MCR |= mINTERRUPT_ON_MR0;
	T0MR0	 = CYCLES_IN_uS * iDelayTime;
	T0TCR |= mCOUNTER_ENABLE;
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~mCOUNTER_RESET;
}

void WaitOnTimer0Match0(void){
	while((mMR0_INTERRUPT & T0IR) == 0){}
		
	T0IR	|= mMR0_INTERRUPT;	
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~mCOUNTER_RESET;
}
