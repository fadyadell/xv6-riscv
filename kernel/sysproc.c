#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "date.h"

// enum sched_policy { SCHED_RR, SCHED_FCFS, SCHED_PRIORITY };
// enum sched_policy current_policy = SCHED_RR; // default: round robin
extern int total_syscalls;

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_countsyscall(void)
{
  return total_syscalls;
}

uint64
sys_getppid(void)
{
  struct proc *p = myproc();
  if(p->parent)
    return p->parent->pid;
  return -1;  // no parent (init process or orphan)
}

extern int getptable(int nproc, struct pstat *ps);
uint64
sys_getptable(void)
{
    int nproc;
    uint64 buf;

    argint(0, &nproc);
    argaddr(1, &buf);

    return getptable(nproc, (struct pstat*)buf);
}
uint64
sys_datetime(void) {
    uint64 user_addr;
    struct rtcdate r;

    // Get the user pointer from the first argument
    argaddr(0, &user_addr);

    // Fill the rtcdate struct with the current time
    cmostime(&r);

    // Copy the struct to user space
    if (copyout(myproc()->pagetable, user_addr, (char *)&r, sizeof(r)) < 0)
        return -1;

    return 0;
}
static uint64 rand_seed = 0;

static uint64
lcg_rand()
{
    // Constants from Numerical Recipes
    rand_seed = rand_seed * 6364136223846793005ULL + 1;
    return (rand_seed >> 33) & 0x7fffffff; // 31 bits
}

uint64
sys_sysrand(void)
{
    if(rand_seed == 0)
        rand_seed = r_time() ^ ticks; // Seed with time and ticks
    return lcg_rand();
}
// extern enum sched_policy current_policy;

uint64 sys_sched_fcfs(void)    { sched_mode = SCHED_FCFS;    return 0; }
uint64 sys_sched_priority(void){ sched_mode = SCHED_PRIORITY; return 0; }
uint64 sys_sched_rr(void)      { sched_mode = SCHED_ROUND_ROBIN; return 0; }
uint64 sys_set_priority(void) {
  int prio;
  argint(0, &prio);
  struct proc *p = myproc();
  p->priority = prio;
  return 0;
}
