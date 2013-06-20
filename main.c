#include "main.h"

/*

	data sheet  : http://www.nxp.com/documents/data_sheet/LPC1315_16_17_45_46_47.pdf
	user manual : http://www.nxp.com/documents/user_manual/UM10524.pdf

	SCK : 1_20
	MOSI: 1_22
	ADC : 0_11
	BUT : 0_1

*/

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
	msTicks++;
}

void delay_ms(uint32_t ms) {
	uint32_t now = msTicks;
	while ((msTicks-now) < ms);
}

int main(void) {


	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	// clock to GPIO
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	// SCK1
	LPC_IOCON->PIO1_20  &= ~0x07;
	LPC_IOCON->PIO1_20  |= 0x02;

	// MOSI1
	LPC_IOCON->PIO1_22  &= ~0x07;
	LPC_IOCON->PIO1_22  |= 0x02;
	
	// AD0
	LPC_IOCON->TDI_PIO0_11  &= ~0x07;
	LPC_IOCON->TDI_PIO0_11  |= 0x02;
	
	// pull-up 
	LPC_IOCON->PIO0_1  &= ~0x18;
	LPC_IOCON->PIO0_1  |= 0x10;



	while(1)
	{
	}
}

