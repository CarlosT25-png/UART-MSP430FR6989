#ifndef UART_H
#define UART_H
#include <stdint.h>

void SETUP_UART_PINS(void);
void INITIALIZE_UART(void);

void SEND_CHAR_UART(unsigned char data);
void SEND_STRING_UART(const char *data);
void SEND_INTEGER_UART(uint32_t num);
unsigned char RECEIVE_CHAR_UART ();

#endif
