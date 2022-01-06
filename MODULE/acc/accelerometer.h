/*
 * accelerometer.h
 *
 *  Created on: 17 déc. 2021
 *      Author: Cedric
 */

#ifndef MODULE_ACC_ACCELEROMETER_H_
#define MODULE_ACC_ACCELEROMETER_H_

#include <stdint.h>



void ACCELEROMETER_Init(void);
uint32_t ACCELEROMETER_GetX(void);
uint32_t ACCELEROMETER_GetY(void);
uint32_t ACCELEROMETER_GetZ(void);

#endif /* MODULE_ACC_ACCELEROMETER_H_ */
