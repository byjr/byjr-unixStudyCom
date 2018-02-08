#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define log printf
#define ARG_NUM 3
#define MAX_NUM 1000
#define BUF_SIZE 100
typedef unsigned int uint;
typedef struct NOTE_T
{
	struct NOTE_T* pre;
	struct NOTE_T* next;
	char date[100];
}note_t;
note_t* craet(){
	note_t* head;
	note_t* tmp;
	if(NULL==(tmp=(note_t*)calloc(1,sizeof(note_t)))){
		log("can not calloc memory\r\n");
		return NULL;
	}
		log("input node date:\r\n");		
		//fgets(tmp->date,BUF_SIZE,stdin);
		scanf("%s",tmp->date);
		if(0==strncmp(tmp->date,"end",3)){
			free(tmp);
			return head;
		}
		tmp->next=tmp;
		tmp->pre=NULL;
		head=tmp;	
	for(;;){
		log("input node date:\r\n");		
		//fgets(tmp->date,BUF_SIZE,stdin);
		scanf("%s",tmp->date);
		if(0==strncmp(tmp->date,"end",3)){
			free(tmp);
			return head;
		}
		tmp->next=tmp;
		tmp->pre=head;
		head=tmp;
		if(NULL==(tmp=(note_t*)calloc(1,sizeof(note_t)))){
			log("can not calloc memory\r\n");
			return NULL;			
		}
	}
}
void show_link_list(note_t* head){
	note_t* node_p=head;
	int i=0;
	for(;NULL!=node_p;node_p=node_p->pre){
		log("%08x:[%s]\r\n",node_p,node_p->date);
		sleep(1);
	}
	log("\r\n");
}
int main(int argc,char * argv[]){
	note_t* head=craet();
	show_link_list(head);
	return 0;
}