#ifndef LEDS_H_
#define LEDS_H_

#include "main.h"

void setLedX(uint8_t x, uint8_t red,uint8_t green,uint8_t blue);
void fillRGB(uint8_t red,uint8_t green,uint8_t blue);
void leds_init(void);
void leds_flush(void);

#endif
