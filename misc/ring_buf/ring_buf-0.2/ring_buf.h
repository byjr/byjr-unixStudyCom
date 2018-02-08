#ifndef _RING_BUF_H
#define _RING_BUF_H 1

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<lzl/misc.h>

#ifndef USER_RB_UNIT_T
typedef struct rb_unit_t{
	int flag;
}rb_unit_t;
#endif

typedef struct ring_buf_t{
	rb_unit_t *tbl;
	int size;
	char full;
	int ri;
	int wi;
}ring_buf_t;

rb_unit_t* rb_read(ring_buf_t *rb);
int rb_write(ring_buf_t *rb,rb_unit_t *p_unit);
int rb_flag_query(ring_buf_t *rb);
ring_buf_t *rb_create(int size);

#define ring_up(p_var,MIN,MAX) ({\
	int a=*p_var,min=MIN,max=MAX;\
	*p_var=(a<max)?a+1:min;\
})
#define ring_down(p_var,MIN,MAX) ({\
	int a=*p_var,min=MIN,max=MAX;\
	*p_var=(a>min)?a-1:max;\
})
#define ring_sub(A,B,P) ({\
	int a=A,b=B,p=P;\
	a<b?a+p-b:a-b;\
})

#endif