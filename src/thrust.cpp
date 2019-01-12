#include <avr/io.h>
#include <util/delay.h>

#include <LUFA/Drivers/USB/USB.h>

#define HX711_DAT PD4
#define HX711_CLK PC6

#define SERVO_CMD_SET 0
#define SERVO_CMD_SETALL 1
#define SERVO_CMD_GET 2
#define SERVO_CMD_GETALL 3

void Servo_set(uint8_t channel, uint16_t value);
void Servo_setAll(uint16_t *values);
uint16_t Servo_get(uint8_t channel);
void Servo_getAll(uint16_t *dest);

void process_SERVO_CMD_SET();
void process_SERVO_CMD_SETALL();
void process_SERVO_CMD_GET();
void process_SERVO_CMD_GETALL();

#define TXLEDS DDRD |= (1<<5)
#define RXLEDS DDRB |= (1<<0)
#define TXLED0 PORTD |= (1<<5)
#define TXLED1 PORTD &= ~(1<<5)
#define RXLED0 PORTB |= (1<<0)
#define RXLED1 PORTB &= ~(1<<0)
#define TXLEDG PORTD & (1<<5)
#define RXLEDG PORTB & (1<<0)

int main(){
	TXLEDS;
	RXLEDS;
	RXLED0;

	while(1) {
		TXLED0;
		_delay_ms(500);
		TXLED1;
		_delay_ms(500);
	}     

	return 1;
}

void EVENT_USB_Device_ControlRequest(){
	if((((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_TYPE) == REQTYPE_CLASS) &&
				(USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_RECIPIENT) == REQREC_DEVICE)){
		if(((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION) == REQDIR_HOSTTODEVICE)){
			switch(USB_ControlRequest.bRequest){
				case SERVO_CMD_SET:
					process_SERVO_CMD_SET();
					break;
				case SERVO_CMD_SETALL:
					process_SERVO_CMD_SETALL();
					break;
			}
		}else{
			switch(USB_ControlRequest.bRequest){
				case SERVO_CMD_GET:
					process_SERVO_CMD_GET();
					break;
				case SERVO_CMD_GETALL:
					process_SERVO_CMD_GETALL();
					break;
			}
		}
	}
}

void process_SERVO_CMD_SET(){
	Endpoint_ClearSETUP();
	Endpoint_ClearStatusStage();
	Servo_set((USB_ControlRequest.wIndex & 0x07), USB_ControlRequest.wValue);
}

void process_SERVO_CMD_SETALL(){
	uint16_t uiServoValues[8];
	Endpoint_ClearSETUP();
	Endpoint_Read_Stream_LE(uiServoValues, 16, 0);
	//Endpoint_ClearOUT();
	//while(!(Endpoint_IsINReady()));
	//Endpoint_ClearIN();
	Endpoint_ClearStatusStage();
	Servo_setAll(uiServoValues);
}

void process_SERVO_CMD_GET(){
	uint16_t uiServoValue = Servo_get(USB_ControlRequest.wIndex);
	Endpoint_ClearSETUP();
	//Endpoint_Write_16_LE(uiServoValue);
	Endpoint_Write_Stream_LE(&uiServoValue, 2, 0);
	Endpoint_ClearIN();
	Endpoint_ClearStatusStage();
}

void process_SERVO_CMD_GETALL(){
	uint16_t uiServoValues[8];
	Endpoint_ClearSETUP();
	Endpoint_Write_Stream_LE(&uiServoValues, 16, 0);
	Endpoint_ClearIN();
	Endpoint_ClearStatusStage();
}

void Servo_set(uint8_t channel, uint16_t value){
	if(channel == 0){
		if(value)
			RXLED1;
		else
			RXLED0;
	}
}

uint16_t Servo_get(uint8_t channel){
	if(channel == 0)
		return RXLEDG;
}

void Servo_setAll(uint16_t *values){
	return;
}

void Servo_getAll(uint16_t *dest){
	return;
}

