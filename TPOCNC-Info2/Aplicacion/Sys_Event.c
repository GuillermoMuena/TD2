/*
 * Sys_Event.c
 *
 *  Created on: 8/11/2015
 *      Author: Grupo4
 */

#include "Aplicacion.h"

/**
	@fn int inicializar_sys(void)
	@brief inicializa el sistema
 	@details  retorna 1
 	@return int
 */

int Inicializar_Sys(void)
{
	settings_restore_global_settings();
	init_system_var();

	return TRUE;
}

/**
	@fn imt key_event (void)
	@brief se fija que tecla se apreto
 	@details devuelve el numero de accion dependiendo de la tecla
 	@return int
 */

int keyEvent(void)
{
	uint8_t c;
	c = Teclado();

	switch(c)
	{
	case key_XR: case key_XL: case key_YR: case key_YL: case key_ZU: case key_ZD:
		sys.manual_key=c;
		return START_MANUAL;

	case key_GO_HOME:
		return START_HOMING;

	case key_SET_HOME:
		return SET_HOME;
	}
	sys.manual_key = NO_KEY;
	return NO_KEY;
}

/**
	@fn int alarmEvent (void)
	@brief Mira el estado de la alarma
 	@details devuelve 0 o 1 dependiendo del estado
 	@return int
 */

int alarmEvent(void)
{

	if(sys.alarm == NO_ALARM)
		return FALSE;
	else
	{
		return TRUE;
	}
}

/**
	@fn void setSettings(char set, float new_value)
	@brief setea las velocidades de los ejes
 	@details --
 	@return void
 */

void setSettings(char set, float new_value)
{
	uint8_t i;
	switch (set)
	{
	case 'F':
		for ( i =0 ; i< N_AXIS-1 ; i++)
		{
		settings.def_feed_rate[i] = new_value;
		}
		settings.def_feed_rate[Z_AXIS] = new_value/2;
		break;
	}
}

/**
	@fn void init_system_var (void)
	@brief inicia las variables del sistema en valores por default
 	@details --
 	@return void
 */

void init_system_var (void)
{
	sys.state = S_INI;
	sys.alarm = NO_ALARM;
	sys.firstHome = TRUE;
	sys.abort = FALSE;
	sys.endstop_rached = FALSE;
	sys.manual_key = NO_KEY;
	sys.suspend = FALSE;

	sys.new_Home_Ref[X_AXIS] = 0;
	sys.new_Home_Ref[Y_AXIS] = 0;
	sys.new_Home_Ref[Z_AXIS] = 0;
	sys.S_Auto.flag_all_blocks_finished = FALSE;
	sys.S_Auto.flag_gcode_finished = FALSE;
}

void init_position(void)
{
	memset(sys.position, 0, sizeof(sys.position));
	memset(sys.planner_position, 0, sizeof(sys.planner_position));
	memset(sys.new_Home_Ref, 0 ,sizeof(sys.new_Home_Ref));
}













