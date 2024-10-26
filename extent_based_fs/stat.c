
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    struct stat st;

    if (argc != 2) {
        printf(2,"Usage: mystat filename\n");
        exit();
    }

    if (stat(argv[1], &st) < 0) {
        printf(2,"Error: cannot stat %s\n", argv[1]);
        exit();
    }

    printf(1,"File type: %d\n", st.type);
    printf(1,"File size: %d\n", st.size);
    printf(1,"Number of links: %d\n", st.nlink);
    printf(1,"Device number: %d\n", st.dev);
    printf(1,"Inode number: %d\n", st.ino);
    if(st.type==5){
    for(int i=0;i<11;i++){
    if(st.addresses[i]!=0){
 printf(1,"Extent %d: Address %d: length: %d\n", i,st.addresses[i]>>8, st.addresses[i]&0xff);
 }
    }
}
else{
for(int i=0;i<13;i++){
    if(st.addresses[i]!=0){
 printf(1,"Address: %d\n", i,st.addresses[i]);
 }
}
}
    exit();
}
