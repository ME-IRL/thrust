#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define INTERRUPT_CONTROL_ENDPOINT

#include <Descriptors.h>
#include <LUFA/Drivers/Board/Board.h>
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>
#include <LUFA/Platform/Platform.h>

#include <thrust.h>

#define HX711_DAT PD4
#define HX711_CLK PC6

USB_ClassInfo_CDC_Device_t CDC_Interface = {
	.Config = {
		.ControlInterfaceNumber = INTERFACE_ID_CDC_CCI,
		.DataINEndpoint = {
			.Address = CDC_TX_EPADDR,
			.Size = CDC_TXRX_EPSIZE,
			.Banks = 1,
		},
		.DataOUTEndpoint = {
			.Address = CDC_RX_EPADDR,
			.Size = CDC_TXRX_EPSIZE,
			.Banks = 1,
		},
		.NotificationEndpoint = {
			.Address = CDC_NOTIFICATION_EPADDR,
			.Size = CDC_NOTIFICATION_EPSIZE,
			.Banks = 1,
		},
	},
};

static FILE Serial;

int main(){

	SetupHardware();
	CDC_Device_CreateBlockingStream(&CDC_Interface, &Serial);
	GlobalInterruptEnable();

	while(1) {
		fprintf(&Serial, "Test\r\n");
		//USB_USBTask();
		//TXLED0;
		//_delay_ms(500);
		//TXLED1;
		//_delay_ms(500);
	}     
}

void SetupHardware(void){
	// Disable watchdog
	MCUSR &= ~(1 <<WDRF);
	wdt_disable();

	// Disable clock division
	clock_prescale_set(clock_div_1);

	LEDs_Init();
	USB_Init();
}

void EVENT_USB_Device_Connect(void){
	LEDs_TurnOnLEDs(LEDS_LED1);
}

void EVENT_USB_Device_Disconnect(void){
	LEDs_TurnOffLEDs(LEDS_LED1);
}

void EVENT_USB_Device_ConfigurationChanged(void){
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&CDC_Interface);
}

void EVENT_USB_Device_ControlRequest(void){
	CDC_Device_ProcessControlRequest(&CDC_Interface);
}

void EVENT_USB_Device_ControlLineStateChanged(USB_ClassInfo_CDC_Device_t *CDCInterfaceInfo){
	bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR);
	
	if(HostReady)
		LEDs_TurnOnLEDs(LEDS_LED2);
	else
		LEDs_TurnOffLEDs(LEDS_LED2);
}
