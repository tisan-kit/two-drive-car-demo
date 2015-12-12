/*
 * peri_steer_wheel.h
 *
 *  Created on: 2015Äê12ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef APP_PERIPHERAL_PERI_STEER_WHEEL_H_
#define APP_PERIPHERAL_PERI_STEER_WHEEL_H_

#include "c_types.h"
#include "driver/pwm.h"
#include "peri_global.h"

extern uint8 g_motor_speed;


enum DD_DIRECTION{ dd_forward, dd_backward, dd_left, dd_right} dd_diection;

struct DD_CAR_STATE
{
	uint8 speed;
	enum DD_DIRECTION direction;   //1: forward; 2:backward; 3:left; 4:right;
};
extern struct DD_CAR_STATE dd_car_state;

void peri_steer_wheel_init(void);
void set_dd_car_forward(void);
void set_dd_car_backward(void);
void set_dd_car_turn_left(void);
void set_dd_car_turn_right(void);
void set_dd_car_stop(void);
void set_dd_car_direction(enum DD_DIRECTION direction);

#endif /* APP_PERIPHERAL_PERI_STEER_WHEEL_H_ */
