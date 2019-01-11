#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRB = _BV(PB0); // Pro Micro TX LED

	while(1) {
		PINB |= _BV(PB0); // toggle TX LED
		_delay_ms(500); // wait 0.5s
	}     

	return 1;
}
