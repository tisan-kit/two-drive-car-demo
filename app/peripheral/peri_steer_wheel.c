/*
 * peri_steer_wheel.c
 *
 *  Created on: 2015Äê12ÔÂ9ÈÕ
 *      Author: Administrator
 */

#include "peri_steer_wheel.h"
#include "driver/gpio.h"
#include "driver/tisan_gpio.h"
#include "eagle_soc.h"
#include "driver/uart.h"
#include "driver/gpio16.h"

#define PIN_AIN1    13
#define PIN_AIN2	14
#define PIN_BIN1	4
#define PIN_BIN2	2

#define SET_PIN_AIN1(x)		GPIO_OUTPUT_SET(PIN_AIN1, x)
#define SET_PIN_AIN2(x)		GPIO_OUTPUT_SET(PIN_AIN2, x)
#define SET_PIN_BIN1(x)		GPIO_OUTPUT_SET(PIN_BIN1, x)
#define SET_PIN_BIN2(x)		GPIO_OUTPUT_SET(PIN_BIN2, x)

static uint8 ain1 = 0;
static uint8 ain2 = 0;
static uint8 bin1 = 0;
static uint8 bin2 = 0;

struct DD_CAR_STATE dd_car_state = {0,dd_forward};

void ICACHE_FLASH_ATTR
set_dd_car_forward(void)
{
	SET_PIN_AIN1(0);
	SET_PIN_AIN2(1);
	SET_PIN_BIN1(0);
	SET_PIN_BIN2(1);
}

void ICACHE_FLASH_ATTR
set_dd_car_backward(void)
{
	SET_PIN_AIN1(1);
	SET_PIN_AIN2(0);
	SET_PIN_BIN1(1);
	SET_PIN_BIN2(0);
}

void ICACHE_FLASH_ATTR
set_dd_car_turn_left(void)
{
	SET_PIN_AIN1(0);
	SET_PIN_AIN2(0);
	SET_PIN_BIN1(0);
	SET_PIN_BIN2(1);
}

void ICACHE_FLASH_ATTR
set_dd_car_turn_right(void)
{
	SET_PIN_AIN1(0);
	SET_PIN_AIN2(1);
	SET_PIN_BIN1(0);
	SET_PIN_BIN2(0);
}

void ICACHE_FLASH_ATTR
set_dd_car_stop(void)
{
	SET_PIN_AIN1(0);
	SET_PIN_AIN2(0);
	SET_PIN_BIN1(0);
	SET_PIN_BIN2(0);
}

void ICACHE_FLASH_ATTR
set_dd_car_direction(enum DD_DIRECTION direction)
{
	switch(direction)
	{
	case dd_forward:	set_dd_car_forward();
		break;
	case dd_backward:	set_dd_car_backward();
		break;
	case dd_left:	set_dd_car_turn_left();
		break;
	case dd_right:	set_dd_car_turn_right();
		break;
	default:	set_dd_car_stop();
		break;
	}
}

void ICACHE_FLASH_ATTR
peri_steer_wheel_init(void)
{
//    PRINTF("I am the dd_car direction_gpio\n");

	PIN_FUNC_SELECT(tisan_get_gpio_name(PIN_AIN1), tisan_get_gpio_general_func(PIN_AIN1));
	PIN_PULLUP_EN(tisan_get_gpio_name(PIN_AIN1));

	PIN_FUNC_SELECT(tisan_get_gpio_name(PIN_AIN2), tisan_get_gpio_general_func(PIN_AIN2));
	PIN_PULLUP_EN(tisan_get_gpio_name(PIN_AIN2));

	PIN_FUNC_SELECT(tisan_get_gpio_name(PIN_BIN1), tisan_get_gpio_general_func(PIN_BIN1));
	PIN_PULLUP_EN(tisan_get_gpio_name(PIN_BIN1));

	PIN_FUNC_SELECT(tisan_get_gpio_name(PIN_BIN2), tisan_get_gpio_general_func(PIN_BIN2));
	PIN_PULLUP_EN(tisan_get_gpio_name(PIN_BIN2));


	set_dd_car_forward();

}
