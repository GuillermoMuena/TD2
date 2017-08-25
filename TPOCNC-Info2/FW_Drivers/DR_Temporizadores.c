/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

extern volatile uint8_t Tmr_Run[ CANT_TIMERS ];				//!< Buffers de temporizadores
extern volatile uint8_t Eventos[ CANT_TIMERS ];						//!< Eventos de timer vencidos

/** @
 * fn void AnalizarTimers( uint8_t  )
 * @brief Decrementa en una unidad a un timer disparado
 * @details Portable
 * @param 	i: numero de temporizador disparado.
 * @return 	void.
 */
void AnalizarTimers( uint8_t i )
{
	if ( Tmr_Run[ i ] )
	{
		Tmr_Run[ i ] --;
		if ( !Tmr_Run[ i ] )
			Eventos[i] =1 ;
	}
}

/**
 * @fn void AnalizarTimers( uint8_t  )
 * @brief decrementa tick, decimas, segundos, etc
 * @details Portable
 * @param 	i: void
 * @return 	void.
 */
void BasesDeTiempo( void )
{
	static uint8_t ticks = UNA_CENTESIMA ;

	ticks --;

	if ( ! ticks )
	{
		ticks = UNA_CENTESIMA;
		AnalizarTimers( DISP_START_OFF );
		AnalizarTimers( DISP_WELCOME );

	}
}
