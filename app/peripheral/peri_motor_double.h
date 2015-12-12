/*
 * peri_motor_double.h
 *
 *  Created on: 2015Äê12ÔÂ9ÈÕ
 *      Author: Administrator
 */

#ifndef APP_PERIPHERAL_PERI_MOTOR_DOUBLE_H_
#define APP_PERIPHERAL_PERI_MOTOR_DOUBLE_H_
#include "c_types.h"
#include "driver/pwm.h"
#include "peri_global.h"
#include "peri_steer_wheel.h"

void peri_motor_double_init(void);
struct PWM_APP_PARAM peri_motor_double_get(void);
void peri_motor_double_set( struct PWM_APP_PARAM motor_param);

#endif /* APP_PERIPHERAL_PERI_MOTOR_DOUBLE_H_ */
