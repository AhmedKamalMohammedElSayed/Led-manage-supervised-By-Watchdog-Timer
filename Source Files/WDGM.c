/*
 * WDGM.c
 *
 *  Created on: Jun 7, 2024
 *      team: 18
 */

#include "WDGM.h"
#include "LEDM.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "timer.h"

static volatile uint32_t g_callCount = 0;
static volatile uint32_t g_lastCheckTime = 0;
static volatile uint32_t g_lastCheckTimeReset = 0;

volatile WDGM_StatusType g_watchdogStatus = OK;
volatile char g_mainFuncStuck = 1;

#define LED_PIN_3 PB3

/**
 * @brief Initializes the Watchdog Manager.
 * This function initializes the call count and records the initial time.
 */
void WDGM_Init(void)
{
    g_callCount = 0;
    g_lastCheckTime = GetMillis();
}

/**
 * @brief Main function of the Watchdog Manager.
 * This function checks if the aliveness indication has been called
 * the expected number of times within 100ms. If it has, the status is set to OK.
 * Otherwise, the status is set to NOK. It also resets the call count and updates
 * the last check time.
 */
void WDGM_MainFunction(void)
{
    g_mainFuncStuck = 1;
    GPIO_Init_test(LED_PIN_3);
    GPIO_Write(LED_PIN_3, 1);

    uint32_t currentTime = GetMillis();

    if ((currentTime - g_lastCheckTime) >= 100)
    {
        if (g_callCount > 8 && g_callCount < 12)
        {
            g_watchdogStatus = OK;
        }
        else
        {
            g_watchdogStatus = NOK;
        }
        g_callCount = 0;
        g_lastCheckTime = currentTime;
    }

    GPIO_Write(LED_PIN_3, 0);
	g_mainFuncStuck = 0;

}

/**
 * @brief Provides the current supervision status of the Watchdog Manager.
 *
 * @return The current status of the Watchdog Manager (OK or NOK).
 */
uint8_t WDGM_PovideSuppervisionStatus(void)
{
    return g_watchdogStatus;
}

/**
 * @brief Increments the aliveness indication call count.
 * This function is called to indicate that the system is alive.
 */
void WDGM_AlivenessIndication(void)
{
    g_callCount++;
}
