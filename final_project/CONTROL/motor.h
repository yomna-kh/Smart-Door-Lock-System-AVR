/*
 * motor.h
 *
 *  Created on: 6 Oct 2022
 *      Author: world
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "std_types.h"

#define PORT_MOTOR PORTB_ID
#define PIN1_MOTOR PIN0_ID
#define PIN2_MOTOR PIN1_ID

typedef enum
{
	 STOP,CW , ACW ,
} DcMotor_State;
void DcMotor_Init(void);
void DcMotor_Rotate( DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
