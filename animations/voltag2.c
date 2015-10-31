#include <string.h>
#include <stdio.h>

#include "main.h"


static unsigned int font5x3[] = {32319,17393,24253,32437,31879,30391,29343,31905,32447,31911};

int get_line(int i, int digit)
{
	if (i>2) return 0;
	if (digit<0) return 0;
	if (digit>9) return 0;

	int line = 0;
	for(int j=0;j<5;j++)
	{
		if(font5x3[digit] & (1<<(i*5+j)))
		{
			line |= (1<<j);
		}
	}
	return line;
}



static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{

	char text[17];
	sprintf(text,"%i",(int)get_voltage());

	uint32_t length = strlen(text);

	uint32_t pos = (uint32_t)((angle)/10.0f);

	uint32_t charpos = (pos - (pos % 4))/4; 

	int ascii = -1 ; 

	if(charpos < length)
	{
		ascii = text[charpos]-48;
	}
	
	uint8_t line = get_line(pos%4,ascii);

	for(uint8_t x = 0; x < 10;x++)
	{
		if(line & (1<<(4-x/2)))
		{
			segment->color[x].red = 255;
			segment->color[x].green = 255;
			segment->color[x].blue = 255;
		}
		else
		{
			segment->color[x].red = 0;
			segment->color[x].green = 0;
			segment->color[x].blue = 30;
		}
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
	registerAnimation(init,tick,deinit, 5,0);
}




