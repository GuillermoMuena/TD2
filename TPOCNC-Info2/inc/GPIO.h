/**
 * @author Catedra Info II
 */
#ifndef GPIO_H_
#define GPIO_H_
#include "infotronic.h"

#define		ACTIVO_BAJO			0
#define		ACTIVO_ALTO			1

//!< Configuracin de PINSEL
#define		FUNCION_GPIO		0
#define		FUNCION_1			1
#define		FUNCION_2			2
#define		FUNCION_3			3

//!< Configuracin de PINMODE
#define		MODO_0				0
#define		MODO_1				1
#define		MODO_2				2
#define		MODO_3				3

#define		ENTRADA				0
#define		SALIDA				1

//!<Prototipos
void SetPINSEL ( uint8_t  , uint8_t  ,uint8_t );
void SetPINMODE( uint8_t  , uint8_t  ,uint8_t );
void SetDIR( uint8_t  , uint8_t  , uint8_t  );
void SetPIN( uint8_t  , uint8_t  , uint8_t  );
uint8_t GetPIN( uint8_t  , uint8_t  , uint8_t );

#endif /* GPIO_H_ */
