/*
 * timer.h
 *
 *  Created on: Jun 18, 2024
 *      team: 18
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

/**
 * @brief Initialize Timer1 for 1 ms interrupt at 1 MHz clock.
 */
void Timer1_Init(void);

/**
 * @brief Initialize Timer2 for 1 ms interrupt at 1 MHz clock.
 */
void Timer2_Init(void);

/**
 * @brief Get the elapsed time in milliseconds.
 *
 * @return Elapsed time in milliseconds.
 */
uint32_t GetMillis(void);

#endif /* TIMER_H_ */
