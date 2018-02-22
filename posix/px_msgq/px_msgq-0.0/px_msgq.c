#include "px_msgq.h"
mqd_t mqd={0};
int px_msgq_showattr(struct mq_attr *p_attr){
	inf("mq_flags	=%ld",p_attr->mq_flags	);   
	inf("mq_maxmsg	=%ld",p_attr->mq_maxmsg	);  
	inf("mq_msgsize	=%ld",p_attr->mq_msgsize); 
	inf("mq_curmsgs	=%ld",p_attr->mq_curmsgs); 
	return 0;
}