#include <Arduino.h>
#include "sensor.h"

sensor::sensor(int sensor)
{
  pinMode(sensor, INPUT);

  _sensor = sensor;

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
  }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  sensorState = sensorTrack;
  return;
}