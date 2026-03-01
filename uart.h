#ifndef UART_H
#define UART_H

void SETUP_UART_PINS(void);
void INITIALIZE_UART(void);

void SEND_CHAR_UART(unsigned char data);
short int RECEIVE_CHAR_UART (unsigned char *c);

#endif
