#include "pitches.h"

#define SPEAKER 2
#define STEPS 16

uint8_t activeButton, patternStep = 0, pattern[STEPS];
uint8_t buttons[] = {3, 4, 5, 7};
uint8_t leds[] = {6, 9, 10, 11};
uint16_t notes[] = {NOTE_FS4, NOTE_DS4, NOTE_CS4, NOTE_GS3, NOTE_FS1};

byte buttonState[] {LOW, LOW, LOW, LOW};
  
void setup() {
  pinMode(SPEAKER, OUTPUT);
  for(uint8_t i=0 ; i<4; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    tone(SPEAKER, notes[i]);
    delay(220);
    noTone(SPEAKER);
    digitalWrite(leds[i], LOW);
  }
  randomSeed(analogRead(0));
  for(uint8_t i=0 ; i<STEPS ; i++) {
    pattern[i] = random(0,4);
  }
  delay(1000);
}

void loop() {
}

void playPattern(uint8_t toStep) {
  for(uint8_t i=0 ; i<= toStep ; i++) {
    tone(SPEAKER, notes[pattern[i]], 300);
    digitalWrite(leds[pattern[i]], HIGH);
    delay(350);
    noTone(SPEAKER);
    digitalWrite(leds[pattern[i]], LOW);
  }
  delay(1000);
}
  
void sense(uint8_t patternStep) {
  byte newButtonState;
  
  for(uint8_t i=0 ; i<4; i++) {
    newButtonState = digitalRead(buttons[i]);
    digitalWrite(leds[i], newButtonState);
    if(newButtonState != buttonState[i]) {
      if(newButtonState == HIGH) {
        activeButton = i;
        noTone(SPEAKER);
        tone(SPEAKER, notes[i]);
      } else {
        if(activeButton == i) {
          noTone(SPEAKER);
        }
      }
    }
    buttonState[i] = newButtonState;
  }
}
