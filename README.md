# Arduino Mega Audio Equalizer mit dem MSGEQ7 
## Torben, Lukas


## Hardware
### MSGEQ7 anschließen

Damit nun der MSGEQ7 Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins Datasheet für den Mikrocontroller schauen, auf dem man unter Typical Application eine Anleitung findet:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
<br>
Der Reset Pin (Pin 7 des MSGEQ7) sowie der Stope Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt, an einen Analogen Pin des Arduino, in diesem Fall an Pin A0 angeschlossen werden. 
<br><br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46586617-5e827500-ca81-11e8-806b-150cc4b182ff.png" width="500px"></p>
<br>
## Software
### Programmcode

Ein Arduino-Programm besteht aus zwei Hauptfunktionen: der Setup- und der Loop-Funktion. In der Setup Funktion werden grundlegende Einstellungen getroffen, die vor Programmstart ausgeführt werden müssen. So etwa Pin-Einstellungen und Konfigurationen. Dennoch werden Variablen außerhalb der Setup-Function deklariert. Für den MSGEQ7 sowie die Schaltung der LEDs werden 4 Variablen benötigt:

```
int strope = 13;      // setzt die Zahl des Pins für den Strope-Impuls
int reset = 12;       // setzt die Zahl des Pins für den Reset-Impuls
int counter;          // integer zum zählen bis 7 um die 7 frequenzen auszugeben
int frequz[7]         // array mit 7 stellen, um die 7 werte für die frequenzen darin zu speichern

```
