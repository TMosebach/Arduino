const int LED = 13;
volatile boolean blink = false;

void setup() {
  pinMode(LED, OUTPUT);
  cli(); // disable interrupts

  TCCR1A = 0;
  TCNT1  = 0;
  TCCR1B = 0;
  
  // Set CS12 and CS10 bits for 1:1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10); 
  
  // turn on CTC mode
  TCCR1B |= (1 << WGM12); 

  OCR1A = 15624; // Sekunde 15624

  // enable timer compare interrupt A
  TIMSK1 |= (1 << OCIE1A); 

  sei(); // allow interrupts
}

void loop() {
  // erst mal nix tun
}

ISR(TIMER1_COMPA_vect) {
  blink = blink?false:true;
  digitalWrite(LED, blink?HIGH:LOW);
}
