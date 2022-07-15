# 进程管理习题

## 进程与线程

### 进程

#### 进程概念

**例题** 进程与程序的根本区别是()。

$A.$静态和动态特点

$B.$是不是被调入内存

$C.$是不是具有就绪、运行和等待三种状态

$D.$是不是占有处理器

解：$A$。动态性是进程最重要的特性，以此来区分文件形式的静态程序。操作系统引入进程的概念，是为了从变化的角度动态地分析和研究程序的执行。

**例题** 同一程序经过多次创建，运行在不同的数据集上，形成了()的进程。

$A.$不同

$B.$相同

$C.$同步

$D.$互斥

解：$A$。一个进程是程序在一个数据集上的一次运行过程。运行于不同的数据集，将会形成不同的进程。

#### 进程结构

**例题** 若一个进程实体由$PCB$、共享正文段、数据堆段和数据栈段组成，请指出下列$C$语言程序中的内容及相关数据结构各位于哪一段中。

Ⅰ.全局赋值变量

Ⅱ.未赋值的局部变量

Ⅲ.函数调用实参传递值

Ⅳ.用`malloc()`要求动态分配的存储区

Ⅴ.常量值（如`1995`、`"string"`）

Ⅵ.进程的优先级

$A.PCB$

$B.$正文段

$C.$堆段

$D.$栈段

解：$B$、$D$、$D$、$C$、$B$、$A$。$C$语言编写的程序在使用内存时一般分为三个段，它们一般是正文段（即代码和赋值数据段）、数据堆段和数据栈段。二进制代码和常量存放在正文段，动态分配的存储区在数据堆段，临时使用的变量在数据栈段。由此，我们可以确定全局赋值变量在正文段赋值数据段，未赋值的局部变量和实参传递在栈段，动态内存分配在堆段，常量在正文段，进程的优先级与进程直接相关，放在$PCB$内。

#### 进程状态

**例题** 下面的叙述中，正确的是()。

$A.$进程获得处理器运行是通过调度得到的

$B.$优先级是进程调度的重要依据，一旦确定不能改动

$C.$在单处理器系统中，任何时刻都只有一个进程处于运行态

$D.$进程申请处理器而得不到满足时，其状态变为阻塞态

解：$A$。选项$B$错在优先级分静态和动态两种，动态优先级是根据运行情况而随时调整的。选项$C$错在至多只存在一个运行态，系统发生死锁时有可能进程全部都处于阻塞态，或无进程任务，$CPU$空闲。选项$D$错在进程申请处理器得不到满足时就处于就绪态，等待处理器的调度。

#### 进程优先级

**例题** 下列选项中，降低进程优先级的合理时机是()。

$A.$进程时间片用完

$B.$进程刚完成$I/O$操作，进入就绪队列

$C.$进程长期处于就绪队列

$D.$进程从就绪态转为运行态

解：$A$。$A$中进程时间片用完，可降低其优先级以让其他进程被调度进入执行状态避免不断占用处理机，使得其他进程产生饥饿。$B$中进程刚完成$I/O$，进入就绪队列等待被处理机调度，为了让其尽快处理$I/O$结果，因此应提高优先级。$C$中进程长期处于就绪队列，为不至于产生饥饿现象，也应适当提高优先级。$D$中进程的优先级不应该在此时降低，如果此时降低了可能会被抢占，导致进程反复切换，降低处理效率，而应在时间片用完后再降低。

#### 父子进程

**例题** 下列关于父进程与子进程的叙述中，错误的是()。

$A.$父进程与子进程可以并发执行

$B.$父进程与子进程共享虚拟地址空间

$C.$父进程与子进程有不同的进程控制块

$D.$父进程与子进程不能同时使用同一临界资源

解：$B$。父进程与子进程当然可以并发执行，$A$正确。父进程可与子进程共享一部分资源，但不能共享虚拟地址空间，在创建子进程时，会为子进程分配资源，如虚拟地址空间等，$B$错误。临界资源一次只能为一个进程所用，$D$正确。进程控制块$PCB$是进程存在的唯一标志，每个进程都有自己的$PCB$，$C$正确。

#### 进程通信

**例题** 下列关于管道（$Pipe$）通信的叙述中，正确的是()。

$A.$一个管道可实现双向数据传输

$B.$管道的容量仅受磁盘容量大小限制

$C.$进程对管道进行读操作和写操作都可能被阻塞

$D.$一个管道只能有一个读进程或一个写进程对其操作

解：$C$。管道类似于通信中半双工信道的进程通信机制，一个管道可以实现双向的数据传输，但是同一时刻只能最多有一个方向的传输，不能两个方向同时进行，所以必须使用两个管道才能实现双向数据传输（特指同时），$A$错误。管道的容量大小通常为内存上的一页，它的大小并不受磁盘容量大小的限制，$B$错误。当管道满时，进程在写管道会被阻塞，而当管道空时，进程在读管道会被阻塞，因此选$C$。一个管道可以被多个读进程或写进程操作，但是同一时间只能有一个读进程或一个写进程对其操作，$D$没有限制是同时所以错误。

### 线程

#### 线程概念

**例题** 系统动态$DLL$库中的系统线程，被不同的进程所调用，它们是()的线程。

$A.$不同

$B.$相同

$C.$可能不同，也可能相同

$D.$不能被调用

解：$B$。进程是暂时的，程序是永久的；进程是动态的，程序是静态的；进程至少由代码、数据和$PCB$组成，程序仅需代码和数据即可；程序代码经过多次创建可对应不同的进程，而同一个系统的进程（或线程）可以由系统调用的方法被不同的进程（或线程）多次使用。

#### 线程实现

**例题** 下面关于用户级线程和内核级线程的描述中，错误的是()。

$A.$采用轮转调度算法，进程中设置内核级线程和用户级线程的效果完全不同

$B.$跨进程的用户级线程调度也不需要内核参与，控制简单

$C.$用户级线程可以在任何操作系统中运行

$D.$若系统中只有用户级线程，则处理机的调度对象是进程

解：$B$。对于$A$，如果是同一个进程中的线程进行切换，用户级线程不需要内核参与，而相反内核级线程则需要，所以使用轮转调度算法进行切换时实现方式是完全不同的。对于$B$，只有相同进程的用户级线程切换可以直接在用户态完成，如果要跨进程用户级线程就需要进行进程调度，从而需要内核参与。对于$C$，用户级线程的维护由应用进程完成，不需要操作系统内核了解用户级线程的存在，因此可在任何操作系统中运行。对于$D$，如果系统只有用户态线程，则线程对操作系统是不可见的，操作系统只能调度进程；如果系统中有内核态线程，则操作系统可以按线程进行调度。

#### 多线程系统

**例题** 在以下描述中，()并不是多线程系统的特长。

$A.$利用线程并行地执行矩阵乘法运算

$B.Web$服务器利用线程响应$HTTP$请求

$C.$键盘驱动程序为每个正在运行的应用配备一个线程，用以响应该应用的键盘输入

$D.$基于$GUI$的调试程序用不同的线程分别处理用户输入、计算和跟踪等操作

解：$C$。对于题目所提的不算多线程系统的特长，即找出下面情形可以用一个线程就可以完成的情况。多线程适用于复杂并发的操作，而整个系统只有一个键盘，而且键盘输入是人的操作，速度比较慢，完全可以使用一个线程来处理整个系统的键盘输入。

## 处理机调度

### 调度算法

#### 先来先服务

**例题** 各进程到达就绪队列的时间、需要的运行时间如下表所示。使用先来先服务调度算法，计算各进程的等待时间、平均等待时间、周转时间、平均周转时间、带权周转时间、平均带权周转时间。

进程|到达时间|运行时间
:--:|:-----:|:------:
P1|0|7
P2|2|4
P3|4|1
P4|5|4

解：

根据先来先服务的思想，根据到达的顺序，得到调度顺序为：$P1$、$P2$、$P3$、$P4$。

所以$P1$在$0$到达，$0+7=7$完成。$P2$在$2$到达，而$7$时$P1$完成。所以$P2$要等待$7-2=5$，所以$P2$从$7$开始，在$7+4=11$完成。$P3$在$4$到达，所以需要等待$11-4=7$，从$11$开始，在$11+1=12$结束。$P4$在$5$到达，需要等待$12-5-7$，从$12$开始，在$12+4=16$结束。

进程|到达时间|运行时间|等待时间|开始时间|完成时间
:--:|:-----:|:------:|:-----:|:-----:|:------:
P1|0|7|0|0|7
P2|2|4|5|7|11
P3|4|1|7|11|12
P4|5|4|7|12|16

因为周转时间=完成时间-到达时间。所以$P1=7-0=7$，$P2=11-2=9$，$P3=12-4=8$，$P4=16-5=11$。

带权周转时间=周转时间÷运行时间。所以$P1=7\div7=1$，$P2=9\div4=2.25$，$P3=8\div1=8$，$P4=11\div4=2.75$。

等待时间=周转时间-运行时间。根据表格可得。

所以平均周转时间$=(7+9+8+11)\div4=8.75$。平均带权周转时间$=(1+2.25+8+2.75)\div4=3.5$。平均等待时间$=(0+5+7+7)\div4=4.75$。

#### 短作业优先

**例题** 各进程到达就绪队列的时间、需要的运行时间如下表所示。使用非抢占式短进程优先调度算法和抢占式短进程优先调度算法，分别计算各进程的等待时间、平均等待时间、周转时间、平均周转时间、带权周转时间、平均带权周转时间。

进程|到达时间|运行时间
:--:|:-----:|:------:
P1|0|7
P2|2|4
P3|4|1
P4|5|4

解：

如果使用非抢占式的，因为每次选择当前已经到达且运行时间最短的作业/进程，因为$P1$第一个到达，所以第一个开始，$P1$完成时是$7$，$P2$、$P3$、$P4$都到达了，所以依次选最短运行时间的开始。$7$时$P3$开始，$7+1=8$时结束，$P2$开始（用了$FCFS$思想），$8+4=12$时结束，$P4$开始，$12+4=16$结束。所以调度顺序为$P1$、$P3$、$P2$、$P4$。

所以$P1$、$P3$、$P2$、$P4$周转时间为$7-0=7$、$8-4=4$、$12-2=10$、$16-5=11$。带权周转时间为$7\div7=1$、$4\div1=4$、$10\div4=2.5$、$11\div4=2.75$。等待时间为$0-0=0$、$7-4=3$、$8-2=6$、$12-5=7$。平均周转时间为$(4+7+10+11)\div4=32\div4=8$。平均带权周转时间为$(1+4+2.5+2.75)\div4=10.25\div4=2.5625$。平均等待时间为$(0+3+6+7)\div4=16\div4=4$。

如果使用抢占式的，若新到达进程剩余时间要比当前运行的进程剩余时间更短，则由新进程抢占处理机。

$0$时$P1$到达，$P1$剩余时间为$7$，所以$P1$开始运行。$2$时$P2$到达，此时$P1$剩余时间为$7-2=5$，而$P2$剩余时间为$4-0=4$，$4<5$，所以$P2$抢占$P1$处理机。$4$时$P3$到达，此时$P2$剩余时间为$4-2=2$，而$P3$剩余时间为$1-0=1$，所以$P3$又抢占$P2$处理机。到$5$时$P4$到达，此时$P3$正好运行完，所以要考虑$P1$、$P2$、$P4$三个的剩余时间，分别为$5$、$2$、$4$，所以$P2$抢占处理机运行。$5+2=7$时$P2$运行完，$P4$剩余时间更少抢占处理机。$7+4=11$时$P4$运行完，$P1$抢占处理机。最后$11+5=16$时$P1$运行完，作业全部结束。

所以$P1$、$P2$、$P3$、$P4$周转时间为$16-0=16$、$7-2=5$、$5-4=1$、$11-5=6$。带权周转时间为$16\div7=2.28$、$5\div4=1.25$、$1\div1=1$、$6\div4=1.5$。等待时间分别为$0-0+11-2=9$、$2-2+5-4=1$、$4-4=0$、$7-5=2$。平均周转时间为$(16+5+1+6)\div4=28\div4=7$。平均带权周转时间为$(2.28+1.25+1+1.5)\div4=1.5$。平均等待时间为$(9+1+0+2)\div4=12\div4=3$。

#### 高响应比优先

**例题** 各进程到达就绪队列的时间、需要的运行时间如下表所示。使用高响应比优先调度算法，计算各进程的等待时间、平均等待时间、周转时间、平均周转时间、带权周转时间、平均带权周转时间。

进程|到达时间|运行时间
:--:|:-----:|:------:
P1|0|7
P2|2|4
P3|4|1
P4|5|4

解：

需要利用公式计算响应比，最重要的是等待时间和运行时间。当$0$时$P1$到达，$P1$运行。$7$时$P1$完成，此时$P2$、$P3$、$P4$全部到达了，而响应比分别为$(7-2+4)\div4=9\div4=2.25$、$(7-4+1)\div1=4\div1=4$、$(7-5+4)\div4=6\div4=1.5$，所以选择$P3$上处理机运行。$7+1=8$时，$P3$完成，此时响应比分别为$P2:(8-2+4)\div4=10\div4=2.5$、$P4:(8-5+4)\div4=7\div4=1.75$，$P2$运行。$8+4=12$时$P2$完成，$P4$运行，最后$12+4=16$时全部完成。

所以$P1$、$P2$、$P3$、$P4$等待时间为$0-0=0$、$8-2=6$、$7-4=3$、$12-5=7$，平均等待时间为$(0+6+3+7)\div4=16\div4=4$。周转时间为$7-0=7$、$12-2=10$、$8-4=4$、$16-5=11$，平均周转时间为$(7+10+4+11)\div4=32\div4=8$。带权周转时间为$7\div7=1$、$10\div4=2.5$、$4\div1=4$、$11\div4=2.75$，平均带权周转时间为$(1+2.5+4+2.75)\div4=2.5625$。

#### 时间片轮转

**例题** 各进程到达就绪队列的时间、需要的运行时间如下表所示。使用时间片轮转调度算法，分析时间片大小为$2$时的进程运行状态。

进程|到达时间|运行时间
:--:|:-----:|:------:
P1|0|7
P2|2|4
P3|4|1
P4|5|4

<span style="color:orange">注意：</span>当同一时刻既有时间片用完也有新进程到达时，默认新到达进程先进入队列，时间片用完的进程后进入。

解：

若时间片为$2$：

当$0$时，因为只有$P1$到达就绪队列，所以$P1$运行一个时间片。

当$2$时，$P1$时间片运行完，余下$7-2=5$个时间。正好$P2$到达就绪队列，所以$P1$处理机被剥夺，重新放到就绪队列尾，让$P2$运行一个时间片。

当$4$时，$P2$时间片运行完，余下$4-2=2$个时间。正好$P3$到达就绪队列加入队尾，此时$P1$到达队头，所以$P2$处理机被剥夺，重新放到就绪队列尾，让$P1$运行一个时间片。

当$5$时，$P4$到达加入就绪队列。此时就绪队列上有$P3$、$P2$、$P4$。

当$6$时，$P1$时间片运行完，余下$5-2=3$个时间。此时$P3$到达队头，所以$P1$处理机被剥夺，重新放到就绪队尾，让$P3$运行。此时就绪队列上有$P2$、$P4$、$P1$。

当$7$时，虽然$P3$时间片没有用完，但是由于$P3$只需一个单位的时间，所以主动放弃处理机，发生调度，让$P2$运行一个时间片。

当$9$时，$P2$正好运行完也用完时间片，$P4$上处理机。此时就绪队列上有$P1$。

当$11$时，$P4$时间片用完，余下$4-2=2$个时间，此时$P1$到达队头，所以$P4$处理机被剥夺，重新放到就绪队尾，让$P1$运行。

当$13$时，$P1$时间片用完，余下$3-2=1$个时间，此时$P4$到达队头，所以$P1$处理机被剥夺，重新放到就绪队尾，让$P4$运行。

当$15$时，$P4$正好运行完也用完时间片，$P1$上处理机。

当$16$时，$P1$运行完，主动放弃处理机。

#### 优先级

**例题** 某系统采用基于优先权的非抢占式进程调度策略，完成一次进程调度和进程切换的系统时间开销为$1\mu s$。在$T$时刻就绪队列中有$3$个进程$P_1$、$P_2$和$P_3$，其在就绪队列中的等待时间、需要的$CPU$时间和优先权如下表所示。

进程|等待时间|需要CPU时间|优先权
:--:|:------:|:---------:|:----:
P1|30|12|10
P2|15|24|30
P3|18|36|20

若优先权值大的进程优先获得$CPU$，从$T$时进刻起系统开始进程调度，则系统的平均周转时间为()。

$A.72\mu s$

$B.73\mu s$

$C.74\mu s$

$D.75\mu s$

解：$D$。执行顺序：$P_2\rightarrow P_3\rightarrow P_1$，基本上计算没什么问题，但是要注意添加上调度时间要依次加一二三次，$P_2=1+15+24=40$、$P_3=18+1+24+1+36=80$、$P_1=30+1+24+1+36+1+12=105$，所以平均$75$。

**例题** 各进程到达就绪队列的时间、需要的运行时间、进程优先数如下表所示。使用非抢占式与抢占式优先级调度算法，分析进程运行状态。（优先数越大，优先级越高）

进程|到达时间|运行时间|优先数
:--:|:-----:|:------:|:---:
P1|0|7|1
P2|2|4|2
P3|4|1|3
P4|5|4|2

解：

非抢占式：$0$时只有$P1$到达，所以$P1$开始处理。$2$时$P2$到达，$4$时$P3$到达，$5$时$P4$到达。$7$时$P1$运行完，因为$P3$优先级更高，所以运行$P3$。$8$时$P3$运行完，$P2$、$P4$优先级相同，但是由于$P2$先到，所以$P2$上处理机。$12$时$P2$运行完，$P4$上处理机。$16$时$P4$运行完。

抢占式：$0$时$P1$到达，$P1$上处理机。$2$时$P2$到达，且$P2$优先级$2$大于$P1$优先级$1$，所以$P2$上处理机，$P1$余下$7-2=5$。$4$时$P3$到达，且$P3$优先级$3$大于$P2$优先级$2$，所以$P3$上处理机，$P2$余下$4-2=2$。$4+1=5$时$P3$运行结束，且$P4$到达，插入就绪队列队尾，$P4$与$P2$优先数都是$2$，而$P2$进入队列时间更早，所以$P2$上处理机。$5+2=7$时$P2$运行结束，且$P4$优先级$4$大于$P1$优先级$1$，所以$P4$上处理机。$7+4=11$时$P4$运行结束，$P1$上处理机。$11+5=16$时$P1$运行结束。

#### 多级反馈队列

**例题** 各进程到达就绪队列的时间、需要的运行时间如下表所示。使用多级反馈队列调度算法，就绪队列使用时间片轮转调度算法，分析进程运行状态。

进程|到达时间|运行时间
:--:|:-----:|:------:
P1|0|7
P2|2|4
P3|4|1
P4|5|4

解：

设置多级就绪队列，各级队列优先级从高到低，时间片从小到大。

新进程到达时先进入第$1$级队列，按$FCFS$原则排队等待被分配时间片。

若用完时间片进程还未结束，则进程进入下一级队列队尾。如果此时已经在最下级的队列，则重新放回最下级队列队尾。

只有第$k$级队列为空时，才会为$k+1$级队头的进程分配时间片。

被抢占处理机的进程重新放回原队列队尾。

定义多级就绪队列如下（优先级与优先数成正比）：

队列序号|优先级|时间片大小
:-----:|:----:|:-------:
1|3|1
2|2|2
3|1|4

$0$时首先$P1$进入第一级队列，此时$P1$优先级为$3$，时间片为$1$，所以$P1$会运行$1$个时间片。

$1$时$P1$余下$6$，没有运行完，进入第二级队列的队尾继续运行一个时间片。

$2$时$P2$进入第一级队列，优先级更高，所以$P1$被剥夺处理机，此时$P1$还余下$5$，回退第二级队列，$P2$开始运行。

$3$时$P2$运行一个时间片后余下$3$，加入第二级队列队尾。此时第二级队列头部为$P1$，所以$P1$开始运行。

$4$时$P3$进入第一级队列，优先级更高，所以$P1$被剥夺处理机，此时$P1$还余下$4$，回退第二级队列，有$P2$、$P1$。

$5$时$P4$进入第一级队列，此时$P3$也正好运行完，处理机交给$P4$。

$6$时$P4$运行一个时间片后余下$3$，加入到第二级队列尾部。第二级队列此时顺序为$P2$（余$3$）、$P1$（余$4$）、$P4$（余$3$），所以$P2$开始运行。

$8$时$P2$运行一个时间片后余下$1$，加入到第三级队列中。$P1$开始占有处理机。

$10$时$P1$运行一个时间后余下$2$，加入到第三级队列中。$P4$开始占有处理机。

$12$时$P4$运行一个时间后余下$1$，加入到第三级队列中。第二级队列为空，开始运行第三级队列，$P2$开始占有处理机。

$13$时$P2$处理完，$P1$占有处理机。

$15$时$P1$处理完，$P4$占有处理机。

$16$时$P4$处理完，全部结束。

**例题** 系统采用二级反馈队列调度算法进行进程调度。就绪队列$Q_1$采用时间片轮转调度算法，时间片为$10ms$；就绪队列$Q_2$采用短进程优先调度算法；系统优先调度$Q_1$队列中的进程，当$Q_1$为空时系统才会调度$Q_2$中的进程；新创建的进程首先进入$Q_1$；$Q_1$中的进程执行一个时间片后，若未结束，则转入$Q_2$。若当前$Q_1$，$Q_2$为空，系统依次创建进程$P_1$，$P_2$后即开始进程调度，$P_1$，$P_2$需要的$CPU$时间分别为$30ms$和$20ms$,则进程$P_1$，$P_2$在系统中的平均等待时间为()。

$A.25ms$

$B.20ms$

$C.15ms$

$D.10ms$

解：$C$。$0ms$时刻$P1$开始运行。$10ms$时刻$P1$停止，余下$20ms$进入$Q2$，$P2$进入$Q1$运行。$20ms$时刻$P2$停止，余下$10ms$，进入$Q2$，而$Q1$空，开始运行$Q2$中的进程，而$P2$余下$10ms$小于$P1$余下的$20ms$，短进程优先，所以$P2$继续开始运行。$30ms$时刻$P2$完成，$P1$运行。$50ms$时刻$P1$运行完成。

所以综上$P1$等待$30-10=20ms$，而$P2$等待$10-0=10ms$。平均等待时间为$(20+10)\div2=15ms$。

#### 多道批处理系统

一般都是单道处理系统，所以作业调度和进程调度都是一样的。而对于多道批处理系统会采用不同的作业调度和进程调度算法。但是基本上运算方法一致。

作业调度是调度作业进内存，有多少道就有多少个内存作业位置，但是有位置不一定能运行，因为需要进行进程调度占用处理机（$CPU$）。

**例题** 有一个具有两道作业的批处理系统，作业调度采用短作业优先调度算法，进程调度采用抢占式优先级调度算法。作业的运行情况见下表，其中作业的优先数即进程的优先数，优先数越小，优先级越高。

作业名|到达时间|运行时间|优先数
:----:|:------:|:------:|:----:
1|8:00|40分钟|5
2|8:20|30分钟|3
3|8:30|50分钟|4
4|8:50|20分钟|6

1）列出所有作业进入内存的时间及结束的时间（以分为单位)。

2）计算平均周转时间。

解：

1）具有两道作业的批处理系统，内存只存放两道作业，它们采用抢占式优先级调度算法竞争$CPU$，而将作业调入内存采用的是短作业优先调度。$8:00$，作业$1$到来，此时内存和处理机空闲，作业$1$进入内存并占用处理机；$8:20$，作业$2$到来，内存仍有一个位置空闲，因此将作业$2$调入内存，又由于作业$2$的优先数高，相应的进程抢占处理机，在此期间$8:30$作业$3$到来，但内存此时已无空闲，因此等待。直至$8:50$，作业$2$执行完毕，此时作业$3$、$4$竞争空出的一道内存空间，作业$4$的运行时间短，因此先调入，但它的优先数低于作业$1$，因此作业$1$先执行。到$9:10$时，作业$1$执行完毕，再将作业$3$调入内存，且由于作业$3$的优先数高而占用$CPU$，作业$3$完成后$4$开始占用$CPU$处理。所有作业进入内存的时间及结束的时间见下表。

作业|到达时间|运行时间|优先数|进入内存时间|结束时间|周转时间
:--:|:------:|:------:|:----:|:---------:|----:|:----:
1|8:00|40min|5|8:00|9:10|70min
2|8:20|30min|3|8:20|8:50|30min
3|8:30|50min|4|9:10|10:00|90min
4|8:50|20min|6|8:50|10:20|90min

2）平均周转时间$为(70+30+90+90)\div4=70min$。

## 进程同步与互斥

### 进程同步与互斥的基本概念

#### 进程关系

**例题** 进程$A$和进程$B$通过共享缓冲区协作完成数据处理，进程$A$负责产生数据并放入缓冲区，进程$B$从缓冲区读数据并输出。进程$A$和进程$B$之间的制约关系是()。

$A.$互斥关系

$B.$同步关系

$C.$互斥和同步关系

$D.$无制约关系

解：$C$。并发进程因为共享资源而产生相互之间的制约关系，可以分为两类：①互斥关系，指进程之间因相互竞争使用独占型资源（互斥资源）所产生的制约关系；②同步关系，指进程之间为协同工作需要交换信息、相互等待而产生的制约关系。本题中两个进程之间的制约关系是同步关系，进程$B$必须在进程$A$将数据放入缓冲区后才能从缓冲区中读出数据。此外，共享的缓冲区一定是互斥访问的，所以它们也具有互斥关系。

#### 临界资源

**例题** 以下()属于临界资源。

$A.$磁盘存储介质

$B.$公用队列

$C.$私用数据

$D.$可重入的程序代码

解：$B$。临界资源与共享资源的区别在于，在一段时间内能否允许被多个进程访问（并发使用)，显然磁盘属于共享设备。在域环境中，公用队列是$Active\,Directory$中发布的队列，因此通过整个$Windows\,Server\,2003$家族林进行复制。公用队列可供多个进程使用，但一次只可供一个进程使用，试想若多个进程同时使用公用队列，势必造成队列中的数据混乱而无法使用。私用数据仅供一个进程使用，不存在临界区问题，可重入的程序代码一次可供多个进程使用。

### 信号量

#### PV操作

**例题** 下列关于$PV$操作的说法中，正确的是()。

Ⅰ.$PV$操作是一种系统调用命令
Ⅱ.$PV$操作是一种低级进程通信原语
Ⅲ.$PV$操作是由一个不可被中断的过程组成
Ⅳ.$PV$操作是由两个不可被中断的过程组成

$A.$Ⅰ、Ⅲ

$B.$Ⅱ、Ⅳ

$C.$Ⅰ、Ⅱ、Ⅳ

$D.$Ⅰ、Ⅳ

解：$B$。$PV$操作是一种低级的进程通信原语，不是系统调用，因此Ⅱ正确；$Р$操作和$V$操作都属于原子操作，所以$PV$操作由两个不可被中断的过程组成，因此Ⅳ正确。

#### 信号量含义

**例题** 设与某资源关联的信号量初值为$3$，当前值为$1$。若$M$表示该资源的可用个数，$N$表示等待该资源的进程数，则$M$，$N$分别是()。

$A.0,1$

$B.1,0$

$C.1,2$

$D.2,0$

解：$D$。信号量是一个特殊的整型变量，只有初始化和$PV$操作才能改变其值。通常，信号量分为互斥量和资源量，互斥量的初值一般为$1$，表示临界区只允许一个进程进入，从而实现互斥。当互斥量等于$0$时，表示临界区已有一个进程进入，临界区外尚无进程等待；当互斥量小于$0$时，表示临界区中有一个进程，互斥量的绝对值表示在临界区外等待进入的进程数。同理，资源信号量的初值可以是任意整数，表示可用的资源数，当资源量小于$0$时，表示所有资源已全部用完，而且还有进程正在等待使用该资源，等待的进程数就是资源量的绝对值。

**例题** 一个进程因在互斥信号量`mutex`上执行`V(mutex)`操作而导致唤醒另一个进程时，执行$V$操作后`mutex`的值为()。

$A.$大于$0$

$B.$小于$0$

$C.$大于等于$0$

$D.$小于等于$0$

解：$D$。由题意可知，$V$操作导致唤醒另一个进程，所以系统原来就存在等待进入临界区的进程，`mutex`小于等于$-1$，因此在执行`V(mutex)`操作后，`mutex`的值小于等于$0$。

#### 信号量初值

**例题** 用$PV$操作实现进程同步，信号量的初值为()。

$A.-1$

$B.0$

$C.1$

$D.$由用户确定

解：$D$。与互斥信号量初值一般为$1$时不同，用$PV$操作实现进程同步，信号量的初值应根据具体情况来确定。若期望的消息尚未产生，则对应的初值应为$0$，若期望的消息已存在，则信号量的初值应设为一个非$0$的正整数。（一般看之前的同步互斥应用一般设置为$0$是因为还没有产生消息）

**例题** 在$9$个生产者、$6$个消费者共享容量为$8$的缓冲器的生产者-消费者问题中，互斥使用缓冲器的信号量初始值为()。

$A.1$

$B.6$

$C.8$

$D.9$

解：$A$。所谓互斥使用某临界资源，是指在同一时间段只允许一个进程使用此资源，所以互斥信号量的初值都为$1$。

#### 信号量值范围

**例题** 有三个进程共享同一程序段，而每次只允许两个进程进入该程序段，若用$PV$操作同步机制，则信号量$S$的取值范围是()。

$A.2,1,0,-1$

$B.3,2,1,0$

$C.2,1,0,-1,-2$

$D.1,0,-1,-2$

解：$A$。因为每次允许两个进程进入该程序段，即资源（这里指可进入的空间）的最大容量为$2$，所以信号量最大值取$2$。至多有三个进程申请，则信号量最小为$-1$，即最多只存在一个进程在等待，所以信号量可以取$2,1,0,—1$。

### 进程同步与互斥应用

#### 进程互斥

**例题** 进程$P_1$和$P_2$均包含并发执行的线程，部分伪代码描述如下所示。

```cpp
// 进程P1
int x=0;
Thread1(){
    int a;
    a=1;
    x+=1;
}
Thread2(){
    int a;
    a=2;
    x+=2;
}

// 进程P2
int x=0;
Thread3(){
    int a;
    a=x;
    x+=3;
}
Thread4(){
    int b;
    b=x;
    x+=4;
}
```

下列选项中，需要互斥执行的操作是()。

$A.a=1$与$a=2$

$B.a=x$与$b=x$

$C.x+=1$与$x+=2$

$D.x+=1$与$x+=3$

解：$C$。只有对共享变量的赋值可能需要互斥操作。$P$中对$a$进行赋值，并不影响最终的结果，因此$a=1$与$a=2$不需要互斥执行，所以$A$不是。$a=x$与$b=x$执行先后不影响$a$与$b$的结果，无须互斥执行，$B$不是。在同一个进程中，$x+=1$与$x+=2$执行先后会影响$x$的结果，需要互斥执行，$C$需要。$P_1$中的x和$P_2$中的$x$虽然是共享变量，但是不同范围中的$x$，互不影响，不需要互斥执行，$D$不需要。所以其实$x+=3$和$x+=4$也要互斥运行。

### 管程

**例题** 以下关于管程的叙述中，错误的是()。

$A.$管程是进程同步工具，解决信号量机制大量同步操作分散的问题

$B.$管程每次只允许一个进程进入管程

$C.$管程中$signal$操作的作用和信号量机制中的$V$操作相同

$D.$管程是被进程调用的，管程是语法范围，无法创建和撤销

解：$C$。管程的$signal$操作与信号量机制中的$V$操作不同，信号量机制中的$V$操作一定会改变信号量的值$S=S+1$。而管程中的$signal$操作是针对某个条件变量的，若不存在因该条件而阻塞的进程，则$signal$不会产生任何影响。

**例题** 若$x$是管程内的条件变量，则当进程执行`x.wait()`时所做的工作是()。

$A.$实现对变量$x$的互斥访问

$B.$唤醒一个在$x$上阻塞的进程

$C.$根据$x$的值判断该进程是否进入阻塞态

$D.$阻塞该进程，并将之插入$x$的阻塞队列中

解：$D$。这是基本的概念，且由于进程已经执行`x.wait()`，证明判断条件为真应该阻塞，所以$C$不对。“条件变量”是管程内部说明和使用的一种特殊变量，其作用类似于信号量机制中的“信号量”，都用于实现进程同步。需要注意的是，在同一时刻，管程中只能有一个进程在执行。若进程$A$执行了`x.wait()`操作，则该进程会阻塞，并挂到条件变量`x`对应的阻塞队列上。这样，管程的使用权被释放，就可以有另一个进程进入管程。若进程$B$执行了`x.signal()`操作，则会唤醒`x`对应的阻塞队列的队首进程。在$Pascal$语言的管程中，规定只有一个进程要离开管程时才能调用`signal()`操作。

## 死锁

### 死锁的概念

**例题** 死锁的四个必要条件中，无法破坏的是()。

$A.$环路等待资源

$B.$互斥使用资源

$C.$占有且等待资源

$D.$非抢夺式分配

解：$B$。所谓破坏互斥使用资源，是指允许多个进程同时访问资源，但有些资源根本不能同时访问，如打印机只能互斥使用。因此，破坏互斥条件而预防死锁的方法不太可行，而且在有的场合应该保护这种互斥性。其他三个条件都可以实现。

**例题** 某个系统采用下列资源分配策略。若一-个进程提出资源请求得不到满足，而此时没有由于等待资源而被阻塞的进程，则自己就被阻塞。而当此时已有等待资源而被阻塞的进程，则检查所有由于等待资源而被阻塞的进程。若它们有申请进程所需要的资源，则将这些资源取出并分配给申请进程。这种分配策略会导致()。

$A.$死锁

$B.$颠簸

$C.$回退

$D.$饥饿

解：$D$。首先根据题目的资源分分配策略可以分析得到：如果只有一个进程等待资源就堵塞，如果有多个就争夺其他堵塞进程的资源。某个进程主动释放资源不会导致死锁，因为破坏了请求并保持条件，选项$A$错。颠簸也就是抖动，这是请求分页系统中页面调度不当而导致的现象，指内容反复调入调出内存，所以没有关系，$B$是错的。回退是指从此时此刻的状态退回到一分钟之前的状态，假如一分钟之前拥有资源$X$，它有可能释放了资源$X$，那就不称回到一分钟之前的状态，也就不是回退，选项$C$错。由于进程过于“慷慨”，不断把自己已得到的资源送给别人，导致自己长期无法完成，所以是饥饿，选项$D$对。

**例题** 若系统$S_1$采用死锁避免方法，$S_2$采用死锁检测方法。下列叙述中，正确的是()。

Ⅰ.$S_1$会限制用户申请资源的顺序，而$S_2$不会

Ⅱ.$S_1$需要进程运行所需的资源总量信息，而$S_2$不需要

Ⅲ.$S_1$不会给可能导致死锁的进程分配资源，而$S_2$会

$A.$仅Ⅰ、Ⅱ

$B.$仅Ⅱ、Ⅲ

$C.$仅Ⅰ、Ⅲ

$D.$Ⅰ、Ⅱ、Ⅲ

解：$B$。死锁预防采用破坏产生死锁的$4$个必要条件中的一个或几个来防止发生死锁。其中之一的“破坏循环等待条件”，一般采用顺序资源分配法，首先给系统的资源编号，规定每个进程必须按编号递增的顺序请求资源，即限制了用户申请资源的顺序，因此Ⅰ的前半句属于死锁预防的范畴。

银行家算法是最著名的死锁避免算法，其中的最大需求矩阵$Max$定义了每个进程对$m$类资源的最大需求量，系统在执行安全性算法中都会检查此次资源试分配后，系统是否处于安全状态,若不安全则将本次的试探分配作废。在死锁的检测和解除中，系统为进程分配资源时不采取任何措施，但提供死锁的检测和解除手段，因此Ⅱ、Ⅲ正确。

### 死锁进程数

**例题** 系统中有$3$个不同的临界资源$R_1$，$R_2$和$R_3$，被$4$个进程$P_1$，$P_2$，$P_3$，$P_4$共享。各进程对资源的需求为: $P_1$申请$R_1$和$R_2$，$P_2$申请$R_2$和$R_3$，$P_3$申请$R_1$和$R_3$，$P_4$申请$R_2$。若系统出现死锁，则处于死锁状态的进程数至少是()。

$A.1$

$B.2$

$C.3$

$D.4$

解：$C$。对于本题，先满足一个进程的资源需求，再看其他进程是否出现死锁状态。因为$P_4$只申请一个资源，当将$R_2$分配给$P_4$后，$P_4$执行完后将$R_2$释放，这时使得系统满足死锁的条件是$R_1$分配给$_1$，$R_2$分配给$P_2$，$R_3$分配给$P_4$，（或者$R_2$分配给$P_1$，$R_3$分配给$P_2$，$R_1$分配给$P_3$）。穷举其他情况，各种情况需要使得处于死锁状态的进程数至少为$3$。（即至多只能满足一个进程）

### 银行家算法

**例题** 系统中有$5$个进程$P_0$到$P_4$，$3$种资源$R_0$到$R_2$，初始数量为$(10,5,7)$，某一时刻的情况可表示如下:

进程|最大需求|已分配
:-:|:------:|:----:
P0|(7,5,3)|(0,1,0)
P1|(3,2,2)|(2,0,0)
P2|(9,0,2)|(3,0,2)
P3|(2,2,2)|(2,1,1)
P4|(4,3,3)|(0,0,2)

解：将已分配的部分全部加起来得到$(7,2,5)$，还剩余资源数$Available=(3,3,2)$。

将每个进程的最大需求减去已分配，会得到最多还需要的资源数量，三列分别为$Max$、$Allocation$、$Need$：

进程|最大需求|已分配|最多还需要
:-:|:------:|:----:|:-------:
P0|(7,5,3)|(0,1,0)|(7,4,3)
P1|(3,2,2)|(2,0,0)|(1,2,2)
P2|(9,0,2)|(3,0,2)|(6,0,0)
P3|(2,2,2)|(2,1,1)|(0,1,1)
P4|(4,3,3)|(0,0,2)|(4,3,1)

将剩余资源数$Work=(3,3,2)$与各个进程的最多还需要值$Need$对比，如果剩余资源数每个资源值都大于该进程的最多还需要的资源值，就代表这个进程可以分配资源。

对比得到$P_1$和$P_3$可以分配。

其中若先$P_1$分配完归还资源后可用资源为$(3,3,2)+(1,2,2)=(5,3,2)$，然后使用该可用资源序列进行下一轮的分配，直到五次循环检查后五个进程都加入了安全序列中$\{P_1,P_3,P_4,P_2,P_0\}$，就得到了一个最终的序列。该算法称为安全性算法。

**例题** 某系统有$R_1$，$R_2$和$R_3$共三种资源，在$T_0$时刻$P_1$，$P_2$，$P_3$，和$P_4$。这四个进程对资源的占用和需求情况见下表，此时系统的可用资源向量为$(2,1,2)$。试问：

1）用向量或矩阵表示系统中各种资源的总数和此刻各进程对各资源的需求数目。

2）若此时进程$P_1$和进程$P_2$均发出资源请求向量$Request(1,0,1)$，为了保证系统的安全性，应如何分配资源给这两个进程？说明所采用策略的原因。

3）若2）中两个请求立刻得到满足，系统此时是否处于死锁状态？

资源情况|最大资源需求量|||已分配资源数量|||
:------:|:-:|:-:|:-:|:-:|:-:|:--:
进程|R1|R2|R3|R1|R2|R3|
P1|3|2|2|1|0|0
P2|6|1|3|4|1|1
P3|3|1|4|2|1|1
P4|4|2|2|0|0|2

解：

1）资源总量为$(9,3,6)$，$Need=\left[\begin{array}{ccc}
    2 & 2 & 2 \\
    2 & 0 & 2 \\
    1 & 0 & 3 \\
    4 & 2 & 0
\end{array}\right]$。

2）若此时$P_1$发出资源请求$Request_1(1,0,1)$，则按银行家算法进行检查：

$Request_1(1,0,1)\leqslant Need_1(2,2,2)$，$Request_1(1,0,1)\leqslant Available(2,1,2)$，$Available(1,1,1)$。

资源情况|Allocation|||Need|||
:------:|:-:|:-:|:-:|:-:|:-:|:-:
P1|1|0|0|2|2|2
P2|4|1|1|2|0|2
P3|2|1|1|1|0|3
P4|0|0|2|4|2|0

再利用安全性算法检查系统是否安全，可用资源$Available(1,1,1)$已不能满足任何进程，系统进入不安全状态，此时系统不能将资源分配给进程$P_1$。

若此时进程$P_2$发出资源请求$Requestz(1,0,1)$，则按银行家算法进行检查：

$Requestz(1,0,1)\leqslant Needz(2,0,2)$，$Requestz(1,0,1)\leqslant Available(2,1,2)$，$Available(1,1,1)$。

试分配并修改相应数据结构，由此形成的进程$P_2$请求资源后的资源分配情况下表：

资源情况|Allocation|||Need|||
:------:|:-:|:-:|:-:|:-:|:-:|:-:
P1|1|0|0|2|2|2
P2|5|1|2|1|0|1
P3|2|1|1|1|0|3
P4|0|0|2|4|2|0

再利用安全性算法检查系统是否安全，可得到如下表中所示的安全性检测情况。$Work$指当前可用资源，注意表中各个进程对应的$Work+Allocation$向量表示在该进程释放资源之后更新的$Work$向量。

资源情况|Need|||Allocation|||Work|||Work|+|Allocation
:------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
P2|1|0|1|5|1|2|1|1|1|6|2|3
P3|1|0|3|2|1|1|6|2|3|8|3|4
P4|4|2|0|0|0|2|8|3|4|8|3|6
P1|2|2|2|1|0|0|8|3|6|9|3|6

从上表中可以看出，此时存在一个安全序列$\{P_2,P_3,P_4,P_1\}$，因此该状态是安全的，可以立即将进程$P_2$所申请的资源分配给它。

3）若2）中的两个请求立即得到满足，则此刻系统并未立即进入死锁状态，因为这时所有的进程未提出新的资源申请，全部进程均未因资源请求没有得到满足而进入阻塞态。只有当进程提出资源申请且全部进程都进入阻塞态时，系统才处于死锁状态。

### 进程与死锁

**例题** 下面是一个并发进程的程序代码，正确的是()。

```cpp
semaphore xl=x2=y=1;
int c1=c2=0;

P1(){
    while(1){
        P(x1);
        if(++c1==1) P(y);
        V(x1);
        computer(A);
        P(x1);
        if(--c1=0) V(y);
        V(x1);
    }
}

P2(){
    while(1){
        P(x2);
        if(++c2==1) P(y);
        V(x2);
        computer(B);
        P(x2);
        if(--c2=0) V(y);
        V(x2);
    }
}
```

$A.$进程不会死锁，也不会“饥饿”

$B.$进程不会死锁，但是会“饥饿”

$C.$进程会死锁，但是不会“饥饿”

$D.$进程会死锁，也会“饥饿”

解：$B$。首先$P1$分别对`x1`、`c1`、`y`操作，$P2$对`x2`、`c2`、`y`操作，其中只存在一个公用`y`，也没有不占有所以不存在抢夺变量的。而代码过程中存在$PV$操作，对$y$进行$P$不断的操作可能导致对方进程饥饿。如$P1$进程更快，$P2$进程稍慢，不断$P1$进入，$P2$被堵塞，而$c1$变成$2$不断被$P1$占用，所以导致饥饿。

**例题** 有两个并发进程，对于如下这段程序的运行，正确的说法是()。

```cpp
int x,y,z,t, u;
P1(){
    while(1){
        x=1;
        y=0;
        if x>=1 then y=y+1;
        z=y;
    }
}

P2(){
    while(1){
        x=0;
        t=0;
        if x<=1 then t=t+2;
        u=t;
    }
}
```

$A.$程序能正确运行，结果唯一

$B.$程序不能正确运行，可能有两种结果

$C.$程序不能正确运行，结果不确定

$D.$程序不能正确运行，可能会死锁

解：$C$。公用变量为$x$，所以可能会导致不同的结果，$A$错误。不存在资源占有等待其他资源，所以不会死锁，$D$错误。最重要的是结果到底有哪几种。通过不同顺序可以得到$(y,z,t,u,x)$为$(1,1,2,2,0)$、$(0,0,2,2,0)$、$(1,1,2,2,1)$三种。

### 资源分配图

**例题** 假定某计算机系统有$R_1$和$R_2$两类可使用资源（其中$R_1$有两个单位，$R_2$有一个单位），它们被进程$P_1$和$P_2$所共享，且已知两个进程均以下列顺序使用两类资源：申请$R_1$→申请$R_2$→申请$R_1$→释放$R_1$→释放$R_2$→释放$R_1$。试求出系统运行过程中可能到达的死锁点，并画出死锁点的资源分配图（或称进程资源图）。

解：在本题中，当两个进程都执行完第一步后，即进程$P_1$和进程$P_2$都申请到了一个$R_1$类资源时，系统进入不安全状态。随着两个进程向前推进，无论哪个进程执行完第二步，系统都将进入死锁状态。可能达到的死锁点是：一个进程占有$P_1$和$P_2$，另一个进程占有一个$P_1$，此时系统内已无空闲资源，而两个进程都在保持已占有资源不释放的条件下造成死锁。

假如$P1$占有了两个资源：

![资源图][resource]

[resource]:data:image/png;base64,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
