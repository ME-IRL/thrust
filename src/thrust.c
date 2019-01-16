#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define INTERRUPT_CONTROL_ENDPOINT
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>

#include <Descriptors.h>
#include <thrust.h>
#include <usb.h>

static FILE serial;

int main(void){
	SetupHardware();
	CDC_Device_CreateStream(&CDC_If, &serial);
	GlobalInterruptEnable();

	while(!serialReady){
		CDC_Device_USBTask(&CDC_If);
	}
	LEDs_TurnOnLEDs(LEDS_LED1);

	for (;;){
		fprintf(&serial, "TEST %d\n", serialReady);
		CDC_Device_Flush(&CDC_If);

		//LEDs_TurnOnLEDs(LEDS_LED1);
		//fprintf(&serial, "On %d\n", PORTB&LEDS_LED1);
		//CDC_Device_Flush(&VirtualSerial_CDC_Interface);
		//_delay_ms(1000);
		//LEDs_TurnOffLEDs(LEDS_LED1);
		//fprintf(&serial, "Off %d\n", PORTB&LEDS_LED1);
		//CDC_Device_Flush(&VirtualSerial_CDC_Interface);
		//_delay_ms(1000);
	}
}

void SetupHardware(void){
	// Disable watchdog
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// Disable clock division
	clock_prescale_set(clock_div_1);

	LEDs_Init();
	USB_Init();
}
