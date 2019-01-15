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

USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface ={
	.Config = {
		.ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
		.DataINEndpoint           = {
			.Address          = CDC_TX_EPADDR,
			.Size             = CDC_TXRX_EPSIZE,
			.Banks            = 1,
		},
		.DataOUTEndpoint = {
			.Address          = CDC_RX_EPADDR,
			.Size             = CDC_TXRX_EPSIZE,
			.Banks            = 1,
		},
		.NotificationEndpoint = {
			.Address          = CDC_NOTIFICATION_EPADDR,
			.Size             = CDC_NOTIFICATION_EPSIZE,
			.Banks            = 1,
		},
	},
};

static FILE serial;
static volatile bool serialReady = false;

int main(void){
	SetupHardware();
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &serial);
	GlobalInterruptEnable();

	//while(!serialReady);
	//LEDs_TurnOffLEDs(LEDS_LED1);

	for (;;){
		LEDs_TurnOnLEDs(LEDS_LED1);
		fprintf(&serial, "On %d\n", PORTB&LEDS_LED1);
		CDC_Device_Flush(&VirtualSerial_CDC_Interface);
		_delay_ms(1000);
		LEDs_TurnOffLEDs(LEDS_LED1);
		fprintf(&serial, "Off %d\n", PORTB&LEDS_LED1);
		CDC_Device_Flush(&VirtualSerial_CDC_Interface);
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

void EVENT_USB_Device_Connect(void){}
void EVENT_USB_Device_Disconnect(void){}

void EVENT_USB_Device_ConfigurationChanged(void){
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

void EVENT_USB_Device_ControlRequest(void){
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo){
	bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;
	serialReady = HostReady;
	
	if(HostReady)
		LEDs_TurnOnLEDs(LEDS_LED2);
	else
		LEDs_TurnOffLEDs(LEDS_LED2);
}
