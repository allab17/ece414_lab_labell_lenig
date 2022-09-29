/* Clock configuration */
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF

#include <xc.h>
#include <inttypes.h>
#include "porta_in.h"
#include "portb_out.h"
#include "timer1.h"

  uint16_t PERIOD_PONG;
  
  uint8_t btndown_player1 = 0;
  uint8_t btndown_player2 = 0;
  uint16_t out = 0x01;
  uint8_t flash_count;
  uint8_t server_hold = 0;

static enum PONG_States {PONG_idle, PONG_right_travel, PONG_left_travel, PONG_lose_player1, PONG_lose_player2} PONG_state;
static enum DEBP1_States {DEBP1_NOPUSH, DEBP1_MAYBENOPUSH, DEBP1_MAYBEPUSH, DEBP1_PUSHED} DEBP1_state;
static enum DEBP2_States {DEBP2_NOPUSH, DEBP2_MAYBENOPUSH, DEBP2_MAYBEPUSH, DEBP2_PUSHED} DEBP2_state;




void tickFct_DEBP1() {
    switch(DEBP1_state) {
        case DEBP1_NOPUSH:
            if (porta_in_read() == 0x02) {
                DEBP1_state = DEBP1_MAYBEPUSH;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        case DEBP1_MAYBEPUSH:
            if (porta_in_read() == 0x02) {
                btndown_player1 = 1;
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        case DEBP1_PUSHED:
            if (porta_in_read() == 0x02) {
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_MAYBENOPUSH;
            }
            break;
        case DEBP1_MAYBENOPUSH:
            if (porta_in_read() == 0x02) {
                DEBP1_state = DEBP1_PUSHED;
            } else {
                DEBP1_state = DEBP1_NOPUSH;
            }
            break;
        default:
            DEBP1_state = DEBP1_NOPUSH;
            break;
    }
}

void tickFct_DEBP2() {
    switch(DEBP2_state) {
        case DEBP2_NOPUSH:
            if (porta_in_read() == 0x01) {
                DEBP2_state = DEBP2_MAYBEPUSH;
            } else {
                DEBP2_state = DEBP2_NOPUSH;
            }
            break;
        case DEBP2_MAYBEPUSH:
            if (porta_in_read() == 0x01) {
                btndown_player2 = 1;
                DEBP2_state = DEBP2_PUSHED;
            } else {
                DEBP2_state = DEBP2_NOPUSH;
            }
            break;
        case DEBP2_PUSHED:
            if (porta_in_read() == 0x01) {
                DEBP2_state = DEBP2_PUSHED;
            } else {
                DEBP2_state = DEBP2_MAYBENOPUSH;
            }
            break;
        case DEBP2_MAYBENOPUSH:
            if (porta_in_read() == 0x01) {
                DEBP2_state = DEBP2_PUSHED;
            } else {
                DEBP2_state = DEBP2_NOPUSH;
            }
            break;
        default:
            DEBP2_state = DEBP2_NOPUSH;
            break;
    }
}



void tickFct_PONG() {
        switch(PONG_state) {
         case PONG_idle:
             PERIOD_PONG = 300;
             flash_count = 1; //sets the count back to zero after leds flash in lose state
             //to initiate the game the serving player is randomly chosen
             //thus 0x01 or 0x80 will be randomly chosen
             uint16_t serving_side;
             if (flip()) {
                 serving_side = 0x01; //if the coin is heads (1) than the serving side will be left side, player 1 serving
             } else {
                 serving_side = 0x80;
             }
             if (!server_hold) {
              out = serving_side;
              portb_out_write(out);
              server_hold = 1;
             }    
             if (serving_side == 0x01 && btndown_player1) { //initiate the game from the left *0000000
                PONG_state = PONG_right_travel;
                btndown_player1 = 0; //set player1 button flag to un-pressed
             } else if (btndown_player2) { //initiate the game from the right 0000000*
                btndown_player2 = 0; //set player2 button flag to un-pressed
                PONG_state = PONG_left_travel;
             }
             break;
         case PONG_right_travel:
             if (out == 0x80) { //0000000* 
                 if (btndown_player2) {
                 btndown_player2 = 0;
                 PONG_state = PONG_left_travel;
                    if (PERIOD_PONG > 100) {
                        PERIOD_PONG -= 20;
                    } 
                 portb_out_write(out);  //led 0000000*
                 } else {
                     portb_out_write(0x0000);
                     PONG_state = PONG_lose_player2;
                 }
             } else if (out != 0x80 && btndown_player1) {
                 btndown_player1 = 0;           //player 1 has pushed the button illegally while the ball is in motion and thus player 2 loses and we set their button flag back to un-pressed
                 portb_out_write(0x0000);  //set all LEDs to off
                 PONG_state = PONG_lose_player1;
             } else if (out != 0x80 && btndown_player2) {
                 btndown_player2 = 0;      //player 2 has pushed the button illegally while the ball is in motion and thus player 2 loses and we set their button flag back to un-pressed
                 portb_out_write(0x0000);  //set all LEDs to off
                 PONG_state = PONG_lose_player2;
             } else { //000*0000  the ball is moving to the right
                 out = out << 1;
                 portb_out_write(out);
                 PONG_state = PONG_right_travel;
             }
            break;
            case PONG_left_travel:
             if (out == 0x01) { //*0000000  the led has reached the left most side and the player has reacted appropriately thus we now move to the right
                 if (btndown_player1) {
                    btndown_player1 = 0;
                    PONG_state = PONG_right_travel;
                    if (PERIOD_PONG > 100) {
                        PERIOD_PONG -= 20;
                    }
                    portb_out_write(out);
                 } else {
                     portb_out_write(0x0000);
                     PONG_state = PONG_lose_player1;
                 }
             } else if (out != 0x01 && btndown_player1) {
                 btndown_player1 = 0;           //player 1 has pushed the buStton illegally while the ball is in motion and thus player 2 loses and we set their button flag back to un-pressed
                 portb_out_write(0x0000);   //set all LEDs to off
                 PONG_state = PONG_lose_player1;
             } else if (out != 0x01 && btndown_player2) {
                 btndown_player2 = 0;      //player 2 has pushed the button illegally while the ball is in motion and thus player 2 loses and we set their button flag back to un-pressed
                 portb_out_write(0x0000);  //set all LEDs to off
                 PONG_state = PONG_lose_player2;
             } else {
                 out = out >> 1;
                 portb_out_write(out);
                 PONG_state = PONG_left_travel;    //0000*000 ball is moving to the left  
             }
            break;
            case PONG_lose_player1:
                //if player1 loses than the led nearest to player2, thus 0x80 will flash 3 times
                //set a timer flag that after 3 counts will reenter the idle state and set itself back to zero
                if (flash_count > 6) { //we start flash_count at 1, 1 - no flash, 2 - flash, 3 - no flash, 4 - flash
                    PONG_state = PONG_idle;
                    server_hold = 0;
                } else if ((flash_count % 2) == 0) { //if there is no remainder when we divide by 2 the number is even
                    flash_count++;
                    portb_out_write(0x80);  //flash the winning player's LED
                    PONG_state = PONG_lose_player1;
                } else {
                    flash_count++;
                    portb_out_write(0x00); //turn all off
                    PONG_state = PONG_lose_player1;
                }
                break;
            case PONG_lose_player2:
                //if player 2 loses than the led nearest to player 1, thus 0x01 will flash 3 times
                //set a timer flag that after 3 counts will reenter the idle state and set itself back to zero
                if (flash_count > 6) { //we start flash_count at 1, 1 - no flash, 2 - flash, 3 - no flash, 4 - flash ...
                    PONG_state = PONG_idle;
                    server_hold = 0;
                } else if ((flash_count % 2) == 0) { //if there is no remainder when we divide by 2 the number is even
                    flash_count++;
                    portb_out_write(0x01);  //flash the winning player's LED
                    PONG_state = PONG_lose_player2;
                } else {
                    flash_count++;
                    portb_out_write(0x00); //turn all off
                    PONG_state = PONG_lose_player2;
                }
                break;
            default:
                PONG_state = PONG_idle;
                server_hold = 0;
                break;
         }
            
     }

int flip() { //coin flip function, generates 1 or 0
    int r_int = rand();
    int h_t = r_int % 2;
    if (h_t == 0) return 1 ;
    else return 0;
}

unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515243 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

 

main() { 
  const uint16_t PERIOD_DEB = 50;
  uint16_t ta1, ta2, tb1, tb2;
  timer1_init();
  porta_in_init();
  portb_out_init();
  PONG_state = PONG_idle;
  out = 0x01;
  ta1 = tb1 = timer1_read();
  while (1) {
     ta2 = tb2 = timer1_read();
     if (timer1_ms_elapsed(ta1, ta2) >= PERIOD_PONG) {
         ta1 = ta2;
         tickFct_PONG();
     }
     if (timer1_ms_elapsed(tb1, tb2) >= PERIOD_DEB) {
         tb1 = tb2;
         tickFct_DEBP1();
         tickFct_DEBP2();
     }
  }
}
