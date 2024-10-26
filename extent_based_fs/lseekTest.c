#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int fd;
  char buf[512];

  fd = open("README", O_RDONLY);
  if(fd < 0){
    printf(2, "cannot open README\n");
    exit();
  }

  int offset = 100;
  int new_offset = lseek(fd, offset);
  if(new_offset < 0){
    printf(2, "lseek error\n");
    exit();
  }

  int n = read(fd, buf, sizeof(buf));
  if(n < 0){
    printf(2, "read error\n");
    exit();
  }

  printf(1, "read %d bytes\n", n);
  printf(1, "read: %s\n", buf);

  exit();
}
