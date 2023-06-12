#ifndef sensor_h
#define sensor_h
extern int score;
extern int point;
#include "Arduino.h"

class sensor
{
  public:
  sensor(int sensor, int sensorSound);
  void sensorRead();

  private:
  int sensorTrack =0 ;
  int _sensor;
  int _sensorSound;
  int sensorState = 0;
};
#endif