# Bare-Metal UART Driver for MSP430FR6989

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Texas Instruments](https://img.shields.io/badge/Texas_Instruments-CC0000?style=for-the-badge&logo=texas-instruments&logoColor=white)
![Embedded Systems](https://img.shields.io/badge/Bare_Metal-2C2C2C?style=for-the-badge)

## Overview
A high-efficiency, bare-metal UART (Universal Asynchronous Receiver-Transmitter) driver engineered specifically for the Texas Instruments MSP430FR6989 microcontroller. This project demonstrates direct hardware register manipulation to achieve reliable, low-latency serial communication without relying on heavy Hardware Abstraction Layers (HALs) or an RTOS.

Initially developed as a polling-based Minimum Viable Product (MVP), the architecture was upgraded to leverage **Interrupt Service Routines (ISRs)**, enabling fully asynchronous, non-blocking data transmission and reception.

## Key Features
* **Bare-Metal Implementation:** Direct manipulation of the eUSCI_A (Enhanced Universal Serial Communication Interface) registers for maximum execution speed and minimal memory footprint.
* **Interrupt-Driven Architecture:** Utilizes RX and TX interrupts (ISRs) to handle asynchronous data streams efficiently, ensuring the main CPU loop is not blocked waiting for peripheral readiness.
* **Clock Optimization:** Custom configuration of the internal Clock System (CS) to ensure precise baud rate generation and reliable timing parameters.
* **Modular Design:** Clean hardware-software abstraction with a clear separation of concerns between the application logic (`main.c`) and the low-level driver implementation (`uart.c` / `uart.h`).

## Hardware & Software Requirements
* **Microcontroller:** TI MSP430FR6989 LaunchPad Development Kit
* **IDE:** Code Composer Studio (CCS)
* **Compiler:** TI CGT for MSP430
* **Serial Terminal:** PuTTY, Tera Term, or any standard serial monitor.

## Architecture & Implementation Details
The driver initializes the eUSCI_A0 module through a strict initialization sequence:
1. Placing the state machine in a software reset state (`UCSWRST`).
2. Configuring the clock source (e.g., SMCLK) and calculating the exact prescalar (`UCAxBRW`) and modulation settings (`UCAxMCTLW`) required for the target baud rate.
3. Routing the UART TX/RX signals to the appropriate GPIO pins by configuring the Port selection registers.
4. Releasing the module from reset for operation and enabling the local RX/TX interrupts.

### Project Structure
* `uart.h`: Exposes the public API for UART initialization, transmitting characters/strings, and defines hardware configuration macros.
* `uart.c`: Contains the core hardware register manipulation and the `USCI_A0_VECTOR` interrupt service routine logic.
* `main.c`: The entry point demonstrating the driver's capability, typically implementing an echo server or a serial prompt loop.

## Getting Started

1. Clone the repository:
   ```bash
   git clone [https://github.com/CarlosT25-png/UART-MSP430FR6989.git](https://github.com/CarlosT25-png/UART-MSP430FR6989.git)
   ```
   Import the project into your Code Composer Studio (CCS) workspace.

2. Connect your MSP430FR6989 LaunchPad to your workstation via USB.

3. Build the project and flash the binary to the target MCU.

4. Open a Serial Terminal connected to the LaunchPad's Application/UART COM port. Ensure the terminal matches the configured baud rate (e.g., 9600, 8-N-1).
## Author
Carlos Torres 

## License
Distributed under the MIT License.
