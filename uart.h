#ifndef UART_MODULE_H
#define UART_MODULE_H

int init_uart();
void uart_send(const char *message);
void uart_close();

#endif
