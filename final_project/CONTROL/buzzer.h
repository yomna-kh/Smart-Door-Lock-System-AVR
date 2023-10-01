/*
 * buzzer.h
 *
 *  Created on: 26 Oct 2022
 *      Author: world
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/
/* The Ports and Pins IDs for the buzzer pin */
#define BUZZER_PORT_ID   PORTC_ID
#define BUZZER_PIN_ID    PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void BUZZER_init(void);
void BUZZER_on(void);
void BUZZER_off(void);

#endif /* BUZZER_H_ */
