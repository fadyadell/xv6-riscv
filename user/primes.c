#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  int nums[100]; // Holds numbers from 2 to 100
  for (int i = 0; i < 100; i++) {
    nums[i] = i + 1;
  }

  for (int i = 0; i < 100; i++) {
    if (nums[i] == 0)
      continue;

    int prime = nums[i];
    printf("prime %d\n", prime);

    // Mark multiples of prime as 0
    for (int j = i + 1; j < 100; j++) {
      if (nums[j] % prime == 0) {
        nums[j] = 0;
      }
    }
  }

  exit(0);
}
