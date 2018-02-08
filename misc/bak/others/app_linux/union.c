#include <stdio.h>  
struct s1{  
        union u{  
                int i;  
        };  
        struct ss1{  
                int i;  
        };  
};  
  
struct s2{  
        union{  
                int i;  
        };  
        struct{  
                int i;  
        };  
};  
  
struct s3{//the same to s2  
        union su3{  
                int i;  
        }su33;  
        struct ss3{  
                int i;  
        }ss33;  
};  
  
union su4{  
        int i;  
};  
struct ss4{  
        int i;  
};  
struct s4{//the same to s3  
        union su4 su44;  
        struct ss4 ss44;  
};  
struct s5{//the same to s1  
        union su4;  
        struct ss4;  
};  
  
struct s6{//the same to s1  
        union{  
                int;  
        };  
        struct{  
                int;  
        };  
};  
  
main(){  
        struct s1 sVal1;  
        struct s2 sVal2;  
        struct s3 sVal3;  
        struct s4 sVal4;  
        struct s5 sVal5;  
        struct s6 sVal6;  
  
        printf("sVal1's size:%d\n",(int)sizeof(sVal1));  
        //printf("sVal1:%p\t%d\n",&sVal1);  
  
        printf("sVal2's size:%d\n",(int)sizeof(sVal2));  
        //printf("sVal2:%p\t%d\n",&sVal2);  
  
        printf("sVal3's size:%d\n",(int)sizeof(sVal3));  
        //printf("sVal3:%p\t%d\n",&sVal3);  
  
        printf("sVal4's size:%d\n",(int)sizeof(sVal4));  
        //printf("sVal4:%p\t%d\n",&sVal4);  
  
        printf("sVal5's size:%d\n",(int)sizeof(sVal5));  
       // printf("sVal5:%p\t%d\n",&sVal5);  
  
        printf("sVal5's size:%d\n",(int)sizeof(sVal5));  
        //printf("sVal5:%p\t%d\n",&sVal5);  
}  