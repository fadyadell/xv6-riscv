#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define BUF_SIZE 512   // one disk block

int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "Usage: cp src dst\n");
    exit(1);
  }

  int fdsrc = open(argv[1], O_RDONLY);
  if(fdsrc < 0){
    fprintf(2, "cp: cannot open %s\n", argv[1]);
    exit(1);
  }

  int fddst = open(argv[2], O_CREATE | O_WRONLY | O_TRUNC);
  if(fddst < 0){
    fprintf(2, "cp: cannot create %s\n", argv[2]);
    close(fdsrc);
    exit(1);
  }

  char buf[BUF_SIZE];
  int n;
  while((n = read(fdsrc, buf, sizeof(buf))) > 0){
    if(write(fddst, buf, n) != n){
      fprintf(2, "cp: write error on %s\n", argv[2]);
      close(fdsrc);
      close(fddst);
      unlink(argv[2]);       // remove partial file
      exit(1);
    }
  }
  if(n < 0){
    fprintf(2, "cp: read error on %s\n", argv[1]);
    close(fdsrc);
    close(fddst);
    unlink(argv[2]);
    exit(1);
  }

  close(fdsrc);
  close(fddst);
  exit(0);
}
