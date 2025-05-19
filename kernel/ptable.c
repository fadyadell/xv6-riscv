#include "kernel/types.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main() {
    struct pstat ps[64];
    int count = getptable(64, ps);

    if (count < 0) {
        printf("Error: getptable failed\n");
        exit(1);
    }

    printf("PID\tPPID\tSTATE\t\tNAME\tSIZE\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%s\t%s\t%lu\n",
            ps[i].pid,
            ps[i].ppid,
            ps[i].state,
            ps[i].name,
            ps[i].sz);
    }

    exit(0);
}
