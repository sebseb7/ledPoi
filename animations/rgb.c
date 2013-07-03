#include "main.h"


static uint8_t tick(uint32_t lap __attribute__((unused)), uint32_t angle, struct segment_t *segment) 
{

	uint8_t red;
	uint8_t green;
	uint8_t blue;

	if ((angle>>4)%3==0)
	{
		red=255;
		green=0;
		blue=0;
	}
	else if ((angle>>4)%3 == 1)
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




