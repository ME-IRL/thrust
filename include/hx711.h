#ifndef _HX711_H
#define _HX711_H

#ifndef HX711_DAT
#define HX711_DAT PD4
#endif

#ifndef HX711_CLK
#define HX711_CLK PC6
#endif

#define HX711_CLKO DDRB |= (1<<4)
#define HX711_CLKI DDRB &= ~(1<<4)
#define HX711_CLKD (PINB & (1<<4))
#define HX711_CLK1 PORTB |= (1<<4)
#define HX711_CLK0 PORTB &= ~(1<<4)

#define HX711_DATAO DDRD |= (1<<4)
#define HX711_DATAI DDRD &= ~(1<<4)
#define HX711_DATAD (PIND & (1<<4))
#define HX711_DATA1 PORTD |= (1<<4)
#define HX711_DATA0 PORTD &= ~(1<<4)

extern uint8_t GAIN;
extern uint32_t OFFSET;

void hx711_init(uint8_t gain);
int hx711_isReady(void);
uint32_t hx711_read(void);
uint32_t hx711_readAvg(uint8_t times);
uint32_t hx711_getVal(uint8_t times);
void hx711_tare(uint8_t times);
void hx711_setGain(uint8_t gain);
uint8_t hx711_getGain(void);
void hx711_setOffset(uint32_t offset);
uint32_t hx711_getOffset(void);
void hx711_down(void);
void hx711_up(void);

#endif
