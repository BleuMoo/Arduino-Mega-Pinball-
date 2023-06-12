#include <Arduino.h>
#include "kicker.h"

kicker::kicker(int kicker, int kickerSound)
{
  pinMode(kicker, INPUT);
  pinMode(kickerSound, OUTPUT);
  _kicker = kicker;
  _kickerSound = kickerSound;

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
    digitalWrite(_kickerSound,HIGH);
    delay(50);
    digitalWrite(_kickerSound, LOW);
  }
    // Delay a little bit to avoid bouncing
    delay(50);

  }
   kickerState = kickerTrack;
  return;
}