#include <xc.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h> // for sprintf
#include "uart1.h"
// Module includes here
// Number of iterations for testing. You may need to play with this
// number. If it is too short, you may not get a very accurate measure
// of performance. Too long and you will have to wait forever.
#define NUM_ITERATIONS 100000
// This is the number of times you repeat the operation within the
// loop. You want to repeat enough times that the loop overhead is
// small for the simplest operations.
#define NUM_REPS 10

void test_uint8_add() {
 uint32_t i;
 uint8_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_uint8_sub() {
 uint32_t i;
 uint8_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_uint8_div() {
 uint32_t i;
 uint8_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}

void test_uint8_mult()
{
 uint32_t i;
 uint8_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_uint16_add() {
 uint32_t i;
 uint16_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_uint16_sub() {
 uint32_t i;
 uint16_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_uint16_mult()
{
 uint32_t i;
 uint16_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_uint16_div() {
 uint32_t i;
 uint16_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}

void test_uint32_add() {
 uint32_t i;
 uint32_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_uint32_sub() {
 uint32_t i;
 uint32_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_uint32_mult()
{
 uint32_t i;
 uint32_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_uint32_div() {
 uint32_t i;
 uint32_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}

void test_uint64_add() {
 uint32_t i;
 uint64_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_uint64_sub() {
 uint32_t i;
 uint64_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_uint64_mult()
{
 uint32_t i;
 uint64_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_uint64_div() {
 uint32_t i;
 uint64_t i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}

void test_float_add() {
 uint32_t i;
 float i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_float_sub() {
 uint32_t i;
 float i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_float_mult()
{
 uint32_t i;
 float i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_float_div() {
 uint32_t i;
 float i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}

void test_double_add() {
 uint32_t i;
 double i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 i3 = i1+i2;
 }
}

void test_double_sub() {
 uint32_t i;
 double i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 i3 = i1-i2;
 }
}

void test_double_mult()
{
 uint32_t i;
 double i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 i3 = i1*i2;
 }
}

void test_double_div() {
 uint32_t i;
 double i1, i2, i3;
 i1 = 15;
 i2 = 26;
 for (i=0; i<NUM_ITERATIONS; i++)
 {
 // Make sure NUM_REPS is the same as the number
 // of repeated lines here.
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 i3 = i1/i2;
 }
}


void main()
{
    uart1_init(9600);
    //T1:
    uart1_txwrite('c');
    //T2:
    uart1_txwrite_str("teststring");
    //T3:
    uart1_txwrite_str("Hello alexandertrevor");
    //T4:
    uart1_txwrite_str("100characterstringasdjfhasdlfhaljdsfhsdfkasdhfkjashdfjhaksdhfkhakfdhjashjfdkjdashfjahfdkjahfkjadshk");
    //T5:
    uart1_txwrite_str("ashorterstring");
    
    //T6:
    char c;
    printf("Enter character: Press * to end test\n");
    while (1) {
        if (uart1_rxrdy()) {
           c = uart1_rxread();
           if (c == '*') break;
           else if (c >= 'A' && c <= 'Z') c = c + 0x20;
           else c = c - 0x20;
            uart1_txwrite(c);
        }
    }

    
 uint8_t t1, t2;
 double rep;
 // !!! Add code: Initialize uart1 & ztimer modules
 zTimerSet();
 // and turn on interrupts
 zTimerOn();
 printf("Performance Summary: Time per operation statistics\r\n");
 rep = 1000.0;
 printf("repeated 10,000 times\n");
 // Test adding bytes/////////////////////////////////////
 t1 = zTimerReadms();
 test_uint8_add();
 t2 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINT8 ADD: %.06f us per operation\r\n",
 (double)(t2-t1)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t1 = zTimerReadms();
 test_uint8_sub();
 t2 = zTimerReadms();
 printf("UINT8 SUB: %.06f us per operation\r\n",
 (double)(t2-t1)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t1 = zTimerReadms();
 test_uint8_mult();
 t2 = zTimerReadms();
 printf("UINT8 MULT: %.06f us per operation\r\n",
 (double)(t2-t1)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t1 = zTimerReadms();
 test_uint8_div();
 t2 = zTimerReadms();
 printf("UINT8 DIV: %.06f us per operation\r\n",
 (double)(t2-t1)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 //16
  uint16_t t3, t4;
 
  // Test adding bytes/////////////////////////////////////
 t3 = zTimerReadms();
 test_uint16_add();
 t4 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINT16 ADD: %.06f us per operation\r\n",
 (double)(t4-t3)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t3 = zTimerReadms();
 test_uint16_sub();
 t4 = zTimerReadms();
 printf("UINT16 SUB: %.06f us per operation\r\n",
 (double)(t4-t3)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t3 = zTimerReadms();
 test_uint16_mult();
 t4 = zTimerReadms();
 printf("UINT16 MULT: %.06f us per operation\r\n",
 (double)(t4-t3)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t3 = zTimerReadms();
 test_uint16_div();
 t4 = zTimerReadms();
 printf("UINT16 DIV: %.06f us per operation\r\n",
 (double)(t4-t3)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // 32 bit
 uint32_t t5, t6;
 
  // Test adding bytes/////////////////////////////////////
 t5 = zTimerReadms();
 test_uint32_add();
 t6 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINT32 ADD: %.06f us per operation\r\n",
 (double)(t6-t5)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t5 = zTimerReadms();
 test_uint32_sub();
 t6 = zTimerReadms();
 printf("UINT32 SUB: %.06f us per operation\r\n",
 (double)(t6-t5)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t5 = zTimerReadms();
 test_uint32_mult();
 t6 = zTimerReadms();
 printf("UINT32 MULT: %.06f us per operation\r\n",
 (double)(t6-t5)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t5 = zTimerReadms();
 test_uint32_div();
 t6 = zTimerReadms();
 printf("UINT32 DIV: %.06f us per operation\r\n",
 (double)(t6-t5)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 //64 bit
 uint64_t t7, t8;
 
 // Test adding bytes/////////////////////////////////////
 t7 = zTimerReadms();
 test_uint64_add();
 t8 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINT64 ADD: %.06f us per operation\r\n",
 (double)(t8-t7)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t7 = zTimerReadms();
 test_uint64_sub();
 t8 = zTimerReadms();
 printf("UINT64 SUB: %.06f us per operation\r\n",
 (double)(t8-t7)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t7 = zTimerReadms();
 test_uint64_mult();
 t8 = zTimerReadms();
 printf("UINT64 MULT: %.06f us per operation\r\n",
 (double)(t8-t7)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t7 = zTimerReadms();
 test_uint64_div();
 t8 = zTimerReadms();
 printf("UINT64 DIV: %.06f us per operation\r\n",
 (double)(t8-t7)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 //float
float t9, t10;
 
 // Test adding bytes/////////////////////////////////////
 t9 = zTimerReadms();
 test_float_add();
 t10 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINTFLOAT ADD: %.06f us per operation\r\n",
 (double)(t10-t9)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t9 = zTimerReadms();
 test_float_sub();
 t10 = zTimerReadms();
 printf("UINTFLOAT SUB: %.06f us per operation\r\n",
 (double)(t10-t9)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t9 = zTimerReadms();
 test_float_mult();
 t10 = zTimerReadms();
 printf("UINTFLOAT MULT: %.06f us per operation\r\n",
 (double)(t10-t9)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t9 = zTimerReadms();
 test_float_div();
 t10 = zTimerReadms();
 printf("UINTFLOAT DIV: %.06f us per operation\r\n",
 (double)(t10-t9)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 //double
 double t11, t12;
 
 // Test adding bytes/////////////////////////////////////
 t11 = zTimerReadms();
 test_double_add();
 t12 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 printf("UINTDOUBLE ADD: %.06f us per operation\r\n",
 (double)(t12-t11)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test subtracting bytes////////////////////////////////
 t11 = zTimerReadms();
 test_double_sub();
 t12 = zTimerReadms();
 printf("UINTDOUBLE SUB: %.06f us per operation\r\n",
 (double)(t12-t11)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test multiplying bytes////////////////////////////////
 t11 = zTimerReadms();
 test_double_mult();
 t12 = zTimerReadms();
 printf("UINTDOUBLE MULT: %.06f us per operation\r\n",
 (double)(t12-t11)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Test dividing bytes//////////////////////////////////
 t11 = zTimerReadms();
 test_double_div();
 t12 = zTimerReadms();
 printf("UINTDOUBLE DIV: %.06f us per operation\r\n",
 (double)(t12-t11)/
 (double)NUM_ITERATIONS /(double)NUM_REPS*rep);
 
 // Add code to test other sizes and operators
 while (1); // When done, wait forever.
}
