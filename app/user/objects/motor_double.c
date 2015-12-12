/*
 * motor_double.c
 *
 *  Created on: 2015Äê12ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "../../pando/pando_object.h"
#include "c_types.h"
#include "user_interface.h"
#include "motor_double.h"
#include "../../peripheral/peri_motor_double.h"
//#include "../../peripheral/driver/pwm.h"
// add your own includes below



struct motor_double {
	int8 speed;
};
void ICACHE_FLASH_ATTR
motor_double_init() {
	// TODO: add your object init code here.
	peri_motor_double_init();

}
void ICACHE_FLASH_ATTR
motor_double_set(struct motor_double* value) {
	// TODO: implement object set function here.
	// the set function read value and operate the hardware.
	struct PWM_APP_PARAM motor_param;
	motor_param.pwm_freq=25000;

	if(value->speed < 0)
	{
		set_dd_car_backward();
		motor_param.pwm_duty[0]= (0-(1 +value->speed))*2;
		motor_param.pwm_duty[1]= (0-(1 + value->speed))*2;
		dd_car_state.speed = (0-(1 + value->speed))*2;
		dd_car_state.direction =  dd_backward;
	}
	else
	{
		set_dd_car_forward();
		motor_param.pwm_duty[0]= (value->speed)*2;
		motor_param.pwm_duty[1]= (value->speed)*2;
		dd_car_state.speed = (value->speed)*2;
		dd_car_state.direction = dd_forward;
	}

	PRINTF("\n steer wheel speed:%d, general speed:%d\n",value->speed, dd_car_state.speed);
	peri_motor_double_set(motor_param);

}
void ICACHE_FLASH_ATTR
motor_double_get(struct motor_double* value) {
	// TODO: implement object get  function here
	// get function retrieve hardware status and assign it to value.


}
/*
	auto generated code below!!
	DO NOT edit unless you know how it works.
*/
struct motor_double* ICACHE_FLASH_ATTR
create_motor_double() {
	struct motor_double* motor_double = (struct motor_double*)os_malloc(sizeof(motor_double));
	return motor_double;
}
void ICACHE_FLASH_ATTR
delete_motor_double(struct motor_double* motor_double) {
	if(motor_double){
		os_free(motor_double);
	}
}
void ICACHE_FLASH_ATTR
motor_double_object_pack(PARAMS * params) {
	if(NULL == params){
		PRINTF("Create first tlv param failed.\n");
		return;
	}

	struct motor_double* motor_double = create_motor_double();
	motor_double_get(motor_double);

	if (add_next_int8(params, motor_double->speed)){
		PRINTF("Add next param failed.\n");
		return;
	}

	delete_motor_double(motor_double);
}
void ICACHE_FLASH_ATTR
motor_double_object_unpack(PARAMS* params) {
	struct motor_double* motor_double = create_motor_double();

	motor_double->speed = get_next_int8(params);

	motor_double_set(motor_double);
	delete_motor_double(motor_double);
}
void ICACHE_FLASH_ATTR
motor_double_object_init() {
	motor_double_init();
	pando_object motor_double_object = {
		1,
		motor_double_object_pack,
		motor_double_object_unpack,
	};
	register_pando_object(motor_double_object);
}



