#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <conio.h>

#include <dos.h>
#include <mem.h>
#include "tasker.h"


/* ATENCAO : DESABILITAR A OPCAO DE "USER REGISTERS VARIABLES"
		DO COMPILADOR  */

void rot1(void);
void rot2(void);


int main(void)
{
   clrscr();
   TASKERinit(_stklen);
   if(!TASKERcreate(rot1)) printf("Cant create t1");
   if(!TASKERcreate(rot2)) printf("Cant create t2");

   TASKERsched();
   TASKERfinalize();
}


void rot1(void)
{
   unsigned int i=38004;
   char str[]="|\-/";
   int mod;

   int value;
   gotoxy(20,20); printf("Waiting:");

   while(i--)
   {
	mod = i%4;
	gotoxy(30,20);
	cprintf("%c",str[mod]);

	TASKERwait();
   }

}


void rot2(void)
{
   int i=7000;
   int value;
   int c=0;
   int k;

   gotoxy(1,1); cprintf("Digite...");
   while(1)
   {

       if(kbhit())
       {
	gotoxy(c,2);
	k=getch();
	gotoxy(c,2);
	cprintf("%c",k); c++;
       }
       if(k == 'X')
	  return;

   TASKERwait();

   }

}



