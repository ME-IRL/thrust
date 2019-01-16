#ifndef _HX711_H
#define _HX711_H

#ifndef HX711_DAT
#define HX711_DAT PD4
#endif

#ifndef HX711_CLK
#define HX711_CLK PD6
#endif

#define HX711_CLKS DDR |= (1<<4)
#define HX711_CLK0 PORTD |= (1<<4)

static uint8_t GAIN;
static double OFFSET;

void hx711_init(uint8_t gain);
void hx711_setGain(uint8_t gain);
uint32_t hx711_read(void);
uint32_t hx711_readAvg(uint8_t times);
uint32_t hx711_getVal(uint8_t times);
void hx711_setOffset(double offset);
double hx711_getOffset(void);
void hx711_down(void);
void hx711_up(void);

#endif
