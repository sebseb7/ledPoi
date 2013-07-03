#include <string.h>

#include "main.h"

#include "libs/font8x6.h"




static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{

	const char* text = "   SEKTO(R)EVOLUTION    ";


	uint32_t length = strlen(text);

	uint32_t pos = (uint32_t)((angle)/10.0f);

	uint32_t charpos = (pos - (pos % 6))/6; 

	uint32_t ascii = 0 ; 

	if(charpos < length)
	{
		ascii = text[charpos]-32;
	}

	uint8_t line = font8x6[ascii][pos%6];

	for(uint8_t x = 0; x < 8;x++)
	{
		if((line & (1<<(7-x)))== (1<<(7-x)))
		{
			segment->color[x].red = 255;
			segment->color[x].green = 255;
			segment->color[x].blue = 255 ;
		}
		else
		{
			segment->color[x].red = 0;
			segment->color[x].green = 0;
			segment->color[x].blue = 30;
		}
	}
	segment->color[8].red = 0;
	segment->color[8].green = 0;
	segment->color[8].blue = 30 ;
	segment->color[9].red = 0;
	segment->color[9].green = 0;
	segment->color[9].blue = 30 ;

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




