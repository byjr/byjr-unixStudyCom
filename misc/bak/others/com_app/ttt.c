#include<stdio.h>
#include<iostream>
int d[100];
int ans[100];
#define n  15
int a[n+1] ={33,1,2,9,3,4,1,3,5,3,4,5,6,7,8};
int pre[n+1];
int main(){
	int head,max_len,i,j,k;
	d[0] = 1 ;
	pre[0] = -1 ;//表示0号元素前面没有元素 
	for(i=1;i<n;i++){
		d[i] = 1;
		pre[i] = -1;  
		for(j=0;j<i;j++){
			if(a[i] > a[j] && d[i] < d[j] + 1 )
			{
				d[i] =d[j] + 1;
				pre[i] = j; 
			} 
		}
	}
	max_len = 1;
	head = 0; 
	for(i=1;i<n;i++){
		if(d[i] > max_len)
		{
			max_len = d[i];
			head = i;
		}
	}
	printf("max is index = %d value = %d\n",head,d[head]);
	k=0;
	while(head != -1){
	//	printf("%d ",head);
		ans[k++] = head;
		head = pre[head];
	}
	//system("pause");
	for(i=k-1;i>=0;i--){
		printf("%d ",a[ans[i]]);
	}
}
