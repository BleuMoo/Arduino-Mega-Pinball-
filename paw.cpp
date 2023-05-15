#include <Arduino.h>
#include "paw.h"

paw::paw(int claw)
{
  pinMode(claw, INPUT);

  _claw = claw;

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
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   clawState = clawTrack;
  return;
}