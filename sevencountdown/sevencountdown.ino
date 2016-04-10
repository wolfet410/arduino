byte seven_seg_digits[7][7] = { 
                                 { 1,1,1,0,1,1,1 },  // = a 
                                 { 0,0,1,1,1,0,0 },  // = u
                                 { 0,0,1,1,1,1,1 },  // = b
                                 { 0,0,0,0,1,0,1 },  // = r
                                 { 0,0,0,0,1,0,0 },  // = i
                                 { 1,1,0,1,1,1,1 },  // = e
                                 { 0,0,0,0,0,0,0 },  // = null
                                };

void setup() {                
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT); // aubrie was here my name is aubrie 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  writeDot(0);  // start with the "dot" off
}

void writeDot(byte dot) {
  digitalWrite(9, dot);
}
    
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  for (byte count = 0; count < 7; count++) {
   delay(1000);
   sevenSegWrite(count); 
  }
  delay(4000);
}

