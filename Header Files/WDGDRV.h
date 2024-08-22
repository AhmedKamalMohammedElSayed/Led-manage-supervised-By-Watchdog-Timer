#ifndef WDDRV_H
#define WDDRV_H

/**
 * @brief Initializes the Watchdog Driver.
 * This function configures the watchdog timer with appropriate settings,
 * including enabling the watchdog interrupt and setting the prescaler.
 * It also ensures the watchdog reset flag is cleared.
 */
void WDGDrv_Init(void);

/**
 * @brief Watchdog Interrupt Service Routine Notification.
 * This function is called in the ISR to reset the watchdog timer if the 
 * system is alive and the main function is not stuck.
 */
void WDGDrv_IsrNotification(void);
#endif