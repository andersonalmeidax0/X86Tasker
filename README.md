# X86Tasker
X86 Tasker is a C library to create multitasking programs in DOS/X86

## TASKERcreate(funcptr p)
Create task  
Use this definition ==> typedef void (*funcptr)(void);

## void TASKERsched(void)
To run scheduler

## void TASKERwait(void)
Use inside task inside a loop process or waiting (pooling) for I/O
