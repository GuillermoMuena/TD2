/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

/** @fn void SysTick_Handler( void )
 * @details Timer del sistema - scheduler de los drivers
 * @details No Portable
 * @param 	void
 * @return 	void.
 */
void SysTick_Handler( void )
{
	DriverTecladoSW (  );
	BasesDeTiempo( );
}

/** @fn void SysTickInic ( void )
 * @details Inicializacion del systick
 * @details No Portable
 * @param 	void
 * @return 	void.
 */
void SysTickInic ( void )
{
	STRELOAD = ( STCALIB / 10) - 1;
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}



