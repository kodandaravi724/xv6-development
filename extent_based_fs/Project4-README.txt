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


1. lseek Implementation:-


To implement lseek I have added new system call lseek which takes the file descriptor, offset user want's to set as an input. Based on the file descriptor user has passed retrieve the struct file object of that file and set the "off" attribute of the file struct to the offset user has passed. If the offset was set beyond the file size then, the extra block was filled with 0's. To implement this, code change is done in filewrite function. In filewrite function check if the offset is less than file. If offset is greater than file size then take the difference of the bytes and fill them with 0's.

In lseek user program, we are reading README file and setting the offset to 100. Hence in the output it was sent that the data is printed from the 100th character in the file.


2. Symlink implementation.

For symlink implementation, I was using inode data blocks to store the path name of the target. I was considering the max path would be 498 bytes and then storing the path in data blocks and filling the remaining bytes in the block with 0's. In open system call when reading the path name is being read from the data blocks and then using that name the inode is derived. This step continues until the i-node type of file is encountered. If the recursion depth exceeds 10 then error is thrown.


In the symlink test program, a symlink to readme file is created with the link name test_symlink.


PART 3

Implementation of doubly-indirect blocks.

I have modified bmap() to implement the doubly-indirect blocks. In current file system there were 12 direct blocks and 1 indirect blocks. I have modified such that there were 11 direct blocks, 1 indirect block  and other block for doubly-indirect block. 

In the On-disk i-node structure change the size of addrs to NDIRECT+2 as count of direct block was reduced by 1.

Before the implementation of doubly indirect blocks, when we tried to write 16523 blocks it has failed with the write error.

After the implementation, 16523 blocks were successfully written.

When tried to write 16600 blocks it again failed with write error.


PART - 4

For task 4 to implement the extent based filesystem 24 bits in each slot of data block is used for address space and 8 bits were used to represent the length of the extent.

In extent based filesystem support for indirect blocks is removed. Only 11 direct blocks were used. In bmap() function code is added to add the support for extent based files.

To free the extent files code was added in itrunc function in which we are checking if the address not 0 then it was assigned hence freeing it.

In the test program, the extent file is written and then 512 bytes is read from the file.

Stat user program is developed using which the information of file is printed.