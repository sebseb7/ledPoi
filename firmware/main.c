#include "main.h"

/*

	data sheet  : http://www.nxp.com/documents/data_sheet/LPC1315_16_17_45_46_47.pdf
	user manual : http://www.nxp.com/documents/user_manual/UM10524.pdf

	SCK : 1_20
	MOSI: 1_22
	ADC : 0_11
	BUT : 0_1

*/

//#include "usb/usb_cdc.h"
#include "core/inc/adc.h"

float voltage;

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
	msTicks++;
}

uint32_t get_voltage(void)
{
	return (uint32_t)voltage;
}


void delay_ms(uint32_t ms) {
	uint32_t now = msTicks;
	while ((msTicks-now) < ms*10);
}
void delay_100ns(uint32_t ms) {
	uint32_t now = msTicks;
	while ((msTicks-now) < ms);
}

#define MAX_ANIMATIONS 200
int animationcount = 0;

struct animation {
	init_fun init_fp;
	tick_fun tick_fp;
	deinit_fun deinit_fp;
	uint32_t duration;
	uint32_t idle;
} animations[MAX_ANIMATIONS];


void registerAnimation(init_fun init,tick_fun tick, deinit_fun deinit,uint16_t count, uint8_t idle)
{
	if(animationcount == MAX_ANIMATIONS)
		return;
	animations[animationcount].init_fp = init;
	animations[animationcount].tick_fp = tick;
	animations[animationcount].deinit_fp = deinit;
	animations[animationcount].duration = count;
	animations[animationcount].idle = idle;

	animationcount++;
}

int main(void) {


	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10000);

	// clock to GPIO
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	// AD0
	LPC_IOCON->TDI_PIO0_11  &= ~0x07;
	LPC_IOCON->TDI_PIO0_11  |= 0x02;
	
	// pull-up 
	LPC_IOCON->PIO0_1  &= ~0x18;
	LPC_IOCON->PIO0_1  |= 0x10;


	leds_init();

	// green red blue

//	usb_init();
//	delay_ms(1000);
	
	ADCInit(ADC_CLK);

	int current_animation = 0;
	animations[current_animation].init_fp();
	
	uint32_t lap = 0;
	uint32_t angle = 0 ; 
	delay_ms(100);
	voltage=(ADCRead(0)/4096.0f*3.3f*4157.0f);
	delay_ms(100);

	while(1)
	{
		if(angle == 0)
		{
//			usbprintf("voltage: %i\n",(uint32_t)(voltage));
			voltage = (voltage*5.0f + (ADCRead(0)/4096.0f*3.3f*4157.0f))/6.0f;
		}


		struct segment_t segment;

		animations[current_animation].tick_fp(lap,angle,&segment);
			
		for(int x = 0; x < LED_WIDTH; x++) 
		{
			setLedX(x,segment.color[x].red,segment.color[x].green,segment.color[x].blue);
		}
		leds_flush();

		delay_100ns(2);

		angle++;
		if(angle == 360*4)
		{
			angle=0;
			lap++;
		}


		if(lap == animations[current_animation].duration)
		{
			animations[current_animation].deinit_fp();

			current_animation++;
			if(current_animation == animationcount)
			{
				current_animation = 0;
			}

			lap=0;
			angle=0;

			animations[current_animation].init_fp();

		}

	}
}

