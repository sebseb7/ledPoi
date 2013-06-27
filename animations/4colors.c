#include "main.h"


static uint8_t tick(uint32_t lap __attribute__((unused)), uint32_t angle, struct segment_t *segment) 
{

	uint8_t red;
	uint8_t green;
	uint8_t blue;

	if(angle < 360)
	{
		red=255;
		green=255;
		blue=255;
	}
	else if (angle < 720)
	{
		red=255;
		green=0;
		blue=0;
	}
	else if (angle < 1080)
	{
		red=0;
		green=255;
		blue=0;
	}
	else 
	{
		red=0;
		green=0;
		blue=255;
	}
#ifdef SIMULATOR
	uint32_t voltage = 12000;
#else
	uint32_t voltage = get_voltage();
#endif
	
	if(voltage < 10000)
	{
		red=25;
		green=0;
		blue=0;
	}

	for(uint8_t x = 0; x < LED_WIDTH;x++)
	{
		segment->color[x].red = red;
	
		segment->color[x].green = green;
	
		segment->color[x].blue = blue;
	}




	if(voltage < 11400)
	{
		segment->color[9].blue = 0;
	}
	if(voltage < 11300)
	{
		segment->color[8].blue = 0;
	}
	if(voltage < 11200)
	{
		segment->color[7].blue = 0;
	}
	if(voltage < 11100)
	{
		segment->color[6].blue = 0;
	}
	if(voltage < 11000)
	{
		segment->color[5].blue = 0;
	}
	if(voltage < 10900)
	{
		segment->color[4].blue = 0;
	}
	if(voltage < 10800)
	{
		segment->color[3].blue = 0;
	}
	if(voltage < 10700)
	{
		segment->color[2].blue = 0;
	}
	if(voltage < 10600)
	{
		segment->color[1].blue = 0;
	}
	if(voltage < 10400)
	{
		segment->color[0].blue = 0;
	}

	return 0;
}

static void init(void)
{
}
static void deinit(void)
{
}



static void constructor(void) CONSTRUCTOR_ATTRIBUTES
void constructor(void) {
	registerAnimation(init,tick,deinit, 20,0);
}




