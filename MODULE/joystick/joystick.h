/*
 * joystick.h
 *
 *  Created on: 17 déc. 2021
 *      Author: Cedric
 */
#include <stdint.h>

#ifndef MODULE_JOYSTICK_JOYSTICK_H_
#define MODULE_JOYSTICK_JOYSTICK_H_

void JOYSTICK_Init(void);
uint32_t JOYSTICK_GetXValue(void);
uint32_t JOYSTICK_GetYValue(void);

#endif /* MODULE_JOYSTICK_JOYSTICK_H_ */
