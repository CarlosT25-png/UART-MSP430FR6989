#include <msp430.h>

/*
    Configuration:
        Baud Rate: 9600
        Data width: 8-Bit data, no parity, 1 stop bit, LSB first, no flow control
        System Clock: SMCLK
*/

void SETUP_UART_PINS(void){
    // P3.4 -> UCA1TXD ; P3.5 -> UCA1RXD

    // TX
    P3DIR |= BIT4;

    // RX
    P3DIR &= ~BIT5;

    // Selecting to TX & RX
    P3SEL0 |= BIT4 | BIT5;
    P3SEL1 &= ~(BIT4 | BIT5);
};

void INITIALIZE_UART(void){
    // UCA Control word 0
    // Some of these fields are ready set to 0 by default
    // but I added anyways to be more flexible in future applications
    
    // UCA1CTLW0 = UCSWRST; // Reset all fields (optional)
    UCA1CTLW0 |= UCSWRST; // enable reset state (this will allow us to edit the settings)
    UCA1CTLW0 &= ~UCPEN; // 0 for ParityDisable, 1 for enable
    UCA1CTLW0 &= ~UCMSB; // 0 for LSB first, 1 for MSB first
    UCA1CTLW0 |= UCSSEL__SMCLK; // Use SMCLK

    // UCA Baud Rate Control Word
    UCA1BRW = 6;

    // UCA Modulation Control Word Register
    // UCBRF = 8 -> 1000 -> UCBRF3
    // UCBRSx = 0x20 -> 0010_0000 -> UCBRS5
    UCA1MCTLW = (UCOS16 | UCBRF3 | UCBRS5);

    UCA1CTLW0 &= ~UCSWRST; // disable reset state
    // --- ADD THIS TO FLUSH THE BUFFER ---
    volatile unsigned char dummy;
    dummy = UCA1RXBUF;      // Reading the buffer clears the RXIFG flag
    UCA1IFG &= ~UCRXIFG;    // Manually ensure the flag is zeroed
}

// Trasmist a char over UART
void SEND_CHAR_UART(unsigned char data) { // ASCII Character -> parse ASCII(1,2,3,4)
    // wait for UART port if busy
    while (!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = data; // TX Starts & TX Flag goes to 0
    return;
}

// Received
int RECEIVE_CHAR_UART (unsigned char *c) {
    // wait for reception
    if (!(UCA1IFG & UCRXIFG)) return 0;
    *c = UCA1RXBUF;
    return 1; // return value and clear the flag 
}

/*
    Steps to setup UART

    1. look for backchannel UART on board user's guide
        look for eUSCI (slau627a.pdf)
        for this MCU is eUSCI_A1
        Channel A (UART, SPI) is usally async while Channel B is synchronous (I2C, SPI)

    2. Pin Mapping
        look for the PIN mapping diagram on the datasheet and look for the corresponding
        TXD, RXD ; In this MCU the pin mapping are the following
        Pin 5.4/UCA1SIMO/UCA1TXD/S1288
        Pin 5.5/UCA1SOMI/UCA1RXD/S1
        Pin 3.4 / UCA1TXD
        Pin 3.5 / UCA1RXD

        in this case we have to sets of ports, we have to figure out which one to use
        go to the board user's guide and check the schematic of the jumpers
        page 33 and it say that the port is connected is P3.4 & P3.5

    3. Pin Functions divert
        look for Pin Functions table on the datasheet (for P3.4 & P3.5) Page 102
        and set the pin to the right pin function in this case UCA1TXD
        P3.4 P3SEL1 == 0 and P3SEL0 == 1 ( same for both pins )

    4. Find the recommended settings for UART
        You can manually calculate this, however, in the MCU user's guide they have recommended
        settings for typical baud rates table, look for this (P. 589)
        For this case that we are using the the SMCLK (1MHz) and Baud Rate 9600
        The recommended settings are UCOS16=1, UCBRx=6, UCBRFx=8, UCBRSx=0x20

        Example of manual calculation
        (clk speed / baud rate) / oversampling
        (1000000/9600) = 104.16/16 -> 6.xx (This is why UCBR is 6)

    5. Adjust parameters for UART
        Go to family MCU user's guide and look for eUSCI_A UART Registers; this are also called
        configuration registers (Starts @ P.692 ) and look for all the settings that you need to setup


    6. Polling the Flags
        UCA1IFG // Register
        UCTXIFG // TX flag -> 0 busy, 1 ready to tx
        UCRXIFG // RX flag -> 0 no new data, 1 new data received
        UCA1TXBUF // TX buffer  // writing to TX buffer start transmission auto (TX Flag goes to zero)
        UCA1RXBUF // RX buffer // reading the RX buffer clear the RX flag automatically
*/