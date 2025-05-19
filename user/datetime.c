#include "kernel/types.h"
#include "kernel/date.h"
#include "user/user.h"

int main() {
    struct rtcdate r;
    if(datetime(&r) < 0){
        printf("datetime syscall failed\n");
        exit(1);
    }
    printf("Date: %d-%d-%d Time: %d:%d:%d\n", r.year, r.month, r.day, r.hour, r.minute, r.second);
    exit(0);
}
