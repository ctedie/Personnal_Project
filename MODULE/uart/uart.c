/*
 * uart.c
 *
 *  Created on: 18 déc. 2021
 *      Author: Cedric
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "inc/hw_uart.h"
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"

#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"

#include "utils/uartstdio.h"

void UART_Init(uint32_t ulClk)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);


    UARTStdioConfig(0, 115200, ulClk);
//    UARTprintf("bonjour\n\0");
}


//void UART_printf(const char *pcString, ...)
//{
////    UARTprintf(pcString, ...);
//}
