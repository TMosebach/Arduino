const int LED = 13;
volatile boolean blink = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SUMMER, OUTPUT);
  cli(); // disable interrupts

  // Timer 1 ca. 1 Sekunde
  
  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // set counter value to 0
  
  OCR1A = 31249; // set compare match register 15624 1S; 62499 4S 31249 2S
  
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1:1024 prescaler

  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt

  sei(); // allow interrupts
}

void loop() {
  // erst mal nix tun
}

ISR(TIMER1_COMPA_vect) {
  blink = blink?false:true;
  digitalWrite(LED, blink?HIGH:LOW);
}
