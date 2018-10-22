# Arduino Mega Audio Equalizer mit dem MSGEQ7 
## Torben, Lukas

### Komponentenliste

- Arduino Mega
- MSGEQ7-Mikrocontroller
- Steckbrett mit Jumper-Kabeln
- Multimeter
- Lötkolben

Passive Bauelemente

- 2x 100nF Keramik-Kondensatoren
- 1x 33pF Keramik-Kondensator
- 1x 10nF Keramik-Kondensator
- 1x 200kOhm Widerstand

Aktive Bauelemente 

- BITTE NOCH EINFÜGEN
- BITTE NOCH EINFÜGEN
### Bauteile
Als Arduino wird in diesem Fall der Elegoo Mega 2560 mit dem ATmega2560-Controller verwendet. Einerseits aufgrund seines günstigen Preises, andererseits wegen der 500mA Überlastungssicherung. Diese ist besonders beim Einsatz vieler kleiner Bauteile wie LEDs und Transistoren mit vielen möglichen Fehlerquellen, wie den Lötstellen und Kabelverbindungen, nützlich, um den Arduino vor Überlastung bei einem Schaltungsfehler zu schützen

Um die einzelnen Frequenzen des Audios korrekt darstellen zu können, muss zunächst das vorhandene Audio in seine einzelnen Frequenzen aufgeteilt werden um anschließend Werte für die Stärke der einzelnen Frequenzen auslesen zu können. Beides kann der Mikrocontroller MSGEQ7 durchführen. 
### Installation der Entwicklungsumgebung

Um Programme auf dem Arduino zu installieren, wird eine IDE benötigt. In diesem Fall wird die Arduino IDE Version 1.8.6 für Windows verwendet:

https://www.elegoo.com/tutorial/Arduino%20IDE%20for%20Windows_1.8.6.zip 

Nach der Installation erhält man dann folgende Entwicklungsumgebung:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46620749-de621b00-cb25-11e8-87e8-e45f394e590d.png" width="400px" height="350px"></p>
<br>

## Hardware
### MSGEQ7 anschließen

Damit nun der MSGEQ7 Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins Datasheet für den Mikrocontroller schauen, auf dem man unter Typical Application eine Anleitung findet:
<br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
Der Reset Pin (Pin 7 des MSGEQ7) sowie der Stope Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt, an einen Analogen Pin des Arduino, in diesem Fall an Pin A0 angeschlossen werden. Zudem muss der Clock Oscillator Pin (Pin 8) über einen 33pF Kondensator und der Ground Pin (Pin 6) über einen 100nF (0.1uF) Kondensator an den Ground Pin des Arduino angeschlossen werden
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
Die "strope" Variable speichert die Zahl des Pins, welcher den Puls für den Strope Pin am MSGEQ7 ausgibt. Das Gleiche gilt für die "reset" Varibale. Die Varibale "counter" dient dazu, später bis 7 hochzuzählen, um alle 7 Frequenzen auszulesen. Die "frequz" Variable ist ein Array, in dem letztlich die Werte für die Frequenzen gespeichert werden. Alle Varibalen sind Integer, da nur Ganzzahlen verwendet werden.

### Quellen

- https://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
- https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf
