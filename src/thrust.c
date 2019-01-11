#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>

// See wiring.c
void init(){
	sei();
	sbi(TCCR0A, WGM01);
	sbi(TCCR0A, WGM00);
	sbi(TCCR0B, CS01);
	sbi(TCCR0B, CS00);
	sbi(TIMSK0, TOIE0);
	TCCR1B = 0;
	sbi(TCCR1B, CS11);
	sbi(TCCR1B, CS10);
	sbi(TCCR1A, WGM10);
	sbi(TCCR3B, CS31);
	sbi(TCCR3B, CS30);
	sbi(TCCR3A, WGM30);
	sbi(TCCR4B, CS42);
	sbi(TCCR4B, CS41);
	sbi(TCCR4B, CS40);
	sbi(TCCR4D, WGM40);
	sbi(TCCR4A, PWM4A);
	sbi(TCCR4C, PWM4D);
	sbi(ADCSRA, ADPS2);
	sbi(ADCSRA, ADPS1);
	sbi(ADCSRA, ADPS0);
	sbi(ADCSRA, ADEN);
}

void initVariant(){
	
}

int main(){
	init();
	initVariant();

	DDRB = _BV(PB0); // Pro Micro TX LED

	while(1) {
		PINB |= _BV(PB0); // toggle TX LED
		_delay_ms(500); // wait 0.5s
	}     

	return 1;
}
