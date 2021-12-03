/*
 * rgb_led.h
 *
 *  Created on: 30 nov. 2021
 *      Author: Cedric
 */

#ifndef MODULE_RGB_LED_RGB_LED_H_
#define MODULE_RGB_LED_RGB_LED_H_



typedef enum
{
    RED,
    GREEN,
    BLUE
}ledColor_t;

typedef enum
{
    OFF,
    ON
}ledState_t;


void LED_Init(void);
void RGB_LED_SetState(ledColor_t color, ledState_t state);


#endif /* MODULE_RGB_LED_RGB_LED_H_ */
