#include "Aplicacion.h"

extern system_t sys;

extern plan_block_t plan_block_buffer[BUFF_TAM];
extern uint8_t buff_in, buff_out;
extern unsigned char buff_empty;
volatile st_block_t st_auto_block;

/**
	@fn st_block_init(void)
	@brief llama a memset  y pone en cero a st_auto_block
 	@details  ---
 	@return void
 */

void st_block_init (void)
{
	memset(&st_auto_block, 0, sizeof(st_auto_block));
}

/*
 * 	@fn  void st_stepper_move (void)
 *	@brief Control de steppers a traves de timers asociados
 *  @details Entramos a esta funcion si no hay alarmas y hay bloques en el buffer
 *  Una vez dentro comprobamos la finalizacion del bloque anterior, en ese caso
 *  sacamos un nuevo bloque del buffer y cargamos los valores de match (que daran la velocidad),
 *  los contadoresde pasos y asignamos las direcciones de ese bloque.
 *	@param void
 *  @return void
 */

void st_stepper_move (void)
{
	uint8_t i;
	st_block_t st_aux_auto_block;

	memset(&st_aux_auto_block, 0, sizeof(st_aux_auto_block));

	if (sys.S_Auto.flag_gcode_finished){
		if (buff_out == buff_in)
		{
			buff_empty = TRUE;
			sys.S_Auto.flag_all_blocks_finished = TRUE;
			splindle_control (SPINDLE_DISABLE);
			return;
		}
	}

	if (sys.S_Auto.flag_end_block[X_AXIS] &&  sys.S_Auto.flag_end_block[Y_AXIS] && sys.S_Auto.flag_end_block[Z_AXIS] )
	{
		for ( i=0; i< N_AXIS ; i++)
		{
			sys.S_Auto.flag_end_block[i] = FALSE;
			st_aux_auto_block.direction_bits[i]=plan_block_buffer[buff_out].direction_bits[i];
			st_aux_auto_block.steps[i]=plan_block_buffer[buff_out].steps[i];
			st_aux_auto_block.max_step_flag[i] = plan_block_buffer[buff_out].max_step_flag[i];

			if(plan_block_buffer[buff_out].feed_rate[i] == 0 )
				st_aux_auto_block.feed_rate[i]= settings.def_feed_rate[i];
			else
				st_aux_auto_block.feed_rate[i]=plan_block_buffer[buff_out].feed_rate[i];
		}

		buff_out++;
		buff_out %= BUFF_TAM;

		st_setdir (X_AXIS , st_aux_auto_block.direction_bits[X_AXIS]);
		st_setdir (Y_AXIS , st_aux_auto_block.direction_bits[Y_AXIS]);
		st_setdir (Z_AXIS , st_aux_auto_block.direction_bits[Z_AXIS]);

		T0MR0 = (MM_SEG/2)/st_aux_auto_block.feed_rate[X_AXIS];
		T0MR1 = MM_SEG/st_aux_auto_block.feed_rate[X_AXIS];

		T1MR0 = (MM_SEG/2)/st_aux_auto_block.feed_rate[Y_AXIS];
		T1MR1 = MM_SEG/st_aux_auto_block.feed_rate[Y_AXIS];

		T2MR0 = (MM_SEG/2)/st_aux_auto_block.feed_rate[Z_AXIS];
		T2MR1 = MM_SEG/st_aux_auto_block.feed_rate[Z_AXIS];

		T0MCR  |=  ( 1 << MR0I );
		T0MCR  |=  ( 1 << MR1I );

		T1MCR |=  ( 1 << MR0I ) ;
		T1MCR |=  ( 1 << MR1I ) ;

		T2MCR |=  ( 1 << MR0I ) ;
		T2MCR |=  ( 1 << MR1I ) ;

		st_auto_block = st_aux_auto_block;

		if (st_aux_auto_block.steps[X_AXIS])
			T0TCR = 0x00000001;
		else
			sys.S_Auto.flag_end_block[X_AXIS] = TRUE;

		if (st_aux_auto_block.steps[Y_AXIS])
			T1TCR = 0x00000001;
		else
			sys.S_Auto.flag_end_block[Y_AXIS] = TRUE;

		if (st_aux_auto_block.steps[Z_AXIS])
			T2TCR = 0x00000001;
		else
			sys.S_Auto.flag_end_block[Z_AXIS] = TRUE;
	}
}

/**
	@fn st_move_line(void)
	@brief se fija que eje es el que se va a mover y lo setea
 	@details retorna DONE o UNDONE
 	@return uint8_t
 */

uint8_t st_move_line ( uint8_t axis, uint8_t dir, uint32_t steps, uint16_t feed_rate )
{
	uint8_t aux;

	if ( sys.firstHome)
		aux = 1;
	else
		aux = soft_check_limit(axis, dir, steps);

	if( aux )
	{
		if(axis==X_AXIS)
		{
			st_auto_block.steps[X_AXIS]=steps;
			st_auto_block.direction_bits[X_AXIS]=dir;
			st_setdir(axis,dir);
			T0MR0 = (MM_SEG/2)/feed_rate;
			T0MR1 = MM_SEG/feed_rate;
			T0TCR = 0x00000001;
			T0MCR  |=  ( 1 << MR0I );
			T0MCR  |=  ( 1 << MR1I );
		}
		if(axis==Y_AXIS)
		{
			st_auto_block.steps[Y_AXIS]=steps;
			st_auto_block.direction_bits[Y_AXIS]=dir;
			st_setdir(axis,dir);
			T1MR0 = (MM_SEG/2)/feed_rate;
			T1MR1 = (MM_SEG)/feed_rate;
			T1TCR = 0x00000001;
			T1MCR |=  ( 1 << MR0I ) ;
			T1MCR |=  ( 1 << MR1I ) ;
		}
		if(axis==Z_AXIS)
		{
			st_auto_block.steps[Z_AXIS]=steps;
			st_auto_block.direction_bits[Z_AXIS]=dir;
			st_setdir(axis,dir);
			T2MR0 = (MM_SEG/2)/feed_rate;
			T2MR1 = (MM_SEG)/feed_rate;
			T2TCR = 0x00000001;
			T2MCR |=  ( 1 << MR0I ) ;
			T2MCR |=  ( 1 << MR1I ) ;
		}
		return DONE;
	}

	sys.alarm = SOFT_LIMIT_ERROR_MANUAL;
	return UNDONE;
}

/**
	@fn st_setdir(uint8_t axis, uint8_t dir)
	@brief setea la direccion a los ejes
 	@details  ---
 	@return void
 */

void st_setdir(uint8_t axis,uint8_t dir)
{
	if (axis == X_AXIS)
		SetPIN(XDIR,dir);
	if (axis == Y_AXIS)
		SetPIN(YDIR,dir);
	if (axis == Z_AXIS)
		SetPIN(ZDIR,dir);
}

/**
	@fn stepper_stop(void)
	@brief frena el movimiento de los ejes
 	@details  ---
 	@return void
 */

void stepper_stop(void)
{
	SetPIN( XSTEP , OFF );
	SetPIN( YSTEP , OFF );
	SetPIN( ZSTEP , OFF );
	SetPIN( XEN , st_OFF );
	SetPIN( YEN , st_OFF );
	SetPIN( ZEN , st_OFF );
	T0IR = ( 1 << IRMR0 );
	T0IR = ( 1 << IRMR1 );
	T1IR = ( 1 << IRMR0 );
	T1IR = ( 1 << IRMR1 );
	T2IR = ( 1 << IRMR0 );
	T2IR = ( 1 << IRMR1 );
	st_auto_block.steps[X_AXIS]=0;
	st_auto_block.steps[Y_AXIS]=0;
	st_auto_block.steps[Z_AXIS]=0;
	T0TCR = 0x00000002;
	T1TCR = 0x00000002;
	T2TCR = 0x00000002;
}

/**
	@fn st_wake_up(void)
	@brief habilita los motores
 	@details  logica inversa
 	@return void
 */

void st_wake_up(void)
{
	SetPIN( XEN , st_ON );
	SetPIN( YEN , st_ON );
	SetPIN( ZEN , st_ON );
}


























