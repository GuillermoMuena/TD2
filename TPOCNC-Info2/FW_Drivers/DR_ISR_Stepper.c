/*
 * DR_ISR_Stepper.c
 *
 *  Created on: 6/11/2015
 *      Author: Fernando
 */


#include "Aplicacion.h"

extern volatile st_block_t st_auto_block;
//system_t sys;

/**
 * \fn TIMERn_IRQHandler
 * \brief control de interrupcion del timern
 * \detail cada vez que interrumpe un match bajamos y subimos el pin de Step, para generarl el tren de pulsos
 */

void TIMER0_IRQHandler (void)
{
	if (T0IR & ( 1 << IRMR0 ) )	///< Si interrumpio Match 0 y quedan pasos por hacer
	{
		T0IR = ( 1 << IRMR0 );			///< Borro flag del Match 0
		if(st_auto_block.steps[X_AXIS] > 0)
		{
			SetPIN(XSTEP , 0 ) ;			///< XSTEP ; estado = 1
			st_auto_block.steps[X_AXIS]--;
			if(st_auto_block.direction_bits[X_AXIS]==CW)
				sys.position[X_AXIS]++;
			if(st_auto_block.direction_bits[X_AXIS]==CCW)
				sys.position[X_AXIS]--;
		}
	}

	if( T0IR & ( 1 << IRMR1 ))			///< Si interrumpio Match 1
	{
		T0IR = ( 1 << IRMR1 ); 			///< Borro flag del Match 1
		SetPIN( XSTEP , 1 ) ;			///< XSTEP ; estado = 0
	}

	if( !st_auto_block.steps[X_AXIS] )
	{

		T0IR = ( 1 << IRMR0 );
		T0IR = ( 1 << IRMR1 );
		T0MCR &= ~( 1 << MR0I ) ;///< Desabilita la interrupcion del MRn
		T0MCR &= ~( 1 << MR1I ) ;

		T0TCR = 0x00000002;	//Apaga y resetea el temporizador
		sys.S_Auto.flag_end_block[X_AXIS] = 1;
	}
}

void TIMER1_IRQHandler(void)
{
	if (T1IR & ( 1 << IRMR0 ))
	{
		T1IR = ( 1 << IRMR0 );
		if(st_auto_block.steps[Y_AXIS] > 0)
		{
			SetPIN(YSTEP , 0 ) ;
			st_auto_block.steps[Y_AXIS]--;
			if(st_auto_block.direction_bits[Y_AXIS]==CW)
				sys.position[Y_AXIS]++;
			if(st_auto_block.direction_bits[Y_AXIS]==CCW)
				sys.position[Y_AXIS]--;
		}
	}

	if( T1IR & ( 1 << IRMR1 ))
	{
		T1IR = ( 1 << IRMR1 );
		SetPIN( YSTEP , 1 ) ;
	}

	if(!st_auto_block.steps[Y_AXIS])
	{
		T1IR = ( 1 << IRMR0 );
		T1IR = ( 1 << IRMR1 );
		T1MCR &= ~( 1 << MR0I ) ;///< Desabilita la interrupcion del MRn
		T1MCR &= ~( 1 << MR1I ) ;

		T1TCR = 0x00000002;
		sys.S_Auto.flag_end_block[Y_AXIS]  = 1;
	}
}

void TIMER2_IRQHandler(void)
{
	if (T2IR & ( 1 << IRMR0 ))
	{
		T2IR = ( 1 << IRMR0 );
		if(st_auto_block.steps[Z_AXIS] > 0 )
		{
			SetPIN(ZSTEP , 0 ) ;
			st_auto_block.steps[Z_AXIS]--;

			if(st_auto_block.direction_bits[Z_AXIS]==CCW)
				sys.position[Z_AXIS]++;
			if(st_auto_block.direction_bits[Z_AXIS]==CW)
				sys.position[Z_AXIS]--;
		}
	}

	if( T2IR & ( 1 << IRMR1 ))
	{
		T2IR = ( 1 << IRMR1 );
		SetPIN( ZSTEP , 1 ) ;
	}

	if(!st_auto_block.steps[Z_AXIS])
	{

		T2IR = ( 1 << IRMR0 );
		T2IR = ( 1 << IRMR1 );
		T2MCR &= ~( 1 << MR0I ) ;///< Desabilita la interrupcion del MRn
		T2MCR &= ~( 1 << MR1I ) ;

		T2TCR = 0x00000002;
		sys.S_Auto.flag_end_block [Z_AXIS] = 1;
	}
}






