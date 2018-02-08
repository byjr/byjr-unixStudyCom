#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <lzl/slog.h>
#include "sv_msgq.h"

int sv_msgqget(int *pmid,proj_id_t proj_id)
{
	key_t key={0};
	if(-1==(key=ftok("/",proj_id))){
		perror("ftok");
		exit(-1);  
	}
	if(-1==(*pmid=msgget(key, 0666 | IPC_CREAT))){
		perror("msgget");
		exit(-2);  	
	}
	return 0;
}
int sv_msgqrcv(msg_st *p_msg,int msgid,msg_type_t type)
{
	memset(p_msg->text,0,sizeof(p_msg->text));
	if(-1==msgrcv(msgid, (void*)p_msg, MSGQ_BUFF_SIZE, type, 0)){
		perror("msgget");
		exit(-1);
	}
	return 0;
}
int sv_msgqrcv_nowait(msg_st *p_msg,int msgid,msg_type_t type)
{
	memset(p_msg->text,0,sizeof(p_msg->text));
	if(-1==msgrcv(msgid, (void*)p_msg, MSGQ_BUFF_SIZE, type, IPC_NOWAIT)){
		//perror("msgrcv nowait");
		return -1;
	}
	return 0;
}

int sv_msgqsnd(int msgid,char *msg_text,msg_type_t type)
{
	msg_st msg={0};
	strncpy(msg.text,msg_text,sizeof(msg.text)-1);
	msg.msg_type=type;
	if(-1==msgsnd(msgid, (void*)&msg, MSGQ_BUFF_SIZE, 0)){
		perror("msgsnd");
		exit(-1);
	}
	return 0;
}
int sv_msgqsnd_nowait(int msgid,char *msg_text,msg_type_t type)
{
	msg_st msg={0};
	strncpy(msg.text,msg_text,sizeof(msg.text)-1);
	msg.msg_type=type;
	if(-1==msgsnd(msgid, (void*)&msg, MSGQ_BUFF_SIZE, IPC_NOWAIT)){
		//perror("msgsnd");
		exit(-1);
	}
	return 0;
}
int sv_msgqdel(int msgid)
{
	if(-1==msgctl(msgid, IPC_RMID, 0)) {
		perror("msgctl");
		exit(-1);  
	}
	return 0;
}



