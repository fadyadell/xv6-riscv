#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main() {
    int ppid = getppid();
    printf("Parent PID: %d\n", ppid);
    exit(0);
}
