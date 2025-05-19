struct pstat {
  int pid;        // Process ID
  int ppid;       // Parent process ID
  char state[16]; // Process state
  char name[16];  // Process name
  uint64 sz;      // Size of process memory (bytes)
};
