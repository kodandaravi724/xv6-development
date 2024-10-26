#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BLOCK_SIZE 512
#define NUM_BLOCKS 16550

char buf[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    int fd, i, j, n;

    // open the file for writing
    if((fd = open("testLFile.txt", O_WRONLY | O_CREATE)) < 0){
        printf(2, "Error: cannot open file %s\n", argv[1]);
        exit();
    }

    // write to the file
    for (i = 0; i < NUM_BLOCKS; i++) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            buf[j] = 'a' + (i % 26);
        }
        if ((n = write(fd, buf, BLOCK_SIZE)) != BLOCK_SIZE) {
            printf(2, "Error: write failed\n");
        }
    }
    // close the file
    close(fd);
 printf(1, "Successfully written 16523 blocks to file\n");

    exit();
}


