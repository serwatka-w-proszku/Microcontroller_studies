#include <LPC210X.H>
#include "uart.h"


// UART

// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// Pin selection
#define	mRX_DATA_AVALIABLE_ON_P0_1								 0x00000004

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004


//	Interrupts

// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020 


// Global variables


char cOdebranyZnak;


//	UART Interrupt vector

__irq void UART0_Interrupt (void) {
   
   unsigned int uiCopyOfU0IIR=U0IIR; 																																					// odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii																																				// odczyt U0IIR powoduje jego kasowanie

   if	((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING){ 	// odebrano znak (str 143) - "010: 2a.Receive Data Available (RDA)"
      cOdebranyZnak = U0RBR;																																									//U0RBR str 141 - zawiera najstarszy otrzymany znak, niezapelniony bajt jest uzupelniany zerami, read only
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING){              	// wyslano znak - nadajnik pusty (str 143/144) - "001: 3. THRE Interrupt"
																																																							// narazie nic nie wysylamy
   }

   VICVectAddr = 0x00; 			 																																									// Potwierdzenie wykonania procedury obslugi przerwania
}


//	UART initialisation

void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0	|= mRX_DATA_AVALIABLE_ON_P0_1	;                       // ustawic pina na odbiornik uart0
   U0LCR		|= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1  (str 146)
   U0DLL  	 = (((15000000)/16)/uiBaudRate);                      // predkosc transmisji			(str 142)
   U0LCR	  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER 		|= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // interrupt when data on Rx avaliable (str 143)

   // Interrupt
   VICVectAddr0  = (unsigned long) UART0_Interrupt;           	  // set interrupt service routine address
   VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     	// use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);                 // Enable UART 0 Interrupt Channel
}

