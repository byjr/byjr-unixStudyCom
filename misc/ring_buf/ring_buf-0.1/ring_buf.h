#ifndef _RING_BUF_H
#define _RING_BUF_H 1
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

void ring_up(int* p_var,int min ,int max);
void ring_down(int* p_var,int min,int max);
int ring_sub(int a,int b,int period);
rb_unit_t* rb_read(ring_buf_t *rb);
int rb_write(ring_buf_t *rb,rb_unit_t *p_unit);
int rb_flag_query(ring_buf_t *rb);
ring_buf_t *rb_create(int size);

#endif