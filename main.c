#include <msp430.h>
#include <uart.h>

int main() {
  WDTCTL = WDTPW | WDTHOLD;

  PM5CTL0 &= ~LOCKLPM5;

  SETUP_UART_PINS();
  INITIALIZE_UART();

  __bis_SR_register(GIE); // enable all interrupts

  P1DIR |= BIT0;
  P9DIR |= BIT7;

  unsigned char rxData;
  int i = 0;
  while (1) {
    SEND_STRING_UART("Test\n");
    SEND_CHAR_UART('A');
    SEND_INTEGER_UART(382245);
    __delay_cycles(1000000);
  }
}
