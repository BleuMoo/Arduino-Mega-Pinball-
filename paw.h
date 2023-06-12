#ifndef paw_h
#define paw_h
extern int score;
extern int point;
#include "Arduino.h"

class paw
{
  public:
  paw(int claw, int clawSound);
  // paw(int claw);
  void claw();

  private:
  int clawTrack = 0 ;
  int _claw;
  int clawState = 0;
  int _clawSound;
};
#endif