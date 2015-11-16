#ifndef DRVREG_H

#define DRVREG_H
#define PINA  0x20  //Input Pins, Port A
#define DDRA  0x21 //Data Direction Register, Port A
#define PORTA 0x22 //Data Register, Port A

#define PINB  0x23  //Input Pins, Port B
#define DDRB  0x24 //Data Direction Register, Port B
#define PORTB 0x25 //Data Register, Port B


#define GIMSK 0x5B //General Interrupt Mask register
#define GIFR 0x5A //General Interrupt Flag Register
#define TIMSK0 0x6E //Timer/Counter Interrupt Mask register
#define TIFR0 0x35 //Timer/Counter Interrupt Flag register
#define MCUCR 0x55 //MCU general Control Register
#define TCCR0A 0x44 //Timer/Counter0 Control Register
#define TCCR0B 0x45 //Timer/Counter0 Control Register
#define OCR0A  0x47 // Output Compare Register A
#define TCNT0 0x46 //Timer/Counter0 (8-bit)

 
#endif
 
