
/*============================================================================
 * main.c
 *      Example code to show how to use the TFT display.  Writes some text
 * as well as some random lines and circles.
 *===========================================================================*/

#define _SUPPRESS_PLIB_WARNING 1

// Configure clocks
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20 //40 MHz
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2 // PB 40 MHz
#pragma config FWDTEN = OFF,  FSOSCEN = OFF, JTAGEN = OFF

#include "tft_master.h"
#include "tft_gfx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <inttypes.h>
#include "ts_lcd.h"
#include "TouchScreen.h"
#include <xc.h>
#include <plib.h>
#include "adc_intf.h"
#include "timer1.h"

// Convenient defines for width and height of display
#define DW          320
#define DH          240
#define MAX_RAD     50

//cursor pos
 uint16_t xpos, ypos;

const uint16_t x_ref = 0;  //first column to scale the calculator buttons
const uint16_t y_ref = 240;

const uint16_t btn_s_w = 60;
const uint16_t btn_s_h = 60;

uint16_t btn_clr_x;
uint16_t btn_clr_y;
uint16_t btn_0_x;
uint16_t btn_0_y;
uint16_t btn_eq_x;
uint16_t btn_eq_y;
uint16_t btn_1_x;
uint16_t btn_1_y;
uint16_t btn_2_x;
uint16_t btn_2_y;
uint16_t btn_3_x;
uint16_t btn_3_y;
uint16_t btn_4_x;
uint16_t btn_4_y;
uint16_t btn_5_x;
uint16_t btn_5_y;
uint16_t btn_6_x;
uint16_t btn_6_y;
uint16_t btn_7_x;
uint16_t btn_7_y;
uint16_t btn_8_x;
uint16_t btn_8_y;
uint16_t btn_9_x;
uint16_t btn_9_y;
uint16_t btn_div_x;
uint16_t btn_div_y;
uint16_t btn_mul_x;
uint16_t btn_mul_y;
uint16_t btn_sub_x;
uint16_t btn_sub_y;
uint16_t btn_add_x;
uint16_t btn_add_y;

void init_button_dim() {
    btn_clr_x = x_ref;
    btn_clr_y = y_ref;
    btn_0_x = x_ref + btn_s_w;
    btn_0_y = y_ref;
    btn_eq_x = x_ref + 2*btn_s_w;
    btn_eq_y = y_ref;
    btn_1_x = x_ref;
    btn_1_y = y_ref - btn_s_h;  
btn_2_x = x_ref + btn_s_w;
 btn_2_y = y_ref - btn_s_h;
 btn_3_x = x_ref + 2*btn_s_w;
 btn_3_y = y_ref - btn_s_h;
btn_4_x = x_ref;
 btn_4_y = y_ref - 2*btn_s_h;
btn_5_x = x_ref + btn_s_w;
btn_5_y = y_ref - 2*btn_s_h;
 btn_6_x = x_ref + 2*btn_s_w;
 btn_6_y = y_ref - 2*btn_s_h;
 btn_7_x = x_ref;
 btn_7_y = y_ref - 3*btn_s_h;
 btn_8_x = x_ref + btn_s_w;
 btn_8_y = y_ref - 3*btn_s_h;
btn_9_x = x_ref + 2*btn_s_w;
 btn_9_y = y_ref - 3*btn_s_h;
 btn_div_x = x_ref + 3*btn_s_w;
 btn_div_y = y_ref;
 btn_mul_x = x_ref + 3*btn_s_w;
btn_mul_y = y_ref - btn_s_h;
 btn_sub_x = x_ref + 3*btn_s_w;
 btn_sub_y = y_ref - 2*btn_s_h;
btn_add_x = x_ref + 3*btn_s_w;
 btn_add_y = y_ref - 3*btn_s_h;
}

void draw_buttons() {
    tft_drawRect(btn_clr_x, btn_clr_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_clr_x, btn_clr_y, 'c', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_0_x, btn_0_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_0_x, btn_0_y, '0', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_eq_x, btn_eq_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_eq_x, btn_eq_y, '=', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_1_x, btn_1_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_1_x, btn_1_y, '1', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_2_x, btn_2_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_2_x, btn_2_y, '2', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_3_x, btn_3_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_3_x, btn_3_y, '3', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_4_x, btn_4_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_4_x, btn_4_y, '4', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_5_x, btn_5_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_5_x, btn_5_y, '5', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_6_x, btn_6_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_6_x, btn_6_y, '6', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_7_x, btn_7_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_7_x, btn_7_y, '7', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_8_x, btn_8_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_8_x, btn_8_y, '8', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_9_x, btn_9_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_9_x, btn_9_y, '9', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_div_x, btn_div_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_div_x, btn_div_y, '/', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_mul_x, btn_mul_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_mul_x, btn_mul_y, '*', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_sub_x, btn_sub_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_sub_x, btn_sub_y, '-', ILI9341_WHITE, ILI9341_BLACK, 2);
    tft_drawRect(btn_add_x, btn_add_y, btn_s_w, btn_s_h, ILI9341_WHITE);
    tft_drawChar(btn_add_x, btn_add_y, '+', ILI9341_WHITE, ILI9341_BLACK, 2);
}


//calc_fsm code

//operand button flags
uint8_t btn_0 = 0;
uint8_t btn_1 = 0;
uint8_t btn_2 = 0;
uint8_t btn_3 = 0;
uint8_t btn_4 = 0;
uint8_t btn_5 = 0;
uint8_t btn_6 = 0;
uint8_t btn_7 = 0;
uint8_t btn_8 = 0;
uint8_t btn_9 = 0;

//operator button flags
uint8_t btn_mul = 0;
uint8_t btn_div = 0;
uint8_t btn_add = 0;
uint8_t btn_sub = 0;

//function button flags
uint8_t btn_clr = 0;
uint8_t btn_eq = 0;

//error flag
uint8_t err = 0;

int32_t val = 0;
int32_t curr_val;
int32_t r; //result

char display_str[100];


uint8_t btn_operand_listener() {
    if (btn_0 || btn_1 || btn_2 || btn_3 || btn_4 || btn_5 || btn_6 || btn_7 || btn_8 || btn_9) return 1;
	else return 0;
}


void set_val() {
		//set the value corresponding to the button
		if (btn_0) val = 0;
		else if (btn_1) val = 1;
		else if (btn_2) val = 2;
		else if (btn_3) val = 3;
		else if (btn_4) val = 4;
		else if (btn_5) val = 5;
		else if (btn_6) val = 6;
		else if (btn_7) val = 7;
		else if (btn_8) val = 8;
		else if (btn_9) val = 9;
}

void deflag_operand() {
btn_0 = 0;
btn_1 = 0;
btn_2 = 0;
btn_3 = 0;
btn_4 = 0;
btn_5 = 0;
btn_6 = 0;
btn_7 = 0;
btn_8 = 0;
btn_9 = 0;
}



void flag_button(uint16_t xpos, uint16_t ypos) { //returns a number corresponding to the button that can be interpreted by the debouncer
		if ((xpos > btn_1_x) && (xpos < (btn_1_x + btn_s_w)) && (ypos > btn_1_y) && (ypos < (btn_1_y + btn_s_h))) {
            btn_1 = 1;
        } else if ((xpos > btn_2_x) && (xpos < (btn_2_x + btn_s_w)) && (ypos > btn_2_y) && (ypos < (btn_2_y + btn_s_h))) {
            btn_2 = 1;
        } else if ((xpos > btn_3_x) && (xpos < (btn_3_x + btn_s_w)) && (ypos > btn_3_y) && (ypos < (btn_3_y + btn_s_h))) {
            btn_3 = 1;
        } else if ((xpos > btn_4_x) && (xpos < (btn_4_x + btn_s_w)) && (ypos > btn_4_y) && (ypos < (btn_4_y + btn_s_h))) {
            btn_4 = 1;
        } else if ((xpos > btn_5_x) && (xpos < (btn_5_x + btn_s_w)) && (ypos > btn_5_y) && (ypos < (btn_5_y + btn_s_h))) {
            btn_5 = 1;
        } else if ((xpos > btn_6_x) && (xpos < (btn_6_x + btn_s_w)) && (ypos > btn_6_y) && (ypos < (btn_6_y + btn_s_h))) {
            btn_6 = 1;
        } else if ((xpos > btn_7_x) && (xpos < (btn_7_x + btn_s_w)) && (ypos > btn_7_y) && (ypos < (btn_7_y + btn_s_h))) {
            btn_7 = 1;
        } else if ((xpos > btn_8_x) && (xpos < (btn_8_x + btn_s_w)) && (ypos > btn_8_y) && (ypos < (btn_8_y + btn_s_h))) {
            btn_8 = 1;
        } else if ((xpos > btn_9_x) && (xpos < (btn_9_x + btn_s_w)) && (ypos > btn_9_y) && (ypos < (btn_9_y + btn_s_h))) {
            btn_9 = 1;
        }  else if ((xpos > btn_clr_x) && (xpos < (btn_clr_x + btn_s_w)) && (ypos > btn_clr_y) && (ypos < (btn_clr_y + btn_s_h))) {
            btn_clr = 1;
        } else if ((xpos > btn_0_x) && (xpos < (btn_0_x + btn_s_w)) && (ypos > btn_0_y) && (ypos < (btn_0_y + btn_s_h))) {
            btn_0 = 1;
        } else if ((xpos > btn_eq_x) && (xpos < (btn_eq_x + btn_s_w)) && (ypos > btn_eq_y) && (ypos < (btn_eq_y + btn_s_h))) {
            btn_eq = 1;
        } else if ((xpos > btn_div_x) && (xpos < (btn_div_x + btn_s_w)) && (ypos > btn_div_y) && (ypos < (btn_div_y + btn_s_h))) {
            btn_div = 1;
        } else if ((xpos > btn_mul_x) && (xpos < (btn_mul_x + btn_s_w)) && (ypos > btn_mul_y) && (ypos < (btn_mul_y + btn_s_h))) {
            btn_mul = 1;
        } else if ((xpos > btn_sub_x) && (xpos < (btn_sub_x + btn_s_w)) && (ypos > btn_sub_y) && (ypos < (btn_sub_y + btn_s_h))) {
            btn_sub = 1;
        } else if ((xpos > btn_add_x) && (xpos < (btn_add_x + btn_s_w)) && (ypos > btn_add_y) && (ypos < (btn_add_y + btn_s_h))) {
            btn_add = 1;
        }
}

void btn_listener() { //button listener
    if (ts_lcd_get_ts(&xpos, &ypos)) { //if there is pressure on the screen
            ts_lcd_get_ts(&xpos, &ypos); //x and y will be updated with the touch pos
            flag_button(xpos,ypos);
    }
}

uint8_t add_flag = 0;
uint8_t sub_flag = 0;
uint8_t mul_flag = 0;
uint8_t div_flag = 0;

uint8_t first_val = 0;

//static enum DEBP1_States {DEBP1_NOPUSH, DEBP1_MAYBENOPUSH, DEBP1_MAYBEPUSH, DEBP1_PUSHED} DEBP1_state;


//void tickFct_DEBP1() {
//    switch(DEBP1_state) {
//        case DEBP1_NOPUSH:
//            if (btn_listener()) {
//                DEBP1_state = DEBP1_MAYBEPUSH;
//            } else {
//                DEBP1_state = DEBP1_NOPUSH;
//            }
//            break;
//        case DEBP1_MAYBEPUSH:
//            if (btn_listener()) {
//                uint16_t x;
//                uint16_t y;
//                x=xpos;
//                y=ypos;
//                flag_button(x, y);
//                DEBP1_state = DEBP1_PUSHED;
//            } else {
//                DEBP1_state = DEBP1_NOPUSH;
//            }
//            break;
//        case DEBP1_PUSHED:
//            if (btn_listener()) {
//                DEBP1_state = DEBP1_PUSHED;
//            } else {
//                DEBP1_state = DEBP1_MAYBENOPUSH;
//            }
//            break;
//        case DEBP1_MAYBENOPUSH:
//            if (btn_listener()) {
//                DEBP1_state = DEBP1_PUSHED;
//            } else {
//                DEBP1_state = DEBP1_NOPUSH;
//            }
//            break;
//        default:
//            DEBP1_state = DEBP1_NOPUSH;
//            break;
//    }
//}


static enum calc_fsm_states {idle, enter_operand, op_mul, op_div, op_add, op_sub, result, clear, error} calc_state;


uint8_t r_flag = 0;
uint8_t err_flag = 0;

void tick_calc() {
    btn_listener(); //each iteration through the tick function we listen for a button, if the button is pressed it will be flagged
    switch (calc_state) {
        case idle:
            if (btn_operand_listener()) {
                set_val(); //set the value corresponding to the operand
                curr_val = val;
                deflag_operand(); //deflag all operand buttons
                
                tft_setCursor(0,0);
                tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                char curr_val_str[50];
                sprintf(curr_val_str, "%d", curr_val);
                strcat(display_str,curr_val_str);
                tft_writeString(display_str); //write to calc screen
                
                calc_state = enter_operand;
            }
            break;
            
        case enter_operand:
            if (curr_val > 100000000 || curr_val < -100000000 || err==1) {
                if (!err == 1) err = 2;
                    
                    calc_state = error;
            } else if (btn_clr) { 
                calc_state = clear; 
            } else if (btn_operand_listener()) {
                set_val(); //set the value corresponding to the operand
                    char curr_val_p_str[50];
                    sprintf(curr_val_p_str, "%d", curr_val);
                    //get length of current value string and deconcatenate by the length of the curr_val_s from the end of display_str
                    uint8_t display_str_l = strlen(display_str);
                    uint8_t curr_val_s_l =  strlen(curr_val_p_str);
                    display_str[display_str_l - curr_val_s_l] = '\0';
                    
                    curr_val = (curr_val * 10) + val;
                    deflag_operand();
                
                    //write value to calc screen
                    tft_setCursor(0,0);
                    tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                    tft_drawRect(0,0,300,50,ILI9341_BLACK);
                    tft_fillRect(0,0,300,50,ILI9341_BLACK);
                    char curr_val_str[50];
                    sprintf(curr_val_str, "%d", curr_val);
                    strcat(display_str,curr_val_str);
                    tft_writeString(display_str);
                
                    calc_state = enter_operand;  
            } else if (btn_eq) {
                btn_eq=0;
                if (!first_val) {
                     r = curr_val;
                     first_val=1;
                } else {
                    if (add_flag) {
                        r = r + curr_val;
                        add_flag = 0;
                    } else if (sub_flag) {
                        r = r - curr_val;
                        sub_flag = 0;
                    } else if (mul_flag) {
                        r = r * curr_val;
                        mul_flag = 0;
                    } else if (div_flag) {
                        if (curr_val == 0) {
                            err = 1;
                        } else {
                            r = r / curr_val;
                        }
                        div_flag = 0;
                    }
                }
                
                if (!err) calc_state = result;
                else calc_state = error;
                
            } else if (btn_mul) {
                if (!first_val) {
                     r = curr_val;
                     first_val=1;
                } else {
                    if (add_flag) {
                        r = r + curr_val;
                        add_flag = 0;
                    } else if (sub_flag) {
                        r = r - curr_val;
                        sub_flag = 0;
                    } else if (mul_flag) {
                        r = r * curr_val;
                        mul_flag = 0;
                    } else if (div_flag) {
                        if (curr_val == 0) {
                            err = 1;
                        } else {
                            r = r / curr_val;
                        }
                        div_flag = 0;
                    }
                }
                
                char r_str[100];
                    //convert the cur_val to string
                    sprintf(r_str, "%d", r);
                    display_str[0] = '\0';
                    strcat(display_str,r_str); //string concatenation
                
                //write to calc screen
                tft_setCursor(0,0);
                tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                strcat(display_str,"*"); //string concatenation
                tft_writeString(display_str);
                
                if (!err) calc_state = op_mul;
            }
            else if (btn_div) {
                 if (!first_val) {
                     r = curr_val;
                     first_val=1;
                } else {
                    if (add_flag) {
                        r = r + curr_val;
                        add_flag = 0;
                    } else if (sub_flag) {
                        r = r - curr_val;
                        sub_flag = 0;
                    } else if (mul_flag) {
                        r = r * curr_val;
                        mul_flag = 0;
                    } else if (div_flag) {
                        if (curr_val == 0) {
                            err = 1;
                        } else {
                            r = r / curr_val;
                        }
                        div_flag = 0;
                    }
                }
                 
                 char r_str[100];
                    //convert the cur_val to string
                    sprintf(r_str, "%d", r);
                    display_str[0] = '\0';
                    strcat(display_str,r_str); //string concatenation
                
                //write to calc screen
                tft_setCursor(0,0);
                tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                strcat(display_str,"/"); //string concatenation
                tft_writeString(display_str);
                
                if (!err) calc_state = op_div;
            }
            else if (btn_add) {
                 if (!first_val) {
                     r = curr_val;
                     first_val=1;
                } else {
                    if (add_flag) {
                        r = r + curr_val;
                        add_flag = 0;
                    } else if (sub_flag) {
                        r = r - curr_val;
                        sub_flag = 0;
                    } else if (mul_flag) {
                        r = r * curr_val;
                        mul_flag = 0;
                    } else if (div_flag) {
                        if (curr_val == 0) {
                            err = 1;
                        } else {
                            r = r / curr_val;
                        }
                        div_flag = 0;
                    }
                }
                 
                 char r_str[100];
                    //convert the cur_val to string
                    sprintf(r_str, "%d", r);
                    display_str[0] = '\0';
                    strcat(display_str,r_str); //string concatenation
                
                //write to calc screen
                tft_setCursor(0,0);
                tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                strcat(display_str,"+"); //string concatenation
                tft_writeString(display_str);
                
                if (!err) calc_state = op_add; 
            }
            else if (btn_sub) {
                 if (!first_val) {
                     r = curr_val;
                     first_val=1;
                } else {
                    if (add_flag) {
                        r = r + curr_val;
                        add_flag = 0;
                    } else if (sub_flag) {
                        r = r - curr_val;
                        sub_flag = 0;
                    } else if (mul_flag) {
                        r = r * curr_val;
                        mul_flag = 0;
                    } else if (div_flag) {
                        if (curr_val == 0) {
                            err = 1;
                        } else {
                            r = r / curr_val;
                        }
                        div_flag = 0;
                    }
                }
                 
                    char r_str[100];
                    //convert the cur_val to string
                    sprintf(r_str, "%d", r);
                    display_str[0] = '\0';
                    strcat(display_str,r_str); //string concatenation
                
                //write to calc screen
                tft_setCursor(0,0);
                tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                strcat(display_str,"-"); //string concatenation
                tft_writeString(display_str);
                
                if (!err) calc_state = op_sub;
            } else calc_state = enter_operand;
            break;
        case op_mul:
            btn_mul = 0;
            mul_flag=1;
            
            if (btn_clr) calc_state = clear;
            else calc_state = idle;
            break;
        case op_div:
            btn_div = 0;
            div_flag=1;
            
            if (btn_clr) calc_state = clear;
            else calc_state = idle;
            break;
        case op_add:
            btn_add = 0;
            add_flag=1;
            
            if (btn_clr) calc_state = clear;
            else calc_state = idle;
            break;
        case op_sub:
            btn_sub = 0;
            sub_flag=1;
            
            if (btn_clr) calc_state = clear;
            else calc_state = idle;
            break;
        case clear :
            btn_clr = 0;
            r=0;
            first_val = 0;
            //write to calc screen
            tft_setCursor(0,0);
            tft_drawRect(0,0,300,50,ILI9341_BLACK);
            tft_fillRect(0,0,300,50,ILI9341_BLACK);
            tft_setTextColor2(ILI9341_WHITE,ILI9341_BLACK);
            //tft_setTextColor2(ILI9341_WHITE, ILI9341_BLACK);
            display_str[0] = '\0';
            tft_writeString("0");
            calc_state = idle;
            break;
        case error:
            if (!err_flag) {
                display_str[0] = '\0';
                tft_setCursor(0,0);
                tft_drawRect(0,0,300,50,ILI9341_BLACK);
                tft_fillRect(0,0,300,50,ILI9341_BLACK);
                tft_setTextColor(ILI9341_RED);
                if (err == 2) { tft_writeString("ERROR"); }
                else  tft_writeString("DIV0");
                err_flag = 1;
            }
            r=0;
            err = 0;
            first_val = 0;
            if (btn_clr) { err_flag = 0;  calc_state = clear; }
            break;
        case result: 
            btn_eq = 0;
                if (!r_flag) {
                    if (r > 100000000 || r < -100000000) {
                    err = 2;
                } else {
                    display_str[0] = '\0';
                    tft_writeString(display_str);
                    //write to calc screen
                    tft_setCursor(0,0); 
                    tft_drawRect(0,0,300,50,ILI9341_BLACK);
                    tft_fillRect(0,0,300,50,ILI9341_BLACK);
                    tft_setTextColor(ILI9341_RED);
                    char r_str[100];
                    //convert the cur_val to string
                    sprintf(r_str, "%d", r);
                    tft_writeString(r_str);
                }
                    r_flag = 1;   
                }
            
            first_val = 0;
            if (err == 2) calc_state = error;
            else if (btn_clr) { r_flag = 0; calc_state = clear; }
            break;
    }
    
}


void main()
{   
    // Turn off analog function of Ports A and B
    ANSELA = 0; 
    ANSELB = 0; 
    
    // Turn off comparator functions
    CM1CON = 0; 
    CM2CON = 0;
    
    configureADC();
    
    // Initialize TFT
    //configureADC();
    tft_init_hw();
    tft_begin();
    tft_setRotation(4);  // Landscape mode.  Use 1 for portrait.
    tft_fillScreen(ILI9341_BLACK);
 
    const uint16_t PERIOD_CALC = 100;
    const uint16_t PERIOD_DEB = 50;
    uint16_t ta1, ta2, tb1, tb2;
    timer1_init();
    ta1 = tb1 = timer1_read();
    init_button_dim();
    while (1)
    {   
        //set a flag so that when we clear the screen we will draw a black rectangle
        tft_setTextSize(2);
        
        ta2 = tb2 = timer1_read();
        
        
        tft_setTextSize(2);
        draw_buttons();
        
        if (timer1_ms_elapsed(ta1, ta2) >= PERIOD_CALC) {
            ta1 = ta2;
            tick_calc();
        }
//        if (timer1_ms_elapsed(tb1, tb2) >= PERIOD_DEB) {
//          tb1 = tb2;
//          tickFct_DEBP1();
//        }
    }    
    
}


