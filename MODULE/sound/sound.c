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

extern music_t tJordan;


uint16_t m_psNotes[] = {DO, RE, MI, FA, SOL, LA, SI};
music_t *m_MtusicInProgress;
static void NextNote(void);
void Interruption(void);
static void CalculITRestante(music_t *tMusic);

static void IT_TEST(void);



void SOUND_Init(void)
{

    m_MtusicInProgress = &tJordan;
    SOUND_bPlaying = false;

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
//    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, DO);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1);    //buzzer


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
    TimerLoadSet(TIMER0_BASE, TIMER_A, 28999/*59999*/);
    //
    // Configure the counter (TimerB) to count both edges.
    //
    TimerControlEvent(TIMER0_BASE, TIMER_B, TIMER_EVENT_BOTH_EDGES);

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //FIXME Crée une erreur
    TimerIntRegister(TIMER0_BASE, TIMER_A, Interruption);
//    TimerIntRegister(TIMER0_BASE, TIMER_A, IT_TEST);


    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);


}

void SOUD_Activate(void)
{
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}

void SOUND_Deactivate(void)
{
    PWMGenDisable(PWM0_BASE, PWM_GEN_0);
}

void SOUND_PlayMusic(music_t* tMusic)
{
    SOUND_bPlaying = true;

    m_MtusicInProgress = tMusic;
    CalculITRestante(m_MtusicInProgress);

    m_ucIndexNote = 0;

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, m_psNotes[m_ucIndexNote]);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, m_psNotes[m_ucIndexNote]/2/*m_psNotes[m_ucIndexNote]*/);    //buzzer

    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

void SOUND_MusicStop(void)
{
    PWMGenDisable(PWM0_BASE, PWM_GEN_0);
    TimerDisable(TIMER0_BASE, TIMER_A);

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

static void PlayNextNote(void)
{
    m_ucIndexNote++;
    CalculITRestante(m_MtusicInProgress);

    if(m_MtusicInProgress->notes[m_ucIndexNote].freq == PAUSE)
    {
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 0);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 0);    //buzzer
    }
    else if(m_MtusicInProgress->notes[m_ucIndexNote].freq == STOP)
    {
        SOUND_MusicStop();
    }
    else
    {

        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, m_MtusicInProgress->notes[m_ucIndexNote].freq);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, m_MtusicInProgress->notes[m_ucIndexNote].freq/2/*m_MtusicInProgress->notes[m_ucIndexNote].freq*/);    //buzzer
    }
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
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, m_psNotes[m_ucIndexNote]/m_psNotes[m_ucIndexNote]);    //buzzer
//        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
        bTest = true;
//        NextNote();
//    }

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void Interruption(void)
{

    uint32_t status;

    status = TimerIntStatus(TIMER0_BASE, false);

    if(SOUND_bPlaying)
    {
        if(m_MtusicInProgress->notes[m_ucIndexNote].ITRestante == 0)
        {
            PlayNextNote();

        }
        else
        {
            m_MtusicInProgress->notes[m_ucIndexNote].ITRestante--;
        }
}
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

}

static void IT_TEST(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

}


static void CalculITRestante(music_t *tMusic)
{
    switch (tMusic->notes[m_ucIndexNote].style)
    {
        case TRIPLE_CROCHE:
            tMusic->notes[m_ucIndexNote].ITRestante = 1;
            break;
        case DOUBLE_CROCHE:
            tMusic->notes[m_ucIndexNote].ITRestante = 2;
            break;
        case CROCHE:
            tMusic->notes[m_ucIndexNote].ITRestante = 4;
            break;
        case NOIRE:
            tMusic->notes[m_ucIndexNote].ITRestante = 8;
            break;
        case BLANCHE:
            tMusic->notes[m_ucIndexNote].ITRestante = 16;
            break;
        case RONDE:
            tMusic->notes[m_ucIndexNote].ITRestante = 32;
            break;
            default:
                break;
    }

}
