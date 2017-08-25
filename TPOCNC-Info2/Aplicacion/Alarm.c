#include "Aplicacion.h"

/**
	@fn  void report_alarm()
	@brief Informa el mensaje de error
 	@details Envia el codigo de error por puerto serie y al LCD
 	@return void
 */

void report_alarm (void)
{
	Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);

	switch (sys.alarm)
	{
	case SOFT_LIMIT_ERROR_MANUAL:
		Display_lcd("SOFT_LIMIT_ERROR", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":");
		sendSerialString("SOFT_LIMIT_ERROR%");
		break;
	case BUFF_RX_EMPTY:
		Display_lcd("BUFF_RX_EMPTY", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":BUFF_RX_EMPTY%");
		break;
	case OVERFLOW_LINE:
		Display_lcd("OVERFLOW_LINE", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":OVERFLOW_LINE%");
		break;
	case SOFT_LIMIT_ERROR_X: case SOFT_LIMIT_ERROR_Y: case SOFT_LIMIT_ERROR_Z:
		Display_lcd("SOFT_LIMIT_ERROR_XYZ", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":SOFT_LIMIT_ERROR_XYZ%");
		break;
	case STATUS_EXPECTED_COMMAND_LETTER:
		Display_lcd("EXPECTED_COMMAND_LETTER", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":EXPECTED_COMMAND_LETTER%");
		break;
	case STATUS_GCODE_UNSUPPORTED_COMMAND:
		Display_lcd("GCODE_UNSUPPORTED_COMMAND", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":GCODE_UNSUPPORTED_COMMAND%");
		break;
	case STATUS_GCODE_COMMAND_VALUE_NOT_INTEGER:
		Display_lcd("COMMAND_VALUE_NOT_INTEGER", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":COMMAND_VALUE_NOT_INTEGER%");
		break;
	case GO_HOME_ERROR:
		Display_lcd("GO_HOME_ERROR", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":GO_HOME_ERROR%");
		break;
	case ABORT_AUTO:
		Display_lcd("ABORT_AUTO", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm", RENGLON1, 1);
		sendSerialString(":ABORT_AUTO%");
		stepper_stop();
		splindle_control(SPINDLE_DISABLE);
		break;
	default:
		Display_lcd("Chan..ALARMA DESCONOCIDA", RENGLON0, 1);
		Display_lcd("Pulse CleanAlarm...", RENGLON0, 1);
		sendSerialString(":Chan..ALARMA DESCONOCIDA%");
		break;
	}
}

/**
	@fn uint8_t soft_check_limit( uint8_t axis, uint8_t dir, uint32_t steps)
	@brief Chequea si va a haber un sobrepaso del limite fisico.
 	@details Si el punto donde va a terminar nuestro movimiento supera el limite fisico de alguno de los ejes retorna FALSO
 	@return uint8_t
 */

uint8_t soft_check_limit ( uint8_t axis, uint8_t dir, uint32_t steps){

	int aux,position;
	if(sys.state!=S_AUTO)
		position=sys.position[axis];
	else
		position=sys.planner_position[axis];

	if(axis==Z_AXIS)
	{
		dir++;
		dir%=2;
	}
	if(dir == CW){
		aux = (steps + position + sys.new_Home_Ref[axis]);
		if(aux > settings.max_travel_steps[axis])
			return FALSE;
	}
	if (dir == CCW){
		aux = ( position + sys.new_Home_Ref[axis] - steps);
		if( aux < 0)
			return FALSE;
	}
	return TRUE;
}






















