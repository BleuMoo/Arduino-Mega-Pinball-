#include <Arduino.h>
#include "bumper.h"

bumper::bumper(int bumper, int bumperReset, int bumperSound)
{
  pinMode(bumper, INPUT);
  pinMode(bumperReset, OUTPUT);
  pinMode(bumperSound, OUTPUT);
  _bumperReset = bumperReset;
  _bumper = bumper;
  _bumperSound = bumperSound;

}

void bumper::bumperRead()
{
      bumperTrack = digitalRead(_bumper);
  // compare the buttonState to its previous state
  
  if (bumperTrack != bumperState) {
    // if the state has changed, increment the counter
    if (bumperTrack == HIGH) {
    score = score + point;
    Serial.println("DWAY");
    //delay(10);
    digitalWrite(_bumperReset, HIGH);
    digitalWrite(_bumperSound, HIGH);
    delay(50);
    digitalWrite(_bumperReset, LOW);
    digitalWrite(_bumperSound, LOW);
  }
      delay(50);
  }
   bumperState = bumperTrack;

  return;
}