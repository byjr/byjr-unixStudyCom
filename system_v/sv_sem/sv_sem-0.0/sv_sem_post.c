#include <stdio.h>
#include <string.h>
#include "sv_sem.c"
int semid=0;
char buf[SEM_TEXT_SIZE]="";
int main(int argc,char **argv)  
{
	sv_semget(&semid,1,TTT_SEM);
	sv_semset(semid,0,0);
	inf("sem post start!");
	while(1){
		fgets(buf,SEM_TEXT_SIZE-1,stdin);
		sv_semop(semid,0,+1);
	}
	return 0;
} 
