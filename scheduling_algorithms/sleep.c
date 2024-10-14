#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char* argv[]){

int sleepDuration=0;

if(argc<2){
printf(1,"Error! please provide sleep duration as an argument!\n");
}
for(int i=1;i<argc;i++){
sleepDuration = atoi(argv[i]);
}
sleep(sleepDuration);

exit();
return 0;
}
