# X86Tasker
X86 Tasker is a C library (using some Assembler) to create multitasking programs in DOS/X86  
Usage:  
1. Create your paralel tasks using "TASKERWait" inside task inside a loop process or waiting (pooling) for I/O  
2. Register tasks using TARKERCreate  
3. Call TASKERsched  to run the scheduler, and your tasks will be scheduled to run in paralel (simulating paralelism)

The scheduler runs each task, every time you call TASKERwait, the lib save the stack, save the instruction pointer, and jumps to the last instruction of the next task, first restoring the stack of that task.  
This is a simple non-preemptible scheduler (AKA cooperative scheduler), also known as multitasking system.

Why use it? It allows you to create multitasking programs in single process O.S (DOS) without the complexity of managing task scheduling.  
Can be used in CS classes to explain Operating Systems concepts.   
   
# Links: 
A good article about Multiprocessing, covering processors, cores and also multitasking and threads.
https://en.wikipedia.org/wiki/Multiprocessing


## TASKERcreate(funcptr p)
Create task  
Use this definition ==> typedef void (*funcptr)(void);

## void TASKERsched(void)
To run scheduler

## void TASKERwait(void)
Use inside task inside a loop process or waiting (pooling) for I/O
