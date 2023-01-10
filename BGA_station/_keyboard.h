/*
 * _keyboard.h
 *
 *  Created on: 25-11-2014
 *      Author: Marek
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_





#define KEY_PIN0                  1<<PC0
#define KEY_PIN1                  1<<PC1
#define KEY_PIN2                  1<<PC2
#define KEY_PIN3                  1<<PC3


#define KEY_DOWN1 ! (PINC & KEY_PIN0)
#define KEY_DOWN2 ! (PINC & KEY_PIN1)
#define KEY_DOWN3 ! (PINC & KEY_PIN2)
#define KEY_DOWN4 ! (PINC & KEY_PIN3)





uint8_t _keyboard (void);
 
 
#endif /* KEYBOARD_H_ */
