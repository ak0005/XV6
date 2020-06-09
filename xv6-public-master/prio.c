#include "types.h"
#include "stat.h"
#include "user.h"
 
int
main(void)
{
printf(1,"default priority %d\n",getprio());


    if(fork()==0){
        if(fork()==0){  
            setprio(10);
            unsigned int i=1,k=10;
                while(i!=0){
                    k*=i;
                    k%=7;
                    i=i+1;
                }
            int a=getrutime(),b=getothtime();
            printf(1,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
            exit();
        }

        setprio(7);
        unsigned int i=1,k=10;
            while(i!=0){
                k*=i;
                k%=7;
                i=i+1;
            }
        
            int a=getrutime(),b=getothtime();
            printf(1,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
        wait();
        exit();

    }
        if(fork()==0){
            if(fork()==0){
                
                setprio(6);
                unsigned int i=1,k=10;
                    while(i!=0){
                        k*=i;
                        k%=7;
                        i=i+1;
                    }
                
            int a=getrutime(),b=getothtime();
            printf(1,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
                exit();
            }
            setprio(4);
            unsigned int i=1,k=10;
                while(i!=0){
                    k*=i;
                    k%=7;
                    i=i+1;
                }
            
            int a=getrutime(),b=getothtime();
            printf(1,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
            wait();
            exit();
        }
    unsigned int i=1,k=10;
        while(i!=0){
            k*=i;
            k%=7;
            i=i+1;
        }
    
            int a=getrutime(),b=getothtime();
            printf(1,"%d parent Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
    wait();
    wait();
    exit();
    
}


