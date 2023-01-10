#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>


//#include  <math.h>
#include <avr/interrupt.h>

//#include "i2c_twi.h"
#include "pcd8544.h"
#include "adc.h"
#include "main.h"
//#include "TWI_TC74_read.h"
#include "_keyboard.h"
#include  "pid.h"
//#include  "R_temp31855.h"

volatile uint8_t kroki;
volatile uint8_t kanal1;

volatile uint8_t ika1;
volatile uint16_t system_clk;

static volatile uint16_t T1,T2, _W1, _W2, _wyn_konc,_Uzas,_Iheat,_Tempset;

static float  Umsr, Imsr,Rmsr, Pmsr,_bufor1,_bufor2,_bufor_1,_bufor_2;
int_fast16_t Tct1;
uint8_t  T3,i_j,zeg_s1, ovheat;
volatile uint8_t pwm1,xa;
uint16_t  zeg_s,T1_rzut;  //T1_rzut jest do prezentacji wyniku na ekranie po usrednieniu 

uint8_t i_asleep,ixix;
char _string[TABLSIZE];


int main()
{

	 Init();
	 
	 

	LcdInit();  //uwaga w tej funkcji sa jescze ustawiane linie spi innych urzadzen
		//display image

		
		    LcdContrast(0x40);
		    LcdClear();
		    LcdImage(waitImage);
		    LcdUpdate();
	
	  _delay_ms(400);

  LcdClear();
LcdUpdate();


init_PID();

_Tempset=Temp_1;
T1_rzut=min_temp;
zeg_s=system_clk;

sprintf(_string,"     %d       ",_Tempset);pisz_lcd(1);

while (1)
{

	
if (system_clk>zeg_s+cykl_pomiaru) {pomiar();zeg_s=system_clk;} //wywo³anie pomiaru oraz zerownie wskaznika czasu czestotliwos wywyolani a f. pomiar




//	sprintf(_string," SET TEMPER.  ");pisz_lcd(1);
//	sprintf(_string," 1:%d  2:%d  ",Temp_1, Temp_2);pisz_lcd(2);
//	sprintf(_string," 2,3:%d      ",min_temp);pisz_lcd(3);

	

//sprintf(_string,"%d          ",_Tempset);pisz_lcd(1);
	
//	sprintf(_string,"R=%f   ",Rmsr);pisz_lcd(2);
	//sprintf(_string,"I=%f   ",Imsr);pisz_lcd(3);
	
//	sprintf(_string,"@=%f    ",_Iheat);pisz_lcd(5);

if ( i_asleep==1) goto skip1;

if (ovheat==1){ sprintf(_string," COOLING DOWN ");pisz_lcd(6);}
	
else  

if (Rmsr==rez_max) {sprintf(_string, "  ----   ");pisz_lcd_l(4);sprintf(_string, " HARDW.PROBLEM ");pisz_lcd(6);
//_Tempset=max_temp;


//tutaj	przejscie w asleep gdy jest hardw problem
 //	ixix++; if (ixix>254) {ixix=0; sleep();} 
	
	
	goto skip1;}

else {sprintf(_string, "  %d'C",T1_rzut);pisz_lcd_l(4);


	sprintf(_string,"   HEATING     ");pisz_lcd(6);}

 //   sprintf(_string,"U=%f   ",Umsr);pisz_lcd(2);
//	sprintf(_string,"tdisp=%d       ",T1);pisz_lcd(6);
//	sprintf(_string,"Tb=%d  Tc=%d       ",T3,T2);pisz_lcd(6);


skip1:

	xa=_keyboard();
	switch(xa)

	{
	case 1:
	
//	if (i_asleep==1){wake_up();}
	_Tempset=Temp_1;
		sprintf(_string,"     %d       ",_Tempset);pisz_lcd(1);
		break;


	case 2:
//	if (i_asleep==1){wake_up();}
	_Tempset=Temp_2;
	    sprintf(_string,"           %d ",_Tempset);pisz_lcd(1);

	break;


	case 3:

	if (i_asleep==1){wake_up();}
	if (_Tempset <max_temp)	_Tempset++;
		sprintf(_string,"     %d       ",_Tempset);pisz_lcd(1);


	break;

	case 4:
	if (i_asleep==1){wake_up();}
	if (_Tempset >min_temp)	_Tempset--;
		sprintf(_string,"     %d       ",_Tempset);pisz_lcd(1);

	break;

case 5:

if (i_asleep==0)
sleep();

else 
	wake_up();

break;


case 6:
	
	_Tempset=min_temp;
	sprintf(_string,"%d              ",_Tempset);pisz_lcd(1);
	
		break;

default:

asm ("nop");
//	_delay_ms(1);

}
asm ("nop");
	_delay_ms(10);

}

  return 0;
}

void (wake_up) (void)
{
	
i_asleep=0;
Init(); //PRZYWROCENIE STANU  PORTÓW
sprintf(_string,">>  WEAK UP <<");pisz_lcd(6);
_delay_ms(1000);	
	
	
}

void (sleep) (void)
{
	
		_off_heater();
		i_asleep=1;
		LcdClear();
		sprintf(_string,">>  ASLEEP  <<");pisz_lcd(6);
		_delay_ms(1000);
	
}

////////////////////////////////////////
////////////////////////////////////////

void Init (void)
{
//inicjalizacja  ca³ego urz¹dznia

//klawiatura  ustawienie portu 

DDRC &= ~KEY_PIN0; //KIERUNEK jako wejœcie 
PORTC |=KEY_PIN0; // PODCI¥GANIE do plusa

DDRC &= ~KEY_PIN1; //KIERUNEK jako wejœcie
PORTC |=KEY_PIN1; // PODCI¥GANIE do plusa

DDRC &= ~KEY_PIN2; //KIERUNEK jako wejœcie
PORTC |=KEY_PIN2; // PODCI¥GANIE do plusa

DDRC &= ~KEY_PIN3; //KIERUNEK jako wejœcie
PORTC |=KEY_PIN3; // PODCI¥GANIE do plusa

//=========================================

DDRE |= HEATER; //KIERUNEK jako wYjœcie
//PORTE &= ~ HEATER;  //ZERO WY£¥CZA 


//DDRE &= ~Z_CROSS; //KIERUNEK jako wejœcie
//PORTE |= Z_CROSS;   
//====================================================

//T_ZAR1_OFF;
	
	// Przerwanie INT4
	
	EICRB |=(1<<ISC41) | (1<<ISC40);//zboczem narastajacym  wyzwalanie
	EIMSK |= (1<<INT4); //zezwolenie na przerwanie tym sygna³em			// odblokowanie INT4


	// TIMER2

	TCCR2 |= (1<<WGM21);				// tryb CTC
	TIMSK |= (1<<OCIE2);				// odblokowanie przerwania COMPARE MATCH
	OCR2 = __OCR_STEP;





/*

//Timer 3 10 bit PWM 

 TCCR3A |= (1<<COM3A1 |1<<WGM30 |1<<WGM31); //|1<<COM3A0
 TCCR3B |= (1<<CS31 |1<<CS30);// (1<<CS32  |1<<CS30); //|1<<CS31
 TIMSK |=(1<<OCIE3A); //ZEZWOLENIE NA PRZERW. COMPARE MATCH
 
//==================================================
*/

//timer 0 - 8bitowy

//TCCR0 |= (1<<WGM01); //TRYB CTC
//// |= (1<<CS02  |1<<CS00); //prescaler 1024
//OCR0= 255;//155; //wyzwalane co 50Hz
//TIMSK |=(1<<OCIE0); //ZEZWOLENIE NA PRZERW. COMPARE MATCH






/*
// ////////////////////////////////
	  //ustawienia do softwareowgo _pwm1()

	    TCCR2 |= (1<<WGM21); //TRYB CTC ??????????????????
	  	TCCR2 |= (1<<CS22  |1<<CS20); //prescaler 1024
	 	
                                    
	  	OCR2= 100;//32; //DZIELNIK CZESTOTLIWOSCI DODATKOWY
	  	TIMSK |=(1<<OCIE2); //ZEZWOLENIE NA PRZERW. COMPARE MATCH
	   sei();
*/


sei();

}


//========================================================
//PWM
void _pwm (uint8_t wypeln) //procent od 0 do 100

{

	kanal1 = procent(wypeln);
  
}

//==========================================================

ISR(INT4_vect) {
	
	
	TIMER2_STOP;
	T_ZAR1_OFF;

	kroki=LICZBA_KROKOW;

	/* podwójne buforowanie, synchronizacja do 50Hz */
	ika1=kanal1;
	TCNT2 = 0;
	TIMER2_START;
	system_clk++;
	
	


}

ISR(TIMER2_COMP_vect) {

if(ika1 && kroki == ika1)

{
	T_ZAR1_ON;

}
	kroki--;
}




//======================================================

void _off_heater(void)	{
	
	EIMSK &= ~(1<<INT4); // zablokowanie INT4
	T_ZAR1_OFF;
	TIMER2_STOP;
}

static uint8_t procent(uint8_t pr)
 {	return (pr * (LICZBA_KROKOW-1))/100;}


void pisz_lcd(uint8_t wiersz) //funkcja pisze na wyswietlacz jako arg nr wiersza
{
	
	uint8_t ix;
			for (ix = 1; ix <= 14; ix++ )
			{
     		LcdGotoXYFont(ix,wiersz);
			LcdChr(FONT_1X,_string[ix-1]);
			LcdUpdate();
			}

}

void pisz_lcd_l(uint8_t wiersz) //funkcja pisze na wyswietlacz jako arg nr wiersza do wyswitlania podwojnej wielkoœci czcionek
{
	
	uint8_t ix,ixi;
			for (ix = 1; ixi <= 12; ix++, ixi=ixi+2 )
			{
     		LcdGotoXYFont(ixi,wiersz);
			 
			LcdChr(FONT_2X,_string[ix-1]);
			LcdUpdate();
			}

}

void pomiar(void)

{
		
//	T2=R_temp31855(PB5);
//	T3=TWI_TC74_read();

	
		if (T1_rzut>(_Tempset+overtemp)) //o ile st C nie moze byc przegrzany grot 
	
	{
		zeg_s1++;
      if (zeg_s1<=timeout_mesure) //co ile  wywo³anie sprawdzana temp.
	  
	  {
		  ovheat=1; //wskaŸnik przegrzania w³¹czony wyswietli sie komunikat
		 _pwm(0);
		  goto nst1;
	  }
	  
	  	  				{_pwm(moc_pomiar);
					_delay_ms(czas_pomiaru);
				zeg_s1=0;goto nst2;} 
		}
	
	
	
	
	ovheat=0; //wsk przegrzania wy³¹czony
	_pwm(moc_pomiar);
	_delay_ms(czas_pomiaru);  //opóŸnienie na ustabilizowanie wyniku na przetw RMS sigmadelta
	
		

nst2:

	for (i_j=0; i_j<_l_probek; i_j++)   //uœrednianie pomiarów 
	
{		
	_bufor_2=_bufor_2+read_adc(2);
	_bufor_1=_bufor_1+read_adc(0);
}
	_bufor_1=_bufor_1/(_l_probek);_bufor1=_bufor_1;
	_bufor_2=_bufor_2/(_l_probek);_bufor2=_bufor_2;

	i_j=0;_bufor_1=0;_bufor_2=0;
	

	
	//pomiar temp ptc na podstawei pradu  i nap

	Umsr=((((UREF/1024*_bufor2)*_div)+2.2)/1.4121);
	Imsr=0.0038*(_bufor1)+0.000000001; //wartoœæ binarna 1bit to 3,8mA dla 2475mA dodanie b. ma³ej wartoœci zapobiega dzieleniu przez gdy nie jest nic pod³aczone do uk³adu 

	Pmsr=(Umsr-Vt)*Imsr;
	

	Rmsr=(Pmsr/(Imsr*Imsr));//     P/I^2=R 
	
	if (Rmsr>rez_max) Rmsr=rez_max; //jesli zbyt du¿a rezystancja obw. wykonawczego to wartoœæ jest "obciêta" i poxniej uzywana do diag.
	
	
	//temperatura z wyliczenia f wielomianu


//y = -5,8194x2 + 168,94x - 766,82  funkcja z excella

	Tct1=(-5.8194)*(Rmsr*Rmsr)+168.94*Rmsr-766.82;
	if (Tct1>max_temp) Tct1=max_temp;
	if (Tct1<min_temp) Tct1=min_temp;

T1=Tct1;

static uint8_t i_jj;
static uint16_t T1_pom;

	T1_pom=T1_pom+Tct1;
	i_jj++;
	
if (i_jj==_l_probek_temperat)     //uœrednianie pomiarów 	
{
	T1_pom=T1_pom/3;T1_rzut=T1_pom;
	i_jj=0;T1_pom=0;
}

//_Iheat=PID(_Tempset,T1);
//_pwm(_Iheat);//


_pwm(PID(_Tempset,T1));


nst1:
asm ("nop");





}
