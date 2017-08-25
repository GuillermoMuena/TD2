/**
 * @author Grupo4
 */

#include "Aplicacion.h"

extern volatile st_block_t st_auto_block;
extern volatile uint8_t Tmr_Run[ CANT_TIMERS ];				//!< Buffers de temporizadores
extern volatile uint8_t Eventos[ CANT_TIMERS ];				//!< Eventos de timer vencidos

void TimerEvent( void )
{
	uint8_t i ;
	for(i=0; i<CANT_TIMERS; i++)
	{
		if(Eventos[ i ])
		{
			switch( i )
			{
			case DISP_START_OFF:
				Dis_Pos();
				Eventos[i] =0;
				TimerStart ( DISP_START_OFF, 2);
				break;
			case DISP_WELCOME:
				Dato_LCD (LCD_CLEARDISPLAY ,LCD_CONTROL);
				Eventos[i] =0;
				TimerStart ( DISP_START_OFF, 2);
				break;
			}
		}
	}
}
