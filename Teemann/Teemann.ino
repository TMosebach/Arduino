#include <Servo.h>

//                 0           1          2          3          4          5          6          7          8          9
const byte z[10]={B00000011, B10011111, B00100101, B00001101, B10011001, B01001001, B01000001, B00011111, B00000001, B00001001};  
int max_Winkel=0;      
int min_Winkel=80;  

Servo Arm;
int time = 0;
boolean mitPunkt = false;

void setup() {
  for (int i=2; i <= 9; i++) // 2-10 sind Ausgänge
    pinMode(i,OUTPUT);

  pinMode(A1, INPUT);        // ON and minutes select switch
  pinMode(A2, INPUT);       // Start / Stop select switch

  segmente(z[time]);

  Arm.attach(11);         // attaches the servo Arm to pin D11 servo object
  Arm.write(min_Winkel);          // tell servo 1 to go to position 10°
}

void loop() {
  if (analogRead(A1) > 900 ) addZiehMinute();
  if (analogRead(A2) > 900 ) startZiehen();
}

void startZiehen() {
  // Erst starten, wenn Taster wieder losgeladden
  do { delay(20); }while (analogRead(A2)>500);

  // Teebeutel senken
  // Tee Beutel langsam abwärts bis zum eingestellten Winkel
    for (int p = min_Winkel; p >=max_Winkel; p--){
      Arm.write(p);
      delay(20);
    }  
  
  while(time > 0) {
    
    for(int i=1; i<60; i++) {
      if(mitPunkt) {
        digitalWrite(9, LOW);
        mitPunkt = false;
      } else {
        digitalWrite(9, HIGH);
        mitPunkt = true;
      }
      delay(1000);
      if (analogRead(A2) > 900 ) {
        time = 0;
        break; 
      }
    }

    time--;
    segmente(z[time]);
  }

  for (int p = max_Winkel; p <=min_Winkel; p++){
    Arm.write(p);          // tell servo 1 to go to position xx degree out of Tea slowly !!
    delay(20);
  }
  tone(10, 440, 1000);

  segmente(z[time]);
}


void segmente(byte n) {
// alle 7 Segmente ansteuern

  for(int k=2; k <= 9; k++) {
    if((n & B10000000) > 0)
      digitalWrite(k, HIGH);
    else 
      digitalWrite(k, LOW);
    n = n << 1;
  }  
}

void addZiehMinute() {
  time++;
  if (time == 10) time = 1;
  segmente(z[time]);
  delay(500);
}
 
