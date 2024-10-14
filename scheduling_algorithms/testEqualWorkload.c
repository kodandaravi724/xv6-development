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

int main(int argc, char *argv[]) {
int tickets[4]={20,10,3000,3};
    int start = uptime();
    int pid;
    int num_process = 4;
    for(int i=0;i<num_process;i++){
    pid = fork();
    if(pid==0){
        set_stride_tickets(tickets[i]);
        cpuIntensive();
        printf(1,"pid: %d, Tickets: %d, TurnaroundTime: %d\n",getpid(),tickets[i],uptime()-start);
        exit();
    }
    }
for(int i=0;i<num_process;i++){
wait();
}
    exit();
}
