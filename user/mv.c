#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "Usage: mv source target\n");
    exit(1);
  }

  // Try to link (create a new name for the file)
  if(link(argv[1], argv[2]) < 0){
    fprintf(2, "mv: failed to link %s to %s\n", argv[1], argv[2]);
    exit(1);
  }

  // Remove the old name
  if(unlink(argv[1]) < 0){
    fprintf(2, "mv: failed to unlink %s\n", argv[1]);
    // Optionally: unlink the new one to "undo"
    unlink(argv[2]);
    exit(1);
  }

  exit(0);
}
