#include "user/user.h"
#include "kernel/types.h"

int main() {
    for(int i = 0; i < 10; i++)
        printf("rand: %d\n", sysrand());
    exit(0);
}
