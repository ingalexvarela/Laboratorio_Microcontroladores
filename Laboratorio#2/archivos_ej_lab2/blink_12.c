#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t button_press = 0;

ISR(PCINT1_vect) {
  button_press = 1; // Establecer la bandera de presión del botón
}

int main(void) {
  DDRB = (1 << 0); // Configurar pin B0 como salida (para el LED)
  DDRA &= ~(1 << 0); // Configurar pin PA0 como entrada (para el botón)
  
  // Configurar pull-up externo en el pin PA0 (conectar una resistencia entre VCC y el pin PA0)
  
  PORTA |= (1 << 0); // activar la resistencia pull-up
  PCMSK1 |= (1 << PCINT8); // Habilitar interrupción en el pin PA0
  GIMSK |= (1 << PCIE1); // Habilitar interrupciones en el pin PA0
  sei(); // Habilitar interrupciones globales
  
  while(1){
    if(button_press){
      PORTB |= (1 << 0); // Encender LED en B0
      _delay_ms(500); // Esperar 500ms
      PORTB &= ~(1 << 0); // Apagar LED en B0
      button_press = 0; // Limpiar la bandera de presión del botón
    }
  }
}