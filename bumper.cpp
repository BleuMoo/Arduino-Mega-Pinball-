#include <Arduino.h>
#include "bumper.h"

bumper::bumper(int bumper)
{
  pinMode(bumper, INPUT);

  _bumper = bumper;

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
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   bumperState = bumperTrack;
  return;
}