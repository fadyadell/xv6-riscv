// filepath: kernel/date.c
#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "date.h"
#include "defs.h"

void
cmostime(struct rtcdate *r) {
    // Example: Set a fixed date and time for testing
    r->year = 2025;
    r->month = 5;
    r->day = 20;
    r->hour = 12;
    r->minute = 0;
    r->second = 0;
}
