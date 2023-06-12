#ifndef bumper_h
#define bumper_h
extern int score;
extern int point;
#include "Arduino.h"

class bumper
{
  public:
  bumper(int bumper, int bumperReset, int bumperSound);
  void bumperRead();

  private:
  int bumperTrack =0 ;
  int _bumper;
  int bumperState = 0;
  int _bumperReset;
  int _bumperSound;
};
#endif