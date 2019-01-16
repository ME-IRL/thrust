#ifndef _HX711_H
#define _HX711_H

#ifndef HX711_DAT
#define HX711_DAT PD4
#endif

#ifndef HX711_CLK
#define HX711_CLK PC6
#endif

#define HX711_CLKO DDRD |= (1<<4)
#define HX711_CLKI DDRD &= ~(1<<4)
#define HX711_CLKD (PIND & (1<<4))
#define HX711_CLK0 PORTD |= (1<<4)
#define HX711_CLK1 PORTD &= ~(1<<4)

#define HX711_DATAO DDRC |= (1<<6)
#define HX711_DATAI DDRC &= ~(1<<6)
#define HX711_DATAD (PINC & (1<<6))
#define HX711_DATA0 PORTC |= (1<<6)
#define HX711_DATA1 PORTC &= ~(1<<6)

extern uint8_t GAIN;
extern double OFFSET;

void hx711_init(uint8_t gain);
int hx711_isReady(void);
uint32_t hx711_read(void);
uint32_t hx711_readAvg(uint8_t times);
double hx711_getVal(uint8_t times);
void hx711_tare(uint8_t times);
void hx711_setGain(uint8_t gain);
uint8_t hx711_getGain(void);
void hx711_setOffset(double offset);
double hx711_getOffset(void);
void hx711_down(void);
void hx711_up(void);

#endif
