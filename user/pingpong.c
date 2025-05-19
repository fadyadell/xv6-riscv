#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p1[2]; // parent to child
  int p2[2]; // child to parent
  char buf[1];

  pipe(p1);
  pipe(p2);

  int pid = fork();
  if (pid < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    // Child process
    read(p1[0], buf, 1);  // Receive from parent
    printf("%d: received ping\n", getpid());
    write(p2[1], buf, 1); // Send back to parent
    close(p1[0]);
    close(p2[1]);
  } else {
    // Parent process
    buf[0] = 'x';
    write(p1[1], buf, 1); // Send to child
    read(p2[0], buf, 1);  // Receive from child
    printf("%d: received pong\n", getpid());
    wait(0);
    close(p1[1]);
    close(p2[0]);
  }

  exit(0);
}
