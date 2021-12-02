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
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"

//#include "rgb_led.h"


static uint8_t m_ucColor = 0;


static uint32_t g_ui32SysClock;

void Init_PWM(void);
void Button_Interrupt(void);
void LED_Init(void);
void Init_Systick(void);

int main(void)
{

    int32_t val;
    uint32_t ui32Loop;

    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);


    Init_PWM();
    //LED_Init();
//    Init_Systick();


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
//
//    GPIOIntRegister(GPIO_PORTJ_BASE, Button_Interrupt);
//
//
//    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
//
//    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
//
//    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
//
//    IntEnable(INT_GPIOJ);
    IntEnable(INT_PWM0_1);
    IntMasterEnable();
    //PWMGenConfigure(PWM0_BASE, )

    while(1)
    {
        //
        // Turn on the LED.
        //
        //RGB_LED_SetState(BLUE, ON);

        //
        // Delay for a bit.
        //
        SysCtlDelay(20000000);
        //
        // Turn off the LED.
        //
        //RGB_LED_SetState(BLUE, OFF);

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

    //
    // Wait for the PWM0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {
    }
    //
    // Enable the PWM0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Wait for the PWM0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }




    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PF2_M0PWM2);




    //
    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    //

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 120 MHz clock, this translates to 120000000 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 12000000 );

    //
    // Set the pulse width of PWM2 for a 501% duty cycle.
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 6000000);
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 00100000);
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 11900000);


    //
    // Enable the outputs.
    //
    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);


    //
    // Start the timers in generator 0.
    //

    PWMGenEnable(PWM0_BASE, PWM_GEN_1);

    PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_1, PWM_INT_CNT_AD);

    PWMIntEnable(PWM0_BASE, PWM_INT_GEN_1);


}

void Init_Systick(void)
{
    uint32_t ui32Value;
    //
    // Configure and enable the SysTick counter.
    //
    SysTickPeriodSet(120000);
    SysTickIntEnable();
    SysTickEnable();
    //
    // Delay for some time...
    //
    //
    // Read the current SysTick value.
    //
    ui32Value = SysTickValueGet();

}

static uint32_t ulCntTick = 0;
bool bTest = false;
void SystickISR(void)
{

    ulCntTick++;
    if(ulCntTick >= 999)
    {
        ulCntTick = 0;
        if(bTest)
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            bTest = false;
        }
        else
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            bTest = true;
        }

    }

}

void PWMISR(void)
{
    uint32_t uiITState;
    uint32_t state2;

    state2 = PWMIntStatus(PWM0_BASE, true);
    uiITState = PWMGenIntStatus(PWM0_BASE, PWM_GEN_1, true);

    if(bTest == true)
    {
        PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
        bTest = false;
    }
    else if(bTest == false)
    {
        PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
        bTest = true;
    }

    PWMGenIntClear(PWM0_BASE, PWM_GEN_1, uiITState);
}
