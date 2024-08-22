/*
 * WDGM.h
 *
 *  Created on: Jun 7, 2024
 *      team: 18
 */

#ifndef WDGM_H
#define WDGM_H
typedef enum
{
    OK = 0,
    NOK = 1
} WDGM_StatusType;

/**
 * @brief Initializes the Watchdog Manager.
 * This function initializes the call count and records the initial time.
 */
void WDGM_Init(void);

/**
 * @brief Main function of the Watchdog Manager.
 * This function checks if the aliveness indication has been called
 * the expected number of times within 100ms. If it has, the status is set to OK.
 * Otherwise, the status is set to NOK. It also resets the call count and updates
 * the last check time.
 */
void WDGM_MainFunction(void);

/**
 * @brief Provides the current supervision status of the Watchdog Manager.
 *
 * @return The current status of the Watchdog Manager (OK or NOK).
 */
WDGM_StatusType WDGM_PovideSuppervisionStatus(void);

/**
 * @brief Increments the aliveness indication call count.
 * This function is called to indicate that the system is alive.
 */
void WDGM_AlivenessIndication(void);
#endif
