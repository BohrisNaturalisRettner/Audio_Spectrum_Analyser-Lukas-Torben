### Torben, Lukas
# Arduino Mega Audio Spectrum Analyser mit dem MSGEQ7 
## Inhaltsverzeichnis
  * <a href="#komponenten">Komponentenliste</a>
  * <a href="#bauundinst">Bauelemente und Installation</a>
    + <a href="#bauelemente">Bauelemente</a>
    + <a href="#installation">Intstallation der Entwicklungsumgebung</a>   
  * <a href="#">Hardware</a>
  * <a href="#software">Software</a>
    + <a href="#setupfunc">Setup Funktion</a>
  * <a href="#">Bitte füllen</a>
  * <a href="#">Bitte füllen</a>
  * <a href="#">Bitte füllen</a>
  * <a href="#">Quellen</a>

<h2 id="komponenten">Komponentenliste</h2>
<details>
  <summary>Arbeitsgeräte</summary>
  <br>
  <li><a href="https://www.conrad.de/de/arduino-board-mega-2560-a000067-191790.html">Arduino Mega</a></li>
  <li><a href="https://www.conrad.de/de/linear-ic-audio-spezialanwendungen-msgeq7-kfz-audio-consumer-audio-automotive-audio-media-player-dip-8-1436444.html">MSGEQ7-Mikrocontroller</a></li>
  <li><a href="#">Steckbrett mit Jumper-Kabeln</a></li>
  <li><a href="#">Multimeter</a></li>
  <li><a href="#">Lötkolben und Lötzinn</a></li>
  <li><a href="https://www.conrad.de/de/tru-components-su528455-europlatine-ohne-cu-auflage-hartpapier-l-x-b-160-mm-x-100-mm-rastermass-254-mm-inhalt-1-st-1566655.html">Lochrasterplatine</a></li><br>
  </details>
<details>
  <summary>Passive Bauelemente</summary>
  <br>
  <li><a href="https://www.conrad.de/de/keramik-kondensator-radial-bedrahtet-100-nf-100-vdc-10-holystone-rdcx104k101dka-1-st-531746.html">2x 100nF Keramik-Kondensatoren</a></li>
  <li><a href="#">1x 33pF Keramik-Kondensator</a></li>
  <li><a href="#">1x 10nF Keramik-Kondensator</a></li>
  <li><a href="https://www.amazon.de/600pcs-Werte-1Ohm-Metallfolie-Widerst%C3%A4nde-Sortiment/dp/B01LYGIOW4/ref=sr_1_4?ie=UTF8&qid=1540302923&sr=8-4&keywords=widerst%C3%A4nde">1x 200kOhm Widerstand</a></li>
  <li><a href="https://www.amazon.de/600pcs-Werte-1Ohm-Metallfolie-Widerst%C3%A4nde-Sortiment/dp/B01LYGIOW4/ref=sr_1_4?ie=UTF8&qid=1540302923&sr=8-4&keywords=widerst%C3%A4nde">1x 22kOhm Widerstand</a></li><br>
</details>
<details>
  <summary>Aktive Bauelemente</summary>
  <br>
  <li><a href="https://www.conrad.de/de/diotec-transistor-bjt-diskret-bc548c-to-92-1-npn-155039.html">49x NPN Transistoren</a></li>
  <li><a href="">50x LEDs</a></li><br>
</details>

<h2 id="bauundinst">Bauelemente und Installation</h2>
<h3 id="bauelemente">Bauelemente</h3>

Als Arduino wird in diesem Fall der Elegoo Mega 2560 mit dem ATmega2560-Controller verwendet. Einerseits aufgrund seines günstigen Preises, andererseits wegen der 500mA Überlastungssicherung. Diese ist besonders beim Einsatz vieler kleiner Bauteile wie LEDs und Transistoren mit vielen möglichen Fehlerquellen, wie den Lötstellen und Kabelverbindungen, nützlich, um den Arduino vor Überlastung bei einem Schaltungsfehler zu schützen

Um die einzelnen Frequenzen des Audios korrekt darstellen zu können, muss zunächst das vorhandene Audio in seine einzelnen Frequenzen aufgeteilt werden um anschließend Werte für die Stärke der einzelnen Frequenzen auslesen zu können. Beides kann der Mikrocontroller MSGEQ7 durchführen. Das Input-Audio wird dabei in 7 verschiedene Frequenzen aufgeteilt und anschließend die Stärke der einzelnen Frequenzen als Spannungswert auf dem Input ausgeben.

Als LEDs werden Standart-Farbige LED Dioden verwendet, welche mit einem NPN Transistor geschaltet werden. Die NPN Transistoren sind besonders für kleine Spannungen (<5V) gut geeignet, weshalb sie nun auch im gegensatz zu Mosfets verwendet werden.

Als Kondensatoren werden Keramik-Kondensatoren verwendet, da diese, im gegensatz zu Elkos in den kleinen Kapazitäten unter 1uF günstig und oft verfügbar sind.

Sonstige Materialien wie Lochrasterplatine und Litze sind Standart-Elektronik-Komponenten ohne besondere Eigenschaften.
<h3 id="installation">Installation der Entwicklungsumgebung</h3>

Um Programme auf dem Arduino zu installieren, wird eine IDE benötigt. In diesem Fall wird die Arduino IDE Version 1.8.6 für Windows verwendet:

https://www.elegoo.com/tutorial/Arduino%20IDE%20for%20Windows_1.8.6.zip 

Nach der Installation erhält man dann folgende Entwicklungsumgebung:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46620749-de621b00-cb25-11e8-87e8-e45f394e590d.png" width="400px" height="350px"></p>
<br>
Nun müssen noch unter Tools der Arduino-Typ und Port ausgewählt werden. Anschließend lassen sich mit einem Klick auf den Pfeil oben links Programme auf den Arduino laden

## Hardware
### MSGEQ7 anschließen
Damit nun der MSGEQ7 Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins Datasheet für den Mikrocontroller schauen, auf dem man unter Typical Application eine Anleitung findet:
<br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
Der Reset Pin (Pin 7 des MSGEQ7) sowie der Stope Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt, an einen Analogen Pin des Arduino, in diesem Fall an Pin A0 angeschlossen werden. Zudem muss der Clock Oscillator Pin (Pin 8) über einen 33pF Kondensator und der Ground Pin (Pin 6) über einen 100nF (0.1uF) Kondensator an den Ground Pin des Arduino angeschlossen werden
<br><br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46586617-5e827500-ca81-11e8-806b-150cc4b182ff.png" width="500px"></p>
<br> 

<h2 id="software">Software</h2>
<h3 id="programmcode">Programmcode</h3>

Ein Arduino-Programm besteht aus zwei Hauptfunktionen: der Setup- und der Loop-Funktion. In der Setup Funktion werden grundlegende Einstellungen getroffen, die vor Programmstart ausgeführt werden müssen. So etwa Pin-Einstellungen und Konfigurationen. Dennoch werden Variablen außerhalb der Setup-Function deklariert. Für den MSGEQ7 sowie die Schaltung der LEDs werden 4 Variablen benötigt:

```
int strope = 13;      // setzt die Zahl des Pins für den Strope-Impuls
int reset = 12;       // setzt die Zahl des Pins für den Reset-Impuls
int analog;          // integer zum zählen bis 7 um die 7 frequenzen auszugeben
int freq[7]         // array mit 7 stellen, um die 7 werte für die frequenzen darin zu speichern
```
Die "strope" Variable speichert die Zahl des Pins, welcher den Puls für den Strope Pin am MSGEQ7 ausgibt. Das Gleiche gilt für die "reset" Varibale. Die Varibale "counter" dient dazu, später bis 7 hochzuzählen, um alle 7 Frequenzen auszulesen. Die "frequz" Variable ist ein Array, in dem letztlich die Werte für die Frequenzen gespeichert werden. Alle Varibalen sind Integer, da nur Ganzzahlen verwendet werden.

Zudem werden die Pins für die LEDs, um sie jeweils später zu verwenden, in integer geschrieben. Dabei wird für jede Led ein Pin-Name, bestehend aus Horizontaler und Vertikaler Reihe verwendet:

<h4 id="setupfunc">Setup Funktion</h4>
Alle zuvor initialisierten Variablen enthalten Pins. Diese müssen nun als Output bzw. Input innerhalb der Setup Funktion des Arduino Programms klassifiziert werden: 

```
// Zunächst die MSGEQ7 Variablen
  pinMode(strobe, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(analog, INPUT);


``` 
Damit nun der MSGEQ7 auch Daten für die Frequenzen ausgibt, muss er zuvor verschiedene Signale vom Arduino erhalten. Ein genaues Diagramm dazu ist im Datasheet des Mikrocontrollers zu finden: 

<p align="center"><img src="https://user-images.githubusercontent.com/42578917/47381631-bfa47c80-d700-11e8-978a-600b845e36c2.png" width="600px"></p>

Vor Programmstart werden noch einmal beide Pins auf Low gesetzt. Das dient dazu, dass bei neustart des Programmes beide Pins auch wirklich keine Spannung ausgeben:
``` 
  digitalWrite(reset, LOW);
  digitalWrite(strope, LOW);
```
Wie nun im Diagramm zu sehen, muss zu Beginn des Programmes ein Reset-Puls geschaltetet werden. Dies wird durch ein PWM (Pulse-Width-Modulated)-Signal über den Arduino gesteuert. Da dies nur zu Beginn und nur einmal ausgeführt werden muss, kann dies ebenso in die Setup-Funktion. Zudem muss der Strope Puls gestartet werden, sobald der Reset durchgeführt wurde. Beides lässt sich mit folgenden Zeilen bewerkstelligen
``` 
  // MSGEQ7 wie im DataSheet genannt reset'en
  digitalWrite(reset, HIGH);                    //
  delay(1);                                     //
  digitalWrite(reset, LOW);                     //  
  digitalWrite(strobe, HIGH);
  delay(1);

```        



### Quellen

- https://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
- https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf
