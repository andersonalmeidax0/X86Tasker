#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>


#include <dos.h>
#include <mem.h>


/* ATENCAO : DESABILITAR A OPCAO DE "USER REGISTERS VARIABLES"
		DO COMPILADOR  */

#define MAXTASKS 16
typedef void (*funcptr)(void);
enum bool  { FALSE,TRUE };

struct TCB
{
  funcptr func;
  jmp_buf context;
  void far * stack;
  int stat;
};
typedef struct TCB TCB;

struct TASKER
{
  int Max;
  int ntasks;
  int active;
  int killed;
  int stklen;
  int base_BP;
  void far *stack;
  jmp_buf context;
  TCB task[MAXTASKS];   /* ...meia boca... */
  // void init(maxtasks,stklen)
  // int create(funcptr)
  // sched()
};
typedef struct TASKER TASKER;
enum taskmodes { RUNNG,BLOCKD,READY,CREATD,KILLD };
void TASKERinit(int stklen);
int  TASKERcreate(funcptr p);
void TASKERsched(void);
void TASKERwait(void);
int  TASKERkill(int taskno);
void TASKERfinalize(void);
void TASKERwait(void);
#define RESTORESTK(area,bp) \
{int len;\
 int sp;\
 sp = _SP;\
 len = (int)(  ((long)MK_FP(_SS,bp)) - ((long)MK_FP(_SS,sp))  );\
 movedata(FP_SEG(area),FP_OFF(area),_SS,sp,len);}

#define SAVESTK(area,bp) \
{ int len;\
  int sp;\
  sp = _SP;\
  len = (int)(  ((long)MK_FP(_SS,bp)) - ((long)MK_FP(_SS,sp))  );\
  movedata(_SS,sp,\
  FP_SEG(area),FP_OFF(area),len); }\


#define ATASK  t.task[t.active]


