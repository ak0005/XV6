#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
 
int
main(void)
{
printf(1,"default priority %d\n",getprio());
int fd=open("output.txt",O_WRONLY|O_CREATE); 

    if(fork()==0){
        if(fork()==0){  
            setprio(10);
            unsigned int i=1,k=10;
                while(i!=10000){
                    printf(1,"!!!");
                    i=i+1;
                }
            int a=getrutime(),b=getothtime();
            printf(fd,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
            exit();
        }

        setprio(7);
        unsigned int i=1,k=10;
            while(i!=10000){
                printf(1,"!!!");
                i=i+1;
            }
        int a=getrutime(),b=getothtime();
       printf(fd,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
        wait();
        exit();

    }
        if(fork()==0){
            if(fork()==0){
                
                setprio(6);
                unsigned int i=1,k=10;
                    while(i!=10000){
                        
                    printf(1,"!!!");
                        i=i+1;
                    }
                int a=getrutime(),b=getothtime();
                printf(fd,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
                exit();
            }
            setprio(4);
            unsigned int i=1,k=10;
                while(i!=10000){
                   
                    printf(1,"!!!");
                    i=i+1;
                }
            int a=getrutime(),b=getothtime();
            printf(fd,"%d child Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
            wait();
            exit();
        }
    unsigned int i=1,k=10;
        while(i!=10000){
            
                    printf(1,"!!!");
            i=i+1;
        }
    int a=getrutime(),b=getothtime();
    printf(fd,"%d parent Done with priority %d and yielded %d times with run time %d othtime %d therefore total time %d\n",k,getprio(),yieldcnt(),a,b,a+b);
    wait();
    wait();
    exit();
    
}


