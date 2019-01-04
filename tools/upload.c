#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT "/dev/ttyACM0"
#define DEVICE "m32u4"

void main(int argc, char **argv){

	char *cmd_tmpl = "avrdude -p %s -c avr109 -P %s";

	char cmd[512];
	sprintf(cmd, cmd_tmpl, DEVICE, PORT);

	if(argc > 1){
		strcat(cmd, " -U flash:w:");
		strcat(cmd, argv[1]);
		strcat(cmd, ":i");
	}

	printf("CMD: %s\n", cmd);

	// Open serial port
	int fd = open(PORT, O_RDWR | O_NOCTTY | O_SYNC);
	if(fd < 0){
	        fprintf(stderr, "Error %d opening %s: %s", errno, PORT, strerror (errno));
	        return;
	}
	
	// Setup for tty setting
	struct termios tty;
    memset(&tty, 0, sizeof tty);

	// Open to 'magic' rate
    cfsetospeed(&tty, B1200);
    cfsetispeed(&tty, B1200);
    tcsetattr(fd, TCSANOW, &tty);

	// Turn of DTR
    cfsetospeed(&tty, B0);
    cfsetispeed(&tty, B0);
    tcsetattr(fd, TCSANOW, &tty);

	// Close
	close(fd);
	
	// Wait for port to come back
	//system("cat /dev/ttyACM0 >> /dev/null");
	sleep(1);

	// Run command (avrdude)
	system(cmd);
}
