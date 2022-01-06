/*
 * accelerometer.c
 *
 *  Created on: 17 déc. 2021
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
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"

#include "accelerometer.h"

#define ADC_SEQENCE_NUMBER      1


void ACCELEROMETER_Init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

    ADCSequenceConfigure(ADC0_BASE, ADC_SEQENCE_NUMBER, ADC_TRIGGER_PROCESSOR, 0);


    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQENCE_NUMBER, 0, ADC_CTL_CH3 | ADC_CTL_IE);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQENCE_NUMBER, 1, ADC_CTL_CH2 | ADC_CTL_IE);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQENCE_NUMBER, 2, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);


    ADCSequenceEnable(ADC0_BASE, ADC_SEQENCE_NUMBER);
//    ADCSequenceEnable(ADC0_BASE, 2);

    ADCIntClear(ADC0_BASE, ADC_SEQENCE_NUMBER);
//    ADCIntClear(ADC0_BASE, 2);


}

uint32_t ACCELEROMETER_GetX(void)
{
    uint32_t u32Val[3];

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQENCE_NUMBER, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQENCE_NUMBER, u32Val);

    return u32Val[0];

}
uint32_t ACCELEROMETER_GetY(void)
{
    uint32_t u32Val[3];

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQENCE_NUMBER, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQENCE_NUMBER, u32Val);

    return u32Val[1];

}
uint32_t ACCELEROMETER_GetZ(void)
{
    uint32_t u32Val[3];

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQENCE_NUMBER, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC0_BASE, ADC_SEQENCE_NUMBER);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQENCE_NUMBER, u32Val);

    return u32Val[2];

}
