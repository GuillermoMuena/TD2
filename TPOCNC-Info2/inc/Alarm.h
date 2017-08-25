/*
 * Alarm.h
 *
 *  Created on: 8/11/2015
 *      Author: Julieta
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

void report_alarm (void);
uint8_t soft_check_limit ( uint8_t axis, uint8_t dir, uint32_t steps);

#define		NO_ALARM					0
#define		SOFT_LIMIT_ERROR_MANUAL		1
#define		CONNECTION_ESTABLISHED		2
#define		NO_PC_CONNECTION			3
#define		BUFF_RX_EMPTY				4
#define		OVERFLOW_LINE				5
#define		SOFT_LIMIT_ERROR_X			6
#define		SOFT_LIMIT_ERROR_Y			7
#define		SOFT_LIMIT_ERROR_Z			8
#define		GO_HOME_ERROR				12
#define		ABORT_AUTO					13

//!< ALARMAS G-CODE
#define  STATUS_EXPECTED_COMMAND_LETTER				9
#define  STATUS_GCODE_UNSUPPORTED_COMMAND			10
#define  STATUS_GCODE_COMMAND_VALUE_NOT_INTEGER		11


#endif /* INC_ALARM_H_ */
