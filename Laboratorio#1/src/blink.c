#include <pic14/pic12f675.h>

/* Inicialización de perifericos y MCU
Configuración ** deshabilitar reset y watchdog timer con macros */ 
typedef unsigned int word;
word __at 0x2007 __CONFIG =  (_MCLRE_OFF & _WDTE_OFF & _BODEN_OFF); 

void delay(unsigned inttiempo); // Acá se define la función del tiempo de espera

void main(void) 				// Función principal para la ejecución de acciones
{
	// ** Establecimiento de las condiciones en registros
	TRISIO = 0b00000000; 		// Poner todos los pines como salidas 
	GPIO = 0b00100000;   		// Poner pines en bajo; terminales en 0
	ANSEL = 0;			 		// Canales analogicos como E/S digitales
	CMCON = 0x07;			    // Apagar comparadores
	unsigned int time1 = 150;   // Tiempo de espera antes de apagar la configuración de los leds

	// Loop forever
	while (1)
	{	
		unsigned int counter = 1;	// se define contador
		while (1)
		{
			if (GP5 == 0x01){     // Hacemos el contador para que sostenga un  número 
				counter ++;
				if (counter == 7){  //número aleatorio enfrascado entre 1 y 6
					counter = 0;
					counter ++;
				}	
			} else { if (GP5 == 0x00){ // Al presionar bottón se configura la salida de los leds
				if (counter == 1){      // Para mostrar el uno en la configuración de leds
					GP1 = ~GP1;
					delay(time1);		// Llamada a condición de espera
					GPIO = 0x20;
					
				} if (counter == 2){    // Para mostrar el dos en la configuración de leds
					GP2 = ~GP2;
					delay(time1);
					GPIO = 0x20;
					
				} if (counter == 3){    // Para mostrar el tres en la configuración de leds
					GP2 = ~GP2;
					GP1 = ~GP1;
					delay(time1);
					GPIO = 0x20;
					
				} if (counter == 4){    // Para mostrar el cuatro en la configuración de leds
					GP0 = ~GP0;
					GP2 = ~GP2;
					delay(time1);
					GPIO = 0x20;
					
				} if (counter == 5){   // Para mostrar el cinco en la configuración de leds
					GP0 = ~GP0;
					GP1 = ~GP1;
					GP2 = ~GP2;
					delay(time1);
					GPIO = 0x20;
					
				} if (counter == 6){    // Para mostrar el seis en la configuración de leds
					GP0 = ~GP0;
					GP2 = ~GP2;
					GP4 = ~GP4;
					delay(time1);
					GPIO = 0x20;
				}
			  }
			}
		}
	}
}

void delay(unsigned int tiempo) // Función para imprimir delay (Dos loops for)
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < tiempo; i++)
		for (j = 0; j < 1275; j++)
			;
}

