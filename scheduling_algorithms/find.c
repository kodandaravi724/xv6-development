#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
//#include<stddef.h>

char* name="-1";
char type='n';
char* size="-1";
int validateName(char* name, char* path){
if((name && strcmp(name,path)==0) || (strcmp(name,"-1")==0)){
return 1;
}
return 0;
}
int compareSize(uint fileSize,char* inputSize){
if(strcmp(size,"-1")==0){
return 1;
}
else{
if(inputSize[0]=='+'){
inputSize = inputSize+1;
if(fileSize>atoi(inputSize)){
return 1;
}
return 0;
}
else if(inputSize[0]=='-'){
inputSize = inputSize+1;
if(fileSize<atoi(inputSize)){
return 1;
}
return 0;
}
else{
if(fileSize==atoi(inputSize)){
return 1;
}
return 0;
}
}
}

void find(char *path)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0)
    {
        printf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0)
    {
        printf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type)
    {
    case T_FILE:
        if(name && strcmp(name, path) == 0){
                if(compareSize(st.size,size)==1){
                printf(1, "%s f\n", path);
                }
            }
        break;

    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf(1, "find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0)
            {
                printf(1, "find: cannot stat %s\n", buf);
                continue;
            }

            if(type == 'f' && st.type == T_FILE && (compareSize(st.size,size)==1) && (validateName(name,p)==1))
            {
                    printf(1, "%s\n", buf);
            }
            if(type == 'd' && st.type == T_DIR && (compareSize(st.size,size)==1)&& (validateName(name,p)==1))
            {
                    printf(1, "%s\n", buf);
            }
            if(type == 'n')
            {

                if((validateName(name,p)==1)&& (compareSize(st.size,size)==1))
                {
                        printf(1,"%s\n",buf);
                }
            }

            if(st.type == T_DIR && !(strcmp(de.name,".")==0)&& !(strcmp(de.name,"..")==0))
                find(buf);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    int i;
    char* inputPath = "-1";
    if(argc < 2)
    {
        find(".");
        exit();
    }
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-name") == 0)
        {
            if(i + 1 < argc)
            {
                name = argv[i+1];
                i++;
                continue;
            }
        }
        if(strcmp(argv[i], "-type") == 0)
        {
            if(i + 1 < argc)
            {
                type = argv[i+1][0];
                i++;
                continue;
            }
        }
        if(strcmp(argv[i],"-size")==0)
        {
            if(i+1<argc)
            {
                size = argv[i+1];
                i++;
                continue;
            }
        }
        inputPath = argv[i];
    }
    if(strcmp(inputPath,"-1")!=0){
    find(inputPath);
    }
    else{
    find(".");
    }
    exit();
    return 0;
}

