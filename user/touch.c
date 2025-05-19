#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: touch filename\n");
        exit(1);
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd >= 0) {
        printf("touch: %s already exists\n", filename);
        close(fd);
        exit(1);
    }

    fd = open(filename, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("touch: cannot create %s\n", filename);
        exit(1);
    }

    close(fd);
    exit(0);
}