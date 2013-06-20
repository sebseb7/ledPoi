#include "main.h"


static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{


	uint8_t green = 180 - ((angle + lap) % 180);
	uint8_t red = (angle - lap + 1440) % 180;;

	segment->color[0].red = red;
	segment->color[1].red = red;
	segment->color[2].red = red;
	segment->color[3].red = red;
	segment->color[4].red = 0;
	segment->color[5].red = 0;
	segment->color[6].red = 0;
	segment->color[7].red = 0;
	
	segment->color[0].green = 0;
	segment->color[1].green = 0;
	segment->color[2].green = 0;
	segment->color[3].green = 0;
	segment->color[4].green = green;
	segment->color[5].green = green;
	segment->color[6].green = green;
	segment->color[7].green = green;
	
	segment->color[0].blue = 0;
	segment->color[1].blue = 0;
	segment->color[2].blue = 0;
	segment->color[3].blue = 0;
	segment->color[4].blue = 0;
	segment->color[5].blue = 0;
	segment->color[6].blue = 0;
	segment->color[7].blue = 0;

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
	registerAnimation(init,tick,deinit, 305, 10000,0);
}




