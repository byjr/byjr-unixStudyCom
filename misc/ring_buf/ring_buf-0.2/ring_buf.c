#include "ring_buf.h"
int rb_write(ring_buf_t *rb,rb_unit_t *p_unit){
	if(!p_unit)return -1;
	if(!rb->full){
		if(ring_sub(rb->wi,rb->ri,rb->size)==rb->size-1)rb->full=1;		
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
rb_unit_t* rb_read(ring_buf_t *rb){
	rb_unit_t* p_unit=NULL;
	if(!rb->full && rb->wi==rb->ri){
		err("buf is empty!");
		return NULL;
	}
	p_unit=&rb->tbl[rb->ri];
	p_unit->flag=0;
	ring_up(&rb->ri,0,rb->size-1);
	if(rb->full)rb->full=0;
	return p_unit;
}
int rb_flag_query(ring_buf_t *rb){
	int i=0;
	if(!rb){
		err("rb is NULL");
		return -1;
	}
	inf("ring buf table:");
	for(i=0;i<rb->size;i++){
		raw("%dV\t",i);
	}raw("\n");
	for(i=0;i<rb->size;i++){
		raw(" %d\t",rb->tbl[i].flag);
	}raw("\n");
	raw("wi=%d,ri=%d\n",rb->wi,rb->ri);
	return 0;
}
ring_buf_t *rb_create(int size){
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

