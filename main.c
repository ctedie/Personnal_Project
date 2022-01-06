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
#include "inc/hw_timer.h"
#include "inc/hw_adc.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"

//#include "rgb_led.h"
#include "utils/uartstdio.h"

#include "modules.h"
#include "sound.h"
#include "notes.h"
#include "buttons.h"
#include "uart.h"
#include "joystick.h"
#include "accelerometer.h"
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
                                             SYSCTL_CFG_VCO_480), 15000000);

//    g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
//                                             SYSCTL_OSC_MAIN |
//                                             SYSCTL_USE_PLL |
//                                             SYSCTL_CFG_VCO_480), 120000000);

#ifdef HAS_SOUND
    SOUND_Init();
#endif

#ifdef HAS_BUTTONS
    BUTTONS_Init();
#endif

#ifdef HAS_JOYSTICK
    JOYSTICK_Init();
#endif

#ifdef HAS_UART
    UART_Init(g_ui32SysClock);
#endif

#ifdef HAS_ACCELEROMETER
    ACCELEROMETER_Init();
#endif

    //LED_Init();
    Init_Systick();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

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
//    IntEnable(INT_PWM0_1);
    IntEnable(INT_TIMER0A);

    IntMasterEnable();
    //PWMGenConfigure(PWM0_BASE, )

    while(1)
    {

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



static uint32_t m_temp = 0;
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
    //
    // Enable the PWM0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

    //
    // Wait for the PWM0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG))
    {
    }




    GPIOPinConfigure(GPIO_PF1_M0PWM1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

//    GPIOPinConfigure(GPIO_PF2_M0PWM2);
//    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
//
//    GPIOPinConfigure(GPIO_PF3_M0PWM3);
//    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
//
//    GPIOPinConfigure(GPIO_PG0_M0PWM4);
//    GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_0);




    //
    // Configure the PWM generator for count down mode with immediate updates
    // to the parameters.
    //

    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
//    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
    m_temp = PWMClockGet(PWM0_BASE);
    //
    // Set the period. For a 50 KHz frequency, the period = 1/50,000, or 20
    // microseconds. For a 120 MHz clock, this translates to 120000000 clock ticks.
    // Use this value to set the period.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, SI);
//    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 533);
//    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 1875000);

    //
    // Set the pulse width of PWM2 for a 501% duty cycle.
    //
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1874981);


    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, SI/2);    //buzzer
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 6);    //LED ROUGE
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, (1875000/4));    //LED VERTE
//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, (1875000/6));    //LED BLEUE


//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 00100000);
//        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 11900000);


    //
    // Enable the outputs.
    //


    //
    // Start the timers in generator 0.
    //

//    PWMIntEnable(PWM0_BASE, PWM_INT_GEN_1);

//    PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_1, PWM_INT_CNT_LOAD);

    PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

    // TODO Uncomment for buzzer
    //PWMGenEnable(PWM0_BASE, PWM_GEN_0);


//    PWMGenEnable(PWM0_BASE, PWM_GEN_2);

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

uint32_t m_pulWidth[] = {187500, 375000, 562500, 750000, 937500, 1125000, 1312500, 1500000, 1687500, 1875000};
uint8_t m_index = 0;
static uint32_t m_ulADCVal_X, m_ulADCVal_Y, m_ulADCVal_Z;
static bool m_bAxe_X_Y = false;
void SystickISR(void)
{

    ulCntTick++;
    if(ulCntTick >= 999)
    {
        //TODO Change PWM pulse width

        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, m_pulWidth[m_index]);
        m_index++;
        m_index = m_index%10;

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

#ifdef HAS_JOYSTICK
    if(m_bAxe_X_Y)
    {
        //Y
        m_ulADCVal_Y = JOYSTICK_GetYValue();


        m_bAxe_X_Y = false;
        UARTprintf("Joystick X = %4d | Joystick Y = %4d\r", m_ulADCVal_X, m_ulADCVal_Y);
    }
    else
    {
        //X
        m_ulADCVal_X = JOYSTICK_GetXValue();

        m_bAxe_X_Y = true;
        UARTprintf("Joystick X = %4d | Joystick Y = %4d\r", m_ulADCVal_X, m_ulADCVal_Y);

    }
#endif
    m_ulADCVal_X = ACCELEROMETER_GetX();
    m_ulADCVal_Y = ACCELEROMETER_GetY();
    m_ulADCVal_Z = ACCELEROMETER_GetZ();
}

void PWMISR(void)
{
    uint32_t uiITState;
    uint32_t state2;

    state2 = PWMIntStatus(PWM0_BASE, true);
    uiITState = PWMGenIntStatus(PWM0_BASE, PWM_GEN_1, true);

    if(bTest == true)
    {
//        PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
//        bTest = false;
    }
    else if(bTest == false)
    {
//        PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
//        bTest = true;
    }

    PWMGenIntClear(PWM0_BASE, PWM_GEN_1, uiITState);
}



