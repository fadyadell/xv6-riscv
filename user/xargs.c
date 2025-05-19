#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "Usage: xargs command [args...]\n");
    exit(1);
  }

  char buf[512];
  char *args[32];
  int i;

  // Copy existing arguments
  for (i = 1; i < argc; i++) {
    args[i - 1] = argv[i];
  }

  // Read input line by line
  while (1) {
    int n = 0;
    char c;

    // Read one line from stdin
    while (read(0, &c, 1) == 1 && c != '\n') {
      buf[n++] = c;
    }

    // If end of input, break
    if (n == 0 && c != '\n') {
      break;
    }

    buf[n] = 0;

    args[i - 1] = buf;
    args[i] = 0; // Null-terminate argv

    if (fork() == 0) {
      exec(argv[1], args);
      fprintf(2, "xargs: exec failed\n");
      exit(1);
    }

    wait(0);
  }

  exit(0);
}
