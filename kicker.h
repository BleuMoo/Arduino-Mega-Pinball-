#ifndef kicker_h
#define kicker_h
extern int score;
extern int point;
#include "Arduino.h"

class kicker
{
  public:
  kicker(int kicker);
  void kickerRead();

  private:
  int kickerTrack =0 ;
  int _kicker;
  int kickerState = 0;
};
#endif