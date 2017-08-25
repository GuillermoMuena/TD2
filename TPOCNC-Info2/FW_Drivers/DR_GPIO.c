/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

/** @fn void SetPINSEL( uint8_t  , uint8_t  ,uint8_t )
 * @details Selecciona la funcionalidad que se le dara al pin
 * @details No Portable
 * @param 	port: Puerto.
 * @param 	pin: numero de bit dentro del puerto.
 * @param 	sel: Tipo de seleccion.
 * @return 	void.
 */
void SetPINSEL( uint8_t port , uint8_t pin ,uint8_t sel )
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ port ] = PINSEL[ port ] & ( ~ ( 3 << pin ) );
	PINSEL[ port ] = PINSEL[ port ] | ( sel << pin );
}

/** @fn void SetPINMODE( uint8_t  , uint8_t  ,uint8_t )
 * @details Selecciona el modo de funcionamiento que tomara la GPIO seleccionada
 * @details No Portable.
 * @param 	port: Puerto.
 * @param 	pin: numero de bit dentro del puerto.
 * @param 	modo: modo de funcionamiento del GPIO seleccionado.
 * @return 	void.
 */

void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

/** @fn void SetDIR( uint8_t  , uint8_t  , uint8_t  )
 * @details Selecciona el modo de funcionamiento que tomara la GPIO seleccionada
 * @details No Portable
 * @param 	port: Puerto.
 * @param 	pin: numero de bit dentro del puerto.
 * @param 	modo: modo de funcionamiento del GPIO seleccionado
 * @return 	void.
 */
void SetDIR(  uint8_t port  ,  uint8_t pin  ,  uint8_t dir  )
{
	port = port * 8;

	GPIO[ port ] = GPIO[ port ] & ( ~ (  1 << pin  ) );
	GPIO[ port ] = GPIO[ port ] | (  dir << pin  );
}

/** @fn void SetPIN( uint8_t  , uint8_t  , uint8_t  )
 * @details escribe un  valor a la GPIO seleccionada
 * @details No Portable
 * @param 	port: Puerto.
 * @param 	pin: numero de bit dentro del puerto.
 * @param 	estado: valor a  asignar al GPIO
 * @return 	void.
 */
void SetPIN( uint8_t port , uint8_t pin , uint8_t estado )
{
	port = port * 8 + 5;

	GPIO[ port ] = GPIO[ port ] & ( ~ ( 1 << pin ) );
	GPIO[ port ] = GPIO[ port ] | ( estado << pin );
}

/** @fn uint8_t GetPIN( uint8_t  , uint8_t  , uint8_t  )
 * @details Informa el  valor a la GPIO seleccionada
 * @details No Portable
 * @param 	port: Puerto.
 * @param 	pin: numero de bit dentro del puerto.
 * @param 	actividad: tipo de actividad del GPIO ( bajo o alto )
 * @return 	void.
 */
uint8_t GetPIN( uint8_t port , uint8_t pin , uint8_t actividad )
{
	port = port * 8 + 5;

	return ( ( ( GPIO[ port ] >> pin ) & 1 ) == actividad ) ? 1 : 0;

}
