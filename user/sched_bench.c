#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NPROCS 5

int main(int argc, char *argv[]) {
    //int pids[NPROCS];
    int i, pid;
    // int turnaround_sum = 0, waiting_sum = 0;

    // Switch scheduler if argument given
    if(argc > 1) {
        if(strcmp(argv[1], "fcfs") == 0)
            sched_fcfs();
        else if(strcmp(argv[1], "priority") == 0)
            sched_priority();
        else
            sched_rr();
    }

    // Optionally set priorities for priority scheduler
    for(i = 0; i < NPROCS; i++) {
      pid = fork();
      if(pid == 0) {
          if(argc > 1 && strcmp(argv[1], "priority") == 0)
              set_priority(10 + i); // Different priorities
          // Waste more CPU time (increase the number)
          for(volatile int j = 0; j < 100000000; j++);
          exit(0);
      }
  }

    // Wait for all children and collect metrics
    for(i = 0; i < NPROCS; i++) {
        int wpid = wait(0);
        // You can print per-process metrics here if you add a syscall to fetch them
        printf("Child %d finished\n", wpid);
    }

    // To print average turnaround/waiting time, you need a syscall to fetch per-process stats.
    // For now, you can print them in the kernel (e.g., in procdump or after all children exit).

    exit(0);
}
