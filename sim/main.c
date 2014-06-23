#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>

#include "main.h"
#include <string.h>
#include<sys/time.h>


uint32_t get_voltage(void)
{
	return (uint32_t)10000;
}


int sdlpause = 0;

#define MAX_ANIMATIONS 200

int animationcount = 0;

struct animation {
	init_fun init_fp;
	tick_fun tick_fp;
	deinit_fun deinit_fp;
	uint duration;
	uint32_t idle;
} animations[MAX_ANIMATIONS];




SDL_Surface* screen;



void registerAnimation(init_fun init,tick_fun tick, deinit_fun deinit, uint16_t count, uint8_t idle)
{
	if(animationcount == MAX_ANIMATIONS)
		return;
	animations[animationcount].init_fp = init;
	animations[animationcount].tick_fp = tick;
	animations[animationcount].deinit_fp = deinit;
	animations[animationcount].duration = count;
	animations[animationcount].idle = idle;

	animationcount++;

}




int main(int argc __attribute__((__unused__)), char *argv[] __attribute__((__unused__))) {


	srand(time(NULL));


	int current_animation = 0;

	screen = SDL_SetVideoMode(RADIUS*2,RADIUS*2,32, SDL_SWSURFACE | SDL_DOUBLEBUF);


	animations[current_animation].init_fp();
	
	int running = 1;

	uint32_t lap = 0;
	int32_t phase = 0;

	while(running) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYUP:
					break;
				case SDL_KEYDOWN:
					switch(ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = 0;
							break;
						case SDLK_SPACE:
							if(sdlpause == 0)
							{
								sdlpause = 1;
							}
							else{
								sdlpause = 0;
							}
							break;
						default: break;
					}
				default: break;
			}
		}


		for(int32_t angle = phase*60 ; angle < (phase+1)*60; angle++)
		{

			struct segment_t segment;



	

	/*		SDL_Rect rect_a = { RADIUS-sinf((angle/4.0f)*M_PI/180.0f)*(RADIUS-90), RADIUS+cosf((angle/4.0f)*M_PI/180.0f)*(RADIUS-90), 2, 2};
			SDL_FillRect(
				screen, 
				&rect_a, 
				SDL_MapRGB(screen->format, 0,0,0)
			);
			SDL_Rect rect_b = { RADIUS-sinf(((angle+60)/4.0f)*M_PI/180.0f)*(RADIUS-90), RADIUS+cosf(((angle+60)/4.0f)*M_PI/180.0f)*(RADIUS-90), 2, 2};
			SDL_FillRect(
				screen, 
				&rect_b, 
				SDL_MapRGB(screen->format, 255,255,255)
			);*/
		
			for(int x = 0; x < LED_WIDTH; x++) {

				SDL_Rect rect = { RADIUS-sinf(((angle-480)/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), RADIUS+cosf(((angle-480)/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), 2, 2};
				SDL_FillRect(
					screen, 
					&rect, 
					SDL_MapRGB(screen->format, 0,0,0)
				);

			}
			animations[current_animation].tick_fp(lap,angle-240,&segment);
			for(int x = 0; x < LED_WIDTH; x++) {

				SDL_Rect rect = { RADIUS-sinf(((angle-240)/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), RADIUS+cosf(((angle-240)/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), 2, 2};
				SDL_FillRect(
					screen, 
					&rect, 
					SDL_MapRGB(screen->format, segment.color[x].red>>1,segment.color[x].green>>1,segment.color[x].blue>>1)
				);

			}
			animations[current_animation].tick_fp(lap,angle,&segment);
		
			for(int x = 0; x < LED_WIDTH; x++) {

				SDL_Rect rect = { RADIUS-sinf((angle/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), RADIUS+cosf((angle/4.0f)*M_PI/180.0f)*(RADIUS-(LED_WIDTH-x)*6), 2, 2};
				SDL_FillRect(
					screen, 
					&rect, 
					SDL_MapRGB(screen->format, segment.color[x].red,segment.color[x].green,segment.color[x].blue)
				);

			}
		}
		
		phase++;
		if(phase==24)
		{
			phase=0;
			lap++;
		}

		
		SDL_Flip(screen);



		if(lap == animations[current_animation].duration)
		{
			animations[current_animation].deinit_fp();

			current_animation++;
			if(current_animation == animationcount)
			{
				current_animation = 0;
			}
			lap=0;


			SDL_Rect rect = { 0, 0, RADIUS*2,RADIUS*2 };
			SDL_FillRect(
				screen, 
				&rect, 
				SDL_MapRGB(screen->format,0,0,0)
			);
			SDL_Flip(screen);
			SDL_Delay(300);


			animations[current_animation].init_fp();


		}
	}

	SDL_Quit();
	return 0;
}

