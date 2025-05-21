// kernel/date.c
#include "types.h"
#include "date.h"
#include "riscv.h"

#ifndef BOOT_EPOCH
#define BOOT_EPOCH 1710000000  // fallback if not set by Makefile
#endif

extern uint ticks;

// Days in each month (not handling leap years)
static const int days_in_month[] = {
  31,28,31,30,31,30,31,31,30,31,30,31
};

void
cmostime(struct rtcdate *r) {
    uint64 seconds_since_boot = ticks / 100;
    uint64 unix_time = BOOT_EPOCH + seconds_since_boot;

    // Break unix_time into components
    uint64 t = unix_time;
    r->second = t % 60;
    t /= 60;
    r->minute = t % 60;
    t /= 60;
    r->hour = t % 24;
    t /= 24;

    // Now t is days since epoch (Jan 1, 1970)
    int year = 1970;
    while (1) {
        int days_in_year = 365;
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            days_in_year = 366;
        if (t >= days_in_year) {
            t -= days_in_year;
            year++;
        } else {
            break;
        }
    }
    r->year = year;

    int month = 0;
    while (1) {
        int dim = days_in_month[month];
        // Handle leap year for February
        if (month == 1 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            dim = 29;
        if (t >= dim) {
            t -= dim;
            month++;
        } else {
            break;
        }
    }
    r->month = month + 1;
    r->day = t + 1;
}
