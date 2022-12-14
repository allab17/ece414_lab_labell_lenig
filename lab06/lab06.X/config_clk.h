/* 
 * File:   config_clk.h
 * Author: nestorj
 *
 * Created on September 24, 2019, 1:20 PM
 * Configure the clock at 40 MHz.  Include this file ONCE in
 * your main module
 */

#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF


