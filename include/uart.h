#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD 9600L
#define BAUD_RATE (F_CPU/(16 * BAUD)) - 1

void uart_init();
static void uart_transmit(char data);
void uart_print(char *str);

#endif