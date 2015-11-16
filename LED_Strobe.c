/*
This code will Glow the LED 7 using the PWM method
U.C. Irvine Extension
X497.32
Instructor: Saleem Yamani
*/	
 
#include "drvreg.h"

#define LED_DELAY 200
#define TC0_CK_1024 5
#define TOIE0 1
#define TOV0  1

#define CS00  1
#define CS01  2
#define CS02  4
#define WGM02 8

#define WGM00   1
#define WGM01   2
#define COM0A00  1 << 6
#define COM0A01  1 << 7

#define MAX_GLOW 255 // 255 = 100% 

// wrapper for writing register 
void WriteReg(unsigned int addr, unsigned char val)
{
	*((volatile unsigned char *)addr) = val;

}

// wrapper for Reading register 
unsigned char ReadReg(unsigned int addr)
{
	unsigned char val;
	
	do
	{
	  val = *((volatile unsigned char *)addr);
	}while( (val != *((volatile unsigned char *)addr)) );  

	return (val);  
}

void Wait(void)
{
    
	 
 	/* Poll the TIFR for an overflow in TOV0. That means the counter 
	has expired. Or get interrupted */
	while ( !(*((volatile unsigned char *)TIFR0) & TOV0));

	// Clear Overflow bit
	WriteReg(TIFR0, TOV0);
 


}
  

void InitPWM(void)
{
   /*
   TCCR0B - Timer Counter Control Register (TIMER0)
   -----------------------------------------------
   BITS DESCRIPTION
   

   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : FOC0A   Force Output Compare [Not used in this example]
   BIT 6 : FOC0B  only active for non-PWM mode 			[Not used in this example]
   BIT 5 : - 
   BIT 4 : -
   BIT 3 : WGM02  Fast PWMD                          	[SET to 0]
   BIT 2 : CS02   Clock Select               			[SET to 1]
   BIT 1 : CS01   Clock Select               			[SET to 0]
   BIT 0 : CS00   Clock Select               			[SET to 1]

Wave form generation Mode bit Operation
Mode 3: Fast PWM, TOP: 0xFF, Update of OCRx at TOP, TOV Flag Set on MAX
2 1 0 WGM0 bits
0 1 1

   The above settings are for
   --------------------------

   Timer Clock = CPU Clock (1024 Prescalling)
   Mode        = Fast PWM
   PWM Output  = Non Inverted

   */

/*
   TCCR0A - Timer Counter Control Register (TIMER0)
   -----------------------------------------------
   BITS DESCRIPTION
   BIT 7 : COM0A1  Compare Output Mode [SET to 1]
   BIT 6 : COM0A0  Compare Output Mode [SET to 1]
   BIT 5 : COM0B1                      [Not used in this example]
   BIT 4 : COM0B0                      [Not used in this example]
   BIT 3 : -
   BIT 2 : -
   BIT 1 : WGM01   Fast PWM Mode       [SET to 1]
   BIT 0 : WGM00   Fast PWM Mode       [SET to 1]
*/
  
WriteReg(TCCR0B, TC0_CK_1024); // Using 1024 prescalar
    

WriteReg(TCCR0A, COM0A01| WGM01 | WGM00);

   //Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
//WriteReg(PORTB,0x00);
WriteReg(DDRB,0x80);
    
}

 

/******************************************************************
Sets the duty cycle of output. 

Arguments
---------
duty: Between 0 - 255

0= 0%

255= 100%

The Function sets the duty cycle of pwm output generated on OC0 PIN
The average voltage on this output pin will be

         duty
 Vout=  ------ x 5v
         255 

This can be used to control the brightness of LED or Speed of Motor.
*********************************************************************/

void SetPWMOutput(unsigned char duty)
{
   WriteReg(OCR0A,duty);
   //OCR0=duty;
}

 


 
int main(void)
{
   unsigned char brightness=0;
  
   //Initialize PWM Channel 0
   InitPWM();    
  
   //Do this forever

   while(1)
   {
 
      //Now Loop with increasing brightness

      for(brightness=0;brightness<MAX_GLOW;brightness++)
      {
         //Now Set The Brighness using PWM

         SetPWMOutput(brightness);

         //Now Wait For Some Time
         Wait();
		  
      }
  
      //Now Loop with decreasing brightness

      for(brightness=MAX_GLOW;brightness>0;brightness--)
      {
         //Now Set The Brighness using PWM

         SetPWMOutput(brightness);

         //Now Wait For Some Time
         Wait();
		 
      }
   }
}

