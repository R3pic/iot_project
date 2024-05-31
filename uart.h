#ifndef UART_MODULE_H
#define UART_MODULE_H

int uart_init(const char *device, int baud_rate);
void uart_send(const char *message);
void uart_close();

#endif
