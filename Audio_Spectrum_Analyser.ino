int strobe = 12;    // Strobe Pin on the MSGEQ7
int reset = 13;    // Reset Pin on the MSGEQ7
int analog = A1;   // Output Pin on the MSGEQ7
int freq[7];          // An array to hold the values from the 7 frequency bands

void setup() { 
  Serial.begin (9600); 
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
  for (int c = 0; c < 7; c++) {    
    Serial.print       (freq[c]);
    Serial.print       ("   ");  
    
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
