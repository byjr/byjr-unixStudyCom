#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "ring_buf.h"
#include "slog.h"
#include "misc.h"

void ring_up(int* p_var,int min ,int max)
{
	int a=*p_var;
	*p_var=(a<max)?a+1:min;
}
void ring_down(int* p_var,int min,int max)
{
	int a=*p_var;
	*p_var=(a>min)?a-1:max;
}
int ring_sub(int a,int b,int period)
{
	if(a<b){
		return a+period-b;		
	}else{
		return a-b;
	}
}
int rb_write(ring_buf_t *rb,rb_unit_t *p_unit)
{
	if(!p_unit)return -1;
	if(!rb->full){
		if(ring_sub(rb->wi,rb->ri,rb->size)==rb->size-1)rb->full=1;
		// if(rb->full)
			// rb_flag_query(rb);
	}
	p_unit->flag++;	
	memcpy(&rb->tbl[rb->wi],p_unit,sizeof(rb_unit_t));
	ring_up(&rb->wi,0,rb->size-1);
	if(rb->full){
		rb->ri=rb->wi;
		war("buf is full!");
	}
	return 0;
}
int rb_read(rb_unit_t* p_unit,ring_buf_t *rb)
{
	if(!rb->full && rb->wi==rb->ri){
		err("%ld/%d read buf is empty!",p_unit->tid,p_unit->flag);
		return -1;
	}
	rb->tbl[rb->ri].flag=0;
	memcpy(p_unit,&rb->tbl[rb->ri],sizeof(rb_unit_t));
	ring_up(&rb->ri,0,rb->size-1);
	if(rb->full)rb->full=0;
	inf("ri=%d",rb->ri);
	return 0;
}
int rb_flag_query(ring_buf_t *rb)
{
	int i=0;
	if(!rb){
		err("rb is NULL");
		return -1;
	}
	inf("ring buf table:");
	for(i=0;i<rb->size;i++){
		raw("%dV\t\t",i);
	}raw("\n");
	// for(i=0;i<rb->size;i++){
		// raw(" %d\t",rb->tbl[i].flag);
	// }raw("\n");
	for(i=0;i<rb->size;i++){
		raw(" %08x\t",rb->tbl[i].func);
	}raw("\n");	
	raw("wi=%d,ri=%d\n",rb->wi,rb->ri);
	return 0;
}
ring_buf_t *rb_create(int size)
{
	int ret=0,fail=1;
	ring_buf_t *rb;
	rb=(ring_buf_t *)calloc(1,sizeof(ring_buf_t));
	if(!rb)return NULL;
	rb->tbl=(rb_unit_t*)calloc(size,sizeof(rb_unit_t));
	if(!rb->tbl) goto Exit1;
	rb->size=size;
	fail=0;
Exit1:
	if(fail)FREE(rb);
	if(fail)return NULL;
	return rb;
}

