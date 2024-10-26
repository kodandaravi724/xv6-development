#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BLOCK_SIZE 512
#define NUM_BLOCKS 3

char buf[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    int fd, i, j, n;

    // open the file for writing
    if((fd = open("extentFile.txt", O_WRONLY | O_CREATE | O_EXTENT)) < 0){
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
    printf(1, "Successfully written the extent file\n");
    printf(1, "Reading 512 bytes from the extent file\n");
  char buf[512];

    fd = open("extentFile.txt", O_RDONLY);
    n = read(fd, buf, sizeof(buf));
  if(n < 0){
    printf(2, "read error\n");
    exit();
  }

  printf(1, "read %d bytes\n", n);
  printf(1, "read: %s\n", buf);

    exit();
}


