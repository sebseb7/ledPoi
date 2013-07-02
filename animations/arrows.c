#include "main.h"


static uint8_t tick(uint32_t lap __attribute__((unused)), uint32_t angle, struct segment_t *segment) 
{

	uint8_t red[10] =  {0,0,0,0,0,0,0,0,0,0};
	uint8_t green[10] =  {0,0,0,0,0,0,0,0,0,0};
	uint8_t blue[10] = {0,0,0,0,0,0,0,0,0,0};

	uint16_t step = angle % 360;




	if(step < 130)
	{
		for(uint8_t x = 0; x < LED_WIDTH;x++)
		{
			blue[x] = 255;
		}
		blue[4] = 0;
		blue[5] = 0;
		red[4] = 255;
		red[5] = 255;
	}
	else if(step < 150)
	{
		for(uint8_t x = 1; x < (LED_WIDTH-1);x++)
		{
			blue[x] = 255;
		}
		blue[4] = 0;
		blue[5] = 0;
		red[4] = 255;
		red[5] = 255;
		red[0] = 255;
		red[9] = 255;
	}
	else if(step < 170)
	{
		for(uint8_t x = 2; x < (LED_WIDTH-2);x++)
		{
			blue[x] = 255;
		}
		blue[4] = 0;
		blue[5] = 0;
		red[4] = 255;
		red[5] = 255;
		red[0] = 255;
		red[9] = 255;
		red[1] = 255;
		red[8] = 255;
	}
	else if(step < 190)
	{
		for(uint8_t x = 0; x < LED_WIDTH;x++)
		{
			red[x] = 255;
		}
		blue[3] = 255;
		blue[6] = 255;
		red[3] = 0;
		red[6] = 0;
	}
	else if(step < 210)
	{
		for(uint8_t x = 1; x < (LED_WIDTH-1);x++)
		{
			red[x] = 255;
		}
		blue[0] = 255;
		blue[9] = 255;
	}
	else if(step < 230)
	{
		for(uint8_t x = 2; x < (LED_WIDTH-2);x++)
		{
			red[x] = 255;
		}
		blue[0] = 255;
		blue[1] = 255;
		blue[8] = 255;
		blue[9] = 255;
	}
	else if(step < 250)
	{
		for(uint8_t x = 3; x < (LED_WIDTH-3);x++)
		{
			red[x] = 255;
		}
		blue[0] = 255;
		blue[1] = 255;
		blue[2] = 255;
		blue[7] = 255;
		blue[8] = 255;
		blue[9] = 255;
	}
	else if(step < 270)
	{
		for(uint8_t x = 4; x < (LED_WIDTH-4);x++)
		{
			red[x] = 255;
		}
		blue[0] = 255;
		blue[1] = 255;
		blue[2] = 255;
		blue[3] = 255;
		blue[6] = 255;
		blue[7] = 255;
		blue[8] = 255;
		blue[9] = 255;
	}else{
		for(uint8_t x = 0; x < LED_WIDTH;x++)
		{
			blue[x] =255;
		}
	}


	for(uint8_t x = 0; x < LED_WIDTH;x++)
	{
		segment->color[x].red = red[x];
	
		segment->color[x].green = green[x];
	
		segment->color[x].blue = blue[x];
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




