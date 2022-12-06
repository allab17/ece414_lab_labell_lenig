#include <xc.h>
#include <plib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "config_clk.h"
#include "ztimer4.h"
#include "timer1.h"
#include "uart1.h"
#include "ic1.h"
#include "oc1_plib.h"

#include "tft_master.h"
#include "tft_gfx.h"
#include "adc_intf.h"

#define _SUPPRESS_PLIB_WARNING 1

float des_r_s;
float kp;
float ki; 
float kd;
float actuator;
float scaled_rpm_duty;

float act_p_m_s;
float act_p_r_s;
float act_r_s;
float integ;
float err;
float deriv;
float integ_max;
float integ_min;

uint8_t set_f;
 
float scale_input_cap(float r) {
        float rpm;
        float scale;
        float min; 
        float max;
        float a;
        float b;
        
        
        rpm = r;
        min = 0;
        max = 3000;
        a = 0x0000;
        b = 0xFFFF;
        
        scale = ((b - a)*(rpm - min) / (max - min)) + a;
        return scale;
 }

static enum cntrl_states {init, ctrl} cntrl_state;

void tickFct_cntrl_fsm() {
    switch(cntrl_state) {
        case init:
            actuator=0;
            act_p_m_s=0;
            integ=0;
            cntrl_state = ctrl;
            integ_min = -1000;
            integ_max = 1000;
        break;
        case ctrl:
            act_r_s = (float) ic1_getrpm();
            scaled_rpm_duty = (uint16_t) scale_input_cap(act_r_s); 
            tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
            tft_setCursor(0,270);
            char b[5];
            sprintf(b, "%f", act_r_s);
            tft_writeString("current RPM:");
            tft_writeString(b);
            tft_setCursor(0,285);
            char bf[5];
            sprintf(bf, "%f", des_r_s);
            tft_writeString("target RPM:");
            tft_writeString(bf);
            err = des_r_s - act_r_s;
            deriv = act_r_s - act_p_r_s;
            act_p_r_s = act_r_s;
            integ = integ + err;
            integ=max(integ,integ_min);
            integ=min(integ, integ_max);
            actuator=kp*err+ki*integ-kd*deriv; 
            if (actuator > 0xffff) {
                actuator = 0xffff;
            } else if (actuator < 0) {
                actuator = 0x0000;
            }
            oc1_setduty_plib((uint16_t)actuator);
            
            
            cntrl_state = ctrl;
        break;
        default: cntrl_state = init;
            
        break;
    }
}

 

static enum comm_states {idle, set_rot, set_kp, set_ki, set_kd} comm_state;

char c[5];
int i;
char cha;
char buffer[50];

void tickFct_comm_fsm() {
    switch(comm_state) {
        case idle:;
            memset(c,0,5);
            i=0;
            tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_setCursor(0,300);
                tft_writeString("s");
                tft_setCursor(20,300);
                sprintf(buffer, "%.6g", des_r_s);
                tft_writeString(buffer);
                tft_setCursor(100,300);
                tft_writeString("p");
                tft_setCursor(120,300);
                sprintf(buffer, "%.6g", kp);
                tft_writeString(buffer);
                tft_setCursor(150,300);
                tft_writeString("i");
                tft_setCursor(170,300);
                sprintf(buffer, "%.6g", ki);
                tft_writeString(buffer);
                tft_setCursor(200,300);
                tft_writeString("d");
                tft_setCursor(220,300);
                sprintf(buffer, "%.6g", kd);
                tft_writeString(buffer);
            
            if (uart1_rxrdy()) {
                cha = uart1_rxread();
                if (cha == 's') {
                    cha = '\0';
                    comm_state = set_rot; 
                    uart1_txwrite('s');
                    tft_setCursor(0,300);
                    tft_drawRect(0,300,300,20,ILI9341_BLACK);
                    tft_fillRect(0,300,300,20,ILI9341_BLACK);
                    tft_writeString("s");
                    set_f = 1;
                } else if (cha == 'p') {
                    cha = '\0';
                    comm_state = set_kp; 
                    uart1_txwrite('p');
                    tft_setCursor(0,300);
                     tft_drawRect(0,0,300,20,ILI9341_BLACK);
                    tft_fillRect(0,0,300,20,ILI9341_BLACK);
                    tft_writeString("p");
                    set_f = 1;
                } else if (cha == 'i') {
                    cha = '\0';
                    comm_state = set_ki; 
                    uart1_txwrite('i');
                    tft_setCursor(0,300);
                    tft_drawRect(0,300,300,20,ILI9341_BLACK);
                    tft_fillRect(0,300,300,20,ILI9341_BLACK);
                    tft_writeString("i");
                    set_f = 1;
                } else if (cha == 'd') {
                    cha = '\0';
                    comm_state = set_kd; 
                    uart1_txwrite('d');
                    tft_setCursor(0,300);
                    tft_drawRect(0,300,300,20,ILI9341_BLACK);
                    tft_fillRect(0,300,300,20,ILI9341_BLACK);
                    tft_writeString("d");
                    set_f = 1;
                }
            } else comm_state = idle;
        break;
        case set_rot:
                if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &des_r_s);
                        //printf("desired set... value: %f", des_r_s);
                        set_f = 0;
                        comm_state = idle;
                    } else {
                        tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                        comm_state = set_rot;
                        c[i] = cha;
                        tft_setCursor(0,300);
                        tft_writeString("s");
                        tft_setCursor(20,300);
                        tft_writeString(c);
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_rot;
        break;
        case set_kp:
            if (uart1_rxrdy()) { 
                cha = uart1_rxread();
                if (cha == '\r') {
                    cha = '\0';
                    sscanf(c, "%f", &kp);
                    //printf("proportional set... value: %f", kp);
                    set_f = 0;
                    comm_state = idle;
            } else {
                comm_state = set_kp;
                c[i] = cha;
                tft_setCursor(0,300);
                        tft_writeString("p");
                        tft_setCursor(20,300);
                        tft_writeString(c);
                        uart1_txwrite(c[i]);
                cha='\0';
                i++;
            }
            } else comm_state = set_kp;
        break;
        case set_ki:
            if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &ki);
                        //printf("integral set... value: %f", ki);  
                        set_f = 0;
                        comm_state = idle;
                    } else {
                        comm_state = set_ki;
                        c[i] = cha;
                        tft_setCursor(0,300);
                        tft_writeString("i");
                        tft_setCursor(20,300);
                        tft_writeString(c);
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_ki;
        break; 
        case set_kd:
            if (uart1_rxrdy()) {
                    cha = uart1_rxread();
                    if (cha == '\r') {
                        cha = '\0';
                        sscanf(c, "%f", &kd);
                        //printf("derivative set... value: %f", kd);
                        set_f = 0;
                        comm_state = idle;
                    } else {
                        comm_state = set_kd;
                        c[i] = cha;
                        tft_setCursor(0,300);
                        tft_writeString("d");
                        tft_setCursor(20,300);
                        tft_writeString(c);
                        uart1_txwrite(c[i]);
                        cha='\0';
                        i++;
                    }
                } else comm_state = set_kd;
        break;
        default:
            comm_state = idle;
        break;
    }
}

uint16_t t;

uint16_t t_max = 240;  //each pixel on LCD corresponds to one time tick

uint16_t scale(uint16_t val,uint16_t min, uint16_t max, uint16_t a, uint16_t b) {
    uint16_t scale;
    scale = ((b - a)*(val - min) / (max - min)) + a;
        return scale;
}

void draw_graph() {
    if (t > t_max) {
        t = 0;
        tft_fillScreen(ILI9341_BLACK);
    }
    else {
        //fill the circles red that correspond to the 
        //each time tick function calls we draw a point on the graph
        
        //scale the actuator to screen size
        uint16_t a;
        a = scale(3000 - actuator, 0,65535,0,260);
        uint16_t d;
        d = scale(3000 - des_r_s, 0,3000,0,260);
        uint16_t ar;
        ar = scale(3000 - act_r_s, 0,3000,0,260);
        
        
        
        tft_drawCircle(t,a,1,ILI9341_BLUE);
        tft_fillCircle(t,a,1,ILI9341_BLUE);

        tft_drawCircle(t,d, 1, ILI9341_GREEN);
        tft_fillCircle(t,d, 1, ILI9341_GREEN);

        tft_drawCircle(t,ar,1,ILI9341_RED);
        tft_fillCircle(t,ar,1,ILI9341_RED);
        
         t++;
    }  
}


int main() {  
    configureADC();
    
    // Initialize TFT
    //configureADC();
    tft_init_hw();
    tft_begin();
    tft_setRotation(2);  // Landscape mode.  Use 1 for portrait.
    tft_fillScreen(ILI9341_BLACK);
    
    uint16_t t1, t2;
    zTimerOn();
    zTimerSet(100);
    ic1_init();
    oc1_init_plib(0x4000);
    INTEnableSystemMultiVectoredInt();
   
    t1 = zTimerReadms();
    t=0;
    set_f = 0;
    

        uart1_init(9600);
        
        comm_state = idle;
        cntrl_state = init;
        
    const uint16_t period_graph = 2;
    uint16_t ta1,ta2;
    timer1_init();
    ta1 = timer1_read();
        
     
    while (1) {
       ta2 = timer1_read();
        tft_setTextSize(2);
             
        
        if (timer1_ms_elapsed(ta1, ta2) >= period_graph) {
            ta1 = ta2;
            draw_graph();
        }
       
        if (zTimerReadFlag()) {
            tickFct_cntrl_fsm();
            tickFct_comm_fsm();
        }
    }

}




