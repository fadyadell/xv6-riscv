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

void unix_to_rtc(uint64 unix_time, struct rtcdate *r);

#endif
