#include "uart.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define BAUD_RATE 9600
#define DEVICE "/dev/ttyS0"
static int serial_port;

int init_uart()
{
    if ((serial_port = serialOpen(DEVICE, BAUD_RATE)) < 0)
    {
        // fprintf(stdout, "Unable to open serial device: %s (error code: %d)\n", stderr(errno);
        printf("Error opening serial device: \n");
        return -1;
    }
    return 0;
}

void uart_send(const char *message)
{
    printf("sending message: %s\n", message);
    serialPuts(serial_port, message);
}

void uart_close()
{
    serialClose(serial_port);
}
