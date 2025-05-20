// filepath: user/datetime.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/date.h"

int
main(void) {
    struct rtcdate r;
    if (datetime(&r) < 0) {
        printf("Error: datetime system call failed\n");
        exit(1);
    }
    printf("Date: %d-%d-%d Time: %d:%d:%d\n", r.year, r.month, r.day, r.hour, r.minute, r.second);
    exit(0);
}
