#include <LPC21xx.H>

#define mCOUNTER_ENABLE 0x00000001 	  //1<<1
#define mCOUNTER_RESET  0x00000002		//1<<2

#define mINTERRUPT_ON_MR0 0x00000001  //1<<1
#define mRESET_ON_MR0     0x00000002  //1<<2
#define mMR0_INTERRUPT    0x00000001  //1<<1

#define VIC_TIMER0_CHANNEL_NR 4

#define mIRQ_SLOT_ENABLE 0x00000020   //1<<5

void (*ptrTimer0InterruptFunction)(void); //inicjalizacja wskanika na funkcje

__irq void Timer0IRQHandler(void){
	T0IR = mMR0_INTERRUPT;				//skasowanie flagi przerwania
	ptrTimer0InterruptFunction();	//wywolanie funkcji przerwania
	VICVectAddr = 0x00;						// potwierdzenie wykonania procedury obslugi przerwania
}

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void)){	
	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR); 					//odblokowanie przerwania z kanalu 4.
	VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR; //wlaczenie slotu 1., ustawienie na przerwania z kanalu 4.
	VICVectAddr1  =	(unsigned long)Timer0IRQHandler;					//przypisanie adresu obslugi przerwania
	ptrTimer0InterruptFunction = ptrInterruptFunction;				//przypisanie adresu dla funkcji ptrTimer0InterruptFunction

	T0MR0 = 15 * uiPeriod;																		//przypisanie okresu do rejestru match
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0);							

	T0TCR |=  mCOUNTER_ENABLE;																//wlaczenie timera
}
