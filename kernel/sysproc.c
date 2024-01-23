#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_setpriority(void){
    //  //  //  //
    /*Code of system call "setpriority" Calls and is implemented by kernel function setpriority

    Input:
    Uint64 temp: The priority number to be set to the priority that calls this system call.

    Output:
    Returns an interger, 0 if everything is fine, -1 if there is an error. Further explained in setpriority
    */
    //  //  //  //
  //define and get the input priority
  uint64 temp;
  argaddr(0, &temp);
  //call kernel function setpriority that does the work, and return its value
  return setpriority(temp);
}

uint sys_getpinfo(void){
    //  //  //  //
    /*Code of system call "getpinfo". Calls and is implemented by kernel function getpinfo

    Input:
    pstat* input: A pointer to a pstat structure. Defined in proc.h

    Output: Interger of either 0 or -1 ,depending on if there was an error or not.
    
    */
    //  //  //  //
  //define and get input pstat struct
  struct pstat* input;
  argaddr(0,(uint64*)&input); //hodge-podge. we'll see if it works lol
  //call kernel process getpinfo that implements the system call and return its value
  return getpinfo(input);
}