#include <LPC21xx.H>
#include "timer.h"

#define mCOUNTER_ENABLE		0x1
#define mCOUNTER_RESET		0x2

#define mRESET_ON_MR0			0x2
#define mINTERRUPT_ON_MR0	0x1

#define mMR0_INTERRUPT		0x1

void InitTimer0(void)
{
	T0TCR |= mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR |= mCOUNTER_RESET;
	T0TCR &= ~(mCOUNTER_RESET);
	while( T0TC < (15 * uiTime) ) { };
}

void InitTimer0Match0(unsigned int uiDelayTime)
{
	T0MR0 = uiDelayTime * 15;
	T0MCR |= ( mRESET_ON_MR0 | mINTERRUPT_ON_MR0 );
	T0TCR |= ( mCOUNTER_ENABLE | mCOUNTER_RESET );
	T0TCR &= ~(mCOUNTER_RESET);
}

void WaitOnTimer0Match0(void)
{
	while((T0IR & mMR0_INTERRUPT)== 0) { };
	T0IR |= mMR0_INTERRUPT;
}
