#ifndef _RING_BUF_H
#define _RING_BUF_H 1

typedef struct rb_unit_t{
	int flag;
	long int tid;
	void *(*func)(void *args);
	void *args;
}rb_unit_t;

typedef struct ring_buf_t{
	rb_unit_t *tbl;
	int size;
	char full;
	int ri;
	int wi;
}ring_buf_t;

extern void ring_up(int* p_var,int min ,int max);
extern void ring_down(int* p_var,int min,int max);
extern int ring_sub(int a,int b,int period);
extern int rb_read(rb_unit_t* p_unit,ring_buf_t *rb);
extern int rb_write(ring_buf_t *rb,rb_unit_t *p_unit);
extern int rb_flag_query(ring_buf_t *rb);
extern ring_buf_t *rb_create(int size);

#endif