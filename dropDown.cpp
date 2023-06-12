#include <Arduino.h>
#include "dropDown.h"

dropDown::dropDown(int drop1, int drop2, int drop3, int dropReset, int dropSound)
{
  pinMode(drop1, INPUT);
  pinMode(drop2, INPUT);
  pinMode(drop3, INPUT);
  pinMode(dropReset, OUTPUT);
  pinMode(dropSound, OUTPUT);
  _drop1 = drop1;
  _drop2 = drop2;
  _drop3 = drop3;
  _dropReset = dropReset;
   _dropSound = dropSound;
}

void dropDown::targets()
{
    
    dropDownTrack1 = digitalRead(_drop1);
    dropDownTrack2 = digitalRead(_drop2);
    dropDownTrack3 = digitalRead(_drop3);
  // compare the buttonState to its previous state
  
  if (dropDownTrack1 != dropDownState1) {
    // if the state has changed, increment the counter
    if (dropDownTrack1 == HIGH) {
    score = score + point;
     Serial.println("DOH1");
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  if (dropDownTrack2 != dropDownState2) {
    // if the state has changed, increment the counter
    if (dropDownTrack2 == HIGH) {
    score = score + point;
     Serial.println("DOH2");
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
 if (dropDownTrack3 != dropDownState3) {
    // if the state has changed, increment the counter
    if (dropDownTrack3 == HIGH) {
    score = score + point;
     Serial.println("DOH3");
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  dropDownState1 = dropDownTrack1;
  dropDownState2 = dropDownTrack2;
  dropDownState3 = dropDownTrack3;
 
  return;
}

void dropDown::reset()
{
 if (dropDownTrack1 == HIGH && dropDownTrack2 == HIGH && dropDownTrack3 == HIGH)
 {
   digitalWrite(_dropReset, HIGH);
   delay(50);
   digitalWrite(_dropSound, HIGH);
   delay(10);
   digitalWrite(_dropReset, LOW);
   delay(10);
   digitalWrite(_dropSound, LOW);
   Serial.println("drop down reset");
  }

}