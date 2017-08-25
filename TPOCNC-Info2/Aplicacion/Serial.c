/*
 * Serial.c
 *
 *  Created on: 6/12/2015
 *      Author: Grupo4
 */

#include "Aplicacion.h"

extern void (*Serial_Events[])(void);

char line[LINE_BUFFER_SIZE];
char line_settings[LINE_BUFFER_SIZE];
int c;
uint8_t i,j,Trama;

/**
	@fn void serialevent(void)
	@brief  mira los evento del puerto serie
 	@details  si el serial state no tiene error va al serial header
 	@return void
 */

void serialEvent(void)
{
	if (sys.serial_state > SERIAL_ERROR_ev)
	{
		sys.state = SERIAL_HEADER_ev;
		return;
	}
	Serial_Events[sys.serial_state]();
}

/**
	@fn void serial_header(void)
	@brief mira si llego un dato y donde enviarlo
 	@details  manda a el dato a algun estado dependiendo de la variable
 	@return void
 */

void SERIAL_HEADER ( void )
{
	static uint8_t spindle_ONOFF = SPINDLE_DISABLE;
	c = serialRead();
	if (c == Ser_ABORT_AUTO  )
	{
		sys.serial_state = SERIAL_HEADER_ev;
		sys.alarm=ABORT_AUTO;
		return;
	}
	if ( c != SERIAL_NO_DATA )
	{
		switch (c)
		{
		case Ser_AUTO:
			sys.serial_code = START_AUTO;
			sys.serial_state = SERIAL_AUTO_ev;
			gc_init();
			pl_init();
			st_block_init();
			i = 0;
			Trama = 0;
			break;

		case Ser_MANUAL:
			sys.serial_code = START_MANUAL;
			sys.serial_state = SERIAL_MANUAL_ev;
			break;

		case Ser_SET_SETTINGS:
			sys.serial_state = SERIAL_SET_SETTINGS_ev;
			j = 0;
			break;

		case Ser_SET_HOME:
			sys.serial_code = SET_HOME;
			sys.serial_state = SERIAL_SET_HOME_ev;
			break;

		case Ser_GO_HOME:
			sys.serial_code = START_HOMING;
			sys.serial_state = SERIAL_GO_HOME_ev;
			break;

		case Ser_GO_IDLE:
			sys.serial_code = GO_IDLE;
			break;

		case Ser_SPINDLE_ON:
			if(spindle_ONOFF)
				splindle_control (SPINDLE_ENABLE);
			else
				splindle_control (SPINDLE_DISABLE);

			spindle_ONOFF ++;
			spindle_ONOFF %= 2;
			break;
		}
	}
	else
	{
		sys.serial_code = NO_KEY;
	}
}

/**
	@fn void serial_auto(void)
	@brief lee la trama que llego y le da una accion
 	@details  ---
 	@return void
 */

void SERIAL_AUTO ( void )
{
	if(sys.alarm!=NO_ALARM)
	{
		sys.serial_state = SERIAL_HEADER_ev;
		return;
	}
	c = serialRead();
	if (c == Ser_ABORT_AUTO  )
	{
		sys.serial_state = SERIAL_HEADER_ev;
		sys.alarm=ABORT_AUTO;
		return;
	}

	if (c != SERIAL_NO_DATA  )
	{
		switch (Trama)
		{
		case Ser_AUTO_TRAMA_INI:
			if ( c == Ser_LINE_AUTO)
				Trama = 1;
			break;

		case Ser_AUTO_TRAMA_BUILD:
			if ( c != '\n' && c != '\r')
			{
				if ( i >= (LINE_BUFFER_SIZE-1))
				{
					sys.alarm = OVERFLOW_LINE;
					sys.serial_state = SERIAL_ERROR_ev;
					i = 0;
					return;
				}
				else
				{
					line[i] = c;
					i++;
				}
			}
			else
			{
				line[i+1]='\0';
				i = 0;
				gcode_execute_line(line);
				memset(&line,0,sizeof(line));
				if ( !sys.S_Auto.flag_gcode_finished )
				{
					Trama = 0;
				}
				if (sys.S_Auto.flag_gcode_finished)
				{
					Trama = 2;
				}
				sendSerialString("$");
			}
			break;

		case Ser_AUTO_TRAMA_FIN:
			if ( c == Ser_FIN_AUTO)
			{
				Trama = 0;
				sys.serial_state = SERIAL_HEADER_ev;
			}
			break;

		default:
			Trama = 0;
			sys.serial_state = SERIAL_HEADER_ev;
			break;

		}
	}
}

/**
	@fn void serial_manual(void)
	@brief lee la trama que llego y le da una accion
 	@details  ---
 	@return void
 */

void SERIAL_MANUAL ( void )
{
	if(sys.alarm != NO_ALARM)
	{
		sys.serial_state = SERIAL_HEADER_ev;
		return;
	}

	static int c_anterior = NO_KEY;
	c = serialRead();

	if ( c  != SERIAL_NO_DATA)
	{
		if( c != c_anterior )
		{
			sys.manual_serial = c;
		}
	}
	c_anterior = c;
	sys.serial_state = SERIAL_HEADER_ev;
}

/**
	@fn void serial_set_settings(void)
	@brief lee la trama que llego y segun ello configura los parametros indicados
 	@details  ---
 	@return void
 */

void SERIAL_SET_SETTINGS ( void )
{
	if(sys.alarm != NO_ALARM)
	{
		sys.serial_state = SERIAL_HEADER_ev;
		return;
	}
	c = serialRead();
	if ( c != SERIAL_NO_DATA)
	{
		if ( isdigit(c) )
		{
			if ( j >= (LINE_BUFFER_SIZE-1))
			{
				sys.alarm = OVERFLOW_LINE;
				sys.serial_state = SERIAL_AUTO_ev;
				return;
			}
			else
			{
				line_settings[j] = c;
				j++;
			}
		}
		else
		{
			j = 0;
			setSettings( c, atoi(line_settings) );
			memset(&line_settings,0,sizeof(line_settings));
			sys.serial_state = SERIAL_HEADER_ev;
		}
	}
}

/**
	@fn void serial_go_home(void)
	@brief lee la trama que llego y va al serial header
 	@details  ---
 	@return void
 */

void SERIAL_GO_HOME (void)
{
	if(sys.alarm!=NO_ALARM)
	{
		sys.serial_state = SERIAL_HEADER_ev;
		return;
	}

	c = serialRead();

	if ( c != SERIAL_NO_DATA)
	{
		sys.manual_serial = c;
		sys.serial_state = SERIAL_HEADER_ev;
	}
}

/**
	@fn void serial_set_home(void)
	@brief lee la trama que llego y fija el set_home
 	@details  ---
 	@return void
 */

void SERIAL_SET_HOME ( void )
{
	if( sys.alarm != NO_ALARM)
	{
		sys.serial_state = SERIAL_HEADER_ev;
		return;
	}

	c = serialRead();

	if ( c  != SERIAL_NO_DATA)
		sys.manual_serial = c;

	sys.serial_state = SERIAL_HEADER_ev;
}

/**
	@fn void serial_error(void)
	@brief lee la trama que llego y envia un string indicando error
 	@details  ---
 	@return void
 */

void SERIAL_ERROR ( void )
{
	sendSerialString("SERIAL_ERROR");
	sys.serial_state = SERIAL_HEADER_ev;
}





























