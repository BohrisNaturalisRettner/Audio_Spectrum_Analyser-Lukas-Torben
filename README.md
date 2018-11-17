### Torben, Lukas
# Arduino Mega Audio Spectrum Analyser mit dem MSGEQ7
<br>

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
  <li><a href="https://www.amazon.de/600pcs-Werte-1Ohm-Metallfolie-Widerst%C3%A4nde-Sortiment/dp/B01LYGIOW4/ref=sr_1_4?ie=UTF8&qid=1540302923&sr=8-4&keywords=widerst%C3%A4nde">1x 22kOhm Widerstand</a></li><br>
</details>
<details>
  <summary>Aktive Bauelemente</summary>
  <br>
  <li><a href="https://www.conrad.de/de/diotec-transistor-bjt-diskret-bc548c-to-92-1-npn-155039.html">49x NPN Transistoren</a></li>
  <li><a href="https://www.amazon.de/gp/product/B01N45KZIR/ref=oh_aui_detailpage_o04_s00?ie=UTF8&psc=1">99x LEDs (28 rote, 29 grüne, 42 gelbe)</a></li><br>

</details>

<br>
<h2 id="bauundinst">Bauelemente und Installation</h2>
<h3 id="bauelemente">Bauelemente</h3>

Als Arduino wird in diesem Fall der <b>Elegoo Mega 2560</b> mit dem ATmega2560-Controller verwendet. Einerseits aufgrund seines günstigen Preises, andererseits wegen der 500mA Überlastungssicherung. Diese ist besonders beim Einsatz vieler kleiner Bauteile wie LEDs und Transistoren mit vielen möglichen Fehlerquellen, wie den Lötstellen und Kabelverbindungen, nützlich, um den Arduino vor Überlastung bei einem Schaltungsfehler zu schützen

Um die einzelnen Frequenzen des Audios korrekt darstellen zu können, muss zunächst das vorhandene Audio in seine einzelnen Frequenzen aufgeteilt werden um anschließend Werte für die Stärke der einzelnen Frequenzen auslesen zu können. Beides kann der <b>Mikrocontroller MSGEQ7</b> durchführen. Das Input-Audio wird dabei in 7 verschiedene Frequenzen aufgeteilt und anschließend die Stärke der einzelnen Frequenzen als Spannungswert auf dem Input ausgeben.

Als LEDs werden Standart-Farbige <b>LED Dioden</b> verwendet, welche mit einem <b>NPN Transistor</b> geschaltet werden. Die NPN Transistoren sind besonders für kleine Spannungen (<5V) gut geeignet, weshalb sie nun auch im gegensatz zu Mosfets verwendet werden.

Als Kondensatoren werden <b>Keramik-Kondensatoren</b> verwendet, da diese, im gegensatz zu Elkos in den kleinen Kapazitäten unter 1uF günstig und oft verfügbar sind.

Sonstige Materialien wie Lochrasterplatine und Litze sind <b>Standart-Elektronik-Komponenten</b> ohne besondere Eigenschaften.


<h3 id="installation">Installation der Entwicklungsumgebung</h3>

Um Programme auf dem Arduino zu installieren, wird eine IDE benötigt. In diesem Fall wird die <b><a href="https://www.elegoo.com/download"> Arduino IDE Version 1.8.6 </a> </b>für Windows verwendet.

Nach der Installation erhält man dann folgende Entwicklungsumgebung:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46620749-de621b00-cb25-11e8-87e8-e45f394e590d.png" width="400px" height="350px"></p>
<br>
Nun müssen noch unter Tools der Arduino-Typ und Port ausgewählt werden. Anschließend lassen sich mit einem Klick auf den Pfeil oben links Programme auf den Arduino laden.

<br> <br>
<h2 id="hardware">Hardware</h2>

<h3 id="msgeq">MSGEQ7 anschließen</h3>
Damit nun der MSGEQ7 Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins <a href="https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf">Datasheet für den Mikrocontroller</a> schauen, auf dem man unter Typical Application eine Anleitung findet:
<br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
Der Reset Pin (Pin 7 des MSGEQ7) sowie der Stope Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt, an einen Analogen Pin des Arduino, in diesem Fall an Pin A0 angeschlossen werden. Zudem muss der Clock Oscillator Pin (Pin 8) über einen 33pF Kondensator und der Ground Pin (Pin 6) über einen 100nF (0.1uF) Kondensator an den Ground Pin des Arduino angeschlossen werden
<br><br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46586617-5e827500-ca81-11e8-806b-150cc4b182ff.png" width="500px"></p>
<br> 

<br>
<h2 id="software">Software</h2>

Ein Arduino-Programm besteht aus zwei Hauptfunktionen: der Setup- und der Loop-Funktion. In der Setup Funktion werden grundlegende Einstellungen getroffen, die vor Programmstart ausgeführt werden müssen. So etwa Pin-Einstellungen und Konfigurationen. Dennoch werden Variablen außerhalb der Setup-Function deklariert. Für den MSGEQ7 sowie die Schaltung der LEDs werden 4 Variablen benötigt:

```
int strope = 13;      // setzt die Zahl des Pins für den Strope-Impuls
int reset = 12;       // setzt die Zahl des Pins für den Reset-Impuls
int analog;          // integer zum zählen bis 7 um die 7 frequenzen auszugeben
int freq[7]         // array mit 7 stellen, um die 7 werte für die frequenzen darin zu speichern

int VerticalOne[7] = {#,#,#,#,#,#,#};
int VerticalTwo[7] = {#,#,#,#,#,#,#};
int VerticalThree[7] = {#,#,#,#,#,#,#};
int VerticalFour[7] = {#,#,#,#,#,#,#};
int VerticalFive[7] = {#,#,#,#,#,#,#};
int VerticalSix[7] = {#,#,#,#,#,#,#};
int VerticalSeven[7] = {#,#,#,#,#,#,#};

```
Die "strope" Variable speichert die Zahl des Pins, welcher den Puls für den Strope Pin am MSGEQ7 ausgibt. Das Gleiche gilt für die "reset" Varibale. Die Varibale "counter" dient dazu, später bis 7 hochzuzählen, um alle 7 Frequenzen auszulesen. Die "frequz" Variable ist ein Array, in dem letztlich die Werte für die Frequenzen gespeichert werden. Alle Varibalen sind Integer, da nur Ganzzahlen verwendet werden.

Zudem werden die Pins für die LEDs, um sie jeweils später zu verwenden, in integer geschrieben. Dabei wird für jede Led ein Pin-Name, bestehend aus Horizontaler und Vertikaler Reihe verwendet:

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

Vor Programmstart werden noch einmal beide Pins auf Low gesetzt. Das dient dazu, dass bei neustart des Programmes beide Pins auch wirklich keine Spannung ausgeben:
``` 
  digitalWrite(reset, LOW);
  digitalWrite(strope, LOW);
  delayMicroseconds(1000);
```
Wie nun im Diagramm zu sehen, muss zu Beginn des Programmes ein Reset-Puls geschaltetet werden. Dies wird durch ein PWM (Pulse-Width-Modulated)-Signal über den Arduino gesteuert. Da dies nur zu Beginn und nur einmal ausgeführt werden muss, kann dies ebenso in die Setup-Funktion. Zudem muss der Strope Puls gestartet werden, sobald der Reset durchgeführt wurde. Beides lässt sich mit folgenden Zeilen bewerkstelligen
``` 
  // MSGEQ7 wie im DataSheet genannt reset'en

digitalWrite(reset, HIGH);
digitalWrite(strobe, HIGH);
delayMicroseconds(500);
digitalWrite(strobe, LOW);
delayMicroseconds(500);
digitalWrite(reset, LOW);
digitalWrite(strobe, HIGH);
delayMicroseconds(500);

```  
<h3 id="loopfunc">Die Loop-Funktion</h3>

Innerhalb des Arduino Programms ist die zweite Funktion die Loop-Funktion. Sie läuft im Gegensatz zur Setup-Funktion, die nur vor Programmstart und nur einmal ausgeführt wird, kontinuerlich durch. Daher ist sie gut geeignet, um kontinuierlich die Werte des MSGEQ7 auszulesen. Dafür wird eine for-Schleife verwendet. Da der MSGEQ7 insgesamt für sieben Frequenzen Werte ausgibt, bevor er von Vorne beginnt, muss die for-Schleife ebenfalls sieben durchläufe haben. Dafür wird zu Beginn der For-Schleife die Varibale "c" (für "counter" deklariert und zu Beginn der Schleife als =0 initialisiert. :

```
for(int c = 0; c < 7; c++) {
	//Hier kommt der Inhalt der for-Schleife rein
}
``` 
Wie dem <a href="#timing">Strope-Timing-Diagramm</a> zu entnehmen, gibt der MSGEQ7 die Wert als Folge des LOW-Schaltens des Strobe Pulses aus. Daher wird zu Beginn der For Schleife der strobe-Pin auf Low geschaltet und ein delayMicroseconds eingefügt.
```
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(500);	
}
```
Als nächstes wird nach dem delay der Input am Analogen Port ausgelesen, welcher zuvor in der Variable analog gespeichert wurde. Dies passiert mit der Funktion analogRead. Diese hat im return einen int Wert, der an der Stelle c (abhängig davon bei welchem Durchlauf sich die for-schleife befindet) im Array freq gespeichert, das wie c ebenfalls 7 Stellen hat: 

```
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(500);
	freq[c] = analogRead(analog);
}
```
Zuletzt wird noch der strobe wieder auf HIGH gesetzt und ein delay eingefügt, um die gleiche Ausgangssituation zum Beginn der nächsten Schleife zu schaffen. Die vollständige Schleife sieht dann so aus:
``` 
for(int c = 0; c < 7; c++) {
	digitalWrite(strobe, LOW);
	delayMicroseconds(500);
	freq[c] = analogRead(analog);
	digitalWrite(strobe, HIGH);
	delayMicroseconds(500);
}
```
Damit nun die LEDs auch nach den Werten aus dem MSGEQ7 geschaltet werden, muss eine weitere for-Schleife genutzt werden. Nachdem das freq array einmal bis zur 7. Stelle gefüllt wurde, werden in der zweiten for-Schleife die Stellen einzelnd ausgelesen und danach die LED-Reihen geschaltet:
```
for(int c = 0; c < 7; c++) {
	//
}
```
Innerhalb der for-Schleife wird dann mithilfe einer if-Schleife geprüft, in welchem Durchgang sich die for Schleife befindet und je nachdem die zugehörige Stelle im freq[c]-Array aufgerufen und ausgelesen. Dann wird geprüft, wie hoch dieser Wert ist und je nachdem unterschiedlich viele LEDs geschaltet. Dies geschieht mit geschachtelten if-Schleifen:
```
for(int c = 0; c < 7; c++) {
	if(c = 0 and freq[c] > 60) {
		digitalWrite(VerticalOne[0], HIGH);
		if(freq[c] > 80) {
			digitalWrite(VerticalOne[1], HIGH);
			if(freq[c] > 110) {
				dititalWrite(VerticalOne[2], HIGH);
				if(freq[c] > 130) {
					digitalWrite(VerticalOne[3], HIGH);
					if(freq[c] >
			}
		}	
	}
}
```
Das wird dann für C: 0-6 widerholt. 

Damit die LEDs nicht einmal angehen und dann an bleiben, müssen sie auch wieder auf LOW geschaltet werden. Dies muss allerdings mit einem kleinen delay ausgeführt werden, damit die LEDs lange genug anbleiben, um sie auch mit dem Auge wahrzunehmen. Es wird also am Ende der for Schleife folgendes eingefügt:

```
delay(50);
digitalWrite(VerticalOne, LOW);
digitalWrite(VerticalTwo, LOW);
digitalWrite(VerticalThree, LOW);
digitalWrite(VerticalFour, LOW);
digitalWrite(VerticalFive, LOW);
digitalWrite(VerticalSix, LOW);
digitalWrite(VerticalSeven, LOW);
```
Damit werden alle LEDs nach einem kleinen delay wieder auf LOW geschaltet. <details> <summary> Der vollständige CODE sieht dann so aus:</summary>

```

int strobe = 13;
int reset = 14;
int analog = A1;
int freq[7];

// LED-Variablen 
int VerticalOne[7] = {#,#,#,#,#,#,#};
int VerticalTwo[7] = {#,#,#,#,#,#,#};
int VerticalThree[7] = {#,#,#,#,#,#,#};
int VerticalFour[7] = {#,#,#,#,#,#,#};
int VerticalFive[7] = {#,#,#,#,#,#,#};
int VerticalSix[7] = {#,#,#,#,#,#,#};
int VerticalSeven[7] = {#,#,#,#,#,#,#};

void setup() {

pinMode(VerticalOne, OUTPUT):
pinMode(VerticalTwo, OUTPUT);
pinMode(VerticalThree, OUTPUT);
pinMode(VerticalFour, OUTPUT);
pinMode(VerticalFive, OUTPUT);
	
pinMode(strobe, OUTPUT);
pinMode(reset, OUTPUT);
pinMode(analog, INPUT);

digitalWrite(strobe, LOW);
digitalWrite(reset, LOW);
delayMicroseconds(1000),

digitalWrite(reset, HIGH);
digitalWrite(strobe, HIGH);
delayMicroseconds(500);
digitalWrite(strobe, LOW);
delayMicroseconds(500);
digitalWrite(reset, LOW);
digitalWrite(strobe, HIGH);
delayMicroseconds(500);
}

void loop() {
	for(int c = 0; c < 7; c++) {
		digitalWrite(strobe, LOW);
		delayMicroseconds(500);
		freq[c] = analogRead(analog);
		digitalWrite(strobe, HIGH);
		delayMicroseconds(500);
	}
	for(int c = 0; c < 7; c++) {
		serial.print(freq[c]);
		serial.print("    ");
		if(c = 0 and freq[c] >= 60) {
			digitalWrite(VerticalOne[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalOne[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalOne[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalOne[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalOne[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalOne[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalOne[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 1 and freq[c] >= 60) {
			digitalWrite(VerticalTwo[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalTwo[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalTwo[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalTwo[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalTwo[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalTwo[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalTwo[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 2 and freq[c] >= 60) {
			digitalWrite(VerticalThree[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalThree[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalThree[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalThree[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalThree[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalThree[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalThree[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 3 and freq[c] >= 60) {
			digitalWrite(VerticalFour[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalFour[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalFour[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalFour[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalFour[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalFour[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalFour[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 4 and freq[c] >= 60) {
			digitalWrite(VerticalFive[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalFive[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalFive[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalFive[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalFive[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalFive[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalFive[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 5 and freq[c] >= 60) {
			digitalWrite(VerticalSix[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalSix[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalSix[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalSix[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalSix[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalSix[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalSix[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
		if(c = 6 and freq[c] >= 60) {
			digitalWrite(VerticalSeven[0], HIGH);
			if(freq[c] >= 80) {
				digitalWrite(VerticalSeven[1], HIGH);
				if(freq[c] >= 100) {
					digitalWrite(VerticalSeven[2], HIGH);
					if(freq[c] >= 120) {
						digitalWrite(VerticalSeven[3], HIGH); 
						if(freq[c] >= 150) {
							digitalWrite(VerticalSeven[4], HIGH);
							if(freq[c] >= 160) {
								digitalWrite(VerticalSeven[5], HIGH);
								if(freq[c] >= 200) {
									digitalWrite(VerticalSeven[6], HIGH);
								}
							}
						}
					}
				}
			}
		}
	}
	serial.println();
	delay(50);
	digitalWrite(LEDS, LOW);	
}
```
</details>

<br>
<h2 id="endprodukt">Endprodukt</h2>

<a href="https://www.youtube.com/watch?v=AfIOBLr1NDU" target="_blank"><img src="http://img.youtube.com/vi/AfIOBLr1NDU/0.jpg" 
alt="MY NAME IS JEFF" width="240" height="180" border="10" /></a>

<br>
<h2 id="quellen">Quellen</h2>

- https://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
- https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf
