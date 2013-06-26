#include "main.h"


static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{
	uint8_t green = 180 - ((angle + (lap*10)) % 180);
	uint8_t red = (angle - (lap*10) + 1440) % 180;;
	
	for(uint8_t x = 0; x < LED_WIDTH/2;x++)
	{
		segment->color[x].red = red;
		segment->color[x].green = 0;
		segment->color[x].blue = 0;
	}
	for(uint8_t x = LED_WIDTH/2; x < LED_WIDTH;x++)
	{
		segment->color[x].red = 0;
		segment->color[x].green = green;
		segment->color[x].blue = 0;
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




