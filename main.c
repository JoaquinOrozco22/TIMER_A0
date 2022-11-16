/******************************************************************************************************************************************************************************************************************************************
*Integrantes:
*- Joaquin Bernardo Orozco Lopez 18060729
*- Sebastian De la Cruz Mendoza 18060707
*- Angel Eduardo Yañez Ramirez C17550468
*
*1.- ¿Que registros asociados al timer se utilizan y para que sirven?
*
*    Se utilizan dso registros asociados al timer. El registro "TA0CCR0" y el registro "CTL".
*
*    - El registro TA0CCR0 es un registro con dos modos, registro de captura/comparación
*        Modo comparación: En este modo el registro almacena el valor a comparar con el valor actual del timer en el registro TA0R
*        Modo captura: En este modo el registro TA0R es copiado a este registro cuando se efectúa la captura
*
*    - El registro CTL es un registro en el que se configura el TimerA0
*
*2.- ¿Que direcciones en memoria tienen?
*
*    - Registro TA0CCR0: 0x4000_0012
*
*    - Registro TA0CTL: 0x4000_0000
*
*3.- ¿Para el programa, qué se configura en ellos y cómo funciona el programa?
*
*    - En el registro TA0CCR0 se estableció el valor de la cuenta en 65000
*
*    - En el registro TA0CTL:
*        1.- Se escribe en el campo TASSEL (bits 8-9) un 2. Este campo sirve para seleccionar la señal de reloj a utilizar para el timer,
*        en este caso se está utilizando la señal de reloj SMCLK (Low-speed subsystem master clock).
*        2.- Se escribe en el campo MC (bits 5-4) un 1. Este campo sirve para el control de modo, en este caso se selecciona el modo Up,
*        es decir, el cuenta hasta el valor guardado en el registro TA0CCR0
*        3.- Se pone en alto el campo TACLR (bit 2). Al poner en alto este campo, se reinicia el registro TA0R,
*        la lógica del divisor del reloj y la dirección de la cuenta. Este bit es reinicido automáticamente y siempre es leído como 0.
******************************************************************************************************************************************************************************************************************************************/

#include "msp.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->DIR |=BIT0; //Se configura el bit 0 del puerto 1 como salida, corresponde al LED1 de la tarjeta

	TIMER_A0->CCR[0]=65000; //Se establece el valor de tiempo al que debe llegar el timer.
	TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;    //Configuracion del timer

	while(1){
	    if((TIMER_A0->CTL & TIMER_A_CTL_IFG)!=0){   //Condicionante if, si hay una interrupcion pendiente (Si hay un 1 en el bit 0 del registro CTL)
	        P1->OUT ^= BIT0;    //Se aplica una xor a la salida con si misma y un 1, cambiando el valor de la salida
	        TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;  //Se limpia la bandera de la interrupcion del timer.
	    }
	}
}
