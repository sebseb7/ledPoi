#include "main.h"

#include "core/inc/ssp1.h"

/*

	data sheet  : http://www.nxp.com/documents/data_sheet/LPC1315_16_17_45_46_47.pdf
	user manual : http://www.nxp.com/documents/user_manual/UM10524.pdf

	SCK : 1_20
	MOSI: 1_22
	ADC : 0_11
	BUT : 0_1

*/

static const uint8_t color_correction[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,15,15,15,16,16,16,17,17,17,18,18,18,19,19,20,20,20,21,21,22,22,23,23,23,24,24,25,25,26,26,27,27,28,29,29,30,30,31,32,32,33,33,34,35,35,36,37,38,38,39,40,41,41,42,43,44,45,46,47,48,48,49,50,51,52,53,54,56,57,58,59,60,61,62,64,65,66,67,69,70,71,73,74,76,77,79,80,82,83,85,87,88,90,92,93,95,97,99,101,103,105,107,109,111,113,115,118,120,122,125,127};

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

	// AD0
	LPC_IOCON->TDI_PIO0_11  &= ~0x07;
	LPC_IOCON->TDI_PIO0_11  |= 0x02;
	
	// pull-up 
	LPC_IOCON->PIO0_1  &= ~0x18;
	LPC_IOCON->PIO0_1  |= 0x10;

	ssp1Init();


	while(1)
	{
		ssp1SendByte(0x80 | color_correction[0] );
		ssp1SendByte(0x80 | color_correction[0] );
		ssp1SendByte(0x80 | color_correction[25] );

		ssp1SendByte(0x80 | color_correction[0] );
		ssp1SendByte(0x80 | color_correction[25] );
		ssp1SendByte(0x80 | color_correction[0] );

		ssp1SendByte(0x80 | color_correction[25] );
		ssp1SendByte(0x80 | color_correction[0] );
		ssp1SendByte(0x80 | color_correction[0] );

		ssp1SendByte(0x80 | color_correction[25] );
		ssp1SendByte(0x80 | color_correction[25] );
		ssp1SendByte(0x80 | color_correction[25] );
	

		ssp1SendByte(0);
		
		//delay_ms(100);
	}
}

