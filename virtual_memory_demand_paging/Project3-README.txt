Group Members:-


Kodanda Ravi Kiran Putta
Avanish Yemula
Sainikhil Reddy Basupally


System Environment:-


Operating System:- Ubuntu


We have installed the Ubuntu virtual machine on my M1 mac. As my architecture is ARM I have installed a cross-compiler that produces 32-bit x86 binaries. I have followed the steps from this URL to install xv6 on my Ubuntu VM ( https://www.cs.virginia.edu/~cr4bd/4414/S2022/xv6intro.html )


Operating system: Windows 11
Processor : Intel i5


We have installed Windows subsystem linux(WSL) on our machine to support the Ubuntu command prompt.




PART - 1


1. Page Allocation in xv6 os

When a process requests additional memory in xv6, the operating system searches for free physical pages to allocate for storing the requested data. Once it finds a suitable page, it adds Page Table Entries (PTEs) to the process's page table that point to the newly allocated physical page. These PTEs are configured with the PTE_U, PTE_W, and PTE_P flags, which indicate that they are accessible in user mode, are writable, and are present in physical memory, respectively.
However, since most processes do not use their entire user address space, xv6 leaves the PTE_P flag clear in the unused PTEs. By doing this, it avoids allocating physical memory for unused portions of the process's address space. Each process's page table translates user addresses to different pages of physical memory, allowing each process to have its own private user memory.
In summary, xv6 allocates physical memory pages to processes when they request additional memory. It creates PTEs for these pages in the process's page table and configures them with the necessary flags to allow user access, writing, and presence in physical memory. Unused portions of the process's address space do not have physical pages allocated to them, and PTEs for these portions do not have the PTE_P flag set. Each process has its own private user memory, and its page table translates user addresses to physical memory pages specific to that process.

2. Why Xv6 is broken after modifying the implementation of sbrk

In the modified version of sbrk system call when it is rewritten to only increment the process's sz field and not allocate the new pages of memory by removing the call to growproc function, the programs that rely on dynamic memory allocation will fail as new memory is not allocated here.

When program requests for memory using sbrok(), in the old version the kernel would allocate new pages of memory if there was not enough memory in the process address space. As in the modified version, we are not allocating new pages when program tries to access the page that has not been allocated yet, it will trigger a page fault. 

For example, when I tried to execute ls command after modifying the implementation of sbrk system call it failed with below panic. 
pid 3 sh: trap 14 err 6 on cpu 1 eip 0x11e8 addr 0x4004--kill proc
From the above statement it can be inferred that program failed with page fault. 

"pid 3" refers to the process ID of the process that caused the panic.
"sh" refers to the name of the shell program that was running when the error occurred.
"trap 14" refers to the type of trap that occurred. In this case, trap 14 indicates a page fault, which occurred as process is trying to access the memory that was not mapped to it's address space.
"err 6" refers to the error code associated with the trap.
"cpu 1" refers to the id of CPU core the process was executing.
"eip 0x11e8" refers to the instruction pointer, which is the memory address of the instruction that caused the trap.
"addr 0x4004" refers to the memory address that the process was trying to access when the page fault occurred.


3. Significance of sbrk system call in xv6

In xv6, sbrk system call allows process to dynamically allocate or deallocate the memory at runtime, which is helpful in efficient use of system resources as there was no need to know the memory needed for the process beforehand. sbrk achieves this by making a call to growproc function with the number of bytes (n) needed. If n is positive, then growproc allocated one or more physical pages and maps them to the top of process address space. If n is negative then it deallocates the memory. The function growproc uses allocuvm function to allocate new pages of memory, and allocuvm uses kalloc() to obtain the free memory.



PART - 3

Implementation of Lazy Allocation:-

In this project, I have implemented Lazy allocation by handling the page faults in trap.c. whenever a process access a virtual address that has not been mapped to physical address, a page fault occurs. This page fault is handled by allocating a new physical page and mapping it to the virtual address. In this, mappages() function is used to map the physical address to the physical address. 

In trap.c when handling the trap, we are checking if trap is a page fault. If it is page fault then below steps are followed.

1) Fetch the virtual address that caused the page fault exception, by calling the function rcr2() that returns the value in register CR2. CR2 register in xv6 holds the value of virtual address that caused page fault exception.
2) Then we are allocating a new physical page using kalloc() which returns a pointer to new physical page. If it returns 0 then that means no physical pages are available.
3) Then we call memset(mem, 0, PGSIZE) to set all bytes of the memory pointed to by mem to zero. Here, mem is a pointer to a page of memory and PGSIZE is a constant that represents the size of a page in xv6 (4096 bytes). 
4) PGROUNDDOWN(rcr2()) is done to ensure that the page fault address falls on a page boundary.
5) After that a mappages() is used to map the physical page to the virtual address that caused the page fault.
6) After allocating page we are returning to user space.

In trap.c when handling page fault I added a debug statement to print the virtual address at which page fault has occurred.
cprintf("page fault at address %p\n",rcr2());
After page has been allocated and mapped to physical address then another print statement is added to print that page has allocated and mapped to virtual address.
cprintf("successfully mapped the virtual address %p to physical address %p\n",PGROUNDDOWN(rcr2()),V2P(mem));


To test the lazy page allocation custom user program is developed.

In user test program we are allocating more pages than are available in the system and accessing them one by one. In the for-loop, the test program attempts to allocate 8 pages by calling the sbrk system call to increase the size of the process's heap by one page (specified by PGSIZE) on each iteration of the loop. If the call to sbrk fails, the program prints an error message and exits.

Since the program is allocating more pages than are physically available in the system, a page fault occurs when the program tries to access a page that has not yet been allocated. This page fault triggers the lazy page allocation mechanism, which allocates a physical page and maps it to the virtual page that caused the fault.

After the page has been allocated and mapped, the program writes the value of i to the first byte of the page using the line *ptr[i]=i;

When I ran the program I got the below output.

$ testlazy
page fault at address 4004
successfully mapped the virtual address 4000 to physical address df2b000
page fault at address bfa4
successfully mapped the virtual address b000 to physical address df2a000
page fault at address 3000
successfully mapped the virtual address 3000 to physical address dfbc000
Allocated page 1 at address 3000

page fault at address 4000
successfully mapped the virtual address 4000 to physical address df76000
Allocated page 2 at address 4000

page fault at address 5000
successfully mapped the virtual address 5000 to physical address dfbf000
Allocated page 3 at address 5000

page fault at address 6000
successfully mapped the virtual address 6000 to physical address dfc0000
Allocated page 4 at address 6000

page fault at address 7000
successfully mapped the virtual address 7000 to physical address dfc1000
Allocated page 5 at address 7000

page fault at address 8000
successfully mapped the virtual address 8000 to physical address dfc2000
Allocated page 6 at address 8000

page fault at address 9000
successfully mapped the virtual address 9000 to physical address dfc3000
Allocated page 7 at address 9000

page fault at address a000
successfully mapped the virtual address a000 to physical address dfc4000
Allocated page 8 at address A000

From the above output, we can see that page faults occur when accessing memory addresses that have not been allocated yet. This is expected behavior since the program is trying to allocate more pages than are physically available in the system.

However, we can also see that the program is successfully allocating pages on demand as they are accessed. For example, when the program accesses address 5000, a page fault occurs and then we are able to map the virtual address 4000 to physical address dfbf000. Similarly, for the remaining pages they were allocated when they were accessed.

Similarly when executing the commands(echo, ls, cat, wc, mkdir) as seen from the screenshots, pages are allocated on demand. When a page fault has occurred, a physical page is allocated and it was mapped to virtual page that caused the fault.
