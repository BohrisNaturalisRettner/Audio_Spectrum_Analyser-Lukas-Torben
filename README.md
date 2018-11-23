### Torben, Lukas
# Arduino Mega Audio Spectrum Analyser mit dem MSGEQ7

<h1>Das Projekt</h1>
Ein Audio Spectrum Analyzer ist ein Gerät, um Audio neben dem akustischen Eindruck auch visuell darzustellen. Um zu verstehen, wie das ganze funktioniert, ist es zunächst wichtig, den Aufbau von Audiosignalen zu verstehen:

<p align="center"><img width="400px" src="https://user-images.githubusercontent.com/42578917/48780230-bdbae280-ecd9-11e8-8181-92e17ee0fbf0.jpg"></p>

Wie zu erkennen, ist Audio aus verschiedenen Frequenzen, oft im Bereich von kHz, aufgebaut. Ein Audio Spectrum Analyser misst die Stärke bestimmter Frequenzen und gibt diese als visuelles Signal, oft in Form eines Balkens, der entsprechend stark oder schwach ausschlägt, wieder. Dieser Analyser tut genau das. Mittels eines Mikrocontrollers werden 7 Frequenzen des eingespeisten Audios durch einen Filter gemessen. Die erhaltenen Werte werden dann als Spannungswerte an einen Arduino übergeben. Dieser speichert die Werte in einer Variable, liest diese dann aus und schaltet dann je nach Höhe des Wertes 1-6 LEDs, die für alle 7 Frequenzen vorgesehen sind. Die LEDs sind mit Transistoren verbunden, der Arduino schaltet dann nur eine Spannung auf die Base, fungiert also quasi als das Bauteil, was den Lichtschalter umlegt, womit die LED angeht. 

Im folgenden kommt zu diesem Projekt eine <a href="#komponenten">Komponentenliste</a>, eine <a href="#software">Software-</a> und eine <a href="#hardware">Hardware-Anleitung</a>:

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
  <li><a href="https://www.amazon.de/gp/product/B073X7GZ1P/ref=oh_aui_detailpage_o04_s00?ie=UTF8&psc=1">Steckbrett mit Jumper-Kabeln</a></li>
  <li><a href="https://www.amazon.de/Multimeter-Widerstand-Messleitung-Messspitzen-Krokodilklemmen/dp/B01N2NI76Y/ref=sr_1_18?ie=UTF8&qid=1542919729&sr=8-18&keywords=multimeter">Multimeter</a></li>
  <li><a href="https://www.amazon.de/Digitale-L%C3%B6tstation-L%C3%B6tkolben-regelbar-Entl%C3%B6tpumpe/dp/B00N7KWIZ0/ref=sr_1_21_sspa?ie=UTF8&qid=1542919761&sr=8-21-spons&keywords=l%C3%B6tkolben&psc=1">Lötkolben und Lötzinn</a></li>
  <li><a href="https://www.conrad.de/de/tru-components-su528455-europlatine-ohne-cu-auflage-hartpapier-l-x-b-160-mm-x-100-mm-rastermass-254-mm-inhalt-1-st-1566655.html">Lochrasterplatine</a></li><br>
  </details>
<details>
  <summary>Passive Bauelemente</summary>
  <br>
  <li><a href="https://www.conrad.de/de/keramik-kondensator-radial-bedrahtet-100-nf-100-vdc-10-holystone-rdcx104k101dka-1-st-531746.html">2x 100nF Keramik-Kondensatoren</a></li>
  <li><a href="https://www.conrad.de/de/keramik-kondensator-radial-bedrahtet-33-pf-100-vdc-5-holystone-rdcn330j101dka-1-st-531789.html">1x 33pF Keramik-Kondensator</a></li>
  <li><a href="https://www.conrad.de/de/keramik-kondensator-radial-bedrahtet-10-nf-50-vdc-10-holystone-rdc103k050dka-1-st-531889.html">1x 10nF Keramik-Kondensator</a></li>
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

Um die einzelnen Frequenzen des Audios korrekt darstellen zu können, muss zunächst das vorhandene Audio in seine einzelnen Frequenzen aufgeteilt werden um anschließend Werte für die Stärke der einzelnen Frequenzen auslesen zu können. Beides kann der <b>Mikrocontroller MSGEQ7</b> durchführen. Das Input-Audio wird dabei in 7 verschiedene Frequenzen aufgeteilt und anschließend die Stärke der einzelnen Frequenzen als Spannungswert auf dem Output ausgeben.

Als LEDs werden standart farbige <b>LED Dioden</b> verwendet, welche mit einem <b>NPN Transistor</b> geschaltet werden. Die NPN Transistoren sind besonders für kleine Spannungen (<5V) gut geeignet, weshalb sie nun auch im Gegensatz zu Mosfets verwendet werden.

Als Kondensatoren werden <b>Keramik-Kondensatoren</b> verwendet, da diese, im Gegensatz zu Elkos, in den kleinen Kapazitäten unter 1uF günstig und oft verfügbar sind.

Sonstige Materialien wie Lochrasterplatine und Litze sind <b>Standart-Elektronik-Komponenten</b> ohne besondere Eigenschaften.


<h3 id="installation">Installation der Entwicklungsumgebung</h3>

Um Programme auf dem Arduino zu installieren, wird eine IDE benötigt. In diesem Fall wird die <b><a href="https://www.elegoo.com/download"> Arduino IDE Version 1.8.6 </a> </b>für Windows verwendet.

Nach der Installation erhält man dann folgende <b>Entwicklungsumgebung</b>:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46620749-de621b00-cb25-11e8-87e8-e45f394e590d.png" width="400px" height="350px"></p>
<br>
Nun müssen noch unter Tools der Arduino-Typ und Port ausgewählt werden. Anschließend lassen sich mit einem Klick auf den Pfeil oben links Programme auf den Arduino laden. Unten ist zudem eine Kommandozeile vorhanden, in der im Falle von Fehlern ein Fehlercode angezeigt wird. Zudem lässt sich unter Werkzeuge der Serielle Monitor öffnen, der in Folge der Verwendung des Serial.print - Arguments die am Arduino Input gemessenen Werte ausgibt. Dies ist besonders für Prototyp-Phasen und Tests sehr sinnvoll, um nachzuvollziehen, ob überhaupt Daten beim Arduino ankommen.

Zuletzt ist noch das Häckchen oben links wichtig. Dieses überprüft den eingegebenen Code und gibt im Zweifelsfall einen Fehler aus. Dies verhindert das Beschädigen von Bauteilen beim Hochladen, wenn fehlerhafter Code verwendet wurde.
<br> <br>
<h2 id="hardware">Hardware</h2>
Nach der Installation der Entwicklungsumgebung muss zunächst die Hardware gebaut werden um zuletzt das Programm zu schreiben. Hierbei sind es der MSGEQ7 und die LEDs, die richtig verkabelt werden müssen.
<h3 id="msgeq">MSGEQ7 anschließen</h3>
Damit nun der <b> MSGEQ7</b> Daten auswirft, muss er korrekt verkabelt werden. Um dies zu tun muss man ins <a href="https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf">Datasheet für den Mikrocontroller</a> schauen, auf dem man unter Typical Application eine Anleitung findet:
<br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46585373-62f26200-ca70-11e8-92b2-6da1fc322290.png" width="300px" align="center"></p>
Der Reset <b>Pin</b> (Pin 7 des MSGEQ7) sowie der Strobe Pin (Pin 4 des MSGEQ7) werden beim Arduino auf einen der PWM-Pins gelegt, in diesem Fall auf Pin 12 und 13. Ausserdem wird der MSGEQ7 von dem 5V Pin sowie dem GND-Pin des Arduino gespeist. Zudem muss der Pin 3 des MSGEQ7, welcher letztlich die Werte für die Frequenzen ausgibt an einen Analogen Pin des Arduino, in diesem Fall an Pin A1, angeschlossen werden. Zuletzt muss der Clock Oscillator Pin (Pin 8) über einen 33pF Kondensator und der Ground Pin (Pin 6) über einen 100nF (0.1uF) Kondensator an den Ground Pin des Arduino angeschlossen werden
<br><br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/46586617-5e827500-ca81-11e8-806b-150cc4b182ff.png" width="500px"></p>
<br>
Die Schaltung wird dann auf eine Lochrasterplatine gebracht und verlötet. Wenn alles verlötet und verkabelt ist, sieht es wie folgt aus:
<br><br>
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48710165-cba03300-ec07-11e8-9344-279011aea2b7.jpg" width="400px"></p>

Desweiteren müssen die LEDs inklusive Transistoren und Widerständen verlötet werden. Die (in diesem Fall blauen) LEDs brauchen eine Spannung von 3V und verbrauchen 20mA. Nach dem Ohm'schen Gesetz U=R x I wird bei einer Versorgungsspannung von 5V, also einem Spannungsabfall von 2V und einem Strombedarf von 20mA, nach R umgestellt R = U/I, ein Widerstand von 100Ohm benötigt
<p align="center">U = R x I	| : I </p>
<p align="center">R = U / I</p>

Da auf die LEDs direkt draufgesehen werden soll (da ein Analyzer vor allem zum Anschauen gedacht ist) sind die LEDs mit 20mA deutlich zu hell. <a href="https://www.amazon.de/gp/product/B01N45KZIR/ref=oh_aui_detailpage_o04_s00?ie=UTF8&psc=1">Bei diesen LEDs</a> ist eine Reduzierung auf 15mA deutlich ansehnlicher. Nach dem Ohmschen Gesetz ergibt dies einen Widerstand von 133,333333 Ohm. In Verbindung mit den vorhandenen <a href="https://www.amazon.de/gp/product/B01LYGIOW4/ref=oh_aui_detailpage_o04_s01?ie=UTF8&psc=1">Widerständen</a> wird in diesem Fall ein 150Ohm Widerstand verwendet, womit ungefähr ~13mA durch die LEDs fließen. 

Die LEDs werden mit einem Transistor geschaltet. In Verbindung mit dem Vorwiderstand sieht die Schaltung für die Verwendung des NPN Transistors als Schalter so aus: 
<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48922518-8dc13a00-eea7-11e8-8692-49f0bb404116.png" width="200px"></p>

In dieser Konfiguration werden dann alle LEDs mit den jeweils einem Widerstand und einem Transistor auf eine Lochrasterplatine gelötet. Das Kabel von der Base des Transistor wird mit jeweils einem Pin auf dem Arduino verbunden:

<p align="center"><img src="https://user-images.githubusercontent.com/42578917/48922649-8babab00-eea8-11e8-880f-5cbc22d26c3e.jpg" width="500px"></p>

Mit dieser Hauptplatine ist auch der letzte Teil der Hardware beendet.
<h2 id="software">Software</h2>

Nachdem nun die Hardware konfiguriert wurde, kann die Software geschrieben werden. 

Innerhalb des Programmes muss folgender Ablauf ausgeführt werden.

1. MSGEQ7 nach dem Datasheet einen Reset und mehrere Strobe-Pulse geben
2. Analogen Input des Arduino auslesen und Wert in Variable speichern
3. Variable auslesen und danach die Pins und damit die LEDs schalten 

Ein Arduino-Programm besteht aus zwei <b>Hauptfunktionen</b>: der Setup- und der Loop-Funktion. In der Setup Funktion werden grundlegende Einstellungen getroffen, die vor Programmstart ausgeführt werden müssen. So etwa Pin-Einstellungen und Konfigurationen. Dennoch werden Variablen außerhalb der Setup-Funktion deklariert. Für den MSGEQ7 werden folgende Variablen benötigt: 

```
int strobe = 13;      // setzt die Zahl des Pins für den Strope-Impuls
int reset = 12;       // setzt die Zahl des Pins für den Reset-Impuls
int analog = A0;          // integer zum zählen bis 7 um die 7 frequenzen auszugeben
int freq[7];         // array mit 7 stellen, um die 7 werte für die frequenzen darin zu speichern
```
Die "strobe" <b>Variable</b> speichert die Zahl des Pins, welcher den Puls für den Strobe Pin am MSGEQ7 ausgibt. Das Gleiche gilt für die "reset" Varibale. Die Variable "analog" dient dazu, später bis 7 hochzuzählen, um alle 7 Frequenzen auszulesen. Die "freq[7]" Variable ist ein Array, in dem letztlich die Werte für die Frequenzen gespeichert werden. Alle Varibalen sind Integer, da nur Ganzzahlen verwendet werden und Integer dafür durch den kleinen Speicherbedarf am besten geeignet sind.

<h3 id="setupfunc">Setup Funktion</h3>
Alle zuvor initialisierten Variablen enthalten Pins. Diese müssen nun als Output bzw. Input innerhalb der Setup Funktion des Arduino Programms klassifiziert werden, damit der Arduino weiß, ob die Pins Input oder Output sind: 

```
  pinMode(strobe, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(analog, INPUT);
``` 
Damit nun der MSGEQ7 auch Daten für die Frequenzen ausgibt, muss er zuvor verschiedene Signale vom Arduino erhalten. Ein genaues Diagramm dazu ist im Datasheet des Mikrocontrollers zu finden: 

<p id="timing" align="center"><img src="https://user-images.githubusercontent.com/42578917/47381631-bfa47c80-d700-11e8-978a-600b845e36c2.png" width="600px"></p>

<b>Vor Programmstart</b> werden noch einmal beide Pins auf LOW gesetzt. Das dient dazu, dass bei Neustart des Programmes beide Pins auch wirklich keine Spannung ausgeben:
``` 
  digitalWrite(reset, LOW);
  digitalWrite(strope, LOW);
  delayMicroseconds(500);
```
Wie nun im Diagramm zu sehen muss zu Beginn des Programmes ein <b>Reset</b>-Puls geschaltetet werden. Dies wird durch ein PWM (Pulse-Width-Modulated)-Signal über den Arduino gesteuert. Da dies nur zu Beginn und nur einmal ausgeführt werden muss, kann dies ebenso in die Setup-Funktion. Zudem muss der Strope Puls gestartet werden sobald der Reset durchgeführt wurde. Dieser muss aber, wie im Diagramm zu erkennen, konstant geschaltet werden. Beides lässt sich mit folgenden Zeilen bewerkstelligen:
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
Die delayMicroseconds - Argumente sorgen dann dafür, das der HIGH, oder eben der LOW, auch eine gewisse Zeit anhält. Das dies notwendig ist, ist gut im<a href="#timing">Diagramm</a> zu erkennen.

<h3 id="loopfunc">Die Loop-Funktion</h3>

Innerhalb des Arduino  Programms ist die zweite Funktion die <b>Loop-Funktion</b>. Sie läuft im Gegensatz zur Setup-Funktion, die nur vor Programmstart und nur einmal ausgeführt wird, kontinuerlich durch. Daher ist sie gut geeignet, um kontinuierlich die Werte des MSGEQ7 auszulesen. Dafür wird eine for-Schleife verwendet. Da der MSGEQ7 insgesamt für sieben Frequenzen Werte ausgibt, bevor er von vorne beginnt, muss die for-Schleife ebenfalls sieben durchläufe haben. Dafür wird zu Beginn der For-Schleife die Varibale "c" (für "counter" deklariert und zu Beginn der Schleife als =0 initialisiert. Mit c < 7 wird die obere Grenze definiert und mittels c++ wird pro Durchlauf c und 1 hochgezählt bis zur oberen Grenze.:

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
Als nächstes wird nach dem delay der Input am analogen Port ausgelesen, welcher zuvor in der Variable analog gespeichert wurde. Dies passiert mit der Funktion analogRead. Diese hat im return einen int Wert vom MSGEQ7, der an der Stelle c (abhängig davon bei welchem Durchlauf sich die for-schleife befindet) im Array freq gespeichert wird, das wie c ebenfalls 7 Stellen hat: 

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
Damit nun die LEDs auch nach den Werten aus dem MSGEQ7 geschaltet werden, muss nach der for-Schleife eine IF-Schleife genutzt werden. Nachdem das freq Array einmal bis zur 7. Stelle gefüllt wurde, werden die Stellen einzelnd ausgelesen und danach die LED-Reihen geschaltet.
<br>
Es wird mithilfe einer if-Schleife geprüft, wie hoch der Wert an der 0.,1.,2.3.... Stelle im freq[] Array ist und je nachdem unterschiedlich viele LEDs geschaltet. Dies geschieht mit geschachtelten if-Schleifen:
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
Die Pins sind dabei genauso wie beim HIGH schalten die Pins, an die die jeweiligen LEDs angeschlossen sind.
<br>
<h2 id="endprodukt">Endprodukt</h2>

Als letztes bleibt nur noch, ein geeignetes Gehäuse für alle Komponenten zu bauen und im Zweifel noch ein bisschen an den Grenzen zu schrauben, an welcher eine bestimmte LED bei einem bestimmten Wert geschaltet wird. Mit den in dieser Anleitung genutzten Komponenten, sieht das Endprodukt dann in Aktion wie folgt aus:

<p align="center"><a href="https://www.youtube.com/watch?v=c1khyxLBbP0&feature=youtu.be"><img src="https://user-images.githubusercontent.com/42578917/48955845-1abfce00-ef50-11e8-8d36-40bc57f555c4.png" width="400px"></a></p>

In diesem Repository lässt sich außerdem der Komplette Code innerhalb der Datei "Audio_Spectrum_Analyser.ino" anschauen oder per Git-Pull ins eigene Repository übertragen. Dies ist eine Arduino IDE Datei, die direkt in der Arduino IDE geöffnet werden und hochgeladen werden kann!
<h2 id="quellen">Quellen</h2>

- https://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
- https://www.sparkfun.com/datasheets/Components/General/MSGEQ7.pdf

