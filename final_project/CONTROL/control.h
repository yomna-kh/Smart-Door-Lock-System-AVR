/*
 * control.h
 *
 *  Created on: 3 Nov 2022
 *      Author: world
 */

#ifndef MAIN_H_
#define MAIN_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ECU_READY 0x11                                   /* defines Ready Signal */
#define PASSWORD    0x01                           /* defines Password Request Signal */
#define PASSWORD_CONFIRMATION   0x02               /* defines Password Confirmation Request Signal */
#define PASSWORD_MATCH_CONFIRMATION   0x03         /* defines Password Match Confirmation Signal */
#define PASSWORD_MATCH_NOT_CONFIRMATION   0x04     /* defines Password Not matched Confirmation Signal */
#define PASSWORD_SCREEN   0x05                     /* defines Password Screen Signal */
#define REQUEST_SCREEN   0x06                      /* defines Options Screen Signal */
#define OPEN_DOOR   0x07                           /* defines Open Door signal */
#define DOOR_IS_OPENNING   0x08                    /* defines Opening state of the door signal */
#define DOOR_IS_LOCKING   0x09                     /* defines Closing state of the door signal */
#define DONE 0x0A                       /* defines completing task signal */
#define ALARM   0x0B                               /* defines Alert Signal */
#define GET_PASSWORD_DONE 0x0C                           /* defines state of getting saved password from EXT-EEPROM */
#define EEPROM_ADDRESS 0x0002                     /* defines the base address location which the password has been saved in the memory */

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

uint8 recieveData(void);                                 /* declaration of the function that recieve data from HMI_ECU */
void passwordCreation(void);                             /* declaration of the function that creates a new password    */
void passwordConfirmation(void);                         /* declaration of the function that match the rentered password with the first one */
void savePassword (uint8 * a_pass);                      /* declaration of the function that save the new password in the EEPROM */
void EEPROM_compare (void);                              /* declaration of the function that compare the requested password with the saved one in the EEPROM */
void Open_Door(void);                                /* declaration of the function that opens and closes the door */
void BUZZER(void);                                       /* declaration of the function that turns on and off the buzzer */
void calledBackFunction (void);                          /* declaration of the function that will be called by Timer 1 when performs its ISR */
void savePassword (uint8 * a_pass);
void Open_Door (void);
#endif /* MAIN_H_ */
