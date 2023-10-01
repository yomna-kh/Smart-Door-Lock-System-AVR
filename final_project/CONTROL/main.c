/*
 * main.c
 *
 *  Created on: 6 Nov 2022
 *      Author: world
 */



#include "uart.h"
#include "common_macros.h"
#include "control.h"
#include "timer1.h"
#include "gpio.h"
#include "motor.h"
#include "twi.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include <util/delay.h>
#include "external_eeprom.h"
#include "BUZZER.h"


/*******************************************************************************
 *                             GLOBAL VARIABLES                           *
 *******************************************************************************/
uint8 pass[6] = { 0 };                             /* array that stores the  passowrd form HMI_ECU */
uint8 data;                                            /* variable to store the recieved data */
uint8 counter = 0;                                  /* variable acts as seconds counter */
uint8 error;                                    /* counter for incorrect password entered */

/*--------------------------------------------------STRUCTURES----------------------------------------------------------------------------*/


Timer1_ConfigType Timer1_Configuration = {0, 8000, F_CPU_1024, COMPARE};
int main() {


	UART_ConfigType UART_Config = {EIGHT_DATA_BITS, DISABLED_PARITY, ONE_STOP_BIT, 9600};
	UART_init(&UART_Config);/*intializes UART Driver */
	DcMotor_Init();


	while (UART_recieveByte() != ECU_READY);   /* waiting HMI_ECU to sent ECU_READY signal */
	UART_sendByte(ECU_READY);
	while (UART_recieveByte() != ECU_READY);   /* waiting HMI_ECU to sent ECU_READY signal */
	while (1) {

		data = recieveData();                /* recieving command from HMI_ECU */

		//IF conditions to determine which function to perfom//
		if (data == PASSWORD )
		{
			passwordCreation();
		}

		else if (data == PASSWORD_CONFIRMATION )
		{
			passwordConfirmation();
		}
		else if( data == PASSWORD_SCREEN )
			EEPROM_compare();

		else if ( OPEN_DOOR )
		{
			Timer1_init(&Timer1_Configuration);
			Open_Door();

		}

	}

}


void passwordCreation(void) {
	uint8 i = 0;
	/* looping until HMI_ECU sends DONE */
	while (UART_recieveByte() != DONE) {
		pass[i] = UART_recieveByte(); /* storing the sent password in pass array */
		i++;
	}
}

void passwordConfirmation(void) {

	uint8 i = 0;
	uint8 flag = 0;
	/* looping until HMI_ECU sends DONE */
	while (UART_recieveByte() != DONE) {
		if (pass[i] == UART_recieveByte()) {

		} else {
			flag = 1;  /* not matched occurs */
		}
		i++;
	}
	if(flag)
	{
		/* send not matched command to HMI_ECU */
		UART_sendByte(PASSWORD_MATCH_NOT_CONFIRMATION );

	}
	else
	{


		savePassword(pass);
		UART_sendByte(PASSWORD_MATCH_CONFIRMATION );
	}
}


void savePassword (uint8 * a_pass)
{
	uint8 i = 0;
	while(i!=5) /* password size */
	{
		EEPROM_writeByte(EEPROM_ADDRESS+i,a_pass[i]); /* writing in EEPROM  */
		i++;
	}
}

void EEPROM_compare (void)
{
	uint8 i = 0;
	uint8 * pass_Ptr = pass;
	while(i!=5) /* looping to store pass in EEPROM */
	{
		EEPROM_readByte(EEPROM_ADDRESS+i,pass_Ptr+i);
		i++;
	}
	UART_sendByte(GET_PASSWORD_DONE); /* send to HMI_ECU GET_PASSWORD_DONE command */
	while(UART_recieveByte() != ECU_READY); /* looping until HMI_ECU sends ECU_READY signal */
	i = 0;
	uint8 flag = 0;
	/* looping until HMI_ECU sends DONE */
	while (UART_recieveByte() != DONE) {
		if (pass[i] == UART_recieveByte()) {

		}
		else
		{
			flag = 1; /* Incorrect password entered */
		}
		i++;
	}
	if(flag)
	{
		error++;
		if(error == 3)
		{
			UART_sendByte(ALARM );
			BUZZER();
			error=0;
		}
		else{
			UART_sendByte(PASSWORD_MATCH_NOT_CONFIRMATION );
		}
	}
	else
	{
		UART_sendByte(PASSWORD_MATCH_CONFIRMATION );
		savePassword(pass);
		error=0;
	}

}


void Open_Door(void)
{


	Timer1_setCallBack(calledBackFunction);
	Timer1_ConfigType Timer1_Configuration = {0, 8000, F_CPU_1024, COMPARE};
	Timer1_init(&Timer1_Configuration);
	UART_sendByte(DOOR_IS_OPENNING );
	DcMotor_Rotate(CW, 255);
	counter = 0;						//Set seconds to 0			//Activate DC Motor
	while(counter != 15);				//Delay 15 seconds using Timer1
	counter = 0;						//Set seconds to 0 to reset count
	DcMotor_Rotate(ACW, 255);			//Activate DC Motor
	UART_sendByte(DOOR_IS_LOCKING );
	while(counter != 15){}				//Delay 15 seconds using Timer1
	DcMotor_Rotate(STOP, 0);			//Deactivate DC Motor
	UART_sendByte(DONE);
	Timer1_deInit();					//Deactivate Timer1



}


void BUZZER(void)
{
	Timer1_setCallBack(calledBackFunction);
	Timer1_ConfigType Timer1_Configuration = {0, 8000, F_CPU_1024, COMPARE};
	Timer1_init(&Timer1_Configuration);

	counter = 0;						//Set seconds to 0
	BUZZER_on();						//Activate BUZZER
	while(counter <= 60){			//Delay 60 seconds using Timer1
	}
	Timer1_deInit();					//Deactivate Timer1
	BUZZER_off();						//Deactivate BUZZER


}

uint8 recieveData(void) {
	while (UART_recieveByte() != ECU_READY);
	UART_sendByte(ECU_READY);
	data = UART_recieveByte();
	UART_sendByte(ECU_READY);
	return data;
}


void calledBackFunction (void){
	counter++;  /* seconds counter */

}
