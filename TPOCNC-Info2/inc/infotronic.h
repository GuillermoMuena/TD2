/**
 * @author Catedra Info II
 */
#ifndef INFOTRONIC_H_
#define INFOTRONIC_H_

#define		__R					volatile const
#define		__W					volatile
#define		__RW				volatile

typedef 	unsigned int 		uint32_t;
typedef 	unsigned short 		uint16_t;
typedef 	unsigned char 		uint8_t;
typedef 	__RW uint32_t 		registro_t;  //!< defino un tipo 'registro'.

#define		ON					1
#define		OFF					0

#define		st_ON				0
#define		st_OFF				1

//!<Identificación de los puertos de expansion:
#define 	EXPANSION0		PORT2,7
#define 	EXPANSION1		PORT1,29
#define 	EXPANSION2		PORT4,28
#define 	EXPANSION3		PORT1,23
#define 	EXPANSION4		PORT1,20
#define 	EXPANSION5		PORT0,19
#define 	EXPANSION6		PORT3,26
#define 	EXPANSION7		PORT1,25
#define 	EXPANSION8		PORT1,22
#define 	EXPANSION9		PORT1,19
#define 	EXPANSION10		PORT0,20
#define 	EXPANSION11		PORT3,25
#define 	EXPANSION12		PORT1,27
#define 	EXPANSION13		PORT1,24
#define 	EXPANSION14		PORT1,21
#define 	EXPANSION15		PORT1,18

#define 	EXPANSION16		PORT1,31
#define 	EXPANSION17		PORT0,24
#define 	EXPANSION18		PORT0,25
#define 	EXPANSION19		PORT0,17
#define 	EXPANSION20		PORT1,31
#define 	EXPANSION21		PORT0,22
#define 	EXPANSION22		PORT0,15
#define 	EXPANSION23		PORT0,16
#define 	EXPANSION24		PORT2,8
#define 	EXPANSION25		PORT2,12
#define 	EXPANSION26		PORT1,31
#define 	EXPANSION27		PORT1,31

//!< Leds (Reles)
#define		RELAY1			PORT2,0
#define		RELAY2			PORT0,23
#define		RELAY3			PORT0,21
#define		RELAY4			PORT0,27
#define		BUZZ			PORT0,28

//!< Motores paso a paso
/*
#define		XSTEP			EXPANSION15
#define		XDIR			EXPANSION7
#define		XEN				EXPANSION8

#define		YSTEP			EXPANSION3
#define		YDIR			EXPANSION1
#define		YEN				EXPANSION2

#define		ZSTEP			EXPANSION13
#define		ZDIR			EXPANSION12
#define		ZEN				EXPANSION14*/

//!< Motores paso a paso
#define		XSTEP			EXPANSION7
#define		XDIR			EXPANSION8
#define		XEN				EXPANSION6

#define		YSTEP			EXPANSION9
#define		YDIR			EXPANSION10
#define		YEN				EXPANSION11

#define		ZSTEP			EXPANSION14
#define		ZDIR			EXPANSION13
#define		ZEN				EXPANSION12

//!< Spindle
#define		SPINDLE_PIN		RELAY2

//!< Led RGB:
#define		RGBB			PORT2,1
#define		RGBR			PORT2,2
#define		RGBG			PORT2,3

//!< Int Externas:
#define		RGBB			PORT2,1

//!< Teclas (teclado 4x1)
#define		KEY0			PORT2,10
#define		KEY1			PORT0,18
#define		KEY2			PORT0,11
#define		KEY3			PORT2,13
#define		KEY4			PORT1,26

//!< teclas expansion 3 (4x2)
#define 	FILA0			EXPANSION0
#define 	FILA1			EXPANSION1
#define 	FILA2			EXPANSION2
#define 	FILA3			EXPANSION3
#define 	COLUMNA0		EXPANSION4
#define 	COLUMNA1		EXPANSION5

#define		K0			0
#define		K1			1
#define		K2			2
#define		K3			3
#define		K4			4

#define		K5			13
#define		K6			14
#define		K7			15

#define		SW1			5
#define		SW2			6
#define		SW3			7
#define		SW4			8
#define		SW5			16
#define		SW6			10
#define		SW7			11
#define		SW8			12

//!< GPIOS LCD:

#define LCD_20x4

#define		LCD_D4		PORT0,5			//GPIO0
#define		LCD_D5		PORT0,10		//GPIO0
#define		LCD_D6		PORT2,4			//GPIO2
#define		LCD_D7		PORT2,5			//GPIO2

#define		LCD_RS		PORT2,6			//GPIO2
#define		LCD_BF		PORT0,28		//GPIO1
#define		LCD_E		PORT0,4			//GPIO0

#define		LCD_E_OFF				SetPIN(LCD_E,0)
#define		LCD_E_ON				SetPIN(LCD_E,1)
#define		LCD_RS_OFF				SetPIN(LCD_RS,0)
#define		LCD_RS_ON				SetPIN(LCD_RS,1)
#define		LCD_DATO(d4,d5,d6,d7)	SetPIN(LCD_D4,d4);SetPIN(LCD_D5,d5);SetPIN(LCD_D6,d6);SetPIN(LCD_D7,d7)

#define		LCD_CONTROL		1
#define		LCD_DATA		0
//!<  COMANDOS LCD
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

//!< flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

//!< flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

//!< flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

#define		RENGLON0		0
#define		RENGLON1		1
#define		RENGLON2		2
#define		RENGLON3		3

void Inicializar_Perifericos( void );
void InitEINTx( void );
void Inicializar_RGB( void );
void InitPLL ( void );
void Inicializar_Timers(void);
void SysTickInic ( void );
void InitLCD(void);
void Dato_LCD (unsigned char , unsigned char );
void Display_lcd( char *, char , char );
void Deb_Disp (char* s);
void Dis_Pos (void );
void Display_bienvenida(void );

#endif /* INFOTRONIC_H_ */
