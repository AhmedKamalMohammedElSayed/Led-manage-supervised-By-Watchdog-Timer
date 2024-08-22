/*
 * main.c
 *
 *  Created on: Jun 18, 2024
 *      team: 18
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "GPIO.h"
#include "LEDM.h"
#include "timer.h"
#include "WDGDRV.h"
#include "WDGM.h"

#define LED_PORT PORTB
#define LED_PIN PB5
#define LED_DDRA DDRB

#define LED_PIN_0 PB0


static volatile uint32_t g_lastCheckTimeMain = 0;
static volatile uint32_t g_lastCheckTimeDrv = 0;

int main()
{
   GPIO_Init_test(LED_PIN_0);
GPIO_Write(LED_PIN_0, 1);
    LEDM_Init();
    Timer1_Init();
    Timer2_Init();
    WDGDrv_Init();
    WDGM_Init();
	
	
	

    while (1)
    {
        uint32_t currentTimeMain = GetMillis();
        if (currentTimeMain - g_lastCheckTimeMain >= 10)
        {
            LEDM_Manage();
            g_lastCheckTimeMain = currentTimeMain;
        }

        uint32_t currentTimeDrv = GetMillis();
        if (currentTimeDrv - g_lastCheckTimeDrv >= 20)
        {
            WDGM_MainFunction();
            g_lastCheckTimeDrv = currentTimeDrv;
        }
    }

    return 0;
}
