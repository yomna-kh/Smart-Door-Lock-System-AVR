/*
 * Timer1.c
 *
 *  Created on: 26 Oct 2022
 *      Author: Yomna Khalid
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"


static volatile void(*Timer1_ptr)(void)= NULL_PTR;
/*

ISR(TIMER1_OVF_vect)
{
	if(Timer1_ptr != NULL_PTR)
	{
		 Call the Call Back function in the application after the event is detected
		(*Timer1_ptr)();
	}
}
*/

ISR(TIMER1_COMPA_vect)
{
	if(Timer1_ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the event is detected */
		(*Timer1_ptr)();
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{


	TCCR1A = (1<<FOC1A) | (((Config_Ptr->mode)& 0b0011)<< WGM10);
	TCCR1B = ((((Config_Ptr->mode)& 0b1100)>>2)<< WGM12) | ((Config_Ptr->prescaler)<<CS10);
	SREG |=(1<<7);
	TIMSK|=(1<<OCIE1A);
	OCR1A = Config_Ptr -> compare_value;
	TCNT1 = Config_Ptr->initial_value;  /* Insert the required initial value in TCNT1 register */
	if ( Config_Ptr->mode == COMPARE )
	{
		TIMSK |= (1<<OCIE1B);
	}
	else if ( Config_Ptr->mode == OVERFLOW )
	{
		TIMSK |= (1<<TOIE1);
	}

}

void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;

	/* Disable the Timer1 Compare interrupt */
	TIMSK &= ~(1<<OCIE1A);
}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	Timer1_ptr = a_ptr;
}
