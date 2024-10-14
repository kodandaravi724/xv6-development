#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

#include "traps.h"

#define PGSIZE 4096

int main(int argc, char *argv[]) {
    int num_pages = 8;
    int i;

    // Allocate more pages than available
    char *ptr[num_pages];
    for (i = 0; i < num_pages; i++) {
        ptr[i] = sbrk(PGSIZE);
        if (ptr[i] == (void *)-1) {
            printf(1,"Out of memory\n");
            break;
        }
        *ptr[i]=i;
        printf(1,"Allocated page %d at address %p\n\n", i+1,ptr[i]);
    }


    exit();
}
