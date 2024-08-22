/*
 * LEDM.h
 *
 *  Created on: Jun 7, 2024
 *      team: 18
 */
#ifndef LEDM_H
#define LEDM_H

/**
 * @brief Initializes the LED manager module.
 * This function initializes the GPIO module and sets the initial state of the LED.
 * It also records the initial time for toggling the LED.
 */
void LEDM_Init(void);

/**
 * @brief Manages the LED toggling and watchdog aliveness indication.
 * This function checks the elapsed time and toggles the LED state every 500ms.
 * It also signals the watchdog manager to indicate that the system is alive.
 */
void LEDM_Manage(void);
#endif