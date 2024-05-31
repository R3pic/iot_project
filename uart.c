#include "uart.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

static int serial_port;

int uart_init(const char *device, int baud_rate)
{
    if ((serial_port = serialOpen(device, baud_rate)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s (error code: %d)\n", strerror(errno), errno);
        return -1;
    }

    if (wiringPiSetup() == -1)
    {
        fprintf(stderr, "Unable to start wiringPi: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void uart_send(const char *message)
{
    serialPuts(serial_port, message);
}

void uart_close()
{
    serialClose(serial_port);
}
