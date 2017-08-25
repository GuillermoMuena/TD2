#include "Aplicacion.h"

extern uint8_t buff_empty;
settings_t settings;
volatile plan_block_t plan_block_buffer[BUFF_TAM];
uint8_t buff_in = 0, buff_out = 0;

/**
	@fn uint8_t plan_move_manual(void)
	@brief Mira que eje debe mover y en que direccion
 	@details Si no se pudo retorna undone
 	@return uint8_t
 */

uint8_t plan_move_manual(void)
{
	switch(sys.manual_key)
	{
	case key_XR:
		if(!st_move_line( X_AXIS, CW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case key_XL:
		if(!st_move_line( X_AXIS, CCW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case key_YR:
		if(!st_move_line( Y_AXIS, CW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case key_YL:
		if(!st_move_line( Y_AXIS, CCW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case key_ZD:
		if(!st_move_line( Z_AXIS, CW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case key_ZU:
		if(!st_move_line( Z_AXIS, CCW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case NO_KEY:
		stepper_stop();
		return DONE;
		break;
	}
	return DONE;
}

/**
	@fn uint8_t plan_move_serial_manual(void)
	@brief Mira que eje debe mover y en que direccion
 	@details Si no se pudo retorna undone
 	@return uint8_t
 */

uint8_t plan_move_serial_manual(void)
{
	switch(sys.manual_serial)
	{
	case Ser_XR:
		if(!st_move_line( X_AXIS, CW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case Ser_XL:
		if(!st_move_line( X_AXIS, CCW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case Ser_YR:
		if(!st_move_line( Y_AXIS, CW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case Ser_YL:
		if(!st_move_line( Y_AXIS, CCW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case Ser_ZD:
		if(!st_move_line( Z_AXIS, CW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case Ser_ZU:
		if(!st_move_line( Z_AXIS, CCW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case Ser_XR_PRESS:
		if(!st_move_line( X_AXIS, CW, DEFAULT_X_MAX_TRAVEL - sys.position[X_AXIS]  , settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case Ser_XL_PRESS:
		if(!st_move_line( X_AXIS, CCW,  DEFAULT_X_MAX_TRAVEL - sys.position[X_AXIS] , settings.def_feed_rate[X_AXIS]))
			return UNDONE;
		break;

	case Ser_YR_PRESS:
		if(!st_move_line( Y_AXIS, CW,  DEFAULT_X_MAX_TRAVEL - sys.position[Y_AXIS] , settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case Ser_YL_PRESS:
		if(!st_move_line( Y_AXIS, CCW,  DEFAULT_X_MAX_TRAVEL - sys.position[Y_AXIS] , settings.def_feed_rate[Y_AXIS]))
			return UNDONE;
		break;

	case Ser_ZD_PRESS:
		if(!st_move_line( Z_AXIS, CW, DEFAULT_Z_MAX_TRAVEL - sys.position[Z_AXIS] , settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case Ser_ZU_PRESS:
		if(!st_move_line( Z_AXIS, CCW, DEFAULT_Z_MAX_TRAVEL - sys.position[Z_AXIS] , settings.def_feed_rate[Z_AXIS]))
			return UNDONE;
		break;

	case Ser_BUTTONS_RELEASED:
		stepper_stop();
		break;

	case NO_KEY:
		stepper_stop();
		break;
	}
	sys.manual_serial = NO_KEY;
	return DONE;
}

/**
	@fn uint8_t mc_line(void)
	@brief Carga la velocidad, direccion y cantidad de pasos en plan_block_buffer
 	@details Buffer circular
 	@return uint8_t
 */

uint8_t mc_line( float *xyz, float feed_rate, uint8_t feed_rate_mode)
{
	plan_block_t  pl_block_aux;
	float valorxyz;
	uint8_t i;
	memset(&pl_block_aux,0,sizeof(pl_block_aux));

	for ( i=0 ; i<N_AXIS; i++)
	{

		valorxyz=xyz[i];
		if ( feed_rate_mode == FEED_RATE_MODE_UNITS_PER_MIN )
			pl_block_aux.feed_rate[i] = feed_rate;
		if ( feed_rate_mode == FEED_RATE_MODE_INVERSE_TIME )
			pl_block_aux.feed_rate[i] =  1/feed_rate;

		pl_block_aux.steps[i] = (int)(xyz[i] * (float)settings.steps_per_mm[i]);
		if(i==Z_AXIS)
		{
			if (pl_block_aux.steps[i]  >= 0)
				pl_block_aux.direction_bits[i] = CCW;
			else
			{
				pl_block_aux.direction_bits[i] = CW;
				pl_block_aux.steps[i]  *= -1;
			}
		}
		else
		{
			if (pl_block_aux.steps[i]  >= 0)
				pl_block_aux.direction_bits[i] = CW;
			else
			{
				pl_block_aux.direction_bits[i] = CCW;
				pl_block_aux.steps[i]  *= -1;
			}
		}

		if ( !soft_check_limit ( i, pl_block_aux.direction_bits[i], pl_block_aux.steps[i]))
		{
			switch(i)
			{
			case X_AXIS:
				sys.alarm = SOFT_LIMIT_ERROR_X;
				break;
			case Y_AXIS:
				sys.alarm = SOFT_LIMIT_ERROR_Y;
				break;
			case Z_AXIS:
				sys.alarm = SOFT_LIMIT_ERROR_Z;
				break;
			}
		}

		if (pl_block_aux.steps[i]  >= 0)
			sys.planner_position[i]+=pl_block_aux.steps[i];
		else
			sys.planner_position[i]-=pl_block_aux.steps[i];

	}

	asignar_velocidades(&pl_block_aux);
	plan_block_buffer[buff_in] = pl_block_aux;
	buff_in++;
	buff_in %= BUFF_TAM;
	buff_empty = FALSE;

	return DONE;
}

/**
	@fn uint8_t goHome (void)
	@brief Mueve los ejes al valor seteado como "home"
 	@details
 	@return uint8_t
 */

uint8_t goHome(void)
{
	uint8_t flag=0;
	st_wake_up();


	if (sys.manual_serial == Ser_GO_HOME )
	{

		if (st_move_line( Z_AXIS, CW, sys.position[Z_AXIS], settings.def_feed_rate[Z_AXIS]))
			sys.planner_position[Z_AXIS]=0;
		else
			flag = 1;
	}

	if (st_move_line( X_AXIS, CCW, sys.position[X_AXIS], settings.def_feed_rate[X_AXIS]))
		sys.planner_position[X_AXIS]=0;
	else
		flag = 1;

	if (st_move_line( Y_AXIS, CCW, sys.position[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
		sys.planner_position[Y_AXIS]=0;
	else
		flag = 1;

	if (flag)
	{
		sys.alarm = GO_HOME_ERROR;
		return UNDONE;
	}

	return DONE;
}

/**
	@fn uint8_t setHome(void)
	@brief Setea "home" en el lugar actual de los ejes
 	@details Actualiza la posicion de sys y planner
 	@return uint8_t
 */

uint8_t setHome(void)
{
	uint8_t teclaAux, Flag_firsthome[4] = {FALSE,FALSE,FALSE,FALSE};

	if ( sys.manual_serial != NO_KEY)
		teclaAux = sys.manual_serial;
	if ( sys.manual_key != NO_KEY)
		teclaAux = sys.manual_key;

	switch (teclaAux)
	{
	case Ser_SET_ZERO_ALL:
		memset (sys.planner_position,0,sizeof(sys.planner_position));
		memset (sys.position,0,sizeof(sys.position));
		Flag_firsthome[0] = TRUE;
		break;
	case Ser_SET_ZERO_X:
		memset (&sys.planner_position[X_AXIS],0,sizeof(sys.planner_position[X_AXIS]));
		memset (&sys.position[X_AXIS],0,sizeof(sys.position[X_AXIS]));
		Flag_firsthome[1] = TRUE;
		break;
	case Ser_SET_ZERO_Y:
		memset (&sys.planner_position[Y_AXIS],0,sizeof(sys.planner_position[Y_AXIS]));
		memset (&sys.position[Y_AXIS],0,sizeof(sys.position[Y_AXIS]));
		Flag_firsthome[2] = TRUE;
		break;
	case Ser_SET_ZERO_Z:
		memset (&sys.planner_position[Z_AXIS],0,sizeof(sys.planner_position[Z_AXIS]));
		memset (&sys.position[Z_AXIS],0,sizeof(sys.position[Z_AXIS]));
		Flag_firsthome[3] = TRUE;
		break;
	}

	if ( Flag_firsthome[1] && Flag_firsthome[2] && Flag_firsthome[3]) //<! sys.firstHome habilita o deshabilita soft_check_limits();
		sys.firstHome = 0;
	if (Flag_firsthome[0])
		sys.firstHome = 0;

	return DONE;
}

/**
	@fn void mc_arc( float *position, float *target, float *ijk, float r, float feed_rate,
		uint8_t feed_rate_mode, uint8_t axis_0, uint8_t axis_1, uint8_t axis_linear, uint8_t is_clockwise_arc)
	@brief  discretiza un arco y pasa cada segmento a mc_line()
 	@details Considera en que cuadrante es el arco
 	@return void
 */

void mc_arc( float *position, float *target, float *ijk, float r, float feed_rate,
		uint8_t feed_rate_mode, uint8_t axis_0, uint8_t axis_1, uint8_t axis_linear, uint8_t is_clockwise_arc)
{
	float delta_0, delta_1, radius, start_angle, finish_angle, sweep,len_arc, sweeping_angle, fraction;
	float pointB_act[N_AXIS], pointB_ant[N_AXIS]={0,0,0},delta[N_AXIS]={0,0,0};
	int num_segments;
	uint8_t i;

	delta_0 = position[axis_0] - ijk[axis_0];
	delta_1 = position[axis_1] - ijk[axis_1];

	radius = sqrt(delta_0*delta_0 + delta_1*delta_1);

	start_angle = atan3_t(delta_1,delta_0);
	finish_angle = atan3_t( (target[axis_1]-ijk[axis_1]), (target[axis_0]-ijk[axis_0]));

	sweep = finish_angle-start_angle;

	if(is_clockwise_arc && sweep<0)
		finish_angle+=2*PI;
	else if(!is_clockwise_arc && sweep>0)
		start_angle+=2*PI;

	sweep = finish_angle - start_angle;

	len_arc = sweep * radius;
	if(len_arc<0)
		len_arc*=(-1);
	num_segments = floor( len_arc / MM_PER_SEGMENT );

	pointB_act[axis_linear]=0;

	for(i=0; i<num_segments; ++i)
	{
		fraction = ((float)i/(float)num_segments);
		sweeping_angle = ( sweep * fraction ) + start_angle;

		pointB_act[axis_0] = ijk[axis_0] + cos(sweeping_angle) * radius ;
		pointB_act[axis_1] = ijk[axis_1] + sin(sweeping_angle) * radius ;

		delta[axis_0] = pointB_act[axis_0] - pointB_ant[axis_0];
		delta[axis_1] = pointB_act[axis_1] - pointB_ant[axis_1];

		pointB_ant[axis_0] = pointB_act[axis_0];
		pointB_ant[axis_1] = pointB_act[axis_1];

		mc_line ( delta, feed_rate, feed_rate_mode );
	}
}

/**
	@fn uint8_t pl_ckeck_buffer (void)
	@brief  compara los buffers
 	@details devuelve 1 o 0
 	@return uint8_t
 */

uint8_t pl_ckeck_buffer (void){

	uint8_t i=1;
	if (i)
	{
		return TRUE;
		i=0;
	}
	if ( buff_in != buff_out)
		return TRUE;

	return FALSE;
}

/**
	@fn  void pl_init (void)
	@brief  llama a memset y pone los buffers en cero
 	@details  ---
 	@return void
 */

void pl_init (void){

	memset(plan_block_buffer,0,sizeof(plan_block_buffer));
	buff_in = buff_out = 0;
}

/**
	@fn void splindle_control (uint8_t spinlde)
	@brief  controla el estado del spindle
 	@details  --
 	@return void
 */

void splindle_control (uint8_t spindle)
{
	if (spindle == SPINDLE_ENABLE)
	{
		SetPIN(SPINDLE_PIN, ON);
	}
	else
	{
		SetPIN(SPINDLE_PIN, OFF);
	}
}

/*
 *	@fn  void asignar_velocidades ( plan_block_t* pl_block_aux )
 *	@brief Asigna velocidades a cada eje
 *  @details Al manejar cada motor individualmente es necesario asignar
 *  velocidades diferentes a cada uno para trazar una diagonal
 *  @return void
 */

void asignar_velocidades ( plan_block_t* pl_block_aux ){

	uint8_t axis_0, axis_1, axis_linear;
	long int deltaA, deltaB, velA, velB, velocidad;

	velocidad = pl_block_aux->feed_rate[0];

	if (pl_block_aux->steps[X_AXIS] != 0 && pl_block_aux->steps[Y_AXIS] != 0 && pl_block_aux->steps[Z_AXIS] != 0 )
	{
		velA = velB = velocidad;
	}
	else
	{
		if (pl_block_aux->steps[X_AXIS] == 0)
		{
			axis_0 = Y_AXIS;
			axis_1 = Z_AXIS;
			axis_linear = X_AXIS;
		}
		if (pl_block_aux->steps[Y_AXIS] == 0)
		{
			axis_0 = Z_AXIS;
			axis_1 = X_AXIS;
			axis_linear = Y_AXIS;
		}
		if (pl_block_aux->steps[Z_AXIS] == 0)
		{
			axis_0 = X_AXIS;
			axis_1 = Y_AXIS;
			axis_linear = Z_AXIS;
		}

		deltaA = (pl_block_aux->steps[axis_0]);
		deltaB = (pl_block_aux->steps[axis_1]);

		if ( deltaB > deltaA )
		{
			velB = velocidad;
			velA = (int) ((deltaA * velB)/deltaB);
		}
		if ( deltaA > deltaB )
		{
			velA = velocidad;
			velB = (int) ((deltaB * velA)/deltaA);
		}
		if (deltaA==deltaB)
			velA=velB=velocidad;
	}

	pl_block_aux->feed_rate[axis_0]= velA;
	pl_block_aux->feed_rate[axis_1]= velB;
	pl_block_aux->feed_rate[axis_linear]= velocidad;
}

/**
	@fn double atan2_t(double y, double x)
	@brief
 	@details traida de math.h
 	@return double
 */

double atan2_t(double y, double x)
{
	double absx, absy, val;

	if (x == 0 && y == 0) {
		return 0;
	}

	absy = y < 0 ? -y : y;
	absx = x < 0 ? -x : x;
	if (absy - absx == absy)
	{
		return y < 0 ? -M_PI_2 : M_PI_2;
	}
	if (absx - absy == absx)
	{
		val = 0.0;
	}
	else    val = atan(y/x);

	if (x > 0)
	{
		return val;
	}
	if (y < 0)
	{
		return val - M_PI;
	}
	return val + M_PI;
}

/**
	@fn atan3_t (float dy , float dx)
	@brief
 	@details diferencia cuadrante
 	@return float
 */

float atan3_t ( float dy, float dx )
{
	float a=atan2(dy,dx);

	if(a<0) a=(PI*2.0)+a;

	return a;
}








