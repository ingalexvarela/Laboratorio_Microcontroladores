//#include <pic14/pic12f683.h>
#include <pic14/pic12f675.h>
//#define _LEGACY_HEADERS
//#define _MCLRE_OFF 0x3FDF
//#define _WDTE_OFF 0x3FF7  

#define LOOP?WAIT?LIMIT 100 

// Inicialización de perifericos y MCU
// Configuración ** deshabilitar reset y watchdog timer con macros
typedef unsigned int word;
word __at 0x2007 __CONFIG =  (_MCLRE_OFF & _WDTE_OFF & _BODEN_OFF); 

void delay(unsigned inttiempo); // Acá se define la función del tiempo de espera

void main(void) // Función principal para la ejecución de acciones
{
	// ** Establecimiento de las condiciones en registros
	TRISIO = 0b00000000; // Poner todos los pines como salidas
	GPIO = 0x00;		 // Poner pines en bajo; terminales en 0
	ANSEL = 0;			 // Canales analogicos como E/S digitales
	CMCON = 0x07;			 // Apagar comparadores
	//CONFIG =   0b0000000000000000;
	unsigned int time = 200;

	// Loop forever
	while (1)
	{
		GPIO = 0x00;
		GPIO = 0b00100000;
		delay(time);
		//GP1 = 0x00;
		//delay(time); // Para imprimir delay entre cada tiro
		//GP0 = 0x01;
	    //delay(time);
		//GP0 = 0x00;
		//GPIO = 0b00000001;
		//GPIO = ~GPIO;
		//GP1 = ~GP1;
		//delay(time);
		unsigned int counter = 1;	
		while (1){
			  if (counter == 6 && GP5 == 0x01){
				counter = 1;
				counter ++;
			  } else { if (GP5 == 0x00){
				GP5 = ~GP5;
				if (counter == 1){
					GP1 = ~GP1;
					delay(time);
				} if (counter == 2){
					GP2 = ~GP2;
					delay(time);
				} if (counter == 3){
					GP2 = ~GP2;
					GP1 = ~GP1;
					delay(time);
				} if (counter == 4){
					GP0 = ~GP0;
					GP2 = ~GP2;
					delay(time);
				} if (counter == 5){
					GP0 = ~GP0;
					GP1 = ~GP1;
					GP2 = ~GP2;
					delay(time);
				} if (counter == 6){
					GP0 = ~GP0;
					GP1 = ~GP1;
					GP2 = ~GP2;
					GP4 = ~GP4;
					delay(time);
				}
			  }
			  }
			  counter ++;
		}
	}
}

void delay(unsigned int tiempo) // Función para imprimir delay
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < tiempo; i++)
		for (j = 0; j < 1275; j++)
			;
}

