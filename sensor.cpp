#include <Arduino.h>
#include "sensor.h"

sensor::sensor(int sensor, int sensorSound)
{
  pinMode(sensor, INPUT);
  pinMode(sensorSound, OUTPUT);

  _sensor = sensor;
  _sensorSound = sensorSound;

}

void sensor::sensorRead()
{
      sensorTrack = digitalRead(_sensor);
  // compare the buttonState to its previous state
  
  if (sensorTrack != sensorState) {
    // if the state has changed, increment the counter
    if (sensorTrack == HIGH) {
    score = score + point;
    Serial.println("DING");
    digitalWrite(_sensorSound, HIGH);
    delay(50);
    digitalWrite(_sensorSound, LOW);
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  sensorState = sensorTrack;
  return;
}