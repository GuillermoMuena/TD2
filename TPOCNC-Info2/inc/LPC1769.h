/**
 * @author Catedra Info II
 */
#ifndef LPC1769_H_
#define LPC1769_H_

#define		PORT0				0
#define		PORT1				1
#define		PORT2				2
#define		PORT3				3
#define		PORT4				4

//!< GPIO - PORT0
/*	*						*
	*************************
	*		FIODIR			*	0x2009C000
	*************************
	*		RESERVED		*	0x2009C004
	*************************
	*		RESERVED		*	0x2009C008
	*************************
	*		RESERVED		*	0x2009C00C
	*************************
	*		FIOMASK			*	0x2009C010
	*************************
	*		FIOPIN			*	0x2009C014
	*************************
	*		FIOSET			*	0x2009C018
	*************************
	*		FIOCLR			*	0x2009C01C
	*************************
	*						*
	*						*
*/
#define			GPIO				( ( __RW uint32_t * ) 0x2009C000UL )

typedef 	__RW uint32_t 		registro;  //!< defino un tipo 'registro' uint32_t volatile.

//!< ////////////////Registros PINSEL//////////////////////////////
//!< 00	GPIO (reset value)		01	funcion 1
//!< 11	funcion 3				10	funcion 2
#define			PINSEL				( ( __RW uint32_t * ) 0x4002C000UL )
#define			PINSEL0				( * ( (__RW uint32_t * ) 0x4002C000UL ) ) //!< P0[15:0]
#define			PINSEL1		(		 * ( (__RW uint32_t * ) 0x4002C004UL ) ) //!< P0[31:16]
//!< //////////////////Registros PINMODE ///////////////////////////
#define			PINMODE				( ( __RW uint32_t * ) 0x4002C040UL )

#define			PINMODE0			PINMODE[0]
#define			PINMODE1			PINMODE[1]
#define			PINMODE2			PINMODE[2]
#define			PINMODE3			PINMODE[3]
#define			PINMODE4			PINMODE[4]
#define			PINMODE5			PINMODE[5]		//!< not used
#define			PINMODE6			PINMODE[6]		//!< not used
#define			PINMODE7			PINMODE[7]
#define			PINMODE8			PINMODE[8]		//!< not used
#define			PINMODE9			PINMODE[9]

#define			PINMODE_PULLUP 		0
#define			PINMODE_REPEAT 		1
#define			PINMODE_NONE 		2
#define			PINMODE_PULLDOWN 	3

#define			PINMODE_OD			( ( __RW uint32_t * ) 0x4002C040UL )

#define			PINMODE_OD0			PINMODE_OD[0]
#define			PINMODE_OD1			PINMODE_OD[1]
#define			PINMODE_OD2			PINMODE_OD[2]
#define			PINMODE_OD3			PINMODE_OD[3]
#define			PINMODE_OD4			PINMODE_OD[4]

#define			GPIO				( ( __RW uint32_t * ) 0x2009C000UL )

#define			FIO0DIR				GPIO[0]
#define			FIO0MASK			GPIO[4]
#define			FIO0PIN				GPIO[5]
#define			FIO0SET				GPIO[6]
#define			FIO0CLR				GPIO[7]
#define			FIO1DIR				GPIO[8]
#define			FIO1MASK			GPIO[12]
#define			FIO1PIN				GPIO[13]
#define			FIO1SET				GPIO[14]
#define			FIO1CLR				GPIO[15]
#define			FIO2DIR				GPIO[16]
#define			FIO2MASK			GPIO[20]
#define			FIO2PIN				GPIO[21]
#define			FIO2SET				GPIO[22]
#define			FIO2CLR				GPIO[23]
#define			FIO3DIR				GPIO[24]
#define			FIO3MASK			GPIO[28]
#define			FIO3PIN				GPIO[29]
#define			FIO3SET				GPIO[30]
#define			FIO3CLR				GPIO[31]
#define			FIO4DIR				GPIO[32]
#define			FIO4MASK			GPIO[36]
#define			FIO4PIN				GPIO[37]
#define			FIO4SET				GPIO[39]
#define			FIO4CLR				GPIO[39]


typedef struct
{
	 __RW uint32_t 	FIODIR ;
		  uint32_t 	RESERVED[3];
	 __RW uint32_t 	FIOMASK	;
	 __RW uint32_t 	FIOPIN;
	 __RW uint32_t 	FIOSET;
	 __RW uint32_t 	FIOCLR;

} gpio_t;


//!< ----------- Estados de PINMODE
//!< 00	Pull Up resistor enable (reset value)		01	repeated mode enable
//!< 11	Pull Down resistor enable					10	ni Pull Up ni Pull DOwn
#define			PINMODE_PULLUP 		0
#define			PINMODE_REPEAT 		1
#define			PINMODE_NONE 		2
#define			PINMODE_PULLDOWN 	3

//!< ///////////////////   PCONP   //////////////////////////
//!<  Power Control for Peripherals register (PCONP - 0x400F C0C4) [pag. 62 user manual LPC1769]
//!< 0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 		PCONP				(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))


//!< ///////////////////   PCLKSEL   //////////////////////////
//!< Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
//!< 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

//!< /////////////		SYSTICK		///////////////////////////
//!< Tipo de dato específico para manejar el SYSTICK
typedef struct
{
	union{
		__RW uint32_t _STCTRL;
		struct{
			__RW uint32_t _ENABLE:1;
			__RW uint32_t _TICKINT:1;
			__RW uint32_t _CLKSOURCE:1;
			__RW uint32_t _RESERVED0:14;
			__RW uint32_t _COUNTFLAG:1;
			__RW uint32_t _RESERVED1:14;
		}bits;
	};
	__RW uint32_t _STRELOAD;
	__RW uint32_t _STCURR;
	__R uint32_t  _STCALIB;
}systick_t;

//!< 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK		( (systick_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK->_STCTRL

	#define	ENABLE			SYSTICK->bits._ENABLE
	#define	TICKINT			SYSTICK->bits._TICKINT
	#define	CLKSOURCE		SYSTICK->bits._CLKSOURCE
	#define	COUNTFLAG		SYSTICK->bits._COUNTFLAG

#define		STRELOAD	SYSTICK->_STRELOAD
#define		STCURR		SYSTICK->_STCURR
#define		STCALIB		SYSTICK->_STCALIB
/////////////////// TIMER 0 Register ////////////////
#define		TIMER0			( ( registro_t  * ) 0x40004000UL )

#define		T0IR			TIMER0[ 0 ]			/** IR - INTERRUPT REGISTER */
	#define		IRMR0		0
	#define		IRMR1		1
	#define		IRMR2		2
	#define		IRMR3		3
	#define		IRCR0		4
	#define		IRCR1		5
#define		T0TCR			TIMER0[ 1 ]			/** TCR - TIMER CONTROL REGISTER */
	#define		CE			0
	#define		CR			1
#define		T0TC			TIMER0[ 2 ]			/** TC - TIMER COUNTER REGISTER */
#define		T0PR			TIMER0[ 3 ]			/** PR - PRESCALE REGISTER */
#define		T0PC			TIMER0[ 4 ]			/** PC - PRESCALE COUNTER REGISTER */
#define		T0MCR			TIMER0[ 5 ]			/** MCR - MATCH CONTROL REGISTER */
	#define		MR0I			0
	#define		MR0R			1
	#define		MR0S			2
	#define		MR1I			3
	#define		MR1R			4
	#define		MR1S			5
	#define		MR2I			6
	#define		MR2R			7
	#define		MR2S			8
	#define		MR3I			9
	#define		MR3R			10
	#define		MR3S			11
#define		T0MR0			TIMER0[ 6 ]			/** MR - MATCH CONTROL REGISTER */
#define		T0MR1			TIMER0[ 7 ]
#define		T0MR2			TIMER0[ 8 ]
#define		T0MR3			TIMER0[ 9 ]
#define		T0CCR			TIMER0[ 10 ]
#define		T0CR0			TIMER0[ 11 ]
#define		T0CR1			TIMER0[ 12 ]
#define		T0EMR			TIMER0[ 13 ]
#define		T0CTCR			TIMER0[ 14 ]		/** CTCR - COUNT CONTROL REGISTER */
	#define		TCM			0
	#define		CIS			2

/////////////////// TIMER 1 Register ////////////////

#define		_T1IR ((uint32_t *) 0x40008000UL)
#define 	T1IR	 	_T1IR [0]
#define 	T1TCR		_T1IR [1]
#define 	T1TC 		_T1IR [2]
#define 	T1PR		_T1IR [3]
#define 	T1PC	 	_T1IR [4]
#define 	T1MCR		_T1IR [5]
#define 	T1MR0		_T1IR [6]
#define 	T1MR1		_T1IR [7]
#define 	T1MR2		_T1IR [8]
#define 	T1MR3		_T1IR [9]
#define 	T1CCR		_T1IR [10]
#define 	T1CR0		_T1IR [11]
#define 	T1CR1		_T1IR [12]
#define 	T1EMR		_T1IR [15]
#define 	T1CTCR		_T1IR [28]

/////////////////// TIMER 2 Register ////////////////

#define 	_T2IR		 ((uint32_t *) 0x40090000UL)
#define 	T2IR	 	_T2IR [0]
#define 	T2TCR	 	_T2IR [1]
#define 	T2TC	 	_T2IR [2]
#define 	T2PR	 	_T2IR [3]
#define 	T2PC	 	_T2IR [4]
#define 	T2MCR	 	_T2IR [5]
#define 	T2MR0	 	_T2IR [6]
#define 	T2MR1	 	_T2IR [7]
#define 	T2MR2	 	_T2IR [8]
#define 	T2MR3	 	_T2IR [9]
#define 	T2CCR	 	_T2IR [10]
#define 	T2CR0	 	_T2IR [11]
#define 	T2CR1	 	_T2IR [12]
#define 	T2EMR	 	_T2IR [15]
#define 	T2CTCR	 	_T2IR [28]

// NVIC ----------------------------------------------------------------------------------------------
#define		NVIC_TIMER0		1
#define		NVIC_TIMER1		2
#define		NVIC_TIMER2		3
#define		NVIC_EINT3		21

// Nested Vectored Interrupt Controller (NVIC)
// 0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( registro_t  * ) 0xE000E100UL )
//!< 0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( ( registro_t  * ) 0xE000E180UL )

// Registros ISER:
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]

// Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]

//****************************************************  UART0  UART1 **********************************************************
////UART0:
////0x4001000CUL : Registro de control de la UART0:
//#define		DIR_U0LCR	( ( uint32_t  * ) 0x4000C00CUL )
////0x40010014UL : Registro de recepcion de la UART0:
//#define		DIR_U0LSR		( ( uint32_t  * ) 0x4000C014UL )
////0x40010000UL : Parte baja del divisor de la UART0:
//#define		DIR_U0DLL	( ( uint32_t  * ) 0x4000C000UL )
////0x40010004UL : Parte alta del divisor de la UART0:
//#define		DIR_U0DLM	( ( uint32_t  * ) 0x4000C004UL )
////0x40010000UL : Registro de recepcion de la UART0:
//#define		DIR_U0RBR		( ( uint32_t  * ) 0x4000C000UL )
////0x40010000UL : Registro de transmision de la UART0:
//#define		DIR_U0THR		( ( uint32_t  * ) 0x4000C000UL )
////0x4000C004UL : Registro habilitacion de interrupciones de la UART0:
//#define		DIR_U0IER	( ( uint32_t  * ) 0x4000C004UL )
////0x4000C008UL : Registro de control de la FIFO de la UART0:
//#define		DIR_U0FCR	( ( uint32_t  * ) 0x40000C008UL )
//
//
////UART1:
////0x4001000CUL : Registro de control de la UART1:
//#define		DIR_U1LCR	( ( uint32_t  * ) 0x4001000CUL )
////0x40010014UL : Registro de recepcion de la UART1:
//#define		DIR_U1LSR		( ( uint32_t  * ) 0x40010014UL )
////0x40010000UL : Parte baja del divisor de la UART1:
//#define		DIR_U1DLL	( ( uint32_t  * ) 0x40010000UL )
////0x40010004UL : Parte alta del divisor de la UART1:
//#define		DIR_U1DLM	( ( uint32_t  * ) 0x40010004UL )
////0x40010000UL : Registro de recepcion de la UART1:
//#define		DIR_U1RBR	( ( uint32_t  * ) 0x40010000UL )
////0x40010000UL : Registro de transmision de la UART1:
//#define		DIR_U1THR	( ( uint32_t  * ) 0x40010000UL )
////0x40010004UL : Registro habilitacion de interrupciones de la UART1:
//#define		DIR_U1IER	( ( uint32_t  * ) 0x40010004UL )
////0x40010008UL : Registro de identificación de la interrupción de la UART1:
//#define		DIR_U1IIR	( ( uint32_t  * ) 0x40010008UL )
////0x40010008UL : Registro de control de la FIFO de la UART1:
//#define		DIR_U1FCR	( ( uint32_t  * ) 0x40010008UL )
//
//
////0x4001004CUL : Registro de control comunicacion 485:
//#define		DIR_U1RS485CTRL		( ( uint32_t  * ) 0x4001004CUL )
////0x40010050UL : Registro de direccion 485:
//#define		DIR_U1RS485ADRMATCH	( ( uint32_t  * ) 0x40010050UL )
////0x40010054UL : Registro de demora entre fin de transmision y fin de RTS:
//#define		DIR_U1RS485DLY	( ( uint32_t  * ) 0x40010054UL )
//
////Registros de la UART0:
//#define		U0THR		DIR_U0THR[0]
//#define		U0RBR		DIR_U0RBR[0]
//#define		U0LCR		DIR_U0LCR[0]
//#define		U0LSR		DIR_U0LSR[0]
//#define		U0DLL		DIR_U0DLL[0]
//#define		U0DLM		DIR_U0DLM[0]
//#define		U0IER		DIR_U0IER[0]
//#define		U0RDR		(U0LSR&0x01)
//#define		U0FCR		DIR_U0FCR[0]
//#define		U0THRE		((U0LSR&0x20)>>5)
//
////Registros de la UART1:
//#define		U1THR		DIR_U1THR[0]
//#define		U1RBR		DIR_U1RBR[0]
//#define		U1LCR		DIR_U1LCR[0]
//#define		U1LSR		DIR_U1LSR[0]
//#define		U1DLL		DIR_U1DLL[0]
//#define		U1DLM		DIR_U1DLM[0]
//#define		U1IER		DIR_U1IER[0]
//#define		U1IIR		DIR_U1IIR[0]
//#define		U1FCR		DIR_U1FCR[0]
//
//#define		U1RDR		(U1LSR&0x01)
//#define		U1THRE		((U1LSR&0x20)>>5)
//
//#define		U1RS485CTRL		DIR_U1RS485CTRL[0]
//#define		U1RS485ADRMATCH	DIR_U1RS485ADRMATCH[0]
//#define		U1RS485DLY		DIR_U1RS485DLY[0]


//!< ///////////////////   Interrupciones Externas   //////////////////////////
#define		EXTINT 		( * ( ( registro_t  * ) 0x400FC140UL ) )
	#define		EINT0		0
	#define		EINT1		1
	#define		EINT2		2
	#define		EINT3		3

#define		EXTMODE 	( * ( ( registro_t  * ) 0x400FC148UL ) )
	#define		EXTMODE0	0
	#define		EXTMODE1	1
	#define		EXTMODE2	2
	#define		EXTMODE3	3

#define		EXTPOLAR 	( * ( ( registro_t  * ) 0x400FC14CUL ) )
	#define		EXTPOLAR0	0
	#define		EXTPOLAR1	1
	#define		EXTPOLAR2	2
	#define		EXTPOLAR3	3

//!< ///////////////////   UART0   //////////////////////////
//!< 0x4000C000UL : Registro de control de la UART0:
#define		UART0	( ( registro  * ) 0x4000C000UL )

//!< Registros de la UART0:
#define		U0THR		UART0[0]
#define		U0RBR		UART0[0]
#define		U0DLL		UART0[0]

#define		U0DLM		UART0[1]
#define		U0IER		UART0[1]

#define		U0IIR		((__R registro *)UART0)[2]
#define		U0FCR		((__W registro *)UART0)[2]

#define		U0LCR		UART0[3]
//!< posición 4 no definida [consultar pag. 300 user manual LPC1769]
#define		U0LSR		UART0[5]
//!< posición 6 no definida [consultar pag. 300 user manual LPC1769]
#define		U0SCR		UART0[7]

//!< ///////////////////   UART1   //////////////////////////
//!< 0x40010000UL : Registro de control de la UART1:
#define		UART1	( ( registro  * ) 0x40010000UL )

//!< Registros de la UART1:
#define		U1THR		UART1[0]
#define		U1RBR		UART1[0]
#define		U1DLL		UART1[0]

#define		U1DLM		UART1[1]
#define		U1IER		UART1[1]

#define		U1IIR		UART1[2]
#define		U1FCR		UART1[2]

#define		U1LCR		UART1[3]
#define		U1MCR		UART1[4]
#define		U1LSR		UART1[5]
#define		U1MSR		UART1[6]
#define		U1SCR		UART1[7]

//!< //////////BITS DE ANALISIS para todas las UARTs   ////////////////////
#define 	IER_RBR		0x01
#define 	IER_THRE	0x02
#define 	IER_RLS		0x04

#define 	IIR_PEND	0x01
#define 	IIR_RLS		0x06
#define 	IIR_RDA		0x04
#define 	IIR_CTI		0x0C
#define 	IIR_THRE	0x02

#define 	LSR_RDR		0x01
#define 	LSR_OE		0x02
#define 	LSR_PE		0x04
#define 	LSR_FE		0x08
#define 	LSR_BI		0x10
#define 	LSR_THRE	0x20
#define 	LSR_TEMT	0x40
#define 	LSR_RXFE	0x80

//!< macros útiles para UARTs
#define		U0RDR		(U0LSR & LSR_RDR)
#define		U0THRE		((U0LSR & LSR_THRE) >>5)
#define		U1RDR		(U1LSR & LSR_RDR)
#define		U1THRE		((U1LSR & LSR_THRE) >>5)
#endif /* LPC1769_H_ */
