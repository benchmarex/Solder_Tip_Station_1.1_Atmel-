void Init ( void );
void pisz_lcd(uint8_t);
void pisz_lcd_l(uint8_t wiersz);
void _pwm (uint8_t);
void _off_heater(void);
static uint8_t procent(uint8_t pr);
//float linearity(int8_t in);
void pomiar(void);
void (wake_up)(void);
void (sleep) (void);


#define HEATER (1<<PE3)
#define Z_CROSS (1<<PE4)
#define _l_probek 20  //liczba pr�bek do czytania 
#define _l_probek_temperat 3 //liczba probek do usredniania temp wyswietlanej na wyswietlacz
#define UREF 2.56 //napi�cie odniesienia
#define _div 16 //dzielnik do pomiaru nap. zasilania
#define Vt 1 // spadek napiecia na triaku
#define czas_pomiaru 300
#define moc_pomiar 50 //minimalne wysterowanie na czas pomiaru
#define min_temp 170
#define max_temp 450 
#define overtemp 25 //dozwolone przegrzanie w st C zanim wejdzie w tryb coolingdown
#define Temp_1 350
#define Temp_2 380  //tempertury zdefinowane pod szybkie klwisze
#define timeout_mesure 2 //przy sch�adzaniu co ile cykli ma sprawdza�  temp. im wi�ksza liczba tym rzadziej sprawdza
#define rez_max 100  //maksymalna mo�liwa rezystancja grza�ki do diagnostyki

#define MENUTIME 1 //ms CZAS jaki zostanie odczekany po wykryciu nacisniecia przycisku w menu
#define MENUTIME2 200 //ms CZAS jaki zostanie odczekany po wykryciu nacisniecia przycisku w menu
#define TABLSIZE 40  //rozmiar tablicy znakowej  dla funkcji przygotowujecej dane dla lcd
//#define cykl_pomiaru 300 //100 razy na sekunde x3 sek cykl co ile robic pomiary

/*********************** D I M M E R  -   U S T A W I E N I A   ***************************/
#define LICZBA_KROKOW 255

// czas trwania szpilki (Detekcja ZERA) wyra�ony w milisekundach np: 1,2,... albo np: 0.5
#define SZPILKA_MS 0.7
//#define szer_imp_triaka 20 //w us
/*********************** D I M M E R  -   U S T A W I E N I A   ***************************/

#define __OCR_STEP ((F_CPU/8)*((1000-((SZPILKA_MS*100)/2))/LICZBA_KROKOW))/100000
//#define __OCR_STEP ((8000000/8)*((1000-((SZPILKA_MS*100)/2))/LICZBA_KROKOW))/100000
//#define procent(x) ((x*(LICZBA_KROKOW-1))/100)


#define T_ZAR1_ON PORTE |= HEATER
#define T_ZAR1_OFF PORTE &= ~HEATER


	#define TIMER2_START TCCR2 |= (1<<CS21)	// prescaler=8
	#define TIMER2_STOP TCCR2 &= ~(1<<CS21)	// prescaler off


/*
 * Image hexes generated using FastLCD Designer 1.20 by Bojan I of Microdesign
 * Save the hexes as "IMAGE", replace all "&h" with "0x", copy from line 2
 * to end of file
 */
static const unsigned char waitImage[] PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xE0,0x00,0x00,0xF0,0x00,0x00,0x80,0x40,0x40,
0x40,0x80,0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x80,0x40,0x40,0x40,0x80,
0x00,0x00,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x0F,0x11,0x31,0x31,0xD1,0xF1,0xD1,0xD1,0x31,0x11,0x11,0x0F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x1F,0x00,
0x00,0x0F,0x12,0x12,0x12,0x0B,0x00,0x00,0x0C,0x12,0x12,0x0A,0x1F,0x00,0x00,0x09,
0x12,0x12,0x12,0x0C,0x00,0x00,0x0F,0x12,0x12,0x12,0x0B,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xF0,0x18,0x86,0x86,0xE1,0xF1,0xE1,0xE1,0x86,0x18,0x18,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x80,0x00,0x80,
0x60,0x80,0x00,0x80,0x60,0x00,0x40,0x20,0x20,0x20,0xC0,0x00,0x00,0xE8,0x00,0x20,
0xF8,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x07,0x07,0x07,0x07,0x07,
0x07,0x07,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x03,0x0C,0x03,0x00,0x03,0x0C,0x03,0x00,0x00,0x06,0x09,0x09,0x05,0x0F,0x00,
0x00,0x0F,0x00,0x00,0x0F,0x08,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
