/*
 * pid.h
 *
 *  Created on: 04-12-2014
 *      Author: Marek
 */

#ifndef PID_H_
#define PID_H_


#define cykl_pomiaru 250 //100 razy na sekunde x3 sek cykl co ile robic pomiary
#define CYKL_U ((cykl_pomiaru*10)+2000) //definiowany w main.h  czas cyklu pomiaru w msek czas plus opóznienie w petli pomiarowej 
//#define CYKL_D 1009 //dolny podgrzewacz /w sekundach 8 E6/1024/256/255  f procesora/dzielnik timera /dodatkowy dzielnik timera/i softw dzilenik w przerwaniu


#define I_min 0 //minimum dla kontorlera pid
#define I_max 100 //max dla kontorlera pid 


void init_PID(void);
//void init_PID_1(void);

uint16_t PID(int16_t, int16_t);
//uint8_t PID_1(int16_t, int16_t);

#endif /* PID_H_ */
