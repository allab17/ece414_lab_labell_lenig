/* 
 * File:   ic1.c
 * Author: nestorj
 *
 * Created on October 3, 2019, 5:34 PM
 * Simple demonstration of Input Capture using IC1 and a vectored interrupt.
 * Note: the user of this module must call INTEnableSystemMultiVectoredInt();
 * after the module (and any other modules using interrupts) are initialized
 * UPDATED Nov. 3, 2022
 */
#include <xc.h>
#include <plib.h>
#include "ic1.h"
#include "tft_master.h"  // for PBCLK declaration

    static uint32_t capture1, last_capture1, capture_period, max_period, min_period;
    static uint8_t capture_flag;  // indicate capture since last readPeriod
    
    // Configure IC1 using Timer3
    // (user must still call INTEnableSystemMultiVectoredInt afterward)
    void ic1_init() {
        OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, 0xffff);
        OpenCapture1( IC_EVERY_RISE_EDGE | IC_INT_1CAPTURE | IC_TIMER3_SRC | IC_ON );
        ConfigIntCapture1(IC_INT_ON | IC_INT_PRIOR_3 | IC_INT_SUB_PRIOR_3 );
        INTClearFlag(INT_IC1);
        PPSInput(3, IC1, RPB13);          // connect PIN 24 to IC1 capture unit
        mPORTBSetPinsDigitalIn(BIT_13);  // Set port as input (important!)
        capture1 = 0;
        last_capture1 = 0;
        capture_period = 0xffff;
    }    
    
    

    // IC1 Interrupt service routine
    void __ISR(_INPUT_CAPTURE_1_VECTOR, ipl3) C1Handler(void) {
        capture1 = mIC1ReadCapture();
        capture_period = capture1- last_capture1;
        // condition on last capture to avoid start up error
        if (capture_period > max_period && last_capture1 > 0) max_period = capture_period;
        if (capture_period < min_period && last_capture1 > 0) min_period = capture_period;
        last_capture1 = capture1;
        capture_flag = 1;
        mIC1ClearIntFlag();     // clear the interrupt flag!
}
    
    // return the period measured by IC1 in 25ns ticks
    uint16_t ic1_getperiod() {
        if (!capture_flag) return 0xffff;
        else {
            capture_flag = 0;
            return capture_period;
        }
    }
    
    const uint32_t TIMER_PRESCALE = 256;
    const uint32_t STRIPES = 1;
    static uint16_t rpm;
    
    // return the estimated RPM of the input capture
    
    uint16_t ic1_ticks2rpm(uint16_t ticks) {
        uint32_t ticks_32, rpm_32;
        if (ticks == 0xffff) return 0;
        else {
            ticks_32 = ticks;
            rpm_32 = ((PBCLK/(STRIPES*TIMER_PRESCALE)) * 60) / ticks_32;
            return rpm_32;
        }
    }
    
    uint16_t ic1_getrpm(){
        uint16_t ticks;
        ticks = ic1_getperiod();
        if (ticks == 0) return 0;
        else return( ic1_ticks2rpm(ticks));
    }
