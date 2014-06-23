#include <string.h>

#include "main.h"

#include "libs/font8x6.h"


static uint32_t h = 0;
static uint32_t s = 0;


static uint32_t nr=0;
static uint32_t ng=0;
static uint32_t nb=0;

static void hsv_to_rgb(void)	
{
	uint16_t R,G,B;			

	uint32_t i,f;
	uint16_t p, q, t;

	if( s == 0 ) 
	{
		nr=1023;										// Auf 8 Bit RGB skalieren, nacher nur noch kopieren
		ng=1023;
		nb=1023;	
		return;
	}

	i = (((uint32_t)h) * 6) & 0xFF0000;
	f = ((((uint32_t)h) * 6) - i)>>8;
	i >>= 16;
	p = 65535 - s * 256;
	q = 65535 - s * f;
	t = 65535 - s * (256 - f);

	switch( i )
	{
		case 0:
			R = 65535; G = t; B = p; break;
		case 1:
			R = q; G = 65535; B = p; break;
		case 2:
			R = p; G = 65535; B = t; break;
		case 3:
			R = p; G = q; B = 65535; break;			
		case 4:
			R = t; G = p; B = 65535; break;
		default:								
			R = 65535; G = p; B = q; break;				// case 5:					
	}

	nr=R>>8;
	ng=G>>8;
	nb=B>>8;


}





static uint8_t tick(uint32_t lap, uint32_t angle, struct segment_t *segment) 
{
	
	h = angle*150.0f+lap*10000;
	h = h % 0xffff;
	s=255;


	hsv_to_rgb();
	
	const char* text = "   GAGGALACKA    ";


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
			segment->color[x].red = nr;
			segment->color[x].green = ng;
			segment->color[x].blue = nb;
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




