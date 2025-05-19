#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(2, "Usage: fact <non-negative integer>\n");
        exit(1);
    }

    int n = atoi(argv[1]);

    if (n < 0) {
        fprintf(2, "Error: Please provide a non-negative integer.\n");
        exit(1);
    }

    int result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    printf("Factorial of %d is %d\n", n, result);
    exit(0);
}
