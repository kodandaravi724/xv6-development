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




time_scheduled() system call implementation

*In trap.c file interrupt is handled for every tick, in that I was calling updateRunningTime function which increments the timeElapsed for the processes in RUNNING state by 1 tick.



Stride Scheduler Implementation:-


* In stride scheduler I have taken stride constant as 100000 and in the scheduler function at each iteration process having the minimum pass value is fetched and then it is given CPU time for 1 tick.
* After 1 tick we will get back the CPU control and then step 1 repeats again.




Lottery Scheduler Implementation:-

* To generate the winning ticket number we have implemented the get_random function which takes min and max as argument. It generates the random number in the range of mi inclusive and max exclusive. 
* In scheduler function for each iteration generate the random winning ticket which is in range of the 1 to totalTIckets of all processes in RUNNABLE state. 
* totalTickets is declared as global variable and it was updated dynamically when process switches to other Staes from RUNNING.
* The process whose ticket is in range of winning ticket number is given the cpu time.
* After 1 tick we will get back the control of CPU, and then process repeats from step 1.


For testing purpose I have created a program testEqualWorkload which creates 4 child processes and each child processes runs the same workload. When changing algorithms the difference in turnaround time is observed for each child. This test case can be run an STRIDE, LOTTERY, DEFAULT scheduling algorithms.


