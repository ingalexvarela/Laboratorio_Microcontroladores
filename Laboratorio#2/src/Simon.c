/*
Código que utiliza interrupciones para detectar cuando se presiona un botón 
conectado al pin y encender un LED conectado a otro pin. 
La variable "button_press" se utiliza como una bandera para indicar si 
se ha presionado el botón y se establece en 1 dentro de la función ISR (interrupción) 
y se vuelve a establecer en 0 en el bucle principal del programa. 
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t button1_press = 0;
volatile uint8_t button2_press = 0;
volatile uint8_t button3_press = 0;
volatile uint8_t button4_press = 0;

ISR(INT0_vect) {
  button1_press = 1; // Establecer la bandera de presión del botón D2
}

ISR(INT1_vect) {
  button2_press = 1; // Establecer la bandera de presión del botón D3
}

ISR(PCINT2_vect) {
  button3_press = 1; // Establecer la bandera de presión del botón D4
}

ISR(PCINT1_vect) {
  button4_press = 1; // Establecer la bandera de presión del botón A0
}

int main(void) {
  DDRB = 0xff; // Configurar pines B como salida (para los LED)
  DDRD &= ~(1 << 2) & ~(1 << 3) & ~(1 << 4) & ~(1 << 5); // Configurar pines D2, D3, D4 y D5 como entrada (para los botones)
  DDRA &= ~(1 << 0); // Configurar pin PA0 como entrada (para el botón)

  // Configurar pull-up externo en los pines D2, D3, D4 y D5 (conectar una resistencia entre VCC y los pines)
  PORTD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5); // activar las resistencias pull-up
  PORTA |= (1 << 0); // activar la resistencia pull-up
  
  GIMSK |= (1 << PCIE1); // Habilitar interrupciones en el pin PA0
  GIMSK |= (1 << INT0) | (1 << INT1) | (1 << PCIE2) | (1 << PCIE1); // Habilitar interrupciones externas en los pines D2, D3, D4 y D5
  MCUCR |= (1 << ISC01) | (1 << ISC11) | (1 << ISC10) | (1 << ISC00); // Configurar interrupciones para flanco de bajada
  PCMSK2 |= (1 << PCINT4); // Habilitar interrupción en el pin D4
  PCMSK1 |= (1 << PCINT8); // Habilitar interrupción en el pin PA0
    
sei(); // Habilitar interrupciones globales

  while(1){
    if(button1_press){
      PORTB |= (1 << 7); // Encender LED en B7
      _delay_ms(5000); // Esperar 500ms
      PORTB &= ~(1 << 7); // Apagar el LED
      button1_press = 0; // Resetear la bandera de presión del botón D2
    }
    if(button2_press){
      PORTB |= (1 << 6); // Encender LED en B6
      _delay_ms(5000); // Esperar 500ms
      PORTB &= ~(1 << 6); // Apagar el LED
      button2_press = 0; // Resetear la bandera de presión del botón D3
	  }
	  if(button3_press){
	  PORTB |= (1 << 1); // Encender LED en B1
    _delay_ms(5000); // Esperar 500ms
    PORTB &= ~(1 << 1); // Apagar el LED
    button3_press = 0; // Resetear la bandera de presión del botón D4
    }
    if(button4_press){
    PORTB |= (1 << 0); // Encender LED en B0
    _delay_ms(5000); // Esperar 500ms
    PORTB &= ~(1 << 0); // Apagar el LED
    button4_press = 0; // Resetear la bandera de presión del botón D5
    }	
  }
return 0;
}