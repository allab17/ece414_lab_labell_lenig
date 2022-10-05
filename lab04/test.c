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


void main()
{
    uart1_init(9600);
    //T1:
    uart1_txwrite('c');
    printf("%c", uart1_rxread());
    //T2:
    uart1_txwrite_str("teststring");
    printf("%c", uart1_rxread());
    
    uart1_txwrite_str("Hello alexandertrevor");
    printf("%s", uart1_rxread());
    
    uart1_txwrite_str("100characterstringasdjfhasdlfhaljdsfhsdfkasdhfkjashdfjhaksdhfkhakfdhjashjfdkjdashfjahfdkjahfkjadshk");
    printf("%s", uart1_rxread());
    
    uart1_txwrite_str("ashorterstring");
    printf("%s", uart1_rxread());
    
    char c;
    printf("Enter character: ");
    c = getchar();
    while (1) {
       printf("Enter character: ");
       c = getchar();
       if (isupper(c)) toupper(c);
       else toupper(c);
        
        uart1_txwrite(c);
        printf("%c", uart1_rxread(c));
    }

    
    
    
     
     
     
     
    
    
    
// uint32_t t1, t2;
// // !!! Add code: Initialize uart1 & ztimer modules
// // and turn on interrupts
// printf("Performance Summary: Time per operation statistics\r\n");
// // Test multiplying bytes
// t1 = zTimerReadms();
// test_uint8_mult();
// t2 = zTimerReadms();
// // Print timing result. Doubles OK here. Not time critical code.
// printf("UINT8 MULT: %.06f us per operation\r\n",
// (double)(t2-t1)/
// (double)NUM_ITERATIONS /(double)NUM_REPS*1000.0);
// // Add code to test other sizes and operators
// // ...
// while (1); // When done, wait forever.
}
