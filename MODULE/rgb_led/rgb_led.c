/*
 * rgb_led.c
 *
 *  Created on: 30 nov. 2021
 *      Author: Cedric
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "rgb_led.h"

#define RED_LED_PIN         GPIO_PIN_2
#define GREEN_LED_PIN       GPIO_PIN_3
#define BLUE_LED_PIN        GPIO_PIN_0

#define RED_LED_PORT        GPIO_PORTF_BASE
#define GREEN_LED_PORT      GPIO_PORTF_BASE
#define BLUE_LED_PORT       GPIO_PORTG_BASE


void LED_Init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))
    {
    }

    GPIOPinTypeGPIOOutput(RED_LED_PORT, RED_LED_PIN | GREEN_LED_PIN); //LED verte et rouge sur le même port
    GPIOPinTypeGPIOOutput(BLUE_LED_PORT, BLUE_LED_PIN);


}

void RGB_LED_SetState(ledColor_t color, ledState_t state)
{

    uint32_t ulPort;
    uint8_t ucPin, ucVal;

    switch (color)
    {
        case RED:
            ulPort = RED_LED_PORT;
            ucPin = RED_LED_PIN;
            if(state == ON)
            {
                ucVal = RED_LED_PIN;
            }
            else
            {
                ucVal = 0;
            }
            break;
        case GREEN:
            ulPort = GREEN_LED_PORT;
            ucPin = GREEN_LED_PIN;
            if(state == ON)
            {
                ucVal = GREEN_LED_PIN;
            }
            else
            {
                ucVal = 0;
            }
            break;
        case BLUE:
            ulPort = BLUE_LED_PORT;
            ucPin = BLUE_LED_PIN;
            if(state == ON)
            {
                ucVal = BLUE_LED_PIN;
            }
            else
            {
                ucVal = 0;
            }
            break;
            default:
                return;
                break;
     }

    GPIOPinWrite(ulPort, ucPin, ucVal);
}







