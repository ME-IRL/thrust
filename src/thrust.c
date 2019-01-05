#include <avr/wdt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <LUFA/Common/Common.h>
#include <LUFA/Drivers/USB/USB.h>

uint32_t Boot_Key ATTR_NO_INIT;

#define MAGIC_BOOT_KEY 0xDEADBEEF
#define BOOTLOADER_START_ADDRESS (0x8000 - 0x1000)

void Bootloader_Jump_Check(void) ATTR_INIT_SECTION(3);
void Bootloader_Jump_Check(void){
	if((MCUSR & (1<<WDRF)) && (Boot_Key == MAGIC_BOOT_KEY)){
		Boot_Key = 0;
		((void (*)(void))BOOTLOADER_START_ADDRESS)();
	}
}

void Jump_To_Bootloader(void){
	//USB_DISABLE();
	cli();
	Delay_MS(2000);
	Boot_Key = MAGIC_BOOT_KEY;
	wdt_enable(WDTO_250MS);
	for(;;);
}

int main(){
	USB_Init();

	DDRB = _BV(PB0); // Pro Micro TX LED

	while(1) {
		PINB |= _BV(PB0); // toggle TX LED
		_delay_ms(500); // wait 0.5s
	}     

	return 1;
}
