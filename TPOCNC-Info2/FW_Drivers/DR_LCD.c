/*
 * DR_LCD.c
 *
 *  Created on: 22/10/2015
 *      Author: admin
 */
#include "Aplicacion.h"

void Dato_LCD ( unsigned char data , unsigned char control )
{
	int q , i = 1;
	uint16_t data_d4,data_d5,data_d6,data_d7;

	do
	{
		data_d4 = ( data >> ( 0 + i * 4 ) ) & 0x01 ;
		data_d5 = ( data >> ( 1 + i * 4 ) ) & 0x01 ;
		data_d6 = ( data >> ( 2 + i * 4 ) ) & 0x01 ;
		data_d7 = ( data >> ( 3 + i * 4 ) ) & 0x01 ;

		LCD_DATO(data_d4,data_d5,data_d6,data_d7);

		if( control == LCD_CONTROL )
			LCD_RS_OFF;
		else
			LCD_RS_ON;

		LCD_E_ON;
		for( q = 0 ; q < 400 ; q++ );
		LCD_E_OFF;
		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i-- );
}

