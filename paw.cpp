#include <Arduino.h>
#include "paw.h"
// #include <TMRpcm.h>

paw::paw(int claw, int clawSound)
{
  pinMode(claw, INPUT);
  pinMode(clawSound, OUTPUT);

  _claw = claw;
  _clawSound = clawSound;

}

void paw::claw()
{
      clawTrack = digitalRead(_claw);
  // compare the buttonState to its previous state
  
  if (clawTrack != clawState) {
    // if the state has changed, increment the counter
    if (clawTrack == HIGH) {
    score = score + point;
    Serial.println("DUHHH");
    digitalWrite(_clawSound, HIGH);
    delay(50);
    digitalWrite(_clawSound, LOW);
  }

    // Delay a little bit to avoid bouncing
    delay(50);
  }
   clawState = clawTrack;
  return;
}