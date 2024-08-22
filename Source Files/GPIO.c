/*
 * GPIO.c
 *
 *  Created on: Jun 18, 2024
 *      team: 18
 */

#include <avr/io.h>
#include "GPIO.h"

#define LED_PORT PORTB
#define LED_PIN PB5
#define LED_DDRB DDRB

void GPIO_Init(void)
{
	LED_DDRB |= (1 << LED_PIN);
}

void GPIO_Write(unsigned char PinId, unsigned char PinData)
{
	if (PinData)
	{
		LED_PORT |= (1 << PinId);
	}
	else
	{
		LED_PORT &= ~(1 << PinId);
	}
}

void GPIO_Init_test(unsigned char Pin_no)
{
	LED_DDRB |= (1 << Pin_no);
}
