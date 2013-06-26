#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>

enum {
	LED_WIDTH = 10,
	RADIUS = 400,
};

struct color_t {    
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};
struct segment_t {    
	struct color_t color[LED_WIDTH];
};

#define LEDPOI
#define SIMULATOR

#define CONSTRUCTOR_ATTRIBUTES	__attribute__((constructor));

typedef void (*init_fun)(void);
typedef void (*deinit_fun)(void);
typedef uint8_t (*tick_fun)(uint32_t lap,uint32_t angle,struct segment_t *segment);


void registerAnimation(init_fun init,tick_fun tick,deinit_fun deinit, uint16_t duration, uint8_t idle);
void setLedX(uint8_t x, uint8_t r,uint8_t g,uint8_t b);
#endif

