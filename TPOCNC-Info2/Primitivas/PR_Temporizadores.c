/**
 * @author Catedra Info II
 */

#include "Aplicacion.h"

extern volatile uint8_t Tmr_Run[ CANT_TIMERS ];				//!< Buffers de temporizadores
extern volatile uint8_t Eventos[ CANT_TIMERS ];

/**
 *	@fn  void TimerStart ( uint8_t  , timer_t   )
 *	@brief Dispara el temporizador n_ev  durante t tiempo
 *  @details Portable
 *	@param [in] n_ev numero de tempotizador
 *	@param [in] t tiempo de duracion
 *  @return void
*/
void TimerStart ( uint8_t n_ev , uint16_t t  )
{
	TICKINT = 0;
	Tmr_Run[ n_ev ] = t ;
	Eventos[ n_ev ] = 0 ;
	TICKINT = 1;
}	

/**
 *	@fn  void TimerClose ( void )
 *	@brief Apaga todos los temporizadores
 *  @details Portable
 *	@param void
 *	@return void
*/
void TimerClose ( void )
{
	int i;
	for ( i = 0 ; i < CANT_TIMERS ; i++ )
		TimerStop( i );							//!< Macro de TimerStart
}

