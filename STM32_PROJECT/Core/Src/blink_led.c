/*
 * blink_led.c
 *
 *  Created on: Nov 24, 2023
 *      Author: than
 */

#include "blink_led.h"

void blink_led_every_500ms(){
	HAL_GPIO_TogglePin(LED_0_GPIO_Port, LED_0_Pin);
}
void blink_led_every_1000ms(){
	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}
void blink_led_every_1500ms(){
	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
}
void blink_led_every_2000ms(){
	HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
}
void blink_led_every_2500ms(){
	HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
}
