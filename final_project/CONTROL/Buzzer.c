/*
 * Buzzer.c
 *
 *  Created on: 26 Oct 2022
 *      Author: world
 */



#include "buzzer.h"
#include "gpio.h"

/* Description:
 * set the buzzer pin direction as output pin by gpio
 */
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
}

/* Description:
 * turn on the buzzer by writing logic one in the buzzer pin by gpio
 */
void BUZZER_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/* Description:
 * turn off the buzzer by writing logic zero in the buzzer pin by gpio
 */
void BUZZER_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
