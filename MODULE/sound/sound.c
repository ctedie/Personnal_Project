/*
 * sound.c
 *
 *  Created on: 5 déc. 2021
 *      Author: Cedric
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"

#include "sound.h"


static uint32_t m_temp = 0;
static uint8_t m_ucIndexNote = 0;



music_t tJordan =
{
    .title = "Misuque Jordan\0",
    .BPM = 120,
    .notes = {
        {DO, NOIRE},
        {FA, NOIRE},
        {FA, CROCHE},
        {FA, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {RE, NOIRE},
        {RE, CROCHE},
        {RE, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {MI, NOIRE},
        {MI, CROCHE},
        {MI, CROCHE},
        {PAUSE, NOIRE},
        {DO, NOIRE},
        {FA, NOIRE},
        {FA, CROCHE},
        {FA, CROCHE}
    }
};

uint16_t m_psNotes[] = {DO, RE, MI, FA, SOL, LA, SI};

void NextNote(void);


void SOUND_Init(void)
{

    // Enable the PWM0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Wait for the PWM0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0))
    {
    }

    // Enable the PWM0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Wait for the PWM0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    // Enable the PWM0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

    // Wait for the PWM0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))
    {
    }




    GPIOPinConfigure(GPIO_PF1_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);


    //
    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    //

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
    m_temp = PWMClockGet(PWM0_BASE);

    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 120 MHz clock, this translates to 120000000 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SI);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, SI/2);    //buzzer


    //
    // Start the timers in generator 0.
    //


    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

    // TODO Uncomment for buzzer
    //PWMGenEnable(PWM0_BASE, PWM_GEN_0);






    // Enable the Timer0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Wait for the Timer0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }

    TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_SYSTEM);

    TimerPrescaleSet(TIMER0_BASE, TIMER_A, 30); //environ Une triple croche : 1/(2^3=8) temps


    //
    // Configure TimerA as a half-width one-shot timer, and TimerB as a
    // half-width edge capture counter.
    //
    TimerConfigure(TIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC));
    //
    // Set the count time for the the one-shot timer (TimerA).
    //
    TimerLoadSet(TIMER0_BASE, TIMER_A, 59999);
    //
    // Configure the counter (TimerB) to count both edges.
    //
    TimerControlEvent(TIMER0_BASE, TIMER_B, TIMER_EVENT_BOTH_EDGES);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);


}


static bool bTest = false;

void TimerA_ISR(void)
{
//    if(bTest)
//    {
//        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
//        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, m_psNotes[m_ucIndexNote]);
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, m_psNotes[m_ucIndexNote]/2);    //buzzer
//        PWMGenDisable(PWM0_BASE, PWM_GEN_0);
//        bTest = false;
//    }
//    else
//    {
//        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, m_psNotes[m_ucIndexNote]);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, m_psNotes[m_ucIndexNote]/2);    //buzzer
//        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
        bTest = true;
        NextNote();
//    }

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

static void NextNote(void)
{
    if(m_ucIndexNote >= 6)
    {
        m_ucIndexNote = 0;
    }
    else
    {
        m_ucIndexNote++;
    }
}
