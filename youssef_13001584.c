#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN 4
#define LED9_PIN   2
#define LED10_PIN  3

int main(void) {
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRD = (1 << LED9_PIN) | (1 << LED10_PIN);
    PORTD = (1 << BUTTON_PIN);

    uint8_t pattern = 0;
    uint8_t button_pressed = 0;

    while(1){
        if (!(PIND & (1 << BUTTON_PIN))) {
            if (!button_pressed) {
                button_pressed = 1;
                pattern ^= 1;

                if (pattern == 0) {
                    PORTB = 0x55;
                    PORTD = (PORTD & ~((1 << LED9_PIN) | (1 << LED10_PIN))) | (1 << BUTTON_PIN) | (1 << LED9_PIN);
                } else {
                    PORTB = 0xAA; 
                    PORTD = (PORTD & ~((1 << LED9_PIN) | (1 << LED10_PIN))) | (1 << BUTTON_PIN) | (1 << LED10_PIN);
                }
            }
        } else {
            button_pressed = 0;
        }
        
        _delay_ms(50); 
    }
}
