/**
 	\file TPO-CNC
 	\brief Firmware router CNC
 	\version 3.3
 	\details Comunicacion serie, interpretacion de cosdigo G, control de movimiento.
 	\author	Bustamante Fernando Abel, Capuj Agustin, Pizzani Juan Pablo, Romero Guido.
 	\date 2015.09
 */


#include "Aplicacion.h"
/*! \mainpage TPO Informática 2
*
* \section intro_sec Router CNC TPO
*
*Un Router CNC es una máquina de fresado equipada con motores en cada uno de sus 3 ejes,
*los mismos son controlados por una computadora a través de un CNC (Control Numérico Computarizado)
*que le indica los movimientos de manera coordinada a cada uno de ellos. Realiza un proceso de
*desbaste mediante una broca que corta el material según las instrucciones y da forma a la pieza
*3D. Además la misma contará con la posibilidad de ser controlada tanto manualmente por el usuario
* a través de los botones, como directamente por la computadora teniendo ya el plano de la pieza deseada.
*
*
*/


//** Buffers del sistema ***************************************************************************
volatile unsigned char key = NO_KEY ;			//!< Buffer de teclado
unsigned char TxStart, buff_empty = TRUE;		//!< Auxiliares
volatile uint8_t Tmr_Run[ CANT_TIMERS ];		//!< Buffers de temporizadores
volatile uint8_t Eventos;						//!< Eventos de timer vencidos
system_t sys;
//***************************************************************************************************

void(* Sys_global[])(void) = {SYS_INI, SYS_ALARM, SYS_IDLE, SYS_MANUAL, SYS_AUTO, SYS_GO_HOME, SYS_SET_HOME, SYS_WAIT};

void(* Serial_Events[])(void) = {SERIAL_HEADER, SERIAL_AUTO, SERIAL_MANUAL, SERIAL_SET_SETTINGS, SERIAL_GO_HOME, SERIAL_SET_HOME, SERIAL_ERROR };

int main(void)
{

	int condicion = 1;

	Inicializar_Perifericos();
	init_position();
	Display_bienvenida();

	sys.state = S_INI;
	sys.serial_state= SERIAL_HEADER_ev;

	while(condicion)
	{
		TimerEvent();

		serialEvent();

		Sys_global_machine();

		if (sys.state == S_AUTO && sys.S_Auto.flag_all_blocks_finished == FALSE && sys.alarm == NO_ALARM)
			st_stepper_move();

	}

	return 0 ;
}











