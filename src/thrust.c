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
#include <hx711.h>

static FILE serial;

int main(void){
	SetupHardware();
	CDC_Device_CreateStream(&CDC_If, &serial);
	GlobalInterruptEnable();

	// Wait for serial
	//fprintf(display, "Waiting for serial connection...\n");
	while(!serialReady){
		CDC_Device_USBTask(&CDC_If);
	}
	
	// Start program
	//fprintf(display, "Connected! Starting program.\n");
	fprintf(&serial, "Connected! Starting program.\n");
	CDC_Device_Flush(&CDC_If);

	for (;;){
		LEDs_TurnOnLEDs(LEDS_LED1);
		fprintf(&serial, "On\n");
		CDC_Device_Flush(&CDC_If);
		_delay_ms(1000);

		LEDs_TurnOffLEDs(LEDS_LED1);
		fprintf(&serial, "Off\n");
		CDC_Device_Flush(&CDC_If);
		_delay_ms(1000);
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
