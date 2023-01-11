//#include <pic14/pic12f683.h>
#include <pic14/pic12f675.h>
//#define _LEGACY_HEADERS
//#define _MCLRE_OFF 0x3FDF
//#define _WDTE_OFF 0x3FF7  
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
	unsigned int time = 100;

	// Loop forever
	while (1)
	{
		GPIO = 0x00;
		//GP0 = 0x00;
		delay(time); // Para imprimir delay entre cada tiro
		GPIO = 0b00111111;
		//GPIO = ~GPIO;
		//GP0 = ~GP0;
		delay(time);
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

