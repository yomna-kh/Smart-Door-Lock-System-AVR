/*
 * HMI.h
 *
 *  Created on: 3 Nov 2022
 *      Author: world
 */

#ifndef HMI_H_
#define HMI_H_
#include "std_types.h"



/*******************************************************************************
 *                                DEFINITIONS                                *
 *******************************************************************************/

#define ECU_READY 0x11                                   /* defines Ready Signal */
#define PASSWORD   0x01                           /* defines Password Request Signal */
#define PASSWORD_CONFIRMATION  0x02               /* defines Password Confirmation Request Signal */
#define PASSWORD_MATCH_CONFIRMATION  0x03         /* defines Password Match Confirmation Signal */
#define PASSWORD_MATCH_NOT_CONFIRMATION  0x04     /* defines Password Not matched Confirmation Signal */
#define PASSWORD_SCREEN  0x05                     /* defines Password Screen Signal */
#define REQUEST_SCREEN  0x06                      /* defines Options Screen Signal */
#define OPEN_DOOR  0x07                           /* defines Open Door signal */
#define DOOR_IS_OPENNING  0x08                    /* defines Opening state of the door signal */
#define DOOR_IS_LOCKING  0x09                     /* defines Closing state of the door signal */
#define DONE 0x0A                                        /* defines completing task signal */
#define ALARM  0x0B                               /* defines Alert Signal */
#define GET_PASSWORD_DONE 0x0C                           /* defines state of getting saved password from EXT-EEPROM */



#define Welcome 0
#define createpass 1
#define checkpass 2
#define menu 3
#define Door 4
#define Buzzer 5


void Welcome_screen (void) ;
void create_pass (void) ;
void check_pass (void);
void main_menu (void);
void Door_screen (void);
void Buzzer_Screen (void);
void sendData (uint8 data);
void messageTimer(void);
#endif /* MAIN_H_ */
