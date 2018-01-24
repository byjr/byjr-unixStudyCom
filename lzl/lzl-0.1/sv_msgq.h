#ifndef MY_MSGQ_H_
#define MY_MSGQ_H_ 1

#ifndef USE_DEFAULT_MSGQ_CONFIG
#define USE_DEFAULT_MSGQ_CONFIG 1
#endif 

#if USE_DEFAULT_MSGQ_CONFIG
#define MSGQ_BUFF_SIZE 128
typedef struct MSG_ST{  
    long int msg_type;  
    char text[MSGQ_BUFF_SIZE];  
}msg_st;

#endif
/* -----------------------------
typedef enum PROJ_ID_T{
	INIT_VALUE_PROJ_ID,	
	U2I_MSG,
	I2U_MSG,
	MAX_PROJ_ID
}int;
typedef enum MSG_TYPE_T{
	INIT_VALUE,
	U2I_STOP,
	U2I_WORK,
	I2U_ANSW,
	MAX_U2I_MSG_TYPE
}int;
----------------------------- */

int sv_msgqget(int *pmid,int proj_id);
int sv_msgqrcv(msg_st *p_msg,int msgid,int type);
int sv_msgqrcv_nowait(msg_st *p_msg,int msgid,int type);
int sv_msgqsnd(int msgid,char *msg_text,int type);
int sv_msgqsnd_nowait(int msgid,char *msg_text,int type);
int sv_msgqdel(int msgid);


#endif