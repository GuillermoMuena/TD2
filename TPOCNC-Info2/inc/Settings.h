/*
 * Settings.h
 *
 *  Created on: 29/10/2015
 *      Author: Julieta
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

typedef struct
{
  float steps_per_mm[N_AXIS];
  float max_feed_rate[N_AXIS];
  float max_travel_steps[N_AXIS];
  uint8_t work_plane;
  uint8_t units;
  float def_feed_rate[N_AXIS];
  float manual_steps[N_AXIS];
  uint8_t def_motion_mode;          // lineal, arco
  uint8_t def_distance_mode;        // abs, incremental
  uint8_t spindle;
  uint8_t def_feedrate_mode;
} settings_t;

extern settings_t settings;

void settings_restore_global_settings();


//!<  Grbl generic default settings. Should work across different machines.
#define DEFAULT_X_STEPS_PER_MM 	PASOSXY_MM
#define DEFAULT_Y_STEPS_PER_MM 	PASOSXY_MM
#define DEFAULT_Z_STEPS_PER_MM 	PASOSZ_MM
#define DEFAULT_X_MAX_RATE CIEN_MM_SEG
#define DEFAULT_Y_MAX_RATE CIEN_MM_SEG
#define DEFAULT_Z_MAX_RATE 50.0
#define DEFAULT_X_MAX_TRAVEL 1000 * PASOSXY_MM	// = 80000 pasos = 40 cm
#define DEFAULT_Y_MAX_TRAVEL 1000 * PASOSXY_MM
#define DEFAULT_Z_MAX_TRAVEL 50 * PASOSZ_MM
#define DEFAULT_PLANE PLANE_SELECT_XY
#define DEFAULT_UNITS UNITS_MODE_MM
#define	DEFAULT_FEEDRATE_XY		DIEZ_MM_SEG
#define	DEFAULT_FEEDRATE_Z		VEINTE_MM_SEG
#define DEFAULT_MANUAL_STEPS_XY	PASOSXY_MM
#define DEFAULT_MANUAL_STEPS_Z	PASOSZ_MM
#define DEFAUL_MOTION_MODE		MOTION_MODE_NONE
#define DEFAUL_DISTANSCE_MODE	DISTANCE_MODE_INCREMENTAL
#define DEFAULT_SPINDLE_MODE	SPINDLE_DISABLE
#define DEFAULT_FEEDRATE_MODE	FEED_RATE_MODE_UNITS_PER_MIN

#endif /* INC_SETTINGS_H_ */





















