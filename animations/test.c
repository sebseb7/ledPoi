#include "main.h"


static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{

	uint8_t red;
	uint8_t green;
	uint8_t blue;

	if(angle < 60)
	{
		red=255;
		green=0;
		blue=0;
	}
	else 
	{
		red=0;
		green=0;
		blue=0;
	}



	for(uint8_t x = 0; x < LED_WIDTH;x++)
	{
		segment->color[x].red = red;
	
		segment->color[x].green = green;
	
		segment->color[x].blue = blue;
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




