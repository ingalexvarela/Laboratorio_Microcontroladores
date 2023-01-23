/*
Código que utiliza interrupciones para detectar cuando se presiona un botón 
conectado al pin D2 y encender un LED conectado al pin B0. 
La variable "button_press" se utiliza como una bandera para indicar si 
se ha presionado el botón y se establece en 1 dentro de la función ISR (interrupción) 
y se vuelve a establecer en 0 en el bucle principal del programa. 
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t button_press = 0;

ISR(PCINT2_vect) {
  button_press = 1; // Establecer la bandera de presión del botón
}

int main(void) {
  DDRB = (1 << 0); // Configurar pin B0 como salida (para el LED)
  DDRD &= ~(1 << 2); // Configurar pin D2 como entrada (para el botón)
  
  // Configurar pull-up externo en el pin D2 (conectar una resistencia entre VCC y el pin D2)
  
  PORTD |= (1 << 2); // activar la resistencia pull-up
  PCMSK2 |= (1 << PCINT2); // Habilitar interrupción en el pin D2
  GIMSK |= (1 << PCIE2); // Habilitar interrupciones en el pin D2
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