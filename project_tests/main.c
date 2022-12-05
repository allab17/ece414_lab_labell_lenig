#include <xc.h>
#include <plib.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "config_clk.h"
#include "ztimer4.h"
#include "uart1.h"
#include "adc_intf.h"


#define _SUPPRESS_PLIB_WARNING 1

static enum comm_states {idle, set_z, set_y} comm_state;

char c[5];
int i;
char cha;
char buffer[50];

float z_servo_duty;
float y_servo_duty;

uint8_t set_f;

void tickFct_comm_fsm() {
    switch(comm_state) {
        case idle:;
            memset(c,0,5);
            int i=0;         
            if (uart1_rxrdy()) {
                cha = uart1_rxread();
                if (cha == 'z') {
                    cha = '\0';
                    set_f = 1;
                    comm_state = set_z; 
                    uart1_txwrite('z');

                } else if (cha == 'y') {
                    cha = '\0';
                    set_f = 1;
                    comm_state = set_y; 
                    uart1_txwrite('y');
                }
            } else comm_state = idle;
        break;
        case set_z:
                if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &z_servo_duty);
                        if (z_servo_duty > 0xffff) z_servo_duty = 0xffff;
                        else if (z_servo_duty < 0x0000) z_servo_duty = 0x0000;
                        comm_state = idle;
                        set_f = 0;
                    } else {
                        comm_state = set_z;
                        c[i] = cha;
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_z;
        break;
        case set_y:
            if (uart1_rxrdy()) { 
                cha = uart1_rxread();
                if (cha == '\r') {
                    cha = '\0';
                    sscanf(c, "%f", &y_servo_duty);
                    if (z_servo_duty > 0xffff) z_servo_duty = 0xffff;
                    else if (z_servo_duty < 0x0000) z_servo_duty = 0x0000;
                    comm_state = idle;
                    set_f = 0;
            } else {
                comm_state = set_y;
                c[i] = cha;
                uart1_txwrite(c[i]);
                cha='\0';
                i++;
            }
            } else comm_state = set_y;
        break;
        default:
            comm_state = idle;
        break;
    }
}

int main() {  
    configureADC();
    
    // Turn off analog function of Ports A and B
    ANSELA = 0; 
    ANSELB = 0;
    TRISAbits.TRISA0 = 1;
    
    //stepper pwm sigal
    zTimerOn();
    zTimerSet(50);
    
    oc1_init_plib(0x4000);
    INTEnableSystemMultiVectoredInt();
    
    uart1_init(9600);
    set_f=0;
    while (1) {
        
        if (zTimerReadFlag()) {
            oc1_setduty_plib(z_servo_duty);
            if (!set_f) {
                printf("z_servo_duty: %f", z_servo_duty);
            }
            
            tickFct_comm_fsm();
        }
    }
    
}
