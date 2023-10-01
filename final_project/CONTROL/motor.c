/*
 * motor.c
 *
 *  Created on: 6 Oct 2022
 *      Author: Yomna Khalid
 */
#include <avr/io.h>
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "PWM.h"
#include "gpio.h"
#include "motor.h"


void DcMotor_Init(void)
{

	GPIO_setupPinDirection(PORT_MOTOR, PIN1_MOTOR, PIN_OUTPUT);
	GPIO_setupPinDirection (PORT_MOTOR, PIN2_MOTOR, PIN_OUTPUT);

	GPIO_writePin(PORT_MOTOR, PIN1_MOTOR, LOGIC_LOW);
	GPIO_writePin(PORT_MOTOR, PIN2_MOTOR, LOGIC_LOW);


}
void DcMotor_Rotate ( DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);
	if ( state == CW )
	{
		GPIO_writePin(PORT_MOTOR, PIN1_MOTOR, LOGIC_LOW);
		GPIO_writePin(PORT_MOTOR, PIN2_MOTOR, LOGIC_HIGH);

	}
	if ( state == ACW )
		{
			GPIO_writePin(PORT_MOTOR, PIN1_MOTOR, LOGIC_HIGH);
			GPIO_writePin(PORT_MOTOR, PIN2_MOTOR, LOGIC_LOW);

		}
	if ( state == STOP )
			{
				GPIO_writePin(PORT_MOTOR, PIN1_MOTOR, LOGIC_LOW);
				GPIO_writePin(PORT_MOTOR, PIN2_MOTOR, LOGIC_LOW);

			}

}



