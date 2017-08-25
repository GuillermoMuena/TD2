/*
 * UART.h
 *
 *  Created on: 17/9/2015
 *      Author: Fernando
 */

#ifndef INC_UART_H_
#define INC_UART_H_

//!< Macros Comunicacion Serie
#define SERIAL_HEADER_ev			0
#define SERIAL_AUTO_ev				1
#define SERIAL_MANUAL_ev			2
#define SERIAL_SET_SETTINGS_ev		3
#define SERIAL_GO_HOME_ev			4
#define SERIAL_SET_HOME_ev			5
#define SERIAL_ERROR_ev				6

#define Ser_AUTO_TRAMA_INI			0
#define Ser_AUTO_TRAMA_BUILD		1
#define Ser_AUTO_TRAMA_FIN			2

#define Ser_AUTO					'@'
#define Ser_LINE_AUTO				'$'
#define Ser_FIN_AUTO				'#'
#define Ser_MANUAL					'%'
#define Ser_SET_SETTINGS			'?'
#define Ser_SET_HOME				'&'
#define Ser_GO_HOME					'H'
#define Ser_SPINDLE_ON				'S'
#define Ser_ABORT_AUTO				';'
#define Ser_GO_IDLE					'='

#define Ser_XR						'a'
#define Ser_XL						'b'
#define Ser_YR						'c'
#define Ser_YL						'd'
#define Ser_ZU						'e'
#define Ser_ZD						'f'
#define Ser_XR_PRESS				'l'
#define Ser_XL_PRESS				'm'
#define Ser_YR_PRESS				'n'
#define Ser_YL_PRESS				'o'
#define Ser_ZU_PRESS				'p'
#define Ser_ZD_PRESS				'q'
#define Ser_BUTTONS_RELEASED		'r'
#define Ser_SET_ZERO_ALL			'g'
#define Ser_SET_ZERO_X				'i'
#define Ser_SET_ZERO_Y				'j'
#define Ser_SET_ZERO_Z				'k'

#define TAM_BUF_RX	100						//!< Tamaño buffer recepcion
#define TAM_BUF_TX	40						//!< Tamaño buffer transmicion

#define U1_FLAG_TX     U1LSR & 0x20			//!< Flag error transmision
#define U1_REG_SAL_TX  U1THR				//!< Registro de salida de transmicion

#define U0_FLAG_TX     U0LSR & 0x20
#define U0_REG_SAL_TX  U0THR

//!< Primitivas UART
void sendSerialString ( char *);
int serialRead(void);
void push_TX(unsigned char);
void Serial_reset_buff_rx ( void );

//!< Drivers UART
void push_RX(unsigned char);
int pop_TX(void);
void InitUART1 ( void );
void InitUART0 ( void );

#endif /* INC_UART_H_ */























