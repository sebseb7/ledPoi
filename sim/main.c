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


		for(uint32_t angle = 0 ; angle < 360*4; angle++)
		{

			struct segment_t segment;


			animations[current_animation].tick_fp(lap,angle,&segment);

	

		
			for(int x = 0; x < LED_WIDTH; x++) {

				SDL_Rect rect = { RADIUS-sinf((angle/4.0f)*M_PI/180.0f)*(RADIUS-x*6), RADIUS+cosf((angle/4.0f)*M_PI/180.0f)*(RADIUS-x*6), 2, 2};
				SDL_FillRect(
					screen, 
					&rect, 
					SDL_MapRGB(screen->format, segment.color[x].red,segment.color[x].green,segment.color[x].blue)
				);

			}
		}
		lap++;

		
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

