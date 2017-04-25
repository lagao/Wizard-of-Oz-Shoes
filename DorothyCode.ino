
#include "pitches.h"
// notes in the melody:
const int buttonPin = 4; // the number of the pushbutton pin

int melody[] = { 
  NOTE_G4, NOTE_C5, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, 0, 
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_C4, //dorothy
  0, 0, 0, 0,  //reset, number is 620-253-0142 (0 means hold silent for 1 whole note)
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, //6
  NOTE_C4, NOTE_D4,//2
  0, 0, //0
  NOTE_C4, NOTE_D4,//2
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, //5
  NOTE_C4, NOTE_D4, NOTE_E4,//3
  0, 0, //0
  NOTE_C4, //1
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, //4
  NOTE_C4, NOTE_D4,//2  
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 8, 4, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 8, 2, //dorothy theme
  2, 2, 2, 2, //reset
  8, 8, 8, 8, 8, 2, //6
  8, 2, //2
  2, 2,//0
  8, 2, //2
  8, 8, 8, 8, 2, //5
  8, 8, 2, //3
  2, 2,//0
  2, //1
  8, 8, 8, 2, //4
  8, 2, //2
};
int count=0;
int timer = 0;
int Pr = 0; // will be used for analog 0.
int PrValue = 0; // value of output
int Pr_Input = 75; // value of when light is on
int LED_pin = 6;

bool isOn = false;

// variables will change:
int buttonState = HIGH; // variable for reading the pushbutton status

void setup() {
// initialize the pushbutton pin as an input:
pinMode(3, OUTPUT);
digitalWrite(3, LOW); //button is pressed, it's low
pinMode(buttonPin, INPUT_PULLUP); //resister is now inside arduino. when not pressed, means pull-up = high
pinMode(5, OUTPUT); //LED
digitalWrite(5, LOW);
pinMode(LED_pin, OUTPUT);
pinMode(7, OUTPUT); //photo resister low (artificial ground)
pinMode(12, OUTPUT); //photo resister high (artificial power)
digitalWrite (7, LOW);
digitalWrite (12, HIGH);
pinMode(10, OUTPUT); //speaker artificial ground
pinMode(11, OUTPUT); //speaker port 11

timer = millis();
Serial.begin(9600); //start serial Monitor
}

void loop(){
  if (millis() > timer + 4000) {
    timer = millis();
    count = 0;
  }

  if (buttonState == HIGH) {
    
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    
    // check if the pushbutton is pressed.
    // if it is, the buttonState is LOW:
    if (buttonState == LOW) {
      count++;
    }
  }
  
  buttonState = digitalRead(buttonPin);

  
  if (count == 3) {
     
    // this is the change
    isOn = !isOn;
    count = 0;
    
    // this is the action
    if (isOn) {
        for (int thisNote = 0; thisNote < 49; thisNote++) {

          int noteDuration = 1000 / noteDurations[thisNote];
      tone(11, melody[thisNote], noteDuration); // sound tone
      int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    PrValue = analogRead(Pr);

delay(1); // value updated every 0.001 second.

if (PrValue < Pr_Input) // if sensor value is less than 10, light will turn on.

{ digitalWrite(LED_pin, HIGH);//LED on 

    } 
        }
    } else {
      noTone(11);
       digitalWrite(LED_pin, LOW);// LED off 
    }
  }
  delay(10);
}

