#include "uart.h"

void uart_init() {
    UBRR0H = 0;
    UBRR0L = BAUD_RATE;
    UCSR0B |= (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}
  
static void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_print(char *str) {
    while (*str)
        uart_transmit(*str++);
}
