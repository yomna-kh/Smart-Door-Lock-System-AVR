/*
 * PWM.c
 *
 *  Created on: 6 Oct 2022
 *      Author: Yomna Khalid
 */

#include <avr/io.h>
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "PWM.h"
#include "gpio.h"


void PWM_Timer0_Start(uint8 duty_cycle)
{
	  TCNT0 = 0; // Set Timer Initial Value to 0

		/* configure the timer
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
		 */
		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

		/* convert the duty cycle from 0->255 to 0->100 */

		OCR0  = duty_cycle ;

		DDRB  = DDRB | (1<<PB3);

}
