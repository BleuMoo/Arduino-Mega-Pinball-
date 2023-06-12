#ifndef dropDown_h
#define dropDown_h
extern int score;
extern int point;
#include "Arduino.h"

class dropDown
{
  public:
  dropDown(int drop1, int drop2, int drop3, int dropReset,int dropSound);
  void targets();
  void reset();

  private:
  int dropDownTrack1 = 0;
  int dropDownTrack2 = 0;
  int dropDownTrack3 = 0;
  int dropDownState1 = 0;
  int dropDownState2 = 0;
  int dropDownState3 = 0;
  int dropDownResetState = 0;
  int _drop1;
  int _drop2;
  int _drop3;
  int _dropReset;
  int _dropSound;
};
#endif