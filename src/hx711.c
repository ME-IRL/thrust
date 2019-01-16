#include <stdint.h>
#include <hx711.h>

void hx711_init(uint8_t gain){
	// Set clock output
	// Set data input
	
	hx711_setGain(gain);
}

void hx711_setGain(uint8_t gain){}
uint32_t hx711_read(){
	return 0;
}
uint32_t hx711_readAvg(uint8_t times){
	return 0;
}
uint32_t hx711_getVal(uint8_t times){
	return 0;
}
void hx711_setOffset(double offset){}
double hx711_getOffset(void){
	return 0.0;
}
void hx711_down(void){}
void hx711_up(void){}
