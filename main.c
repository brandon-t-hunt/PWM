/*
 * Lab 3
 *
 * 	(c) Brandon Hunt
 */

#include <msp430.h>

int dir = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Initialize PWM
  P2DIR |= BIT0 + BIT4 + BIT5;                       // P2.0 and P2.1 output
  P2SEL |= BIT0 + BIT4 + BIT5;                       // P2.0 and P2.1 options select
  TA1CCR0 = 20000;                          // PWM Period = 20 ms
  TA1CCTL1 = OUTMOD_6;                      // CCR1 reset/set
  TA1CCR1 = 1500;                            // CCR1 PWM duty cycle (init to halt)
  TA2CCTL2 = OUTMOD_6;                      // CCR2 reset/set
  TA2CCR0 = 20000;
  TA2CCR2 = 1500;                            // CCR2 PWM duty cycle	(init to halt)

  TA2CCTL1 = OUTMOD_6;                      // CCR2 reset/set

//  TA2CCR0 = 20000;
  TA2CCR1 = 1500;                            // CCR2 PWM duty cycle	(init to halt)


  TA1CTL = TASSEL_2 + MC_1 + TACLR + ID_0;   // SMCLK, up mode, clear TAR, div by 1
  TA2CTL = TASSEL_2 + MC_1 + TACLR + ID_0;   // SMCLK, up mode, clear TAR, div by 1


  P4DIR |= BIT7;
  P4OUT |= BIT7;


  // Initialize Timer B for PWM control
  TBCTL = TBSSEL_1 | MC_1 | TBCLR;			// AuxClk, Upmode, clear count
  TB0CCTL0 = CCIE;
  TB0CCR0 = 0x05FF;




  __bis_SR_register(GIE);             // Enable Interrupts
//  __no_operation();                   // For debugger


  	  P3DIR |= 0x03;	// P1.0-P1.1 as outties
      P1DIR &= ~0x3C;	// set P1.2-P1.5 as innies
      P1REN |= 0x3C;	// enable pulling rezzies
      P1OUT |= 0x3C;	// pully rezzies set to high

      int col = 0;	// declare row index
      int j, temp, numFlag;
      int buttons[4][4] = {
      		{1,2,3,10},
      		{4,5,6,11},
      		{7,8,9,12},
      		{13,0,15,14}};

      int ccr[16] = {1000,1100,1200,1300,1400,1450,1475,1500,1525,1550,1600,1700,1800,1900,2000,2000};


      int row, poll;

      while(1){

      	// iterate through 00,01,10,11
      	col++;
      	if(col==0x04)(col=0);
      	P3OUT &= ~0x03;
      	P3OUT |= col;
      	row = 0x04;


      	for(j=0; j<4; j++){         // iterate through columns
      		poll = P1IN;
      		if(~poll & row){    // poll button

      			temp = buttons[j][col];
      			numFlag = 1;
      			TA1CCR1 = ccr[temp];
      			TA2CCR1 = ccr[temp];

      			TA2CCR2 = ccr[14-temp];
      			break;
      		}

      		row <<= 0x01;
      	}
      }
}

#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR (void){

}


