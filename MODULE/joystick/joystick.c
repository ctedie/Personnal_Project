/*
 * joystick.c
 *
 *  Created on: 17 d�c. 2021
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
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"



void JOYSTICK_Init(void)
{
    //
    // The ADC0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    //
    // For this example ADC0 is used with AIN0 on port E7.
    // The actual port and pins used may be different on your part, consult
    // the data sheet for more information.  GPIO port E needs to be enabled
    // so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //
    // Select the analog ADC function for these pins.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);

    //
    // Enable sample sequence 3 with a processor signal trigger.  Sequence 3
    // will do a single sample when the processor sends a signal to start the
    // conversion.  Each ADC module has 4 programmable sequences, sequence 0
    // to sequence 3.  This example is arbitrarily using sequence 3.
    //
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 1);

    //
    // Configure step 0 on sequence 3.  Sample channel 0 (ADC_CTL_CH0) in
    // single-ended mode (default) and configure the interrupt flag
    // (ADC_CTL_IE) to be set when the sample is done.  Tell the ADC logic
    // that this is the last conversion on sequence 3 (ADC_CTL_END).  Sequence
    // 3 has only one programmable step.  Sequence 1 and 2 have 4 steps, and
    // sequence 0 has 8 programmable steps.  Since we are only doing a single
    // conversion using sequence 3 we will only configure step 0.  For more
    // information on the ADC sequences and steps, reference the datasheet.
    //
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE |
                             ADC_CTL_END);

    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH9 | ADC_CTL_IE |
                             ADC_CTL_END);

    //
    // Since sample sequence 3 is now configured, it must be enabled.
    //
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCSequenceEnable(ADC0_BASE, 2);

    //
    // Clear the interrupt status flag.  This is done to make sure the
    // interrupt flag is cleared before we sample.
    //
    ADCIntClear(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 2);

    //
    // Sample AIN0 forever.  Display the value on the console.
    //
//    while(1)
//    {
//        //
//        // Trigger the ADC conversion.
//        //
//        ADCProcessorTrigger(ADC0_BASE, 3);
//
//        //
//        // Wait for conversion to be completed.
//        //
//        while(!ADCIntStatus(ADC0_BASE, 3, false))
//        {
//        }
//
//        //
//        // Clear the ADC interrupt flag.
//        //
//        ADCIntClear(ADC0_BASE, 3);
//
//        //
//        // Read ADC Value.
//        //
//        ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);
//
//        //
//        // Display the AIN0 (PE3) digital value on the console.
//        //
//        UARTprintf("AIN0 = %4d\r", pui32ADC0Value[0]);
//
//        //
//        // This function provides a means of generating a constant length
//        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
//        // 250ms arbitrarily.
//        //
//#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
//    defined(TARGET_IS_TM4C129_RA1) ||                                         \
//    defined(TARGET_IS_TM4C129_RA2)
//        SysCtlDelay(ui32SysClock / 12);
//#else
//        SysCtlDelay(SysCtlClockGet() / 12);
//#endif
//    }

}

