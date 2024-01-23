//  //  //  //
/*Ps.c
Prints information about processes in xv6 kernel using. Similar function to "ps" function in Linux.

Inputs:
None

Output:
Information about the processes in xv6 kernel.

*/
//  //  //  //

#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h" //needed to be expanded to avoid include conflicts that came up from using the kernel files proc.h and param.h. See file for more

 int main(void){
   //define and allocate memory to a temporary "pstat" structure to fill with information about processes.
    struct pstat* temp = malloc(sizeof(struct pstat));
    int error_test; //used to check for errors with functions called
   // call the system call getpinfo, check for errors
    error_test= getpinfo(temp); 
    if(error_test == -1){
      printf("error occured \n");
    }  
   //table to translate state values into strings. Shamelessly stolen from proc.c procdump function :P
   static char *states[] = {
      [UNUSED]    "unused",
      [USED]      "used",
      [SLEEPING]  "sleep ",
      [RUNNABLE]  "runble",
      [RUNNING]   "run   ",
      [ZOMBIE]    "zombie"
  };
   printf("Name\tPid\tPriority\tSize\tState\tParentPid\n");     // Print header for the process information table
   // Iterate through the process information stored in temp and print details
   for(int i=0;i<NPROC;i++){
      //break the loop at the first process with state UNUSED we find that is not init. Processes that fit this criteria and after take up space in the table for no reason
      if(temp->state[i]==0&&i!=0){
         break;
      }
      //Print the process name, pid, priority,size, state in string form and parent pid
      printf("%s\t",temp->name[i]);
      printf("%d\t",temp->pid[i]);
      printf("%d\t\t",temp->priority[i]);
      printf("%d\t",temp->size[i]);
      printf("%s\t",states[temp->state[i]]);
      printf("%d\n",temp->ppid[i]); 
   }
    free(temp); //free the space allocated to the "temp" pstat structure
    return 0;
 }