#include "VirtualSerial.h"

#define TXLEDS DDRD |= (1<<5)
#define RXLEDS DDRB |= (1<<0)
#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
				.DataINEndpoint           =
					{
						.Address          = CDC_TX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = CDC_RX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.NotificationEndpoint =
					{
						.Address          = CDC_NOTIFICATION_EPADDR,
						.Size             = CDC_NOTIFICATION_EPSIZE,
						.Banks            = 1,
					},
			},
	};

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
static FILE USBSerialStream;
static char *baud = "0\r\n";

int main(void)
{
	SetupHardware();

	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

	GlobalInterruptEnable();

	for (;;)
	{
		/* Write the string to the virtual COM port via the created character stream */
		fputs(baud, &USBSerialStream);

		/* Alternatively, without the stream: */
		// CDC_Device_SendString(&VirtualSerial_CDC_Interface, ReportString);

		/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#else
#error Only AVR8 is supported
#endif

	/* Hardware Initialization */
	TXLEDS; // Setup TX LED
	RXLEDS; // Setup RX LED
	TXLED0; // Turn off TX LED
	RXLED0; // Turn off RX LED

	USB_Init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** CDC class driver callback function the processing of changes to the virtual
 *  control lines sent from the host..
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
	/* You can get changes to the virtual CDC lines in this callback; a common
	   use-case is to use the Data Terminal Ready (DTR) flag to enable and
	   disable CDC communications in your application when set to avoid the
	   application blocking while waiting for a host to become ready and read
	   in the pending data from the USB endpoints.
	*/
	bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;
	(void)HostReady;

	if(HostReady){
		TXLED1;
	}else{
		TXLED0;
	}
}

//uint16_t *magic_pos = 0x0800;
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo){

	switch(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS){
		case 1200: baud = "1200\r\n"; break;
		case 9600: baud = "9600\r\n"; break;
		case 38400: baud = "38400\r\n"; break;
		case 115200: baud = "115200\r\n"; break;
		default: baud = "UNKOWN\r\n";
	}

	//if(CDCInterfaceInfo->State.LineEncoding.BaudRateBPS == 1200){ // and check if open
	//	*magic_pos = 0x7777;
	//	sdtcsr_save = WDTCSR;
	//	wdt_enable(WDT_120MS);
	//}else if(*magic_pos == 0x7777){
	//	wdt_reset();
	//	WDTCSR |= (1<<WDCE) | (1<<WDE);
	//	WDTCSR = wdtcsr_save;
	//}

}

