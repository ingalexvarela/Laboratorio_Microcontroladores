#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h> // para usar la función rand()


// Volatile variables to indicate button presses
volatile uint8_t button1_press = 0;
volatile uint8_t button2_press = 0;
volatile uint8_t button3_press = 0;
volatile uint8_t button4_press = 0;

// Game variables
volatile uint8_t game_started = 0; // nueva variable para indicar si el juego ha comenzado
volatile uint8_t game_over = 0;    // nueva variable para indicar si el juego ha terminado
volatile uint8_t user_sequence[4]; // nueva variable para almacenar la secuencia ingresada por el usuario
volatile uint8_t user_errors = 0;  // nueva variable para contar los errores del usuario

// Declarar variables para el LFSR
#define LFSR_TAP 0xCE  // Polinomio del LFSR
#define LFSR_SEED 0x01 // Semilla del LFSR
uint8_t lfsr = LFSR_SEED;
uint8_t lfsr_next();
uint8_t lsb;

// Declarar variables para la secuencia de LEDS
uint8_t game_sequence[4];     // Sequence to be played
uint8_t game_input_index = 0; // Current index of the user input

// void check_user_input(uint8_t button);
//void generate_sequence();
uint8_t game_initiated = 0; // Variable auxiliar para registrar si el juego ha sido iniciado
uint8_t game_initial = 0; // Variable auxiliar para registrar para corregir un error


// Function to generate the next number in the LFSR
uint8_t lfsr_next()
{
    uint8_t lsb = lfsr & 1;
    lfsr = (lfsr >> 1) | (lsb << 7);
    if (lsb)
    {
        lfsr ^= LFSR_TAP;
    }
    return lfsr;
}

// Function to generate the game sequence
void generate_sequence()
{
    for (int i = 0; i < 4; i++)
    {
        game_sequence[i] = lfsr_next() % 4;
    }
}

// Function to play the game sequence
void play_sequence()
{
    for (int i = 0; i < 4; i++)
    {
        switch (game_sequence[i])
        {
        case 0:
            PORTB |= (1 << 7); // Turn on B7
            _delay_ms(2000);
            PORTB &= ~(1 << 7); // Turn off B7
            break;
        case 1:
            PORTB |= (1 << 6); // Turn on B6
            _delay_ms(2000);
            PORTB &= ~(1 << 6); // Turn off B6
            break;
        case 2:
            PORTB |= (1 << 1); // Turn on B1
            _delay_ms(2000);
            PORTB &= ~(1 << 1); // Turn off B1
            break;
        case 3:
            PORTB |= (1 << 0); // Turn on B0
            _delay_ms(2000);
            PORTB &= ~(1 << 0); // Turn off B0
            break;
        }
        _delay_ms(2000);
    }
}

void check_user_input(uint8_t button)
{   
    if (game_sequence[game_input_index] == button)
    {
	     game_input_index++;
          if (game_input_index == 4)
          {
          // Completo con exito
		game_started = 1; 
		game_initiated = 0;  
		// Ir a Segundo estado
           }
    }
    else
    {   
        //perdio 
        game_over = 1;
	   // Ir a Tercer estado

    }
}


// Interrupciones externas de los botones
ISR(INT0_vect)
{
    button1_press = 1; // Establecer la bandera de presión del botón D2 maneja B7
    PORTB |= (1 << 7);
    check_user_input(0);
    _delay_ms(2000);
    PORTB &= ~(1 << 7); //_delay_ms(1000);
    //if (game_started == 1){
    //check_user_input(0); //button1_press);
    //}	
}

ISR(INT1_vect)
{
    button2_press = 1; // Establecer la bandera de presión del botón D3 maneja B6
    PORTB |= (1 << 6);
    check_user_input(1);
    _delay_ms(2000);
    PORTB &= ~(1 << 6); //_delay_ms(1000);

    //if (game_started == 1){
    //check_user_input(1);//button2_press);
    //}	
}

ISR(PCINT2_vect)
{
    button3_press = 1; // Establecer la bandera de presión del botón D4  maneja B1
    PORTB |= (1 << 1);
    check_user_input(2);
    _delay_ms(2000);
    PORTB &= ~(1 << 1); //_delay_ms(1000);
    //if (game_started == 1){
    //check_user_input(2);//button3_press);
    //}	
}

ISR(PCINT1_vect)
{
    button4_press = 1; // Establecer la bandera de presión del botón A0 maneja BO
    PORTB |= (1 << 0);
    check_user_input(3);
    _delay_ms(2000);
    PORTB &= ~(1 << 0); //_delay_ms(1000);
    //if (game_started == 1){
    //check_user_input(3);//button4_press);
    //}	
}


int main()
{
    DDRB = 0xff;                                                        // Configurar pines B como salida (para los LED)
    DDRD &= ~(1 << 2) & ~(1 << 3) & ~(1 << 4) & ~(1 << 5);              // Configurar pines D2, D3, D4 y D5 como entrada (para los botones)
    DDRA &= ~(1 << 0);                                                  // Configurar pin PA0 como entrada (para el botón)
    PORTD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);                 // activar las resistencias pull-up
    PORTA |= (1 << 0);                                                  // activar la resistencia pull-up
    GIMSK |= (1 << PCIE1);                                              // Habilitar interrupciones en el pin PA0
    GIMSK |= (1 << INT0) | (1 << INT1) | (1 << PCIE2) | (1 << PCIE1);   // Habilitar interrupciones externas en los pines D2, D3, D4 y D5
    MCUCR |= (1 << ISC01) | (1 << ISC11) | (1 << ISC10) | (1 << ISC00); // Configurar interrupciones para flanco de bajada
    PCMSK2 |= (1 << PCINT4);                                            // Habilitar interrupción en el pin D4
    PCMSK1 |= (1 << PCINT8);                                            // Habilitar interrupción en el pin PA0
    sei();

    // Main loop
    while (1)
    {
        // Primer estado (Inicio)
        if (game_started == 0)
        {   if (game_initial == 0)
            {
            	if (button1_press || button2_press || button3_press || button4_press)
            	{
                	for (int i = 0; i < 2; i++)
	                { // parpadear los LEDS 2 veces
	                    PORTB = 0xc3;
	                    _delay_ms(5000); // esperar 500ms
	                    PORTB = 0x00;    // apagar todos los LEDS
	                    _delay_ms(5000); // esperar 500ms
	                }
                	button1_press = 0; // resetear la bandera de presión del botón D2
	                button2_press = 0; // resetear la bandera de presión del botón D3
	                button3_press = 0; // resetear la bandera de presión del botón D4
	                button4_press = 0; // resetear la bandera de presión del botón A0
	                game_started = 1;  // resetear la bandera de fin del juego
				game_initiated = 0;
            	}
		 }
        }

        // Segundo estado (arranque de funciones)
        if (game_started == 1 && game_initiated == 0)
        {   //game_input_index = 0;
            generate_sequence();
            play_sequence();
            game_initiated = 1; 
		  game_initial = 1;
		  game_started = 1;
        }
        // tercer estado (Fin del juego)
        if (game_over == 1)
        { // si el usuario se equivocó
            for (int i = 0; i < 3; i++)
            { // parpadear los LEDS 3 veces
                PORTB = 0xC3;
                _delay_ms(5000); // esperar 500ms
                PORTB = 0x00;    // apagar todos los LEDS
                _delay_ms(5000); // esperar 500ms
            }
            game_over = 0;    // resetear la bandera de fin del juego	
            game_started = 0; // resetear la bandera de inicio del juego
		  game_initial = 0;
		  button1_press = 0; // resetear la bandera de presión del botón D2
            button2_press = 0; // resetear la bandera de presión del botón D3
            button3_press = 0; // resetear la bandera de presión del botón D4
            button4_press = 0; // resetear la bandera de presión del botón A0
        }
    }
    return 0;
}