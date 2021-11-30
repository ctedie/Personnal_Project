/*
 * main.c
 *
 *  Created on: 24 nov. 2021
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


static uint8_t m_ucColor = 0;


static uint32_t g_ui32SysClock;

void Init_PWM(void);
void Button_Interrupt(void);
void LED_Init(void);

int main(void)
{

    int32_t val;
    uint32_t ui32Loop;

    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);


    //Init_PWM();
    LED_Init();

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
//    {
//    }
//
//    GPIOIntRegister(GPIO_PORTJ_BASE, Button_Interrupt);
//
//    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
//
//    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
//
//    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
//
//    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
//
//    IntEnable(INT_GPIOJ);
//    IntMasterEnable();
    //PWMGenConfigure(PWM0_BASE, )

    while(1)
    {
        //
        // Turn on the LED.
        //
        RGB_LED_SetState(BLUE, ON);

        //
        // Delay for a bit.
        //
        SysCtlDelay(20000000);
        //
        // Turn off the LED.
        //
        RGB_LED_SetState(BLUE, OFF);

        //
        // Delay for a bit.
        //
        SysCtlDelay(20000000);


//        val = GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0);
    }

}


void Button_Interrupt(void)
{

    m_ucColor++;
    if(m_ucColor >= 8)
    {
        m_ucColor = 0;
    }

    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
}

void Init_PWM(void)
{
    //
    // Enable the PWM0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);

    ///
    // Wait for the PWM0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {
    }
    //
    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    //
    //PWMGenConfigure(PWM0_BASE PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 20 MHz clock, this translates to 400 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 400);

    //
    // Set the pulse width of PWM0 for a 25% duty cycle.
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 100);

    //
    // Set the pulse width of PWM1 for a 75% duty cycle.
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 300);

    //
    // Start the timers in generator 0.
    //
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    //
    // Enable the outputs.
    //
    PWMOutputState(PWM0_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), true);

}
