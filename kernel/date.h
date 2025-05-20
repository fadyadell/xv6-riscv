#ifndef _DATE_H_
#define _DATE_H_

#include "types.h"
struct rtcdate {
  int second;
  int minute;
  int hour;
  int day;
  int month;
  int year;
};

void cmostime(struct rtcdate *r);
#endif
