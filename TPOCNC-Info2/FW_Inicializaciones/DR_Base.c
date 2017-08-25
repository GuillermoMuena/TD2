/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

/** @fn void Inicializar( void )
 * @details Inicializacion del Hardware
 * @details Portable
 * @param 	void
 * @return 	void.
 */
void Inicializar_Perifericos( void )
{
	InitPLL();
	InicializarTeclado(  );
	Inicializar_RGB(  );
	stepper_init();
	spindle_init();
	Inicializar_Timers();
	SysTickInic (  );
	InitUART0 (  );
	InitLCD (  );
	InitEINTx( );
}

/** @fn void Inicializar_RGB( void )
 * @brief Inicializa las GPIO inherentes al teclado
 * @details No Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> RGBn: puero y bit del puerto
 * 		<li> FUNCION_GPIO: Funcion GPIO del pin del micro
 * 		<li> SALIDA: Configura a la GPIO como salida
 * 		</ul>
 * @param 	void.
 * @return 	void.
 */
void Inicializar_RGB( void )
{
	SetPINSEL ( RGBR , FUNCION_GPIO );
	SetPINSEL ( RGBG , FUNCION_GPIO );
	SetPINSEL ( RGBB , FUNCION_GPIO );

	SetDIR ( RGBR , SALIDA );
	SetDIR ( RGBG , SALIDA );
	SetDIR ( RGBB , SALIDA  );

	SetPIN( RGBR , OFF );
	SetPIN( RGBG , OFF );
	SetPIN( RGBB , OFF );
}

void InitEINTx( void )
{
	SetPINSEL( KEY3 , 1 ); 				// Pin9:P2[13] 	GPIO / EINT3 / Reserved / I2STX_SDA
	EXTMODE |= ( 1 << EXTMODE3 );		// externa por flanco
	EXTPOLAR &= ~( 1 << EXTPOLAR3 ) ;	// descendente
	//EXTPOLAR |= ( 1 << EXTPOLAR3 );		// ascendente
	ISER0 |= ( 1 << NVIC_EINT3 ) ;		// Habilito Interrupcion externa 3
}

void stepper_init(void)
{
	SetPINSEL ( XSTEP , FUNCION_GPIO );
	SetPINSEL ( XDIR , FUNCION_GPIO );
	SetPINSEL ( XEN , FUNCION_GPIO );

	SetPINSEL ( YSTEP , FUNCION_GPIO );
	SetPINSEL ( YDIR , FUNCION_GPIO );
	SetPINSEL ( YEN , FUNCION_GPIO );

	SetPINSEL ( ZSTEP , FUNCION_GPIO );
	SetPINSEL ( ZDIR , FUNCION_GPIO );
	SetPINSEL ( ZEN , FUNCION_GPIO );

	SetDIR ( XSTEP , SALIDA );
	SetDIR ( XDIR , SALIDA );
	SetDIR ( XEN , SALIDA  );

	SetDIR ( YSTEP , SALIDA );
	SetDIR ( YDIR , SALIDA );
	SetDIR ( YEN , SALIDA  );

	SetDIR ( ZSTEP , SALIDA );
	SetDIR ( ZDIR , SALIDA );
	SetDIR ( ZEN , SALIDA  );

	SetPIN( XEN , st_OFF );
	SetPIN( YEN , st_OFF );
	SetPIN( ZEN , st_OFF );
}
void spindle_init(void)
{
	SetPINSEL ( SPINDLE_PIN , FUNCION_GPIO );

	SetDIR ( SPINDLE_PIN , SALIDA );

	SetPIN( SPINDLE_PIN , OFF );
}

/********************************************************************************
	\fn  void Inicializar_Timer(void)
	\brief Inicialización de Interrupcion y funcionamiento del T/C 0.
	\author & date: Informática II
 	\param void
	\return:	void
 */
void Inicializar_Timers(void)
{
	PCONP |= 1 << 1 ;	//Prende el TimerCounter 0
	PCLKSEL0 |= 0 << 2 ;//Fuente de Clock = CCLK/4

	// t1
	PCONP |= 1 << 2 ; // Prende el TimerCounter 1
	PCLKSEL0 |= 0 << 4 ;//Fuente de Clock = CCLK/4

	// t2
	PCONP |= 1 << 22 ; // Prende el TimerCounter 2
	PCLKSEL1 |= 0 << 12 ;//Fuente de Clock = CCLK/4

	T0MR0 = 0x7fffff/5000; //Configuro el valor de match 0
	T0MR1 = 0xffffff/5000 ;//Configuro el valor de match 1

	// t1
	T1MR0 = 0x7fffff/5000; //Configuro el valor de match 0
	T1MR1 = 0xffffff/5000 ;//Configuro el valor de match 1

	// t2
	T2MR0 = 0x7fffff/5000; //Configuro el valor de match 0
	T2MR1 = 0xffffff/5000 ;//Configuro el valor de match 1

	T0MCR  = ( ( 1 << MR0I ) | ( 0 << MR0R ) | ( 0 << MR0S ) ) ;//habilita la interrupcion  al match0
	T0MCR |= ( ( 1 << MR1I ) | ( 1 << MR1R ) | ( 0 << MR1S ) ) ;// habilita la interrupcion  al match1 y resetea timecounter del match1

	// t1
	T1MCR  = ( ( 1 << MR0I ) | ( 0 << MR0R ) | ( 0 << MR0S ) ) ;//habilita la interrupcion  al match0
	T1MCR |= ( ( 1 << MR1I ) | ( 1 << MR1R ) | ( 0 << MR1S ) ) ;// habilita la interrupcion  al match1 y resetea timecounter del match1

	// t2
	T2MCR  = ( ( 1 << MR0I ) | ( 0 << MR0R ) | ( 0 << MR0S ) ) ;//habilita la interrupcion  al match0
	T2MCR |= ( ( 1 << MR1I ) | ( 1 << MR1R ) | ( 0 << MR1S ) ) ;// habilita la interrupcion  al match1 y resetea timecounter del match1

	T0TCR &= ( ~( 1 << CE ) ) ;// deshabilita el timer  0
	T1TCR &= ( ~( 1 << CE ) ) ;// deshabilita el timer  1
	T2TCR &= ( ~( 1 << CE ) ) ;// deshabilita el timer  2

	T0TCR &= ( ~( 1 << CR ) ) ;// deshabilita el reset timer  0
	T1TCR &= ( ~( 1 << CR ) ) ;// deshabilita el reset timer  1
	T2TCR &= ( ~( 1 << CR ) ) ;// deshabilita el reset timer  2

	//T0TCR |= (    1 << CE ) ;//habilita el timer  0

	ISER0 |= ( 1 << NVIC_TIMER0 ) ;//Habilita la interrupcion del Timer 0 en el NVIC
	ISER0 |= ( 1 << NVIC_TIMER1 ) ;//Habilita la interrupcion del Timer 1 en el NVIC
	ISER0 |= ( 1 << NVIC_TIMER2 ) ;//Habilita la interrupcion del Timer 2 en el NVIC
}









