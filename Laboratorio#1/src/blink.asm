;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"blink.c"
	list	p=12f675
	radix dec
	include "p12f675.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config 0x3f97
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_ANSEL
	extern	_TRISIO
	extern	_CMCON
	extern	_GPIO
	extern	_GPIObits
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_delay

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0020
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_blink_0	udata
r0x1008	res	1
r0x1009	res	1
r0x100A	res	1
r0x1001	res	1
r0x1000	res	1
r0x1002	res	1
r0x1003	res	1
r0x1004	res	1
r0x1005	res	1
r0x1006	res	1
r0x1007	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; initialized absolute data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_blink	code
;***
;  pBlock Stats: dbName = M
;***
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;4 compiler assigned registers:
;   r0x1008
;   r0x1009
;   r0x100A
;   STK00
;; Starting pCode block
S_blink__main	code
_main:
; 2 exit points
;	.line	13; "blink.c"	TRISIO = 0b00000000; 		// Poner todos los pines como salidas 
	BANKSEL	_TRISIO
	CLRF	_TRISIO
;	.line	14; "blink.c"	GPIO = 0b00100000;   		// Poner pines en bajo; terminales en 0
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
;	.line	15; "blink.c"	ANSEL = 0;			 		// Canales analogicos como E/S digitales
	BANKSEL	_ANSEL
	CLRF	_ANSEL
;	.line	16; "blink.c"	CMCON = 0x07;			    // Apagar comparadores
	MOVLW	0x07
	BANKSEL	_CMCON
	MOVWF	_CMCON
;	.line	22; "blink.c"	unsigned int counter = 1;	// se define contador
	MOVLW	0x01
	MOVWF	r0x1008
	CLRF	r0x1009
_00125_DS_:
;	.line	25; "blink.c"	if (GP5 == 0x01){     // Hacemos el contador para que sostenga un  número 
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,5
	INCF	r0x100A,F
	MOVF	r0x100A,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00122_DS_
;	.line	26; "blink.c"	counter ++;
	INCF	r0x1008,F
	BTFSC	STATUS,2
	INCF	r0x1009,F
;	.line	27; "blink.c"	if (counter == 7){  //número aleatorio enfrascado entre 1 y 6
	MOVF	r0x1008,W
	XORLW	0x07
	BTFSS	STATUS,2
	GOTO	_00125_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00125_DS_
;	.line	29; "blink.c"	counter ++;
	MOVLW	0x01
	MOVWF	r0x1008
	CLRF	r0x1009
	GOTO	_00125_DS_
_00122_DS_:
;	.line	31; "blink.c"	} else { if (GP5 == 0x00){ // Al presionar bottón se configura la salida de los leds
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,5
	GOTO	_00125_DS_
;	.line	32; "blink.c"	if (counter == 1){      // Para mostrar el uno en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x01
	BTFSS	STATUS,2
	GOTO	_00108_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00108_DS_
;	.line	33; "blink.c"	GP1 = ~GP1;
	CLRF	r0x100A
	BTFSC	_GPIObits,1
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,1
	BTFSC	STATUS,0
	BSF	_GPIObits,1
;	.line	34; "blink.c"	delay(time1);		// Llamada a condición de espera
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	35; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00108_DS_:
;	.line	37; "blink.c"	} if (counter == 2){    // Para mostrar el dos en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x02
	BTFSS	STATUS,2
	GOTO	_00110_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00110_DS_
;	.line	38; "blink.c"	GP2 = ~GP2;
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,2
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,2
	BTFSC	STATUS,0
	BSF	_GPIObits,2
;	.line	39; "blink.c"	delay(time1);
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	40; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00110_DS_:
;	.line	42; "blink.c"	} if (counter == 3){    // Para mostrar el tres en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x03
	BTFSS	STATUS,2
	GOTO	_00112_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00112_DS_
;	.line	43; "blink.c"	GP2 = ~GP2;
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,2
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,2
	BTFSC	STATUS,0
	BSF	_GPIObits,2
;	.line	44; "blink.c"	GP1 = ~GP1;
	CLRF	r0x100A
	BTFSC	_GPIObits,1
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,1
	BTFSC	STATUS,0
	BSF	_GPIObits,1
;	.line	45; "blink.c"	delay(time1);
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	46; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00112_DS_:
;	.line	48; "blink.c"	} if (counter == 4){    // Para mostrar el cuatro en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x04
	BTFSS	STATUS,2
	GOTO	_00114_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00114_DS_
;	.line	49; "blink.c"	GP0 = ~GP0;
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,0
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,0
	BTFSC	STATUS,0
	BSF	_GPIObits,0
;	.line	50; "blink.c"	GP2 = ~GP2;
	CLRF	r0x100A
	BTFSC	_GPIObits,2
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,2
	BTFSC	STATUS,0
	BSF	_GPIObits,2
;	.line	51; "blink.c"	delay(time1);
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	52; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00114_DS_:
;	.line	54; "blink.c"	} if (counter == 5){   // Para mostrar el cinco en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x05
	BTFSS	STATUS,2
	GOTO	_00116_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00116_DS_
;	.line	55; "blink.c"	GP0 = ~GP0;
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,0
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,0
	BTFSC	STATUS,0
	BSF	_GPIObits,0
;	.line	56; "blink.c"	GP1 = ~GP1;
	CLRF	r0x100A
	BTFSC	_GPIObits,1
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,1
	BTFSC	STATUS,0
	BSF	_GPIObits,1
;	.line	57; "blink.c"	GP2 = ~GP2;
	CLRF	r0x100A
	BTFSC	_GPIObits,2
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,2
	BTFSC	STATUS,0
	BSF	_GPIObits,2
;	.line	58; "blink.c"	delay(time1);
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	59; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
_00116_DS_:
;	.line	61; "blink.c"	} if (counter == 6){    // Para mostrar el seis en la configuración de leds
	MOVF	r0x1008,W
	XORLW	0x06
	BTFSS	STATUS,2
	GOTO	_00125_DS_
	MOVF	r0x1009,W
	XORLW	0x00
	BTFSS	STATUS,2
	GOTO	_00125_DS_
;	.line	62; "blink.c"	GP0 = ~GP0;
	CLRF	r0x100A
	BANKSEL	_GPIObits
	BTFSC	_GPIObits,0
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,0
	BTFSC	STATUS,0
	BSF	_GPIObits,0
;	.line	63; "blink.c"	GP2 = ~GP2;
	CLRF	r0x100A
	BTFSC	_GPIObits,2
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,2
	BTFSC	STATUS,0
	BSF	_GPIObits,2
;	.line	64; "blink.c"	GP4 = ~GP4;
	CLRF	r0x100A
	BTFSC	_GPIObits,4
	INCF	r0x100A,F
	COMF	r0x100A,W
	MOVWF	r0x100A
	RRF	r0x100A,W
	BTFSS	STATUS,0
	BCF	_GPIObits,4
	BTFSC	STATUS,0
	BSF	_GPIObits,4
;	.line	65; "blink.c"	delay(time1);
	MOVLW	0x96
	MOVWF	STK00
	MOVLW	0x00
	PAGESEL	_delay
	CALL	_delay
	PAGESEL	$
;	.line	66; "blink.c"	GPIO = 0x20;
	MOVLW	0x20
	BANKSEL	_GPIO
	MOVWF	_GPIO
	GOTO	_00125_DS_
;	.line	72; "blink.c"	}
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;has an exit
;9 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   r0x1002
;   r0x1003
;   r0x1004
;   r0x1005
;   r0x1006
;   r0x1007
;; Starting pCode block
S_blink__delay	code
_delay:
; 2 exit points
;	.line	74; "blink.c"	void delay(unsigned int tiempo) // Función para imprimir delay (Dos loops for)
	MOVWF	r0x1000
	MOVF	STK00,W
	MOVWF	r0x1001
;	.line	79; "blink.c"	for (i = 0; i < tiempo; i++)
	CLRF	r0x1002
	CLRF	r0x1003
_00136_DS_:
	MOVF	r0x1000,W
	SUBWF	r0x1003,W
	BTFSS	STATUS,2
	GOTO	_00157_DS_
	MOVF	r0x1001,W
	SUBWF	r0x1002,W
_00157_DS_:
	BTFSC	STATUS,0
	GOTO	_00138_DS_
;;genSkipc:3307: created from rifx:0x7ffdb6b6ed00
;	.line	80; "blink.c"	for (j = 0; j < 1275; j++)
	MOVLW	0xfb
	MOVWF	r0x1004
	MOVLW	0x04
	MOVWF	r0x1005
_00134_DS_:
	MOVLW	0xff
	ADDWF	r0x1004,W
	MOVWF	r0x1006
	MOVLW	0xff
	MOVWF	r0x1007
	MOVF	r0x1005,W
	BTFSC	STATUS,0
	INCFSZ	r0x1005,W
	ADDWF	r0x1007,F
	MOVF	r0x1006,W
	MOVWF	r0x1004
	MOVF	r0x1007,W
	MOVWF	r0x1005
	MOVF	r0x1007,W
	IORWF	r0x1006,W
	BTFSS	STATUS,2
	GOTO	_00134_DS_
;	.line	79; "blink.c"	for (i = 0; i < tiempo; i++)
	INCF	r0x1002,F
	BTFSC	STATUS,2
	INCF	r0x1003,F
	GOTO	_00136_DS_
_00138_DS_:
;	.line	82; "blink.c"	}
	RETURN	
; exit point of _delay


;	code size estimation:
;	  278+   29 =   307 instructions (  672 byte)

	end
