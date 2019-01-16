#define INTERRUPT_CONTROL_ENDPOINT
#include <LUFA/Drivers/Board/LEDs.h>
#include <LUFA/Drivers/USB/USB.h>

#include <Descriptors.h>
#include <usb.h>

USB_ClassInfo_CDC_Device_t CDC_If ={
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

bool serialReady = false;

void EVENT_USB_Device_Connect(void){}
void EVENT_USB_Device_Disconnect(void){}

void EVENT_USB_Device_ConfigurationChanged(void){
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&CDC_If);
}

void EVENT_USB_Device_ControlRequest(void){
	CDC_Device_ProcessControlRequest(&CDC_If);
}

void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo){
	bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;

	serialReady = HostReady;
	
	if(HostReady)
		LEDs_TurnOnLEDs(LEDS_LED2);
	else
		LEDs_TurnOffLEDs(LEDS_LED2);
}
