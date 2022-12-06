/* Clock configuration */
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF

#include <inttypes.h>
#include <xc.h>
#include <plib.h>
#include <stdio.h>
#include "uart1.h"

const int CLOCK_FREQ = 40000000;

void uart1_init(uint32_t baudrate) {
    ANSELA = 0;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA2 = 1;
    
    __XC_UART=1;
    
    PPSOutput(1, RPA0, U1TX);    
    PPSInput(3, U1RX, RPA2);
    
    U1BRG = (CLOCK_FREQ / (16*baudrate)) - 1;
    U1MODEbits.BRGH = 0;
    
    //enable transmission and receiving
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    
    //enable UART
    U1MODEbits.ON = 1;
    
}

uint8_t uart1_txrdy() {
    return  !U1STAbits.UTXBF; //if the buffer is full we are not ready
}

void uart1_txwrite(char c) {
    while (!uart1_txrdy());  
    U1TXREG = c;
}

void uart1_txwrite_str(char *cp) {
    while (*cp) { 
        uart1_txwrite(*cp++);  //serially writes the characters to implement the string 
    }
}

uint8_t uart1_rxrdy() {
    return U1STAbits.URXDA; //the rx buffer contains data 
}

 uint8_t uart1_rxread() {
    while (!uart1_rxrdy);
    return U1RXREG;
}