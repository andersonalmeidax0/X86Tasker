#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <conio.h>

#include <dos.h>
#include <mem.h>
#include "tasker.h"

/* ATENCAO : DESABILITAR A OPCAO DE "USER REGISTERS VARIABLES"
		DO COMPILADOR  */

TASKER t;


void TASKERinit(int stklen)
{
  t.Max = MAXTASKS;
  t.ntasks = 0;
  t.active = -1;
  t.stklen = stklen;
  t.killed = 0;
  t.stack = malloc(t.stklen);
  if(!t.stack)
   {
     printf("Malloc failed!!!");
     exit(0);
   }
};

int TASKERcreate(funcptr p)
{
  if(t.ntasks == t.Max)
    return FALSE;

  t.task[t.ntasks].func = p;
  t.task[t.ntasks].stat = CREATD;
  t.task[t.ntasks].stack = malloc(t.stklen);

  if(!t.task[t.ntasks].stack)
   {
     printf("Malloc failed!!!");
     exit(0);
   }

  t.ntasks++;

  return TRUE;
};

int TASKERkill(int taskno)
{
  if(taskno > t.ntasks )
    return FALSE;

  free(t.task[taskno].stack);
  t.task[taskno].stat = KILLD;

  t.killed++;
  return TRUE;
};


void TASKERwait(void)
{
   int value;
   value = setjmp(ATASK.context);

   if (value != 0)
   {
//	restore stack
	RESTORESTK(ATASK.stack,t.base_BP);
	return;
   }

// save stack
   SAVESTK(ATASK.stack,t.base_BP);
   longjmp(t.context,1);

   return;
}



void TASKERfinalize(void)
{
}


void TASKERsched(void)
{

   int value;
   int count=0;

   t.base_BP = _BP;


   loop:
	   /* ponto de entrada do sched */
	   value = setjmp(t.context); /* funciona tambem se jmp_shd local*/
	   if (value != 0) /* retornou de rotina ??? */
	   {
	      //restore
	      RESTORESTK(t.stack,t.base_BP);
	   }
	   else
	   {
	      //savestk
	      SAVESTK(t.stack,t.base_BP);
	   };


	   if(t.ntasks == t.killed)  /* finalize ?? */
	      return;

	   t.active++;	/* task index */
	   if(t.active == t.ntasks) /* Wrap around... */
	      t.active = 0;

	   switch(ATASK.stat)
	   {
		case CREATD: ATASK.stat = RUNNG;
			     ATASK.func();
			     if(!TASKERkill(t.active))
			       printf("Cant kill task");
			     break;

		case RUNNG:  ATASK.stat = RUNNG;
			     //savestk
			     SAVESTK(t.stack,t.base_BP);
			     longjmp(ATASK.context,1); break;
		case KILLD:  break;  /* pula task... */

		default: printf("TASK ERROR2"); exit(0);

	   };

   goto loop;

}





