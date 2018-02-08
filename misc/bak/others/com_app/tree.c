#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MIN(a,b,type) ({type __a=(a),__b=(b);__a<__b?__a:__b;})
#define log printf
#define SEG_SIZE 5
typedef unsigned int uint;
typedef struct SUB_T{
	struct SUB_T* next;
	struct node_t* sub;
}sub_t;
typedef struct node_t{
	char date[SEG_SIZE];
	struct SUB_T* sub_star;
	uint weight;
}node_t;
void traversing_tree_show_node(node_t **father_p,int iteration_count)
{	
	sub_t **sub_index_p=&((*father_p)->sub_star);
	char buf[13]="";
	uint tab_count=iteration_count;
	memset(buf,' ',MIN(sizeof(buf),4*tab_count,uint));
	for(;(*sub_index_p);sub_index_p=&((*sub_index_p)->next)){
		//log("---------------------------------------------------------------------------%d\r\n",tab_count);		
		if((*sub_index_p)->sub->sub_star){
			(*sub_index_p)->sub->weight\
				?printf("%s|---%s[%d]\r\n",buf,(*sub_index_p)->sub->date,(*sub_index_p)->sub->weight)\
				:printf("%s|---%s\r\n",buf,(*sub_index_p)->sub->date);		
			traversing_tree_show_node(&((*sub_index_p)->sub),tab_count+1);
		}else{
			(*sub_index_p)->sub->weight\
				?printf("%s|---%s[%d]\r\n",buf,(*sub_index_p)->sub->date,(*sub_index_p)->sub->weight)\
				:printf("%s|---%s\r\n",buf,(*sub_index_p)->sub->date);				
		}
		//log("show node addr:0x%08x,seg=%s\r\n",(*sub_index_p)->sub,(*sub_index_p)->sub->date);		
	}
}
void show_tree(node_t * root){
	if(NULL==root||NULL==root->sub_star){
		return;
	}
	traversing_tree_show_node(&root,0);
}
char strs[][20]={
	"163.cn",	
	"163.com.cn",
	"163.net",
	"163.com.cn",
	"163.com",
	"163.com.cn",
	"192.168.0.1",
/* 	"192.168.1.1",
	"162.com.cn" */
};
int get_str_seg(char *star,char ch){
	uint i;
	if(0==star[0]||(void *)NULL==star){
		return -1;
	}
	for(i=0;ch!=star[i];i++){
		if(0==star[i]){
			return -2;
		}
	}
	return i;
}
typedef enum END_T{
	UN_END_L,
	END_L,
	MAX_END_T
}end_t;
int add_tree_node(node_t **father_p,char seg[],end_t end){
	node_t *node =*father_p;
	sub_t **sub_index_p=&(node->sub_star);
	if(NULL==father_p || NULL==*father_p){
		return -1; 
	}
	for(;NULL!=(*sub_index_p);sub_index_p=&((*sub_index_p)->next)){
		if(0==strcmp(seg,(*sub_index_p)->sub->date)){
			if(END_L==end)
				(*sub_index_p)->sub->weight++;
			*father_p=(*sub_index_p)->sub;
			return 1;
		}
	}
	if(NULL==((*sub_index_p)=(sub_t*)calloc(1,sizeof(sub_t)))){
		//log("calloc sub_t fail!\r\n");
		return -2;
	}
	if(NULL==((*sub_index_p)->sub=(node_t*)calloc(1,sizeof(node_t)))){
		//log("calloc node_t fail!\r\n");
		return -3;		
	}
	strncpy((*sub_index_p)->sub->date,seg,SEG_SIZE);
	if(END_L==end)
		(*sub_index_p)->sub->weight++;
	//log("creat node addr:0x%08x,seg=%s\r\n",(*sub_index_p)->sub,seg);	
	*father_p=(*sub_index_p)->sub;
	return 2;
}
int creat_tree(node_t * root){
	int i;
	for(i=0;i<sizeof(strs)/sizeof(strs[0]);i++){
		node_t *father=root;
		char *sub_str=strs[i];
		for(;;){			
			int index=get_str_seg(sub_str,'.');
			if(-1==index)
				return -1;
			else if(-2==index){			
				add_tree_node(&father,sub_str,END_L);
				break;
			}else{
				char seg[SEG_SIZE]="";	
				strncpy(seg,sub_str,MIN(sizeof(seg),index,uint));	
				add_tree_node(&father,seg,UN_END_L);					
				sub_str+=index+1;
			}			
		}		
	}	
	return 0;
}
int main(){
	node_t *root;
	if(NULL==(root=(node_t*)calloc(1,sizeof(node_t)))){
		log("calloc root fail!\r\n");
	}
	//log("creat root node addr:0x%08x,root->sub_star=0x%08x\r\n",root,root->sub_star);		
	if(0!=creat_tree(root)){
		log("creat tree fail\r\n");
		return -1;
	}
	//log("created root node addr:0x%08x,root->sub_star=0x%08x\r\n",root,root->sub_star);			
	show_tree(root);
	//log("show root node addr:0x%08x,root->sub_star=0x%08x\r\n",root,root->sub_star);	
	return 0;
}