#include "types.h"
#include "stat.h"
#include "user.h"


void cpuIntensive(){
    int i, j, k;
    volatile int sum = 0;
    // Loop to perform a highly intensive CPU task
    for (i = 0; i < 100000; i++) {
        for (j = 0; j < 500; j++) {
            for (k = 0; k < 10; k++) {
                sum = (sum + (i*j)); // Do some arithmetic operations
            }
        }
    }
}

void cpuIntensive2(){
    int i, j, k;
    volatile int sum = 0;
    for (i = 0; i < 100000; i++) {
        for (j = 0; j < 500; j++) {
            for (k = 0; k < 2; k++) {
                sum=sum+i; // Do some arithmetic operations
            }
        }
    }
}

int main(int argc, char *argv[]) {

    int pid;
    int num_process = 4;
    for(int i=0;i<num_process;i++){
    pid = fork();
    if(pid==0){
        if((i%2)==0){
        cpuIntensive();
        }
        else{
        cpuIntensive2();
        }
       printf(1,"PID %d scheduled for %d ticks\n",getpid(),time_scheduled(getpid()));
        exit();
    }
    }
for(int i=0;i<num_process;i++){
wait();
}
    exit();
}

