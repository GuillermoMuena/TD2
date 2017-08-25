#ifndef system_h
#define system_h

/*
 * Eje XY
 * pasos_por_mm = (pasos_por_vuelta_del_motor * micropasos_del_driver_del_motor ) / (paso_entre_dientes_de_la_polea * numero_dientes_polea)
 * pasos_por_mm = (200 * 32) / (16 * 2)
 *
 * Eje Z
 * Varilla 5/16 18 hilos
 * pasos_por_mm = (pasos_por_vuelta_del_motor * micropasos_del_driver_del_motor) / paso_varilla
 * (200 * 32) / (25,4/18)
 */

///< Macros de la aplicacion
#define		RIGHT			1
#define		LEFT			0
#define		E_ON			1
#define		E_OFF			0

#define		CW				0
#define		CCW				1
#define		X_AXIS			0
#define		Y_AXIS			1
#define		Z_AXIS			2
#define		N_AXIS			3

#define		UN_MM_SEG			1
#define		DOS_MM_SEG			2
#define		CINCO_MM_SEG		5
#define		DIEZ_MM_SEG			10
#define		VEINTE_MM_SEG		20
#define		TRYCINCO_MM_SEG		35
#define		CINCUENTA_MM_SEG	50
#define		CIEN_MM_SEG			100 //Velocidad maxima ?

#define 	MM_SEG			125000
#define 	PASOSXY_MM		(200 * 32) / (16 * 2)
#define		PASOSZ_MM		(int)(200 * 32) / (25.4/18)

//!< Macros teclas
#define		 key_XR			SW1
#define		 key_XL			SW5
#define		 key_YR			SW2
#define		 key_YL			SW6
#define		 key_ZU			SW3
#define		 key_ZD			SW7
#define		 key_SET_HOME	SW4
#define		 key_GO_HOME	SW8

//!< Declaracion de estados main
#define 	TRUE  		1
#define 	FALSE  		0

#define 	S_INI		0
#define 	S_ALARM		1
#define 	S_IDLE		2
#define 	S_MANUAL	3
#define 	S_AUTO		4
#define 	S_GO_HOME	5
#define 	S_SET_HOME	6
#define 	S_ESPERA	7

#define START_HOMING	1
#define START_AUTO		2
#define SET_SETTINGS	3
#define START_MANUAL	4
#define GO_IDLE			5
#define DONE			6
#define SET_HOME		8
#define UNDONE			0



typedef struct
{
  uint8_t state;								//!< Estado del systema en modo auto
  uint8_t flag_gcode_finished;					//!< Flag finalizacion de ultimo comando G
  uint8_t flag_all_blocks_finished;				//!< Flag finalizacion del ultimo bloque stepper
  volatile uint8_t flag_end_block[N_AXIS];		//!< Flag finalizacion de bloque stepper
} sys_auto;

/**
 * @brief Estructura del systema global
 */

typedef struct {
  uint8_t abort;
  uint32_t state;                 				//!< Estado acual del systema
  uint8_t suspend;               				//!< Flag ded suspencion del systema. Usado para pausas por comando (Dwell)

  volatile uint8_t serial_code;  				//!<  Global realtime executor bitflag variable for state management. See EXEC bitmasks.
  volatile uint8_t alarm;  						//!<  Flag de alarma global en tiempo real

  volatile int position[N_AXIS];      		//!< Posicion de la maquina en tiempo real, en pasos
  volatile uint32_t new_Home_Ref[N_AXIS];  		//!< nuevo Home si fue seteado
  volatile int planner_position[N_AXIS];   		//!< Posicion donde el planer cree que esta despues de un bloque (target)

  uint8_t firstHome;       						//!< Flag auxiliar que indica primer home
  uint8_t manual_key;							//!< Tecla pulsada en modo manual
  uint8_t manual_serial;						//!< Tecla pulsada en modo manual
  uint8_t endstop_rached; 						//!< Flag final de carrera alcanzado

  volatile sys_auto S_Auto;
  volatile uint8_t serial_state;

} system_t;

extern system_t sys;

void Sys_global_machine(void);

//!< Prototipos de funciones para la maquina
void SYS_INI (void);
void SYS_ALARM (void);
void SYS_IDLE (void);
void SYS_MANUAL (void);
void SYS_AUTO (void);
void SYS_GO_HOME (void);
void SYS_SET_HOME(void);
void SYS_WAIT(void);

//!< Prototipos de los eventos
int Inicializar_Sys(void);
int keyEvent(void);
int alarmEvent(void);
void setSettings(char,float);

//!< Prototipo funcion aux eventos
void init_system_var (void);
void init_position(void);

//!< Prototipos de funciones S_Auto // SERIAL_HEADER, SERIAL_AUTO, SERIAL_MANUAL, SERIAL_SET_SETTINGS, SERIAL_GO_HOME, SERIAL_SET_HOME, SERIAL_ERROR
void serialEvent(void);
void SERIAL_HEADER (void);
void SERIAL_AUTO (void);
void SERIAL_MANUAL (void);
void SERIAL_SET_SETTINGS (void);
void SERIAL_GO_HOME (void);
void SERIAL_SET_HOME (void);
void SERIAL_ERROR (void);

#endif
