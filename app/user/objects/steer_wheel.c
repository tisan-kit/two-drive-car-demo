/*
 * steer_wheel.c
 *
 *  Created on: 2015Äê12ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "../../pando/pando_object.h"
#include "c_types.h"
#include "user_interface.h"
#include "steer_wheel.h"
#include "../../peripheral/peri_steer_wheel.h"
// add your own includes below


struct steer_wheel {
	int8 speed;
};
void ICACHE_FLASH_ATTR
steer_wheel_init() {
	// TODO: add your object init code here.
	peri_steer_wheel_init();

}
void ICACHE_FLASH_ATTR
steer_wheel_set(struct steer_wheel* value) {
	// TODO: implement object set function here.
	// the set function read value and operate the hardware.
	struct PWM_APP_PARAM motor_param;
	motor_param.pwm_freq=25000;

	if(value->speed == 0)
	{
		set_dd_car_direction(dd_car_state.direction);

		motor_param.pwm_duty[0]=dd_car_state.speed;
		motor_param.pwm_duty[1]=dd_car_state.speed;
	}
	else if(value->speed < 0)
	{
		//	set_dd_car_turn_left();

		if(dd_car_state.speed/2 <= (0-(1 + value->speed)))
		{
			motor_param.pwm_duty[1] = 0;
		}
		else
		{
			motor_param.pwm_duty[1] = (dd_car_state.speed/2 + value->speed + 1)*2;
		}
		motor_param.pwm_duty[0]=dd_car_state.speed;
	}
	else
	{
		//set_dd_car_turn_right();
		if(dd_car_state.speed/2 <= value->speed)
		{
			motor_param.pwm_duty[0] = 0;
		}
		else
		{
			motor_param.pwm_duty[0] = (dd_car_state.speed/2 - value->speed)*2;
		}

		motor_param.pwm_duty[1]=dd_car_state.speed;

	}

	PRINTF("\n steer wheel speed:%d, general speed:%d\n",value->speed,dd_car_state.speed );
	peri_motor_double_set(motor_param);

}

void ICACHE_FLASH_ATTR
steer_wheel_get(struct steer_wheel* value) {
	// TODO: implement object get  function here
	// get function retrieve hardware status and assign it to value.


}
/*
	auto generated code below!!
	DO NOT edit unless you know how it works.
*/
struct steer_wheel* ICACHE_FLASH_ATTR
create_steer_wheel() {
	struct steer_wheel* steer_wheel = (struct steer_wheel*)os_malloc(sizeof(steer_wheel));
	return steer_wheel;
}
void ICACHE_FLASH_ATTR
delete_steer_wheel(struct steer_wheel* steer_wheel) {
	if(steer_wheel){
		os_free(steer_wheel);
	}
}
void ICACHE_FLASH_ATTR
steer_wheel_object_pack(PARAMS * params) {
	if(NULL == params){
		PRINTF("Create first tlv param failed.\n");
		return;
	}

	struct steer_wheel* steer_wheel = create_steer_wheel();
	steer_wheel_get(steer_wheel);

	if (add_next_int8(params, steer_wheel->speed)){
		PRINTF("Add next param failed.\n");
		return;
	}

	delete_steer_wheel(steer_wheel);
}
void ICACHE_FLASH_ATTR
steer_wheel_object_unpack(PARAMS* params) {
	struct steer_wheel* steer_wheel = create_steer_wheel();

	steer_wheel->speed = get_next_int8(params);

	steer_wheel_set(steer_wheel);
	delete_steer_wheel(steer_wheel);
}
void ICACHE_FLASH_ATTR
steer_wheel_object_init() {
	steer_wheel_init();
	pando_object steer_wheel_object = {
		2,
		steer_wheel_object_pack,
		steer_wheel_object_unpack,
	};
	register_pando_object(steer_wheel_object);
}



