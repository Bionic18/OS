#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"//NOT SURE WHICH ONE OF THESE I ACTUALLY NEED


 
 int main(void){
    struct pstat* temp = malloc(sizeof(struct pstat));
    int error_test;
    error_test= getpinfo(temp);
    if(error_test == -1){
      printf("error occured \n");
    }  
   static char *states[] = {
      [UNUSED]    "unused",
      [USED]      "used",
      [SLEEPING]  "sleep ",
      [RUNNABLE]  "runble",
      [RUNNING]   "run   ",
      [ZOMBIE]    "zombie"
  };
   printf("Name\tPid\tPriority\tSize\tState\tParentPid\n");
   for(int i=0;i<NPROC;i++){
      if(temp->state[i]==0&&i!=0){
         break;
      }
      printf("%s\t",temp->name[i]);
      printf("%d\t",temp->pid[i]);
      printf("%d\t\t",temp->priority[i]);
      printf("%d\t",temp->size[i]);
      printf("%s\t",states[temp->state[i]]);
      printf("%d\n",temp->ppid[i]);
      // printf("%d\t%s\t%d\t%d\t%s\n",temp->pid[i],temp->ppid[i],temp->priority[i],temp->size[i],states[temp->state[i]]);
 
   }
    free(temp);
    return 0;
 }