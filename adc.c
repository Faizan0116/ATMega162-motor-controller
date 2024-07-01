#include <avr/io.h>
#include <avr/interrupt.h>

void init_adc0804() {
    // Configure control pins as output
    DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4);
    // Configure INTR pin as input
    DDRB &= ~(1 << PB1);
    // Configure PORTC as input
    DDRC = 0x00;

    // Initialize control pins
    PORTB |= (1 << PB4); // CS high (inactive)
    PORTB |= (1 << PB2); // RD high (inactive)
    PORTB |= (1 << PB3); // WR high (inactive)
}

void start_conversion() {
    PORTB &= ~(1 << PB4); // CS low (active)
    PORTB &= ~(1 << PB3); // WR low (start conversion)
    PORTB |= (1 << PB3);  // WR high
    PORTB |= (1 << PB4);  // CS high (inactive)
}

uint8_t read_adc() {
    PORTB &= ~(1 << PB4); // CS low (active)
    PORTB &= ~(1 << PB2); // RD low (enable read)
    uint8_t value = PINC; // Read value from PORTC
    PORTB |= (1 << PB2);  // RD high
    PORTB |= (1 << PB4);  // CS high (inactive)
    return value;
}

void init_timer0() {
    // Configure Timer0 in Fast PWM mode
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
    // Set initial value of OCR0
    OCR0 = 0x00;
}

int main(void) {
    // Initialize ADC0804
    init_adc0804();
    // Initialize Timer0
    init_timer0();
    
    while (1) {
        // Start ADC conversion
        start_conversion();
        // Wait for conversion to complete
        while (PINB & (1 << PB1));
        // Read ADC value
        uint8_t adc_value = read_adc();
        // Set OCR0 value
        OCR0 = adc_value;
    }
}
