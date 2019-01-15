#ifndef __LEDS_USER_H__
#define __LEDS_USER_H__

#if defined(__cplusplus)
	extern "C" {
#endif

#if !defined(__INCLUDE_FROM_LEDS_H)
	#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
#endif

#define LEDS_LED1        (1<<0)
#define LEDS_LED2        (1<<5)
#define LEDS_NO_LEDS     0

static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask){
	if(LEDMask == LEDS_LED1)
		PORTB |= LEDMask;
	if(LEDMask == LEDS_LED2)
		PORTD |= LEDMask;
}

static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask){
	if(LEDMask == LEDS_LED1)
		PORTB &= ~LEDMask;
	if(LEDMask == LEDS_LED2)
		PORTD &= ~LEDMask;
}

static inline void LEDs_Init(void){
	DDRB |= LEDS_LED1;
	DDRD |= LEDS_LED2;
	LEDs_TurnOffLEDs(LEDS_LED1);
	LEDs_TurnOffLEDs(LEDS_LED2);
}

static inline void LEDs_Disable(void){
	LEDs_TurnOffLEDs(LEDS_LED1);
	LEDs_TurnOffLEDs(LEDS_LED2);
	DDRB &= ~LEDS_LED1;
	DDRD &= ~LEDS_LED2;
}

static inline void LEDs_SetAllLEDs(const uint8_t LEDMask){
	PORTB |= LEDS_LED1;
	PORTD |= LEDS_LED2;
}

static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask){
	// TODO: Add code to set the Leds in the given LEDMask to the status given in ActiveMask here
}

static inline void LEDs_ToggleLEDs(const uint8_t LEDMask){
	PORTB ^= LEDS_LED1;
	PORTD ^= LEDS_LED2;
}

static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
static inline uint8_t LEDs_GetLEDs(void){
	return ((PORTB & LEDS_LED1) | (PORTD & LEDS_LED2));
}

#if defined(__cplusplus)
	}
#endif
#endif

