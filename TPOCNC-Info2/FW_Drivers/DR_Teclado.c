
#include "Aplicacion.h"

extern volatile unsigned char key ;		//!< Buffer de teclado

/** @fn void InicializarTeclado( void )
 * @brief Inicializacion del teclado de 4x1 de la placa BASE Infotronic Y teclado 4x2 Expansion 3
 * @details No portable
 * 		<ul>
 *		<li> KEY0..3 / SW0...7: puerto y pin de cada tecla
 * 		<li> FUNCION_GPIO: Funcion GPIO del pin del micro
 * 		<li> ENTRADA: Configura a la GPIO como entrada
 * 		<li> SALIDA: Configura a la GPIO como salida
 * 		<li> PINMODE_PULLUP: aplica a la entrada un pullup interno
 * 		</ul>
 * @param 	void.
 * @return 	void.
 */
void InicializarTeclado( void )
{

	SetPINSEL ( KEY0 , FUNCION_GPIO );
	SetPINSEL ( KEY1 , FUNCION_GPIO );
	SetPINSEL ( KEY2 , FUNCION_GPIO );
	SetPINSEL ( KEY3 , FUNCION_GPIO );
	SetPINSEL ( KEY4 , FUNCION_GPIO );

	SetDIR ( KEY0 , ENTRADA );
	SetDIR ( KEY1 , ENTRADA );
	SetDIR ( KEY2 , ENTRADA );
	SetDIR ( KEY3 , ENTRADA );
	SetDIR ( KEY4 , ENTRADA );

	SetPINMODE ( KEY0 , PINMODE_PULLUP );
	SetPINMODE ( KEY1 , PINMODE_PULLUP );
	SetPINMODE ( KEY2 , PINMODE_PULLUP );
	SetPINMODE ( KEY3 , PINMODE_PULLUP );
	SetPINMODE ( KEY4 , PINMODE_PULLUP );


	SetPINSEL ( FILA0 , FUNCION_GPIO );
	SetPINSEL ( FILA1 , FUNCION_GPIO );
	SetPINSEL ( FILA2 , FUNCION_GPIO );
	SetPINSEL ( FILA3 , FUNCION_GPIO );
	SetPINSEL ( COLUMNA0 , FUNCION_GPIO );
	SetPINSEL ( COLUMNA1 , FUNCION_GPIO );

	SetDIR ( FILA0 , ENTRADA );
	SetDIR ( FILA1 , ENTRADA );
	SetDIR ( FILA2 , ENTRADA );
	SetDIR ( FILA3 , ENTRADA );
	SetDIR ( COLUMNA0 , SALIDA );
	SetDIR ( COLUMNA1 , SALIDA );

	SetPINMODE ( FILA0 , PINMODE_PULLUP );
	SetPINMODE ( FILA1 , PINMODE_PULLUP );
	SetPINMODE ( FILA2 , PINMODE_PULLUP );
	SetPINMODE ( FILA3 , PINMODE_PULLUP );
}

/** @fn void DriverTecladoSW (  void )
 * @brief Elimina el rebote de la tecla pulsada
 * @details Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> REBOTES: Cantidad de veces que se cuenta un cambio de estado para darlo por valido
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		</ul>
 * @param 	void.
 * @return	void.
 */

/******************************Driver DriverTecladoSW Propio****************************************************/

/** @fn void DriverTecladoSW (  void )
 * @brief Elimina el rebote de la tecla pulsada
 * @details Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> REBOTES: Cantidad de veces que se cuenta un cambio de estado para darlo por valido
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		</ul>
 * @param 	void.
 * @return	void.
 */
void DriverTecladoSW (  void ){

	static unsigned char CodigoAnterior = NO_KEY;	//!< Conserva el valor del codigo de la tecla  ante el primer cambio de estado
	//static uint16_t Repeticion_Tecla = 0;
	static unsigned char EstadosEstables;			//!< Contador de estados estables consecutivos
	unsigned char CodigoActual;

	if((CodigoActual = DriverTecladoHW())!= NO_KEY)
	{
		if(CodigoActual ==  CodigoAnterior)
		{
			EstadosEstables++;
			if (EstadosEstables == REBOTES)
			{
				key = CodigoActual;
				EstadosEstables++;
			}
			else if (EstadosEstables > REBOTES)
			{
				key = CodigoActual;
			}
		}
	}
	else
	{
		key = NO_KEY;
		EstadosEstables=0;
	}
	CodigoAnterior = CodigoActual;
}


/** @fn unsigned char DriverTecladoHW( void )
 * @brief Lectura de las GPIO asignadas a las teclas
 * @details No Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		<li> KEY0..3: puerto y pin de cada tecla
 * 		<li> ACTIVO_ALTO: Configuracion del  puerto como activo alto
 * 		</ul>
 * @param 	void.
 * @return 	codigo asignado a la tecla leida.
 */
unsigned char DriverTecladoHW( void )
{

	if ( ! GetPIN ( KEY0 , ACTIVO_ALTO ) )
		return K0;

	if ( ! GetPIN ( KEY1 , ACTIVO_ALTO ) )
		return K1;

	if ( ! GetPIN ( KEY2 , ACTIVO_ALTO ) )
		return K2;

	if ( ! GetPIN ( KEY3 , ACTIVO_ALTO ) )
		return K3;

	if ( ! GetPIN ( KEY3 , ACTIVO_ALTO ) )
		return K4;

	SetPIN(COLUMNA0,OFF); SetPIN(COLUMNA1,ON);
	SetPIN(COLUMNA0,OFF); SetPIN(COLUMNA1,ON);


	if (! GetPIN (FILA0,ACTIVO_ALTO))
		return SW4;
	if (! GetPIN (FILA1,ACTIVO_ALTO))
		return SW1;
	if (! GetPIN (FILA2,ACTIVO_ALTO))
		return SW3;
	if (! GetPIN (FILA3,ACTIVO_ALTO))
		return SW2;

	SetPIN (COLUMNA0,ON); SetPIN (COLUMNA1,OFF);
	SetPIN (COLUMNA0,ON); SetPIN (COLUMNA1,OFF);


	if ( !GetPIN (FILA0,ACTIVO_ALTO))
		return SW5;
	if ( !GetPIN (FILA1,ACTIVO_ALTO))
		return SW8;
	if ( !GetPIN (FILA2,ACTIVO_ALTO))
		return SW6;
	if ( !GetPIN (FILA3,ACTIVO_ALTO))
		return SW7;

	return NO_KEY;
}
