#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <hx711.h>

uint8_t GAIN;
double OFFSET;
static uint8_t pulses;

void hx711_init(uint8_t gain){
	// Set clock output
	HX711_CLKO;
	HX711_CLK0;
	// Set data input
	HX711_DATAI;
	
	hx711_setGain(gain);
}

uint32_t hx711_read(void){
	while(!hx711_isReady());

	unsigned long count;

	HX711_DATA1;
	_delay_us(1);
	HX711_CLK0;
	_delay_us(1);

	count = 0;
	while(!hx711_isReady());

	for(uint8_t i = 0; i < pulses; i++){
		HX711_CLK1;
		_delay_us(1);
		HX711_CLK0;
		_delay_us(1);
		count = count << 1;

		if(!hx711_isReady()) count++;
	}

	count = count >> 6;

	HX711_CLK1;
	_delay_us(1);
	HX711_CLK0;
	_delay_us(1);

	count ^= 0x800000;

	return count;
}

int hx711_isReady(){
	return !HX711_DATAD;
}

uint32_t hx711_readAvg(uint8_t times){
	uint32_t sum = 0;
	for(uint8_t i = 0; i < times; i++){
		sum += hx711_read();
	}
	return sum/times;
}

double hx711_getVal(uint8_t times){
	return hx711_readAvg(times) - OFFSET;
}

void hx711_tare(uint8_t times){
	hx711_setOffset(hx711_readAvg(times));
}

void hx711_setGain(uint8_t gain){
	GAIN = gain;
	switch(gain){
		case 128: pulses = 25; break;
		case 64: pulses = 27; break;
		case 32: pulses = 26; break;
	}
	hx711_read();
}

uint8_t hx711_getGain(void){
	return GAIN;
}

void hx711_setOffset(double offset){
	OFFSET = offset;
}

double hx711_getOffset(void){
	return OFFSET;
}

void hx711_down(void){
	HX711_CLK0;
	HX711_CLK1;
	_delay_us(70);
}

void hx711_up(void){
	HX711_CLK0;
}
