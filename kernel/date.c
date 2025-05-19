#include "date.h"

static const int days_per_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

void
unix_to_rtc(uint64 unix_time, struct rtcdate *r)
{
    uint64 days = unix_time / 86400;
    uint64 seconds = unix_time % 86400;

    // Calculate time
    r->hour = seconds / 3600;
    seconds %= 3600;
    r->minute = seconds / 60;
    r->second = seconds % 60;

    // Calculate date
    r->year = 1970;
    while (days >= 365) {
        if ((r->year % 4 == 0 && r->year % 100 != 0) || r->year % 400 == 0) {
            if (days >= 366) {
                days -= 366;
                r->year++;
            } else {
                break;
            }
        } else {
            days -= 365;
            r->year++;
        }
    }

    // Calculate month and day
    r->month = 0;
    while (r->month < 12) {
        int mdays = days_per_month[r->month];
        if (r->month == 1 && ((r->year % 4 == 0 && r->year % 100 != 0) || r->year % 400 == 0)) {
            mdays++;
        }
        if (days < mdays)
            break;
        days -= mdays;
        r->month++;
    }
    r->month++; // Convert to 1-based month
    r->day = days + 1; // Convert to 1-based day
}
