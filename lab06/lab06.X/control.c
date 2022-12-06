#include <inttypes.h>
#include <stdio.h>
#include <xc.h>
#include <plib.h>

float des_r_s;
float kp;
float ki; 
float kd;
float actuator;

static enum cntrl_states {init, ctrl} cntrl_state;

void tickFct_cntrl_fsm() {
    switch(cntrl_state) {
        case init:;
            
            static uint16_t act_p_m_s;
            static uint16_t act_p_r_s;
            static uint16_t act_r_s;
            static uint16_t integ;
            static uint16_t err;
            static uint16_t deriv;
            static uint16_t integ_max;
            static uint16_t integ_min;
            actuator=0;
            act_p_m_s=0;
            integ=0;
        break;
        case ctrl:
            act_r_s = ic1_getrpm();
            err = des_r_s - act_r_s;
            deriv = act_r_s - act_p_r_s;
            act_p_r_s = act_r_s;
            integ = integ + err;
            integ=max(integ,integ_min);
            integ=min(integ, integ_max);
            actuator=kp*err+ki*integ+kd*deriv;
            oc1_setduty_plib(actuator);
        break;
        default:
            
        break;
    }
}

static enum comm_states {idle, set_rot, set_kp, set_ki, set_kd} comm_state;



void tickFct_comm_fsm() {
    switch(comm_state) {
        case init:;
            static char c[30];
            static int i=0;
            if (uart1_rxrdy() && uart1_rxread() == 's') {
                comm_state = set_rot; 
            }
            else comm_state = idle;
            uart1_txwrite(c);
        break;
        case set_rot:
            if (uart1_rxrdy() && uart1_rxread() == '\r') { 
                comm_state = idle;
                sscanf(c, "%d", &des_r_s);
            } else if (uart1_rxrdy()) {
                comm_state = set_rot;
                c[i] = uart1_rxread();
                i++;
            }
            uart1_txwrite(c);
        break;
        case set_kp:
            if (uart1_rxrdy() && uart1_rxread() == '\r') { 
                comm_state = idle;
                sscanf(c, "%d", &kp);
            } else if (uart1_rxrdy()) {
                comm_state = set_kp;
                c[i] = uart1_rxread();
                i++;
            }
            uart1_txwrite(c);
        break;
        case set_ki:
            if (uart1_rxrdy() && uart1_rxread() == '\r') { 
                comm_state = idle;
                sscanf(c, "%d", &ki);
            } else if (uart1_rxrdy()) {
                comm_state = set_ki;
                c[i] = uart1_rxread();
                i++;
            }
            uart1_txwrite(c);
        break;
        case set_kd:
            if (uart1_rxrdy() && uart1_rxread() == '\r') { 
                comm_state = idle;
                sscanf(c, "%d", &kd);
            } else if (uart1_rxrdy()) {
                comm_state = set_kd;
                c[i] = uart1_rxread();
                i++;
            }
            uart1_txwrite(c);
        break;
        default:
            
        break;
    }
}
