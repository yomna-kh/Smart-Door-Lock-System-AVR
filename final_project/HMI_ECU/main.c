/*
 * main.c
 *
 *  Created on: 6 Nov 2022
 *      Author: world
 */


#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h"
#include "lcd.h"
#include "timer1.h"
#include "gpio.h"
#include "HMI.h"
#include <util/delay.h>
#include "keypad.h"

/**************************************************GLOBAL VARIABLES************************************************************************/
uint8 volatile g_index = 0;
uint8 volatile g_choice = 1;
uint8 g_data;
uint8 volatile g_flag = 0;
/* pointer to array of functions */
volatile uint8 message_time=0;

void (*fun_ptr_arr[])(void)
	= { Welcome_screen , create_pass , check_pass,main_menu,Door_screen, Buzzer_Screen}
;


Timer1_ConfigType Timer1_Configuration = {0, 8000, F_CPU_1024, COMPARE};

int main() {





	/* Initializes UART Driver */
	UART_ConfigType UART_Config = {EIGHT_DATA_BITS, DISABLED_PARITY, ONE_STOP_BIT, 9600};

	UART_init(&UART_Config);

	/* Initializes LCD */

	LCD_init();
	/* clear the screen */
	LCD_clearScreen();

	/* sending to CONTROL_ECU ECU_READY signal */
	UART_sendByte(ECU_READY);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (UART_recieveByte() != ECU_READY);
	Timer1_setCallBack(messageTimer);


	/* sending to CONTROL_ECU ECU_READY signal */
	UART_sendByte(ECU_READY);
	(*fun_ptr_arr[Welcome])();
	while (1)

	{
		/* calling the function by using pointer to the function
		 * each function has its own index in fun_ptr_arr
		 */

		(*fun_ptr_arr[g_index])();
	}

	return 0;

}

void messageTimer(void){	//SET CALLBACK Function
	message_time++;			//Increment number of seconds every time interrupt occurs and set callback function is called
}
void Welcome_screen(void)
{
	LCD_clearScreen ();
	LCD_moveCursor (0,5);
	LCD_displayString ("WECLOME");
	_delay_ms(1000);
	g_index = createpass;

}
void create_pass(void)
{
	uint8 key =0,counter=0;
	uint8 flag = 1;
	uint8 command = 0;
	sendData(PASSWORD  );
	LCD_clearScreen();
	if(g_flag)
	{
		LCD_displayString("REENTER  PASS");
	}
	else
	{
		LCD_displayString("PLZ ENTER PASS");
	}
	LCD_moveCursor(1, 3);

	while(key != '#')
	{
		key = KEYPAD_getPressedKey();
		UART_sendByte(key);
		if(key != '#')
		{
			LCD_displayCharacter('*');
			_delay_ms(400);
		}
		counter++;
		_delay_ms(500);
	}


	UART_sendByte(DONE);
	sendData(PASSWORD_CONFIRMATION  );
	LCD_clearScreen();
	LCD_displayString("PLZ RE ENTER");
	LCD_moveCursor(1, 3);
	key = 0;
	counter=0;
	while(key != '#'){
		key = KEYPAD_getPressedKey();
		UART_sendByte(key);
		if(key != '#')
		{
			LCD_displayCharacter('*');
		}
		counter++;
		_delay_ms(500);
	}
	UART_sendByte(DONE);

	while (flag) {
		command = UART_recieveByte();
		switch (command) {
		case PASSWORD_MATCH_CONFIRMATION  :
			g_index = menu;
			flag = 0;
			break;
		case PASSWORD_MATCH_NOT_CONFIRMATION  :
			g_index = createpass;
			LCD_clearScreen();
			LCD_displayString("WRONG PASSWORD");
			_delay_ms(500);
			flag = 0;
			break;
		}

	}
}

void check_pass(void){
	uint8 key = 0;
	uint8 flag = 1;
	uint8 command = 0;
	sendData(PASSWORD_SCREEN  );
	LCD_clearScreen();
	if(g_flag)
	{
		LCD_displayString("ENTER OLD PASSWORD");
	}
	else
	{
		LCD_displayString("ENTER NEW PASSWORD");
	}
	LCD_moveCursor(1, 0);
	while (UART_recieveByte() != GET_PASSWORD_DONE);

	/* sending to CONTROL_ECU ECU_READY signal */
	UART_sendByte(ECU_READY);
	do {
		key = KEYPAD_getPressedKey();
		UART_sendByte(key);
		if (key != '#')
			LCD_displayCharacter('*');
		_delay_ms(500);
	} while (key != '#');

	UART_sendByte(DONE);

	while (flag) {
		command = UART_recieveByte();
		switch (command) {
		case PASSWORD_MATCH_CONFIRMATION  :

			if (g_choice==0) {
				g_index = Door;
			}
			else {
				g_index = createpass;
			}

			flag = 0;
			break;
		case PASSWORD_MATCH_NOT_CONFIRMATION  :
			g_index = checkpass;
			LCD_clearScreen();
			LCD_displayString("WRONG PASSWORD");
			_delay_ms(500);
			flag = 0;
			break;
		case ALARM  :
			g_index =Buzzer;
			flag = 0;
			break;
		default:
			break;
		}

	}
}

void main_menu(void)
{
	uint8 key=0;
	LCD_clearScreen ();
	sendData(REQUEST_SCREEN  );
	LCD_moveCursor (0,0);
	LCD_displayString ("#: Change PW");
	LCD_moveCursor (1,0);
	LCD_displayString ("*: Open Door");
	key = KEYPAD_getPressedKey();
	_delay_ms(500);
	if (key == '#') {
		g_index = checkpass;
		g_choice = 1;
	} else if (key == '*') {
		g_index = checkpass;
		g_choice = 0;
		g_flag = 1;
	} else {
		LCD_clearScreen();
		g_index = menu;

	}
	_delay_ms(500);
}
void Door_screen(void){

	LCD_clearScreen();
	sendData(OPEN_DOOR  );
	while (UART_recieveByte() != DOOR_IS_OPENNING  );
	LCD_displayString ("DOOR IS UNLOCKING");
	while (UART_recieveByte() != DOOR_IS_LOCKING  );
	LCD_clearScreen();
	LCD_displayString("DOOR IS LOCKING");
	while (UART_recieveByte() != DONE);
	g_index = menu;

}
void Buzzer_Screen(void){
	Timer1_init(&Timer1_Configuration);
	LCD_clearScreen();
	LCD_displayString("CALLING THE ");
	LCD_moveCursor(1,0);
	LCD_displayString("POLICE!! ");
	while (UART_recieveByte() != DONE);
	g_index = Welcome;
}
void sendData(uint8 data)
{
	/* sending to CONTROL_ECU ECU_READY signal */
	UART_sendByte(ECU_READY);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (UART_recieveByte() != ECU_READY)
		;
	UART_sendByte(data);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (UART_recieveByte() != ECU_READY);

}

