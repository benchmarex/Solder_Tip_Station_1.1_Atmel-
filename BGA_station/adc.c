/*
 * adc.c
 *
 *  Created on: 24-11-2014
 *      Author: Marek
 */
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"


		 
		 
//float _v_msr_vin; //napiecie zasilania

uint16_t read_adc (uint8_t kanal)
{
ADMUX  |= (1<<REFS0) | (1<<REFS1); //WEWNETRZNE ZR. NAP ODN. 2,56V

ADCSRA |= (1<<ADEN )| (1<<ADPS1) |(1<<ADPS0) | (1<<ADPS2); //PRESCALER 64
	
	
//	ADCSRA &=~_BV(ADFR);



ADMUX = (ADMUX & 0xF8) |kanal;     //Ustawienie kana³u  ADC
		
		//DDRE &= ~ (1<<PE2); //KIERUNEK jako wejœcie
		//if (kanal==0)
		//PORTE |= (1<<PE2); 
		  
//ADMUX  |= (1<<REFS0); //WEWNETRZNE ZR. NAP ODN. 2,56V


		ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
		while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji
		//_delay_us(300);
	//  PORTE &= ~ (1<<PE2); 

		return ADC;



}
