#ifndef __LEDS_USER_H__
#define __LEDS_USER_H__

	/* Includes: */
		// TODO: Add any required includes here

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_LEDS_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/LEDS.h instead.
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** LED mask for the first LED on the board. */
			#define LEDS_LED1        (1<<0)

			/** LED mask for the second LED on the board. */
			#define LEDS_LED2        (1<<5)

			/** LED mask for all the LEDs on the board. */
			#define LEDS_ALL_LEDS    (LEDS_LED1 | LEDS_LED2)

			/** LED mask for none of the board LEDs. */
			#define LEDS_NO_LEDS     0

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void LEDs_Init(void)
			{
				DDRB |= LEDS_LED1;
				PORTB &= ~LEDS_LED1;
				DDRD |= LEDS_LED2;
				PORTD &= ~LEDS_LED2;
			}

			static inline void LEDs_Disable(void)
			{
				DDRB &= ~LEDS_LED1;
				PORTB &= ~LEDS_LED1;
				DDRD &= ~LEDS_LED2;
				PORTD &= ~LEDS_LED2;
			}

			static inline void LEDs_TurnOnLEDs(const uint8_t LEDMask)
			{
				if(LEDMask == LEDS_LED1)
					PORTB |= LEDMask;
				if(LEDMask == LEDS_LED2)
					PORTD |= LEDMask;
			}

			static inline void LEDs_TurnOffLEDs(const uint8_t LEDMask)
			{
				if(LEDMask == LEDS_LED1)
					PORTB &= ~LEDMask;
				if(LEDMask == LEDS_LED2)
					PORTD &= ~LEDMask;
			}

			static inline void LEDs_SetAllLEDs(const uint8_t LEDMask)
			{
				PORTB |= LEDS_LED1;
				PORTD |= LEDS_LED2;
			}

			static inline void LEDs_ChangeLEDs(const uint8_t LEDMask, const uint8_t ActiveMask)
			{
				// TODO: Add code to set the Leds in the given LEDMask to the status given in ActiveMask here
			}

			static inline void LEDs_ToggleLEDs(const uint8_t LEDMask)
			{
				PORTB ^= LEDS_LED1;
				PORTD ^= LEDS_LED2;
			}

			static inline uint8_t LEDs_GetLEDs(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t LEDs_GetLEDs(void)
			{
				return ((PORTB & LEDS_LED1) | (PORTD & LEDS_LED2));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

