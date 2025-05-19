#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

  int seconds = atoi(argv[1]);
  if (seconds < 0) {
      printf("Please enter a non-negative number.\n");
      return 1;
  }

  sleep(seconds);
  return 0;
}
