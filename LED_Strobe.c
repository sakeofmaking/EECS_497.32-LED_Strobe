/* Title: Programming Assignment 4
 * 
 * Author: Nicholas LaJeunesse
 *
 */

#include "drvreg.h"

#define MAX_GLOW 255

// Write value to register
void WriteReg(int RegAddr, int value){
	*((volatile unsigned char *)RegAddr) = value;
}

// Read value from register
unsigned char ReadReg(int RegAddr){
	return(*((volatile unsigned char *)RegAddr));
}

// Delay using TCNT0
void Wait(unsigned int count){
	WriteReg(TCNT0, 255 - count);
	while((ReadReg(TIFR0) & 0x01) != 0x01){};
	WriteReg(TIFR0, (1<<TOV0));
}

// Initialize PWM Channel 0
void InitPWM(){
	// Initialize Timer0 in PWM mode
	WriteReg(TCCR0A, (1<<COM0A1)|(1<<COM0B1)|(1<<WGM01)|(1<<WGM00));
	WriteReg(TCCR0B, (1<<CS02)|(1<<CS00));

	// Set OC0A pin as output by setting bit 7 in DDRB
	WriteReg(DDRB, (1<<7));
}

// Set the duty cycle of PWM Output
void SetPWMOutput(unsigned char duty_cycle){
	WriteReg(OCR0A, duty_cycle);
}

int main(void)
{
   unsigned char brightness = 0;
  
   //Initialize PWM Channel 0
   InitPWM();
  
   //Do this forever
   while(1)
   {
      // Loop through with increasing brightness
      for(brightness = 0; brightness < MAX_GLOW; brightness++)
      {
         // Set the brightness using by setting duty cycle of PWM Output
         SetPWMOutput(brightness);

         //Now Wait For Some Time
         Wait(255);         
      }
  
      // Loop through with decreasing brightness
      for(brightness = MAX_GLOW; brightness > 0; brightness--)
      {
         // Set The Brighness using PWM
         SetPWMOutput(brightness);

         // Wait For some time
         Wait(255);
      }
   }
}

