#include <avr/io.h>
#include <avr/interrupt.h>

volatile int button_state[2] = {0};

ISR(INT0_vect) {
  button_state[0] = !(PIND & (1 << 2));
}

ISR(INT1_vect) {
  button_state[1] = !(PIND & (1 << 3));
}

int main(void) {
  DDRB = (1 << 0) | (1 << 1); // Configurar pin B0 y B1 como salida (leds)
  DDRD &= ~((1 << 2) | (1 << 3)); // Configurar pin D2 y D3 como entrada (botones)
  PORTD |= (1 << 2) | (1 << 3); // Habilitar resistencia pull-up en pin D2 y D3
  
  MCUCR |= (1 << ISC00) | (1 << ISC10); // Configurar interrupción INT0 y INT1 para activarse en flanco de bajada
  GIMSK |= (1 << INT0) | (1 << INT1); // Habilitar interrupción INT0 y INT1
  
  sei(); // Habilitar interrupciones globales
  
  while(1){
    if(button_state[0]) PORTB |= (1 << 0); // Encender el led 1
    else PORTB &= ~(1 << 0); // Apagar el led 1
    if(button_state[1]) PORTB |= (1 << 1); // Encender el led 2
    else PORTB &= ~(1 << 1); // Apagar el led 2
  }
}

