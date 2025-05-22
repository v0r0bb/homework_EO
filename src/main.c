#include <stdio.h>
#include <util/delay.h>
#include "uart.h"

#define LED_PIN PB5
#define X1 PD2
#define X2 PD3
#define X3 PD4
#define X4 PD5
#define X5 PD6
#define Y PD7

void display(uint8_t num) {
    PORTD &= ~((1 << X1) | (1 << X2) | (1 << X3) | (1 << X4) | (1 << X5));

    if (num & 0b10000) PORTD |= (1 << X1);  
    if (num & 0b01000) PORTD |= (1 << X2);  
    if (num & 0b00100) PORTD |= (1 << X3);  
    if (num & 0b00010) PORTD |= (1 << X4); 
    if (num & 0b00001) PORTD |= (1 << X5); 
    
    _delay_us(10); 
    char buf[20];
    snprintf(buf, sizeof(buf), "%-3d%-3d%-3d%-3d%-3d\t%d\n",
	(num >> 4) & 1, 
	(num >> 3) & 1,
	(num >> 2) & 1,  
	(num >> 1) & 1,  
	num & 1,    
    (PIND & (1 << Y)) ? 1 : 0);
    uart_print(buf);
}


int main(void) {
	uart_init();

	DDRD |= (1 << X1) | (1 << X2) | (1 << X3) | (1 << X4) | (1 << X5);  
    DDRD &= ~(1 << Y);  
    PORTD |= (1 << Y);  

	uart_print("X1 X2 X3 X4 X5  Y\n");
	for (int i = 0; i < 32; i++) {
		display(i);
		_delay_ms(1000);
	}
}