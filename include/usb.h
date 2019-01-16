#ifndef _USB_H_
#define _USB_H_

#include <stdbool.h>

extern bool serialReady;
extern USB_ClassInfo_CDC_Device_t CDC_If;

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

#endif
