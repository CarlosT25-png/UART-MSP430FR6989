#include <msp430.h>
#include <uart.h>

int main () {
    WDTCTL = WDTPW | WDTHOLD;

    PM5CTL0 &= ~LOCKLPM5;

    SETUP_UART_PINS();
    INITIALIZE_UART();

    // SEND_CHAR_UART('H');
    // SEND_CHAR_UART('E');
    // SEND_CHAR_UART('L');
    // SEND_CHAR_UART('L');
    // SEND_CHAR_UART('O');

    unsigned char rxData;
    while(1) {
        if (RECEIVE_CHAR_UART(&rxData)) { 
            SEND_CHAR_UART('5'); // Echo the character back
        }
    }
}