# X86Tasker
X86 Tasker is a C library (using some Assembler) to create multitasking programs in DOS/X86  
Usage:  
1. create functions using "TASKERWait" inside task inside a loop process or waiting (pooling) for I/O  
2. register functions using TARKERCreate  
3. Call TASKERsched  to run the scheduler  

The scheduler runs each task, every time you call TASKERwait, the lib save the stack, save the instruction pointer, and jumps to the last instruction of the next task, first restoring the stack of that task.  


   


## TASKERcreate(funcptr p)
Create task  
Use this definition ==> typedef void (*funcptr)(void);

## void TASKERsched(void)
To run scheduler

## void TASKERwait(void)
Use inside task inside a loop process or waiting (pooling) for I/O
