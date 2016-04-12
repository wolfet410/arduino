#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

static const long int BUTTON0 = 0xFF6897;
static const long int BUTTON1 = 0xFF30CF;
static const long int BUTTON2 = 0xFF18E7;
static const long int BUTTON3 = 0xFF7A85;
static const long int BUTTON4 = 0xFF10EF;
static const long int BUTTON5 = 0xFF38C7;
static const long int BUTTON6 = 0xFF5AA5;
static const long int BUTTON7 = 0xFF42BD;
static const long int BUTTON8 = 0xFF4AB5;
static const long int BUTTON9 = 0xFF52AD;
static const long int BUTTONGIVEUP = 0xFF9867;

static const byte DIGIT[14][7] = {
  { 1,1,1,1,1,1,0 }, // 0
  { 0,1,1,0,0,0,0 }, // 1
  { 1,1,0,1,1,0,1 }, // 2
  { 1,1,1,1,0,0,1 }, // 3
  { 0,1,1,0,0,1,1 }, // 4
  { 1,0,1,1,0,1,1 }, // 5
  { 1,0,1,1,1,1,1 }, // 6
  { 1,1,1,0,0,0,0 }, // 7
  { 1,1,1,1,1,1,1 }, // 8
  { 1,1,1,0,0,1,1 }, // 9
  { 1,0,0,0,0,0,0 }, // top
  { 0,0,0,0,0,0,1 }, // middle
  { 0,0,0,1,0,0,0 }, // bottom
  { 1,0,0,1,0,0,1 }  // reset
};

int numberToGuess = (rand() % (int)(10));
int dot = 0;
int dotCount = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  irrecv.enableIRIn();
}

void sevenSegWrite(byte key) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, DIGIT[key][segCount]);
    ++pin;
  }
  delay(2000);
  sevenSegClear();
}

void sevenSegClear() {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, 0);
    ++pin;
  }
}

void sevenSegDot(byte dot) {
  digitalWrite(9, dot);
}

void loop() {

  int guessed = 999;

  ++dotCount;
  if (dotCount == 32767) {
    dot ^= 1;
    sevenSegDot(dot);
    dotCount = 0;
  }
 
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case BUTTONGIVEUP:
        numberToGuess = (rand() % (int)(10));
        sevenSegWrite(13);
        break;
      case BUTTON0:
        guessed = 0;
        sevenSegWrite(0);
        break;
      case BUTTON1:
        guessed = 1;
        sevenSegWrite(1);
        break;
      case BUTTON2:
        guessed = 2;
        sevenSegWrite(2);
        break;
      case BUTTON3:
        guessed = 3;
        sevenSegWrite(3);
        break;
      case BUTTON4:
        guessed = 4;
        sevenSegWrite(4);
        break;
      case BUTTON5:
        guessed = 5;
        sevenSegWrite(5);
        break;
      case BUTTON6:
        guessed = 6;
        sevenSegWrite(6);
        break;
      case BUTTON7:
        guessed = 7;
        sevenSegWrite(7);
        break;
      case BUTTON8:
        guessed = 8;
        sevenSegWrite(8);
        break;
      case BUTTON9:
        guessed = 9;
        sevenSegWrite(9);
        break;
    }

    if (guessed != 999) {
      if (guessed == numberToGuess) {
        sevenSegWrite(11);
        numberToGuess = (rand() % (int)(10));
      } else if (guessed < numberToGuess) {
        sevenSegWrite(12);
      } else if (guessed > numberToGuess) {
        sevenSegWrite(10);
      }
    }
    
    irrecv.resume();
  }

}
