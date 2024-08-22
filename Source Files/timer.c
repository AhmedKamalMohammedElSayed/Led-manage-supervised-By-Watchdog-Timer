/*
 * timer.c
 *
 *  Created on: Jun 18, 2024
 *      team: 18
 */

#include "timer.h"
#include <avr/interrupt.h>
#include "WDGDRV.h"
#include "WDGM.h"
#include <avr/wdt.h>

volatile uint32_t g_milliseconds = 0; // Global variable to store milliseconds, volatile because it's modified in an interrupt


/**
 * @brief Initialize Timer1 for 51 ms interrupt at 1 MHz clock.
 * This function sets Timer1 to CTC mode, configures the compare match register,
 * enables the Timer1 compare interrupt, sets the prescaler, and enables global interrupts.
 */
void Timer1_Init()
{
    // Set Timer1 to CTC (Clear Timer on Compare Match) mode
    TCCR1B |= (1 << WGM12);

    // Set the compare match register to value for 51 ms interrupt at 1 MHz
    OCR1A = 815; // 51*16 - 1 = 816 -1 = 815

    // Enable Timer1 compare interrupt A
    TIMSK1 |= (1 << OCIE1A);

    // Set prescaler to 64 and start Timer1
    TCCR1B |= (1 << CS11) | (1 << CS10);

    // Enable global interrupts
    sei();
}

/**
 * @brief Initialize Timer2 for 1 ms interrupt at 1 MHz clock.
 * This function sets Timer2 to CTC mode, configures the compare match register,
 * enables the Timer2 compare interrupt, sets the prescaler, and enables global interrupts.
 */
void Timer2_Init()
{
    // Set Timer2 to CTC (Clear Timer on Compare Match) mode
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS21) | (1 << CS20); // Prescaler = 64

    // Set the compare match register to value for 1 ms interrupt at 1 MHz
    OCR2A = 31; // (2*(16*1)) -1 =31

    // Enable Timer2 compare interrupt A
    TIMSK2 |= (1 << OCIE2A);

    // Set prescaler to 64 and start Timer2

    // Enable global interrupts
    sei();
}

/**
 * @brief Interrupt Service Routine (ISR) for Timer1 compare match A.
 * This function is called every time Timer1 reaches the compare match value.
 * It calls the watchdog driver ISR notification function.
 */
ISR(TIMER1_COMPA_vect)
{


    WDGDrv_IsrNotification(); // Call the callback function every 50 ms

    //GPIO_Write(LED_PIN_0, 0);
}

/**
 * @brief Interrupt Service Routine (ISR) for Timer2 compare match A.
 * This function is called every time Timer2 reaches the compare match value.
 * It increments the milliseconds counter.
 */
ISR(TIMER2_COMPA_vect)
{
    g_milliseconds++; // Increment milliseconds counter
}

/**
 * @brief Get the elapsed time in milliseconds.
 * This function returns the value of the global milliseconds counter.
 * It ensures atomic access to the variable by disabling interrupts.
 *
 * @return Elapsed time in milliseconds.
 */
uint32_t GetMillis()
{
    uint32_t ms;
    // Ensure atomic access to milliseconds variable
    cli(); // Disable interrupts
    ms = g_milliseconds;
    sei(); // Enable interrupts
    return ms;
}
