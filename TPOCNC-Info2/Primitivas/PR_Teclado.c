/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

extern volatile unsigned char key ;			//!< Buffer de teclado

/**
 *	@fn  unsigned char Teclado( void )
 *	@brief lectura del bufer de teclado, si hay codigo lo retorna y borra el buffer
 *  @details Portable
 * 	@param [in]
 *	@return Exito: Codigo de tecla, No Exito NO_KEY
*/
uint8_t Teclado( void )
{
	uint8_t v_Key = NO_KEY;
	v_Key = key;

	return v_Key;
}
