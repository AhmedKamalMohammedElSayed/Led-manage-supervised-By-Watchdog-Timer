/*
 * WDGDRV.c
 *
 *  Created on: Jun 7, 2024
 *      team: 18
 */

#include "WDGDrv.h"
#include "WDGM.h"
#include "stdint.h"
#include "GPIO.h"
#include <avr/io.h>

#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"
#include <avr/interrupt.h>

extern volatile WDGM_StatusType g_watchdogStatus;
extern volatile char g_mainFuncStuck;

#define WDE 3
#define WDCE 4
#define LED_PIN_1 PB1

/**
 * @brief Initializes the Watchdog Driver.
 * This function configures the watchdog timer with appropriate settings,
 * including enabling the watchdog interrupt and setting the prescaler.
 * It also ensures the watchdog reset flag is cleared.
 */
void WDGDrv_Init(void)
{
    // Disable global interrupts
    cli();
    wdt_reset();
    // Clear the watchdog reset flag
    MCUSR &= ~(1 << WDRF);
    // Enable the watchdog change enable and watchdog enable bits
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    // Set watchdog interrupt enable, watchdog enable, and prescaler
    WDTCSR = (1 << WDIE) | (1 << WDE) | (0x02);

    sei(); // Enable global interrupts
}

/**
 * @brief Watchdog Interrupt Service Routine Notification.
 * This function is called in the ISR to reset the watchdog timer if the
 * system is alive and the main function is not stuck.
 */
void WDGDrv_IsrNotification(void)
{



    if ((!g_watchdogStatus) && (!g_mainFuncStuck))
    {
		GPIO_Init_test(LED_PIN_1);
		GPIO_Write(LED_PIN_1, 1);

        wdt_reset(); // refresh the wdg (recount) 
    
		GPIO_Write(LED_PIN_1, 0);
	}

    
}
