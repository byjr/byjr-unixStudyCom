#include <stdio.h>
#include <string.h>
#include "sv_sem.c"
int semid=0;
int main(int argc,char **argv)  
{
	int ret=0;
	sv_semget(&semid,1,TTT_SEM);
	inf("sem wait start");
	while(1){
		sv_semop(semid,0,-1);
		inf("sem wait succeed!");	
	}
	return 0;
} 
