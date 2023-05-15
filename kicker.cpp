#include <Arduino.h>
#include "kicker.h"

kicker::kicker(int kicker)
{
  pinMode(kicker, INPUT);

  _kicker = kicker;

}

void kicker::kickerRead()
{
      kickerTrack = digitalRead(_kicker);
  // compare the buttonState to its previous state
  
  if (kickerTrack != kickerState) {
    // if the state has changed, increment the counter
    if (kickerTrack == HIGH) {
    score = score + point;
    Serial.println("DONG");
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
   kickerState = kickerTrack;
  return;
}