/*
 * Stepper.h
 *
 *  Created on: 8/11/2015
 *      Author: Julieta
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

/**
 * @brief Estructura de datos para la ejecucion de un bloque
 *
 * Con esta estructura se llena el buffer que es usado por
 * los timers para ejecutar los movimientos
 */

typedef struct
{
  uint8_t direction_bits[N_AXIS];
  uint16_t feed_rate[N_AXIS];
  uint32_t steps[N_AXIS];
  uint8_t max_step_flag[N_AXIS];
} st_block_t;


//!< Prototipos de funciones Stepper
void st_block_init (void);
void stepper_init(void);
void stepper_stop(void);
uint8_t st_move_line ( uint8_t, uint8_t, uint32_t, uint16_t);
void st_setdir(uint8_t,uint8_t);
void st_stepper_move (void);
void spindle_init(void);
void st_wake_up();

#endif /* INC_STEPPER_H_ */
