#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[]) {
  int process[4];
  int times[4];

    int start = uptime();
    int pid;
    int num_process = 4;
    for(int i=0;i<num_process;i++){
    pid = fork();
    if(pid==0){
        if(i==0){
        set_lottery_tickets(40000);
        char *args[2];
        args[0]="stressfs";
        args[1]=0;
        exec(args[0],args);

        }
        else if(i==1){
        set_lottery_tickets(2);
        char *args[4];
        args[0]="uniq";
        args[1]="-i";
        args[2]="test.txt";
        args[3]=0;
        exec(args[0],args);
        }
        else if(i==2){
        set_lottery_tickets(2);
        char *args[4];
        args[0]="find";
        args[1]=".";
        args[2]="-name";
        args[3]="test.txt";
        exec(args[0],args);
        }
        else{
        set_lottery_tickets(2);
        char *args[4];
        args[0]="cat";
        args[1]="README";
        args[2]=0;
        exec(args[0],args);

        }
        exit();
    }
    }
    int ind=0;
for(int i=0;i<num_process;i++){
process[ind]=wait();
times[ind] = uptime()-start;
ind++;
}
for(int i=0;i<4;i++){
printf(1,"pid: %d, time: %d\n",process[i],times[i]);
}
    exit();
}
