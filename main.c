#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd/lcd.h"

int read_val;

ISR(INT2_vect) {
	read_val = 0x0F & PINC;
	
		switch(read_val){
			case 0x00:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("Ready");
			lcd_gotoxy(0,1);
			lcd_puts("Select Speed");
			break;
			
			case 0x01:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("Off");
			OCR0=255;
			break;
			
			case 0x04:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("speed 1");
			OCR0=200;
			
			break;
			
			case 0x05:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("speed 2");
			OCR0=128;
			break;
			
			case 0x06:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("speed 3");
			OCR0=1;
			break;
			
			default:
			lcd_clrscr();             /* clear screen of lcd */
			lcd_home();               /* bring cursor to 0,0 */
			lcd_puts("Wrong Option");
			break;
		}
	
	
}

int main(void) {
	lcd_init(LCD_DISP_ON_CURSOR);
	DDRC = 0x00; // Make PORTC as input
	DDRD = 0xFF; // PORTD as output to lcd
	GICR = (1 << INT2); // Enable INT2
	MCUCSR = (1 << ISC2) ; // Trigger INT2 on rising edge
	sei(); // Enable Global Interrupt
	lcd_puts("Click on");
	DDRB = 0xFF; //controlling l293d motor driver
	TCCR0 = 0b01110101;
	TIMSK = 0x00;
	OCR0=254;
	

	while (1) {
		// Your main program logic here
	}

	return 0;
}
