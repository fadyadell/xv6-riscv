#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("Total system calls so far: %d\n", countsyscall());
    sleep(1);  // generates a syscall
    printf("After sleep, total: %d\n", countsyscall());
    exit(0);
}
