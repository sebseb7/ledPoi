#include "main.h"



uint8_t sin_table[256] = 
{
	0,0,1,2,3,3,4,5,6,7,7,8,9,10,11,11,12,13,14,15,15,16,17,18,19,19,20,21,22,23,23,24,25,26,26,
	27,28,29,30,30,31,32,33,33,34,35,36,36,37,38,39,40,40,41,42,43,43,44,45,46,46,47,48,48,49,50,
	51,51,52,53,54,54,55,56,56,57,58,59,59,60,61,61,62,63,64,64,65,66,66,67,68,68,69,70,70,71,72,
	72,73,74,74,75,76,76,77,77,78,79,79,80,81,81,82,82,83,84,84,85,85,86,87,87,88,88,89,89,90,91,
	91,92,92,93,93,94,94,95,95,96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,103,104,104,
	105,105,106,106,107,107,107,108,108,109,109,110,110,110,111,111,112,112,112,113,113,113,114,
	114,114,115,115,116,116,116,117,117,117,117,118,118,118,119,119,119,120,120,120,120,121,121,
	121,121,122,122,122,122,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,125,125,
	126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
	127,127,127,127,127,127,127,127,127
};

// input 0..1023 ; output 0..255
uint8_t sini(uint16_t x)
{
	x = x & 1023;

#ifdef __AVR__
	if(x < 256) return pgm_read_byte(&sin_table[x])+128;
	if(x < 512) return pgm_read_byte(&sin_table[511-x])+128;
	if(x < 768) return 127-pgm_read_byte(&sin_table[x-512]);
	return 127-pgm_read_byte(&sin_table[1023-x]); 
#else
	if(x < 256) return sin_table[x]+128;
	if(x < 512) return sin_table[511-x]+128;
	if(x < 768) return 127-sin_table[x-512];
	return 127-sin_table[1023-x]; 
#endif

}

uint32_t h = 0;
uint32_t s = 0;


uint32_t nr=0;
uint32_t ng=0;
uint32_t nb=0;

void hsv_to_rgb(void)	
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

	h = angle*45.51f;
	s=255;
	
	//printf("%i\n",nr);

	hsv_to_rgb();
	
	for(uint8_t x = 0; x < LED_WIDTH;x++)
	{
		segment->color[x].red = nr ;//* (sini(lap*360+x*(1024/LED_WIDTH))/255.0f);
		segment->color[x].green = ng ;//* (sini(lap*360+x*(1024/LED_WIDTH))/255.0f);
		segment->color[x].blue = nb ;//* (sini(lap*360+x*(1024/LED_WIDTH))/255.0f);
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




