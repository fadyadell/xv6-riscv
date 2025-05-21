#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int n1= atoi (argv[1]);
  int n2= atoi (argv[2]);
  int result=n1+n2;
  printf("result=%d\n",result);
  exit(0);

}
