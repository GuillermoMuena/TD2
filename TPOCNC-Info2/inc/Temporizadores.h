/**
 * @author Catedra Info II
 */

#ifndef INTEGRADOR_PR_TIMERS_H_
#define INTEGRADOR_PR_TIMERS_H_


#define 	CANT_TIMERS			4		//!< Cantidad de temporizadores

#define 	UNA_DECIMA 		100			//!< con ticks de 2,5 ms
#define 	UN_SEGUNDO 		10
#define 	UNA_CENTESIMA	10
#define 	DISP_START_OFF	2
#define		DISP_WELCOME	1

//!< Drivers
void AnalizarTimers( uint8_t  );
void BasesDeTiempo( void );
void TimerEvent( void );

//!< Primitivas
void TimerStart ( uint8_t  , uint16_t );
void TimerClose ( void );
#define 	TimerStop( eve )	TimerStart ( eve , 0 )

#endif /* INTEGRADOR_PR_TIMERS_H_ */
