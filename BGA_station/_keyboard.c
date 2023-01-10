/*
 * _keyboard.c
 *
 *  Created on: 25-11-2014
 *      Author: Marek
 */
#include <avr/io.h>
#include <util/delay.h>
#include "_keyboard.h"

//#include "adc.h"

uint8_t _keyboard (void) //funkcja zwraca nr klawisza od 1 do 4
{

/*

	//pomiar napiecia klawiatury wczesniej musi byæ init_adc wywo³any ale to raz w programie
		ADMUX = (0B11000011);

		ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
		while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji


	uint16_t _vkey;
	uint8_t _key_nr=0;
	return 			_key_nr;
//	static uint8_t latch_key,_key_nr1;


			_vkey=ADC;
			//_vkeyboard=(_vkeyboard)/1024*VREF; //przeliczenie na napiecie

//sprawdzenie który klawisz zosta³ naciniety, sprawdzane s¹ wartoci binarne ¿eby procedura dzia³a jak najszybcie nie przelicza³a na wolty


*/

uint8_t _key_nr=255; // NIE NACIŒNIETY ¯ADEN KLAWISZ


///////////////////////////////////////////////

if (KEY_DOWN1 && KEY_DOWN2)
{
	//		_delay_ms(80);
	//		if (KEY_DOWN4)
	//		{
	_key_nr=6;
	return _key_nr;
	//		}
	
}




if (KEY_DOWN4 && KEY_DOWN3)
{
	//		_delay_ms(80);
	//		if (KEY_DOWN4)
	//		{
	_key_nr=5;
	return _key_nr;
	//		}
	
}



			if (KEY_DOWN1)   
			{
			//	_delay_ms(80);
				//	if (KEY_DOWN1) 
				//	{
					_key_nr=1;	
					return _key_nr;
				//	}
		
			}

///////////////////////////////////////////////
	if (KEY_DOWN2)
	{
		//_delay_ms(80);
		//if (KEY_DOWN2)
		//{
			_key_nr=2;
			return _key_nr;
		//}

	}


///////////////////////////////////////////////

			if (KEY_DOWN3)
			{
		//		_delay_ms(80);
			//	if (KEY_DOWN3)
			//	{
					_key_nr=3;
					return _key_nr;
			//	}
		
			}

/////////////////////////////////////////////

				if (KEY_DOWN4)
				{
			//		_delay_ms(80);
			//		if (KEY_DOWN4)
			//		{
						_key_nr=4;
						return _key_nr;
			//		}
					
				}








	
			return 			_key_nr;
		

 



}









