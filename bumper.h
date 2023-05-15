#ifndef bumper_h
#define bumper_h
extern int score;
extern int point;
#include "Arduino.h"

class bumper
{
  public:
  bumper(int bumper);
  void bumperRead();

  private:
  int bumperTrack =0 ;
  int _bumper;
  int bumperState = 0;
};
#endif