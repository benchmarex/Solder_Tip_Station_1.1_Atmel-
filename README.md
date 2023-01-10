# Solder_Tip_Station_1.1_Atmel-
Solder_Tip_Station_1.1_Atmel XMEGA128 


PL
  Stacja lutownicza zaprojektowana i wykonana przezemnie na własny użytek. Program napisany w Atmel Studio 6 w jezyku C na procesor XMEGA128-L. 
Jako element wykonawczy zastosowałem lutownicę ERSA RT80 24W 80W podłączona do zaprojektowanego przezemnie sterownika. Lutownica zasilana jest prądem zmiennym 24V z transformatora toroidalnego 230V 100W. Regulacja mocy odbywa się za pomocą triaka sterowanego fazowo w momencie przejścia sieci przez zero. Prąd grzałki jest mierzony za pomocą przekładnika prądowego a następnie przetwarzany w przetworniku TrueRMS. Pomiar temperatury grota odbywa się na podstawie pomiaru rezystancji grzałki przy 50% wysterowaniu mocy. Kontrolą wysterowania grzałki zajmuje się algorytm PID. Na płycie urządzenia znajduje się również układ do pomiaru temperatury z termoelementu  'thermocouple', jednak nie ma tu zastosowania z uwagi na pomiar temperatury realizowany poprzez pomiar rezystancji grzałki. Dzięki dodaniu tego układu można zastosować inny typ lutownicy który ma pomiar temperatury oparty na termoparze. 
  Wyświetlanie komunikatów i aktualnych danych odbywa sie na ekraniue LCD, sterowanie realizowane za pomocą 4 przycisków. Umożliwa zmianę temperatury od 150 do 450st C lub wybranie jednej z 3 zaprogramowanych - 150; 400, 450

EN 
Soldering station created and made by me for my own use. Program written in Atmel Studio 6 in C language for XMEGA128-L processor.
As an element, an ERSA RT80 24W 80W soldering iron was used, connected to the controller I used. The soldering iron is powered by 24V alternating current from a 230V 100W toroidal transformer. behavior control by means of a phase-controlled triac in the zero-crossing of the network. The heater current is measured by a current transformer and then operated in a TrueRMS converter. The measurement of the temperature of the tip is based on the measurement of the resistance of the heater at 50% of the power control. PID algorithm heater control. The device also has a temperature measurement system from a thermocouple "thermocouple", but it is not applicable here, due to the remarks on temperature measurement by measuring the resistance of the heater. With the addition of this chip, another type of soldering iron can be used that has a temperature measurement on a thermocouple.
  Messages and current data are displayed on the LCD screen, communication is supported by 4 devices. Enabling to change the temperature from 150 to 450 degrees C or choosing one of 3 temperatures - 150; 400, 450
