### Torben, Lukas
# Arduino Mega Audio Spectrum Analyser mit dem MSGEQ7
<br>


<h1>Das Projekt</h1>
Ein Audio Spectrum Analyzer ist ein Gerät, das Audio neben dem akustischen Eindruck auch visuell darzustellen. Um zu verstehen, wie das ganze funktioniert, ist es zunächst wichtig, den Aufbau von Audiosignalen zu verstehen:

<p align="center"><img width="400px" src="https://user-images.githubusercontent.com/42578917/48780230-bdbae280-ecd9-11e8-8181-92e17ee0fbf0.jpg"></p>

Wie zu erkennen, ist Audio aus verschiedenen Frequenzen, oft im Bereich von kHz, aufgebaut. Ein Audio Spectrum Analyzer misst die Stärke bestimmter Frequenzen und gibt diese als visuelles Signal, oft in Form eines Balkens, der entsprechend stark oder schwach ausschlägt, wieder. Dieser Analyser tut genau das. Mittels eines Mikrocontrollers werden 7 Frequenzen des eingespeisten Audios durch einen Filter gemessen. Die erhaltenen Werte, werden dann als Spannungswerte an einen Arduino übergeben. Dieser speichert die Werte in einer Variable, liest diese dann aus und schaltet dann je nach höhe des Wertes 1- 6 LEDs, die für alle 7 Frequenzen vorgesehen sind. Die LEDs sind mit Transistoren verbunden, die LED mit dem Ground am Source, der Drain mit dem GND der Spannungsquelle verbunden. Der Arduino schaltet dann nur eine Spannung auf die Base, fungiert also quasi als das Bauteil, was den Lichtschalter umlegt, womit die LED angeht. 

## Inhaltsverzeichnis
  * <a href="#komponenten">Komponentenliste</a>
  * <a href="#bauundinst">Bauelemente und Installation</a>
    + <a href="#bauelemente">Bauelemente</a>
    + <a href="#installation">Intstallation der Entwicklungsumgebung</a>   
  * <a href="#hardware">Hardware</a>
    + <a href="#msgeq">MSGEQ7</a>
  * <a href="#software">Software</a>
    + <a href="#setupfunc">Setup Funktion</a><br>
    + <a href="#loopfunc">Loop-Funktion</a>
  * <a href="#endprodukt">Endprodukt</a>
  * <a href="#quellen">Quellen</a>

<br>
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
  <li><a href="https://www.amazon.de/600pcs-Werte-1Ohm-Metallfolie-Widerst%C3%A4nde-Sortiment/dp/B01LYGIOW4/ref=sr_1_4?ie=UTF8&qid=1540302923&sr=8-4&keywords=widerst%C3%A4nde">1x 22kOhm Widerstand</a></li>
	<li><a href="https://www.amazon.de/600pcs-Werte-1Ohm-Metallfolie-Widerst%C3%A4nde-Sortiment/dp/B01LYGIOW4/ref=sr_1_4?ie=UTF8&qid=1540302923&sr=8-4&keywords=widerst%C3%A4nde">42x 150Ohm Widerstand</a></li><br>
</details>
<details>
  <summary>Aktive Bauelemente</summary>
  <br>
  <li><a href="https://www.conrad.de/de/diotec-transistor-bjt-diskret-bc548c-to-92-1-npn-155039.html">42x NPN Transistoren</a></li>
  <li><a href="https://www.amazon.de/gp/product/B01N45KZIR/ref=oh_aui_detailpage_o04_s00?ie=UTF8&psc=1">84x blaue LEDs</a></li><br>

</details>

<br>
<h2 id="bauundinst">Bauelemente und Installation</h2>
<h3 id="bauelemente">Bauelemente</h3>

Als Arduino wird in diesem Fall der <b>Elegoo Mega 2560</b> mit dem ATmega2560-Controller verwendet. Einerseits aufgrund seines günstigen Preises, andererseits wegen der 500mA Überlastungssicherung. Diese ist besonders beim Einsatz vieler kleiner Bauteile wie LEDs und Transistoren mit vielen möglichen Fehlerquellen, wie den Lötstellen und Kabelverbindungen, nützlich, um den Arduino vor Überlastung bei einem Schaltungsfehler zu schützen

Um die einzelnen Frequenzen des Audios korrekt darstellen zu können, muss zunächst das vorhandene Audio in seine einzelnen Frequenzen aufgeteilt werden um anschließend Werte für die Stärke der einzelnen Frequenzen auslesen zu können. Beides kann der <b>Mikrocontroller MSGEQ7</b> durchführen. Das Input-Audio wird dabei in 7 verschiedene Frequenzen aufgeteilt und anschließend die Stärke der einzelnen Frequenzen als Spannungswert auf dem Input ausgeben.

Als LEDs werden Standart-Farbige <b>LED Dioden</b> verwendet, welche mit einem <b>NPN Transistor</b> geschaltet werden. Die NPN Transistoren sind besonders für kleine Spannungen (<5V) gut geeignet, weshalb sie nun auch im Gegensatz zu Mosfets verwendet werden.

Als Kondensatoren werden <b>Keramik-Kondensatoren</b> verwendet, da diese, im Gegensatz zu Elkos in den kleinen Kapazitäten unter 1uF günstig und oft verfügbar sind.

Sonstige Materialien wie Lochrasterplatine und Litze sind <b>Standart-Elektronik-Komponenten</b> ohne besondere Eigenschaften.


<h3 id="installation">Installation der Entwicklungsumgebung</h3>

Um Programme auf dem Arduino zu installieren, wird eine IDE benötigt. In diesem Fall wird die <b><a href="https://www.elegoo.com/download"> Arduino IDE Version 1.8.6 </a> </b>für Windows verwendet.

Nach der Installation erhält man dann folgende <b>Entwicklungsumgebung</b>:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46620749-de621b00-cb25-11e8-87e8-e45f394e590d.png" width="400px" height="350px"></p>
<br>
Nun müssen noch unter Tools der Arduino-Typ und Port ausgewählt werden. Anschließend lassen sich mit einem Klick auf den Pfeil oben links Programme auf den Arduino laden.

<br> <br>
<h2 id="hardware">Hardware</h2>

<h3 id="msgeq">MSGEQ7 anschließen</h3>
Damit nun der <b> MSGEQ7</b> Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins <a href="https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf">Datasheet für den Mikrocontroller</a> schauen, auf dem man unter Typical Application eine Anleitung findet:
<br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
Der Reset <b>Pin</b> (Pin 7 des MSGEQ7) sowie der Strobe Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt, an einen Analogen Pin des Arduino, in diesem Fall an Pin A1 angeschlossen werden. Zudem muss der Clock Oscillator Pin (Pin 8) über einen 33pF Kondensator und der Ground Pin (Pin 6) über einen 100nF (0.1uF) Kondensator an den Ground Pin des Arduino angeschlossen werden
<br><br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46586617-5e827500-ca81-11e8-806b-150cc4b182ff.png" width="500px"></p>
<br>
Die Schaltung wird dann auf eine Lochrasterplatine gebracht und verlötet. Wenn alles verlötet und verkabelt ist, sieht es wie folgt aus:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48710165-cba03300-ec07-11e8-9344-279011aea2b7.jpg" width="400px"></p>
<h2 id="software">Software</h2>

Nachdem nun die Hardware konfiguriert wurde, kann die Software geschrieben werden. 

Ein Arduino-Programm besteht aus zwei <b>Hauptfunktionen</b>: der Setup- und der Loop-Funktion. In der Setup Funktion werden grundlegende Einstellungen getroffen, die vor Programmstart ausgeführt werden müssen. So etwa Pin-Einstellungen und Konfigurationen. Dennoch werden Variablen außerhalb der Setup-Function deklariert. Für den MSGEQ7 werden folgende Variablen benötigt:

```
int strobe = 13;      // setzt die Zahl des Pins für den Strope-Impuls
int reset = 12;       // setzt die Zahl des Pins für den Reset-Impuls
int analog = A0;          // integer zum zählen bis 7 um die 7 frequenzen auszugeben
int freq[7];         // array mit 7 stellen, um die 7 werte für die frequenzen darin zu speichern

```
Die "strobe" <b>Variable</b> speichert die Zahl des Pins, welcher den Puls für den Strobe Pin am MSGEQ7 ausgibt. Das Gleiche gilt für die "reset" Varibale. Die Variable "analog" dient dazu, später bis 7 hochzuzählen, um alle 7 Frequenzen auszulesen. Die "freq" Variable ist ein Array, in dem letztlich die Werte für die Frequenzen gespeichert werden. Alle Varibalen sind Integer, da nur Ganzzahlen verwendet werden.

<h3 id="setupfunc">Setup Funktion</h3>
Alle zuvor initialisierten Variablen enthalten Pins. Diese müssen nun als Output bzw. Input innerhalb der Setup Funktion des Arduino Programms klassifiziert werden: 

```
// Zunächst die MSGEQ7 Variablen
  pinMode(strobe, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(analog, INPUT);


``` 
Damit nun der MSGEQ7 auch Daten für die Frequenzen ausgibt, muss er zuvor verschiedene Signale vom Arduino erhalten. Ein genaues Diagramm dazu ist im Datasheet des Mikrocontrollers zu finden: 

<p id="timing" align="center"><img src="https://user-images.githubusercontent.com/42578917/47381631-bfa47c80-d700-11e8-978a-600b845e36c2.png" width="600px"></p>

<b>Vor Programmstart</b> werden noch einmal beide Pins auf Low gesetzt. Das dient dazu, dass bei Neustart des Programmes beide Pins auch wirklich keine Spannung ausgeben:
``` 
  digitalWrite(reset, LOW);
  digitalWrite(strope, LOW);
  delayMicroseconds(500);
```
Wie nun im Diagramm zu sehen, muss zu Beginn des Programmes ein <b>Reset</b>-Puls geschaltetet werden. Dies wird durch ein PWM (Pulse-Width-Modulated)-Signal über den Arduino gesteuert. Da dies nur zu Beginn und nur einmal ausgeführt werden muss, kann dies ebenso in die Setup-Funktion. Zudem muss der Strope Puls gestartet werden, sobald der Reset durchgeführt wurde. Beides lässt sich mit folgenden Zeilen bewerkstelligen
``` 
  // MSGEQ7 wie im DataSheet genannt reset'en

digitalWrite(reset, HIGH);
digitalWrite(strobe, HIGH);
delayMicroseconds(100);
digitalWrite(strobe, LOW);
delayMicroseconds(100);
digitalWrite(reset, LOW);
digitalWrite(strobe, HIGH);
delayMicroseconds(100);

```  
<h3 id="loopfunc">Die Loop-Funktion</h3>

Innerhalb des Arduino  Programms ist die zweite Funktion die <b>Loop-Funktion</b>. Sie läuft im Gegensatz zur Setup-Funktion, die nur vor Programmstart und nur einmal ausgeführt wird, kontinuerlich durch. Daher ist sie gut geeignet, um kontinuierlich die Werte des MSGEQ7 auszulesen. Dafür wird eine for-Schleife verwendet. Da der MSGEQ7 insgesamt für sieben Frequenzen Werte ausgibt, bevor er von Vorne beginnt, muss die for-Schleife ebenfalls sieben durchläufe haben. Dafür wird zu Beginn der For-Schleife die Varibale "c" (für "counter" deklariert und zu Beginn der Schleife als =0 initialisiert. :

```
for(int c = 0; c < 7; c++) {
	//Hier kommt der Inhalt der for-Schleife rein
}
``` 
Wie dem <a href="#timing">Strobe-Timing-Diagramm</a> zu entnehmen, gibt der MSGEQ7 die Wert als Folge des LOW-Schaltens des Strobe Pulses aus. Daher wird zu Beginn der For-Schleife der strobe-Pin auf Low geschaltet und ein delayMicroseconds eingefügt.
```
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(100);	
}
```
Als nächstes wird nach dem delay der Input am Analogen Port ausgelesen, welcher zuvor in der Variable analog gespeichert wurde. Dies passiert mit der Funktion analogRead. Diese hat im return einen int Wert, der an der Stelle c (abhängig davon bei welchem Durchlauf sich die for-schleife befindet) im Array freq gespeichert, das wie c ebenfalls 7 Stellen hat: 

```
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(100);
	freq[c] = analogRead(analog);
}
```
Zuletzt wird noch der strobe wieder auf HIGH gesetzt und ein delay eingefügt, um die gleiche Ausgangssituation zum Beginn der nächsten Schleife zu schaffen. Die vollständige Schleife sieht dann so aus:
``` 
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(100);
	freq[c] = analogRead(analog);
	digitalWrite(strobe, HIGH);
	delayMicroseconds(100);
}
```
Damit nun die LEDs auch nach den Werten aus dem MSGEQ7 geschaltet werden, muss nach der for-Schleife eine IF-Schleife genutzt werden. Nachdem das freq array einmal bis zur 7. Stelle gefüllt wurde, werden die Stellen einzelnd ausgelesen und danach die LED-Reihen geschaltet.
<br>
Dann wird mithilfe einer if-Schleife geprüft, in welchem Durchgang sich die for Schleife befindet und je nachdem die zugehörige Stelle im freq[c]-Array aufgerufen und ausgelesen. Dann wird geprüft, wie hoch dieser Wert ist und je nachdem unterschiedlich viele LEDs geschaltet. Dies geschieht mit geschachtelten if-Schleifen:
```
if(freq[0] > 60) {
	digitalWrite(41, HIGH);
	if(freq[0] > 80) {
        	digitalWrite(41, HIGH);
        	if(freq[0] > 90) {
          		digitalWrite(39, HIGH); 
          		if(freq[0] > 100) {
            			digitalWrite(43, HIGH);
            			if(freq[0] > 110){
              				digitalWrite(37, HIGH);
              				if(freq[0] > 120) {
                				digitalWrite(35, HIGH);
              				}
            			}
          		}
        	}
      	}      
   } 
```
Das wird dann für C: 0-6 wiederholt. 

Damit die LEDs nicht einmal angehen und dann an bleiben, müssen sie auch wieder auf LOW geschaltet werden. Dies muss allerdings mit einem kleinen delay ausgeführt werden, damit die LEDs lange genug anbleiben, um sie auch mit dem Auge wahrzunehmen. <br>
<details><summary>Es wird also am Ende der IF-Schleifen folgendes eingefügt:</summary>

```
  delay(50);
  digitalWrite(45, LOW);
  digitalWrite(41, LOW);
  digitalWrite(39, LOW);
  digitalWrite(43, LOW);
  digitalWrite(37, LOW);
  digitalWrite(35, LOW);
   
  digitalWrite(26, LOW);
  digitalWrite(24, LOW);
  digitalWrite(22, LOW);
  digitalWrite(32, LOW);
  digitalWrite(30, LOW); 
  digitalWrite(28, LOW); 

  digitalWrite(33, LOW);
  digitalWrite(31, LOW);
  digitalWrite(29, LOW);
  digitalWrite(27, LOW);
  digitalWrite(25, LOW);
  digitalWrite(23, LOW); 

  digitalWrite(A15, LOW); 
  digitalWrite(9, LOW);
  digitalWrite(48, LOW);
  digitalWrite(46, LOW);
  digitalWrite(11, LOW);
   
  digitalWrite(42, LOW);
  digitalWrite(38, LOW);
  digitalWrite(44, LOW);
  digitalWrite(40, LOW);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW); 

  digitalWrite(51, LOW); 
  digitalWrite(3, LOW);
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(53, LOW);
  digitalWrite(8, LOW);

  digitalWrite(49, LOW); 
  digitalWrite(52, LOW);
  digitalWrite(50, LOW);
  digitalWrite(52, LOW);
  digitalWrite(47, LOW);
  digitalWrite(2, LOW);
```
</details><br>
Damit werden alle LEDs nach einem kleinen delay wieder auf LOW geschaltet. <br>
<details><summary><b> Der vollständige CODE sieht dann so aus:</b></summary>

```
int strobe = 12;    // Strobe Pin on the MSGEQ7
int reset = 13;    // Reset Pin on the MSGEQ7
int analog = A1;   // Output Pin on the MSGEQ7
int freq[7];          // An array to hold the values from the 7 frequency bands

void setup() {   
  pinMode(strobe, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(analog, INPUT);

  digitalWrite(strobe, LOW);
  digitalWrite(reset, LOW);
  delayMicroseconds(500),

  digitalWrite(reset, HIGH);
  digitalWrite(strobe, HIGH);
  delayMicroseconds(100);
  digitalWrite(strobe, LOW);
  delayMicroseconds(100);
  digitalWrite(reset, LOW);
  digitalWrite(strobe, HIGH);
  delayMicroseconds(100);
  } 
void loop() {  
  for (int c = 0; c < 7; c++) {
    digitalWrite(strobe, LOW);
    delayMicroseconds(100);
    freq[c] = analogRead (analog);
    digitalWrite(strobe, HIGH);
    delayMicroseconds  (100); 
  }   
   if(freq[0] > 60) {
      digitalWrite(41, HIGH);
      if(freq[0] > 80) {
        digitalWrite(41, HIGH);
        if(freq[0] > 90) {
          digitalWrite(39, HIGH); 
          if(freq[0] > 100) {
            digitalWrite(43, HIGH);
            if(freq[0] > 110){
              digitalWrite(37, HIGH);
              if(freq[0] > 120) {
                digitalWrite(35, HIGH);
              }
            }
          }
        }
      }      
   } 
    if(freq[1] > 60) {
      digitalWrite(34, HIGH);
      if(freq[1] > 80) {
        digitalWrite(40, HIGH);
        if(freq[1] > 90) {
          digitalWrite(36, HIGH); 
          if(freq[1] > 100) {
            digitalWrite(44, HIGH);
            if(freq[1] > 110){
              digitalWrite(38, HIGH);
              if(freq[1] > 120) {
                digitalWrite(42, HIGH);
              }
            }
          }
        }
      }      
   }
   
    if(freq[2] > 60) {
      digitalWrite(33, HIGH);
      if(freq[2] > 80) {
        digitalWrite(31, HIGH);
        if(freq[2] > 90) {
          digitalWrite(29, HIGH); 
          if(freq[2] > 100) {
            digitalWrite(27, HIGH);
            if(freq[2] > 110){
              digitalWrite(25, HIGH);
              if(freq[2] > 120) {
                digitalWrite(23, HIGH);
              }
            }
          }
        }
      }      
   }
   if(freq[3] > 60) {
      digitalWrite(49, HIGH);
      if(freq[3] > 80) {
        digitalWrite(52, HIGH);
        if(freq[3] > 90) {
          digitalWrite(50, HIGH); 
          if(freq[3] > 100) {
            digitalWrite(52, HIGH);
            if(freq[3] > 110){
              digitalWrite(47, HIGH);
              if(freq[3] > 120) {
                digitalWrite(2, HIGH);
              }
            }
          }
        }
      }      
   }
   if(freq[4] > 60) {
      digitalWrite(A15, HIGH);
      if(freq[4] > 80) {
        digitalWrite(9, HIGH);
        if(freq[4] > 90) {
          digitalWrite(48, HIGH); 
          if(freq[4] > 100) {
            digitalWrite(46, HIGH);
            if(freq[4] > 110){
              digitalWrite(11, HIGH);             
            }
          }
        }
      }      
   }
   if(freq[5] > 60) {
      digitalWrite(30, HIGH);
      if(freq[5] > 80) {
        digitalWrite(28, HIGH);
        if(freq[5] > 90) {
          digitalWrite(26, HIGH); 
          if(freq[5] > 100) {
            digitalWrite(24, HIGH);
            if(freq[5] > 110){
              digitalWrite(22, HIGH);
              if(freq[5] > 120) {
                digitalWrite(32, HIGH);
              }
            }
          }
        }
      }      
   } 
    if(freq[6] > 60) {
      digitalWrite(51, HIGH);
      if(freq[5] > 80) {
        digitalWrite(3, HIGH);
        if(freq[5] > 90) {
          digitalWrite(0, HIGH); 
          if(freq[5] > 100) {
            digitalWrite(4, HIGH);
            if(freq[5] > 110){
              digitalWrite(53, HIGH);
              if(freq[5] > 120) {
                digitalWrite(8, HIGH);
              }
            }
          }
        }
      }      
   }
  Serial.println (); 
  delay(50);
  digitalWrite(45, LOW);
  digitalWrite(41, LOW);
  digitalWrite(39, LOW);
  digitalWrite(43, LOW);
  digitalWrite(37, LOW);
  digitalWrite(35, LOW);
   
  digitalWrite(26, LOW);
  digitalWrite(24, LOW);
  digitalWrite(22, LOW);
  digitalWrite(32, LOW);
  digitalWrite(30, LOW); 
  digitalWrite(28, LOW); 

  digitalWrite(33, LOW);
  digitalWrite(31, LOW);
  digitalWrite(29, LOW);
  digitalWrite(27, LOW);
  digitalWrite(25, LOW);
  digitalWrite(23, LOW); 

  digitalWrite(A15, LOW); 
  digitalWrite(9, LOW);
  digitalWrite(48, LOW);
  digitalWrite(46, LOW);
  digitalWrite(11, LOW);
   
  digitalWrite(42, LOW);
  digitalWrite(38, LOW);
  digitalWrite(44, LOW);
  digitalWrite(40, LOW);
  digitalWrite(34, LOW);
  digitalWrite(36, LOW); 

  digitalWrite(51, LOW); 
  digitalWrite(3, LOW);
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);
  digitalWrite(53, LOW);
  digitalWrite(8, LOW);

  digitalWrite(49, LOW); 
  digitalWrite(52, LOW);
  digitalWrite(50, LOW);
  digitalWrite(52, LOW);
  digitalWrite(47, LOW);
  digitalWrite(2, LOW);
}
```
</details>

<br>
<h2 id="endprodukt">Endprodukt</h2>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48711879-a3670300-ec0c-11e8-9b8e-edbc1f48ef8a.jpeg" width="400px"></p>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48711989-efb24300-ec0c-11e8-85c2-862e390c59b5.jpeg" width="400px"></p>
<br>
<h2 id="quellen">Quellen</h2>

- https://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
- https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf
