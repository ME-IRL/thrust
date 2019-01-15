int main(void);
void SetupHardware(void);
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_ControlLineStateChanged(USB_ClassInfo_CDC_Device_t *);
