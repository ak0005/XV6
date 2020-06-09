# XV6
An attempt to make scheduler of xv6 a weighted round robin schduler

Description


1. first added an unsigned int variable priority in structure proc in **proc.h** and add syscall to set value of priority named it **setprio(n)** and default value of priority is set in **allocproc()** in **proc.c** to 1

**p->priority=1;//change**

process can check its priority by calling syscall **getprio().** The definition of these are in proc.c.

1. Initially scheduler is round robin but I did 3 changes to make it more of weighted round robin scheduler.

- After selecting the runnable process it run an another loop inside the previous one to select the process with highest priority.
- created an integer array named **arr** to protect the processes with less priority from starvation which otherwise may happen if we give highest priority to the process with large run time.

The **arr** will act as the visited array which will tell that in current batch given process been already given cpu time or not, If it had, scheduler will pick another process instead.

- also changes running time quanta for each process according to its priority which is mentioned in the description of **ticked** below.

```
for(p = ptable.proc; p && ptable.proc[NPROC]; p++){

//for every process in process table 
    if(p&&gt;state != RUNNABLE)
      continue; 
    highp=p;
    // choose one with highest priority 
    for(p1=ptable.proc;p1&&ptable.proc[NPROC];p1++){
        if(p1->state!=RUNNABLE ) 
              continue;
        if (highp->priority < p1->priority && arr[p1-ptable.proc]==0) // larger value, higherpriority
              highp=p1;
     }
     arr[highp-ptable.proc]=1;//set visited to 1

//run the process.....
```

Initial scheduler time complexity was O(n).

Initial scheduler space complexity was O(1).

Current time complexity is O(n\*n)

Current space complexity is O(n)

1. added few more variables

**int yielded; // yeild count**

**int ticked; // Count numbers of ticked faced since last yield**

**int rutime; // spend as running**

**int othtime; // spend as runnable**

**yielded** maintain the number of times a yeild function called for the given process. That is how many times are process got context switched because of the time interrupt. This is done by adding **incyielded()** function in trap.c .

Its definition is written in proc.c.

The purpose of this to check whether the change in time quanta is functioning or not.


     if(myproc() && myproc()->state == RUNNING &&tf->trapno == T_IRQ0+IRQ_TIMER &&incticked()>=(myproc()->priority))

      {

      incyielded(); //for yield count

      yield();

      }

**Ticked** count the numbers of time the process has faced the tick while running since it get yielded last time. Did this by setting ticked zero each time whenever the scheduler picks up the process and then in trap.c whenever process is checked for being yielded we increase the ticked count by one using **incticked()** function whose definition is in proc.c . this function increment the ticked count and returns the ticked count's value.

**Using this we can change the time given to each process before it gets yielded**

Since default priority is one each process got enough time or ticks comparable to its priority. Hence more priority results in bigger time quanta hence less context switching.

**Rutime** and **othtime** are only meant to keep account of time spent by the process in running state and other state respectively.

It is done by adding **updatestatistics()** in trap.c whose definition is proc.c

It is called on ticks and update the rutime and othtime of all processes.

These are accessed by **getrutime()** and **getothtime()** syscall respectively

**For multiple cores**.

Haven't done anything that effect the xv6 capability of working on two core cpu also took the necessary precautions every time control enter the crittical sections hence I believe that modifications will work effectively on multiple cores where the xv6 can work.

**TESTING**

**prio.c**

Created prio.c file which create four processes they are cpu-bound process differ only in priority. Each process prints the priority, yield count, run time other time,total time before exititng or waiting for child to exit to check time needed for running loop . every process is like.

    while(i!=0){
        k*=i; k%=7;
        i=i+1;
    }

    int a=getrutime(),b=(int)othtime();
        printf(/*details*/);
    exit();

Here all four process have different priorities running long loop with computationally heavy mathematical operation of modulo.

**prio2.c**

Created prio2.c file similar to prio.c but it creates I/O bound process and prints "!!!" to screen and details of execution on output.txt

every process is

    int fd=open("output.txt",O_WRONLY|O_CREATE); 
    while(i!=100000){
        printf(1,"!!!"); 
        i=i+1;
    }
    int a=getrutime(),b=getothtime(); printf(out,/*details*/);
    exit();
