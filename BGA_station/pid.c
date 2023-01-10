/*
 * pid.c
 *
 *  Created on: 04-12-2014
 *      Author: Marek
 */

#include <avr/io.h>
#include  "pid.h"



//--------------------
static float   a0,a1,a2,b0,b1,b2,ku1,ku2,ke0,ke1,ke2, Ts;
//int16_t  u,Kp, Ki,Kd, e2, e1, e0,u0,u2, u1;
static float  Kp, Ki,Kd, e2, e1, e0,u0,u2, u1;
static uint8_t  N;

void init_PID(void)
{

//Ts=CYKL_U;
//Ts=Ts/1000;    //wartosc w ms 
//Ts = 0.01;   // This must match actual sampling time PID

Ts=CYKL_U/1000;  //wartosc w ms dziele przez 1000 ms bo i cykl tyle wynosi 

N = 10;   	   // filter coefficients
Kp =1.2;   // proportional gain
Ki =1.1; 	// integral gain
Kd =2.00;  	// derivative gain

a0 = (1+N*Ts);
a1 = -(2 + N*Ts);
a2 = 1;
b0 = Kp*(1+N*Ts) + Ki*Ts*(1+N*Ts) + N;
b1 = -(Kp*(2+N*Ts) + Ki*Ts + 2*N);
b2 = Kp + N;

ku1 = a1/a0; 
ku2 = a2/a0;
ke0 = b0/a0;
ke1 = b1/a0;
ke2 = b2/a0;
}

uint16_t  PID(int16_t w_zadana, int16_t w_zmierzona)
{
		e2=e1; e1=e0; u2=u1; u1=u0; // update variables
		
		e0 =w_zadana-w_zmierzona;
		
		u0 = -ku1*u1 - ku2*u2+ ke0*e0 + ke1*e1 + ke2*e2; // eq (12)
		
		if (u0 > I_max) u0 = I_max;
		
		if (u0 < I_min) u0 = I_min;

		
				return u0;
		
}