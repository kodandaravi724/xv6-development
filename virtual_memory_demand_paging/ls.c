#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
char hidden = 't';
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      if(de.name[0]!='.' || !(hidden=='t')){
      if(st.type==1){
      printf(1, "%s%c %d %d %d\n", p,'/', st.type, st.ino, st.size);
      }
      else{
      printf(1, "%s %d %d %d\n", p, st.type, st.ino, st.size);
      }
      }

    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  if(argc==2 && strcmp(argv[1],"-a")==0){
  hidden = 'f';
  ls(".");
  exit();
  }
  for(i=1; i<argc; i++){
  if(strcmp(argv[i],"-a")==0){
  hidden = 'f';
  }
  }
  for(i=1; i<argc; i++){
  if(strcmp(argv[i],"-a")!=0){
  ls(argv[i]);
  }
  }
  exit();
}
