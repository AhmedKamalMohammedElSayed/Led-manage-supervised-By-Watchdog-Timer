/*
 * LEDM.c
 *
 *  Created on: Jun 18, 2024
 *      team: 18
 */
#include <avr/io.h>
#include "GPIO.h"
#include "LEDM.h"
#include <util/delay.h>
#include "timer.h"
#include "WDGM.h"

#define LED_PIN  PB5
#define LED_PIN_2  PB2


static uint32_t lastToggleTime = 0;
static uint8_t ledState = 1;

/**
 * @brief Initializes the LED manager module.
 * This function initializes the GPIO module and sets the initial state of the LED.
 * It also records the initial time for toggling the LED.
 */
void LEDM_Init(void)
{
	GPIO_Init();
	GPIO_Write(LED_PIN, ledState);
	lastToggleTime = GetMillis();
}

/**
 * @brief Manages the LED toggling and watchdog aliveness indication.
 * This function checks the elapsed time and toggles the LED state every 500ms.
 * It also signals the watchdog manager to indicate that the system is alive.
 */
void LEDM_Manage(void)
{
	GPIO_Init_test(LED_PIN_2);
	GPIO_Write(LED_PIN_2, 1);
		
	uint32_t currentTime = GetMillis();
	if (currentTime - lastToggleTime >= 500) {
		ledState = ledState ?0: 1;
		GPIO_Write(LED_PIN, ledState);
		lastToggleTime = currentTime;
	}
	WDGM_AlivenessIndication();
	
	GPIO_Write(LED_PIN_2, 0);
}
