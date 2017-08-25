/**
 *	\file funciones.c
 *	\brief
 *	\details Descripcion detallada del archivo
 *	\author Bustamante, Capuj, Romero, Pizzani
 *	\date 06-11-2015 09:48:39
 */

#include "Aplicacion.h"

extern void (*Sys_global[])(void);
extern uint8_t flag[N_AXIS];
char Stepper_Start = 1;

/**
	@fn void SYS_INI(void)
	@brief pone en uno la funcion inicializar_sys y va al estado alarm
 	@details --
 	@return void
 */

void SYS_INI(void)
{
	if ((Inicializar_Sys() == TRUE))
	{
		sys.state = S_ALARM;
	}
}

/**
	@fn void SYS_ALARM(void)
	@brief Mira el estado de alarmevent() y de ahi va al estado correspondiente
	@details --
 	@return void
 */

void SYS_ALARM(void)
{
	if ((alarmEvent() == FALSE))
	{
		sys.state = S_IDLE;
	}
	else
	{
		if ((alarmEvent() == TRUE))
		{
			TimerClose();
			report_alarm();
			sys.state = S_ESPERA;
			sys.alarm = NO_ALARM;
		}
	}
}

/**
	@fn void SYS_IDLE(void)
	@brief mira el valor de keyevent() y de ahi va al estado correspondiente
 	@details --
 	@return void
 */

void SYS_IDLE(void)
{
	if ((keyEvent() == START_HOMING) || (sys.serial_code == START_HOMING))
	{
		sys.state = S_GO_HOME;
	}

	if ((keyEvent() == SET_HOME) || (sys.serial_code == SET_HOME))
	{
		sys.state = S_SET_HOME;
	}

	if ( (keyEvent() == START_AUTO) || (sys.serial_code == START_AUTO) )
	{
		sys.state = S_AUTO;
		st_wake_up();
		if (Stepper_Start)
		{
			sys.S_Auto.flag_end_block[X_AXIS] = 1; //!< cuando es el primer movimiento fuerzo el flag
			sys.S_Auto.flag_end_block[Y_AXIS] = 1;
			sys.S_Auto.flag_end_block[Z_AXIS] = 1;
			Stepper_Start = 0;
		}
	}
	if ( (keyEvent() == START_MANUAL) || (sys.serial_code == START_MANUAL) )
	{
		st_wake_up();
		sys.state = S_MANUAL;
	}
}

/**
	@fn void SYS_WAIT(void)
	@brief mira el valor de keyevent() y muestra en el LCD la informacion
 	@details --
 	@return void
 */

void SYS_WAIT(void)
{
	int i;
	if ( (keyEvent() == GO_IDLE) || (sys.serial_code == GO_IDLE) )
	{
		Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
		TimerStart ( DISP_START_OFF, 1);
		for(i=0;i<N_AXIS;i++)
			flag[i]=1;

//		Display_lcd (" Posiciones: ", RENGLON0, 1);
//		sendSerialString("X: 0.00%");
//		Display_lcd("X: 0.00",RENGLON1,10);
//		sendSerialString("Y: 0.00%");
//		Display_lcd("Y: 0.00",RENGLON2,10);
//		sendSerialString("Z: 0.00%" );
//		Display_lcd("Z: 0.00",RENGLON3,10);
		sys.serial_state = SERIAL_HEADER_ev;
		sys.state = S_INI;
	}
}

/**
	@fn void SYS_MANUAL(void)
	@brief mira el valor de alarmevent() y de ahi va al estado correspondiente
 	@details --
 	@return void
 */

void SYS_MANUAL(void)
{

	if ( (alarmEvent() == TRUE) )
	{
		sys.state = S_ALARM;
	}
	if ( (alarmEvent() == FALSE) )
	{
		if ( sys.manual_serial != NO_KEY)
			plan_move_serial_manual();
		if ( sys.manual_key != NO_KEY)
			plan_move_manual();

		sys.state = S_IDLE;
		sys.manual_serial = NO_KEY;
	}
}

/**
	@fn void SYS_AUTO(void)
	@brief  segun el valor de alarmevent() y si llego al final de stepper cambia de estado
 	@details --
 	@return void
 */

void SYS_AUTO(void)
{
	if ( (alarmEvent() == TRUE) )
	{
		sys.state = S_ALARM;
	}
	if ( (sys.S_Auto.flag_all_blocks_finished == TRUE) )
	{
		stepper_stop();
		sys.state = S_IDLE;
		sys.S_Auto.flag_gcode_finished = FALSE;
		sys.S_Auto.flag_all_blocks_finished = FALSE;
	}
}

/**
	@fn void SYS_GO_HOME(void)
	@brief mira el valor de alarmevent() si es 1 se va a alarm sino a idle
 	@details --
 	@return void
 */

void SYS_GO_HOME(void)
{
	if ((alarmEvent() == TRUE))
	{
		sys.state = S_ALARM;
	}
	if ((alarmEvent() == FALSE) && (goHome() == DONE))
	{
		sys.state = S_IDLE;
		sys.manual_serial = NO_KEY;
	}
}

/**
	@fn void SYS_SET_HOME(void)
	@brief mira el valor de alarmevent() si es verdadero va a alarm sino muestra informacion en display y va a IDLE
 	@details --
 	@return void
 */

void SYS_SET_HOME(void)
{
	int i;
	if ((alarmEvent() == TRUE))
	{
		sys.state = S_ALARM;
	}
	if (alarmEvent() == FALSE)
	{
		TimerClose();
		Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
		if ( setHome() )
		{
			TimerStart ( DISP_START_OFF, 1);
			for(i=0;i<N_AXIS;i++)
						flag[i]=1;
//			Display_lcd (" Posiciones: ", RENGLON0, 1);
//			sendSerialString("X: 0.00%");
//			Display_lcd("X: 0.00",RENGLON1,10);
//			sendSerialString("Y: 0.00%");
//			Display_lcd("Y: 0.00",RENGLON2,10);
//			sendSerialString("Z: 0.00%" );
//			Display_lcd("Z: 0.00",RENGLON3,10);
			sys.state = S_IDLE;
			sys.manual_serial = NO_KEY;
		}
		else
			sys.state = S_ALARM;
	}
}

/**
	@fn void Sys_global_machine(void)
	@brief compara el estado actual con espera y lo lleva a INI
 	@details --
 	@return void
 */

void Sys_global_machine()
{
	if (sys.state > S_ESPERA)
	{
		sys.state = S_INI;
		return;
	}

	Sys_global[sys.state]();
}


