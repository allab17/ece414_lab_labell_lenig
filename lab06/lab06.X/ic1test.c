//#include <xc.h>
//#include <plib.h>
//#include <inttypes.h>
//#include <stdio.h>
//
//#include "config_clk.h"
//#include "ztimer4.h"
//#include "uart1.h"
//#include "ic1.h"n() {
//    uint16_t period, lastperiod;
//    uint8_t buffer [20];
//    uint16_t t1, t2;
//    zTimerOn();
//    zTimerSet(1000);
//    uart1_init(9600);
//    uart1_txwrite_str("Beginning IC1 test\n\r");
//    ic1_init();
//    INTEnableSystemMultiVectoredInt();
//    t1 = zTimerReadms();
//    while (1) {
//        if (zTimerReadFlag()) {
//            period = ic1_getperiod();
//            sprintf(buffer, "period: %6d\r\n", period);
//            uart1_txwrite_str(buffer);
//            if (period != lastperiod) {
//                lastperiod = period;
//            }
//        }
//
//    }
//
//}

//int mai

