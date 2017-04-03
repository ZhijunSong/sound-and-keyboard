#include "pitches.h"
#include <Wire.h>
#include "Adafruit_MPR121.h"
Adafruit_MPR121 cap = Adafruit_MPR121();
int speaker= 9;
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
int notes[ ]={
 NOTE_C4,
 NOTE_CS4,
 NOTE_D4, 
 NOTE_DS4,
 NOTE_E4,
 NOTE_F4,
 NOTE_FS4,
 NOTE_G4,
 NOTE_GS4,
 NOTE_A4,
 NOTE_AS4,
 NOTE_B4 
};
const int threshold= 20;
int ledPin=5;

void setup() {
 Serial.begin(9600);
 while (!Serial) {
    delay(10);
  }
 Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
 if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  pinMode(speaker,OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  currtouched = cap.touched();
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched");
        tone(9,notes[i], 500);
         
        digitalWrite(ledPin, HIGH);
    }
    
 if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
       Serial.print(i); Serial.println(" released");
        digitalWrite(ledPin, LOW);


 }
         //delay(tempo / 2); 

  }
    lasttouched = currtouched;

}


