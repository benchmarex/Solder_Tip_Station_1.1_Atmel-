# Solder_Tip_Station_1.1_Atmel-
Solder_Tip_Station_1.1_Atmel XMEGA128 



Stacja lutownicza zaprojektowana i wykonana przezemnie na własny użytek. Program napisany w Atmel Studio 6 w jezyku C na procesor XMEGA128-L. 
Jako element wykonawczy zastosowałem lutownicę ERSA RT80 24W 80W podłączona do zaprojektowanego przezemnie sterownika. Lutownica zasilana jest prądem zmiennym 24V z transformatora toroidalnego 230V 100W. Regulacja mocy odbywa się za pomocą triaka sterowanego fazowo w momencie przejścia sieci przez zero. Prąd grzałki jest mierzony za pomocą przekładnika prądowego a następnie przetwarzany w przetworniku TrueRMS. Pomiar temperatury grota odbywa się na podstawie pomiaru rezystancji grzałki przy 50% wysterowaniu mocy. Kontrolą wysterowania grzałki zajmuje się algorytm PID. 

