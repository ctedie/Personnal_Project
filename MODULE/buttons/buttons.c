/*
 * buttons.c
 *
 *  Created on: 17 déc. 2021
 *      Author: Cedric
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "sound.h"
#include "buttons.h"
#include "music.h"

music_t tJordan
=
{
    .title = "Misuque Jordan\0",
    .BPM = 120,
    .notes = g_ptPapaNoel
};


void BUTTONS_Init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);

    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_1 | GPIO_PIN_2);

    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1 | GPIO_PIN_2, GPIO_FALLING_EDGE);

    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_INT_PIN_1 | GPIO_INT_PIN_2);

    GPIOIntClear(GPIO_PORTL_BASE, GPIO_INT_PIN_1 | GPIO_INT_PIN_2);

    IntEnable(INT_GPIOL);

}

static bool m_bLast = false;
void BUTTONS_Int(void)
{

    SOUND_PlayMusic(&tJordan);

    GPIOIntClear(GPIO_PORTL_BASE, GPIO_INT_PIN_1 | GPIO_INT_PIN_2);
}
