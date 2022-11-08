# 排序

## 基本概念

+ 排序：将一个数据元素的任意序列重新排列成一个按关键字有序的序列。
+ 内部排序：待排序的记录存放在计算机的内存中所进行的排序操作称为内部排序。
+ 外部排序：待排序的记录数量很大，以致内存一次不能容纳全部记录，在排序过程中需要访问外存的排序过程称为外部排序。
+ 稳定的排序：比如一个序列是“$1,4,3,3*,2$”，按从小到大排序后变成“$1,2,3,3*,4$”，就叫做稳定排序，即3和3*相对顺序不变。如果相同关键字的顺序发生了改变，则是不稳定的排序。稳定性的需要看具体的应用场景。
+ 内部排序的算法性能取决于算法的时间复杂度和空间复杂度，而时间复杂度一般是由比较和移动次数决定的。外部排序除此之外还要考虑磁盘读写速度和次数。
+ 大部分排序算法都仅适用于顺序存储的线性表。
+ 大部分排序需要经过比较和移动两个过程。（基数排序不需要比较）排序时至少需要比较$\lceil\log_2(n!)\rceil$次。每次比较两个关键字后，仅出现两种可能的转移。假设整个排序过程至少需要做$t$次比较。则显然会有$2^t$种情况。由于$n$个记录共有$n!$种不同的排列，因而必须有$n!$种不同的比较路径，于是有$2^t\geqslant n!$，所以得到不等式。

## 插入排序

### 插入排序共性

+ 插入排序的排序序列分为未排序序列和已排序序列。
+ 插入排序就是将选定的目标值插入到对应的位置，然后不断增长已排序序列并缩减未排序序列的过程。
+ 每一趟排序都不能保证有一个元素到达最终的位置上。

### 直接插入排序

#### 直接插入排序过程

每次将一个待排序的记录按其关键字大小插入到前面已排好序的子序列中，直到全部记录插入完成为止。

#### 直接插入排序性能

空间复杂度为$O(1)$。

时间复杂度主要来自对比关键字，移动元素，若有$n$个元素，则需要$n-1$趟处理。

最好情况是原本的序列就是有序的，需要$n-1$趟处理，每次只需要对比一次关键字，不用移动元素，时间复杂度为$O(n)$。

最坏情况是原本的序列是逆序的，需要$n-1$趟处理，第$i$趟处理需要对比关键字$i+1$次，移动元素$i+2$次，时间复杂度是$O(n^2)$。

所以平均时间复杂度是$O(n^2)$。

直接插入排序算法是稳定的。

如果使用链表实现直接插入排序，移动元素的次数变少了，但是关键字对比次数仍然时$O(n^2)$，从而整体时间复杂度依然是$O(n^2)$。

#### 直接插入排序特性

+ 在待排序的元素序列基本有序的前提下，直接插入排序效率最高的。
+ 直接插入排序进行$n$躺后能保证前$n+1$个元素是有序的，但是不能保证其都在最终的位置上。

### 二分插入排序

#### 二分插入排序过程

也称为折半插入排序，是对直接插入排序的优化，在寻找插入位置时使用二分查找的方式。

当$data[mid]==data[i]$时，为了保证算法的稳定性，会继续在$mid$所指位置右边寻找插入位置。

当$low>high$时停止折半查找，并将$[low,i-1]$内的元素全部右移，并把元素值赋值到$low$所指的位置。

折半插入排序是找到位置了后一起移动元素，而直接插入排序是边查找边排序。

#### 二分插入排序性能

空间复杂度为$O(1)$。

二分插入排序是稳定的。

比起直接插入排序，比较关键字的次数减少为$O(n\log_2n)$，移动元素的次数没变，所以总体时间复杂度为$O(n^2)$。

#### 二分插入排序特性

+ 对于直接插入的优化仅在于二分查找的比较次数。
+ 二分插入排序进行$n$躺后能保证前$n+1$个元素是有序的，但是不能保证其都在最终的位置上。

### 希尔排序

又称缩小增量排序。

#### 希尔排序过程

希尔排序也是对直接插入排序的优化。直接插入排序对于基本有序的序列排序效果较好，所以就希望序列能尽可能基本有序。从而希尔排序的思想就是先追求表中元素部分有序，然后逐渐逼近全局有序。

先将整个待排序元素序列分割成若干个子序列（由相隔某个“增量”的元素组成的），分别进行**直接插入排序**，然后缩小增量重复上述过程，直到增量为$1$。每次对比只对比两个以上的个元素进行插入交换。

增量序列的选择建议是第一趟选择元素个数的一半，后面不断缩小到原来的一半。

#### 希尔排序性能

空间复杂度为$O(1)$。

而时间复杂度和增量序列的选择有关，目前无法使用属性手段证明确切的时间复杂度。最坏时间复杂度为$O(n^2)$，在某个范围内可以达到$O(n^{1.3})$。

希尔排序是不稳定的。（因为相同的元素可能分到不同的子序列中进行重排打乱原有顺序）

希尔排序只适用于顺序表而不适合用于链表，无法快速进行增量的访问。

#### 希尔排序特性

+ 希尔排序在最后一趟前都不能保证元素在最后的位置上。
+ 希尔排序在最后一趟前都不能保证元素是有序的。

## 交换排序

### 交换排序共性

+ 交换排序即根据序列中两个元素关键的比较结构然后交换这两个记录在序列中的位置。
+ $n$趟排序后就有$n$个元素到达最终的位置上。

### 冒泡排序

重点就是相邻两两比较。

#### 冒泡排序过程

从后往前或从前往后两两比较相邻元素的值，若逆序则交换这两个值，如果相等也不交换，直到序列比较完。这个过程是一趟冒泡排序，第$i$趟后第$i$个元素会已经排序完成。每一趟都会让关键字最小或最大的一个元素到未排序队列的第一个或最后一个。一共需要$n-1$趟排序。

冒泡排序中所产生的有序子序列一定是全局有序的（不同于直接插入排序），也就是说，有序子序列中的所有元素的关键字一定小于或大于无序子序列中所有元素的关键字，这样每趟排序都会将一个元素放置到其最终的位置上。

#### 冒泡排序性能

空间复杂度为$O(1)$。

最好情况下即本身序列有序，则比较次数是$n-1$，交换次数是$0$，从而时间复杂度是$O(n)$。

最坏情况是逆序情况，比较次数和交换次数都是$\dfrac{n(n-1)}{2}$，所以时间复杂度是$O(n^2)$。

从而平均时间复杂度是$O(n^2)$。

冒泡排序是稳定的。

冒泡排序可以用于链表。

#### 冒泡优化

对于每行冒泡进行优化：如果发现排序前几轮就已经实现了排序成功，那么后面的排序岂不是都浪费了时间进行比较？可以在第一轮循环中设置一个布尔值为$false$，如果在这一轮发生排序交换就设置为$true$，如果一轮结束后发现这个值还是$false$，说明这一轮没有进行交换，表示已经排序成功，就直接所有退出循环。

对于每列冒泡进行优化：默认每一轮冒泡是从$[length-i]$结束，如一共$5$个元素排序，需要$4$轮排序，第二轮冒泡排序应该从$0$开始，到$3$结束，因为最后一个元素4已经在第一轮排序成功。但是如果在第二轮发现$2$，$3$已经排序成功了不需要交换，那么默认排序方法第三轮还是要从$0$到$2$进行排序，还要比较一次$1$和$2$位置的数据，这就造成了浪费，那么如何解决？记录每一轮发生比较的元素的最大索引值，下一轮比较到这个索引值直接结束，不需要继续比较后面的元素。如果最大索引值为$0$则直接退出。这就进一步优化了上面一种策略。

```c
void Bubble(int[] a) {
   int n = a.length - 1;
   while (true) 
   {
      //表示最后一次交换元素位置
      int last = 0;
      for (int i = 0; i < n; i++) 
      {
         if (a[i] > a[i + 1]) {
            swap(a, i, i + 1);
            last = i;
         }
      }
      n = last;
      if (n == 0) 
      {
         return;
      }
   }
}
```

#### 冒泡排序特性

+ 冒泡排序产生的序列全局有序，$n$趟排序后第$n$个元素到达最终的位置上，前$n$个或后$n$个位置的元素确定。

### 快速排序

排序过程类似于构建二叉排序树。基于分治法。

#### 快速排序过程

取待排序序列中的某个元素$pivot$作为基准（一般取第一个元素），通过一趟排序，将待排元素分为左右两个子序列，左子序列元素的关键字均小于或等于基准元素的关键字，右子序列的关键字则大于基准元素的关键字，称进行了一趟快速排序（一次划分），这个$pivot$已经成功排序。然后分别对两个子序列继续进行快速排序，直至整个序列有序。

#### 单边循环快排

即$lomuto$洛穆托分区方案。

1. 选择最右边的元素值做标杆，把标杆值放入$pivot$变量中。
2. 初始时，令$low$和$high$都指向最左边的元素。其中$low$用于被动向右移动，维护小于标杆值的元素的边界，即每次交换的目标索引，一旦交换$low$就向右移动一个；$high$用于主动向右移动，寻找比标杆值小的元素，一旦找到就与$low$指向元素进行交换。
3. 然后$high$开始移动，判断$high$指向的元素值是否小于$pivot$值，如果不小于就继续向右移动。
4. 当遇到比标杆小的值，$high$指向的值就和$low$指向的值进行交换，如果$high$和$low$指向的值为同一个则不进行交换，然后$low$右移一个，$high$继续右移查找。
5. $high$继续移动，最后$high>=pivot$时将基准点元素值与$low$指向值进行交换，该轮排序结束。此时$low$指向的位置就是$pivot$值所应该在的位置。
6. 返回基准点元素所在索引，从而确定排序上下边界，递归继续执行排序。

#### 双边循环快排

分为普通分区方案和$hoare$霍尔分区方案。逻辑基本上一样，只是边界选择方式不同。

1. 先选择个值做标杆，一般为最左边值，把标杆值放入$pivot$变量中。
2. 初始时，令$high$指向序列最右边的值，$low$指向序列最左边的值。
3. 然后从$high$开始不断左移，当遇到比标杆大或等于的值时$high--$。
4. 如果发现比标杆小的值，即$high<pivot$，需要交换，然后$high$不动，$low++$开始移动去找要交换的大于标杆的值。
5. 若$low$所指向的值比标杆小或等于，则$low++$进行寻找。（为什么要加上一个等于标杆值可以继续向右移动的条件？因为标杆值默认是第一个值，即初始化$pivot$跟$low$指向同一个值，如果只能小于标杆值才能继续移动不交换，则在第一个元素时，由于标杆值被初始化赋值为第一个值，则标杆$pivot$值等于$low$值，从而导致$low$值跟$high$值进行交换，导致$pivot$标杆值被交换走了，标杆值变为了最开始最右边的$high$值，导致了排序有问题）
6. 若$low$所指向的值比标杆大，则$low$值与$high$值进行交换。
7. 交换后$low$不动，$high--$开始移动。回到步骤三开始执行。
8. 当$low=high$时表示$low$和$high$之前的元素都比基准小，$low$和$high$之后的元素都比基准大，完成了一次划分。然后把基准元素放入$low==high$指向的位置。
9. 不断交替使用$low$和$high$指针进行对比。对左右子序列进行同样的递归操作即可，从步骤三开始。若左右两个子序列的元素数量小等于一，则无需再划分。

即对序列进行比较，有头尾两个指针，尾指针开始比较向前移动，若指向值比对比值小则要交换，交替让头指针开始移动，否则不改变指针则尾指针继续向前；同理头指针向后移动，若指向值比对比值大则交换，交替让尾指针移动，否则不改变指针则头指针继续向后。最后头尾指针指向一个位置，将对比值插入到当前值，此时一趟完成。

[洛穆托分区与霍尔分区比较](https://qastack.cn/cs/11458/quicksort-partitioning-hoare-vs-lomuto
)。

#### 快速排序性能

由于快速排序使用了递归，所以需要递归工作栈，空间复杂度与递归层数相关，所以为$O($递归层数$)$。

每一层划分只需要处理剩余的待排序元素，时间复杂度不超过$O(n)$，所以时间复杂度为$O(n\times$归层数$)$。

而快速排序会将所有元素组织成为二叉树，二叉树的层数就是递归调用的层数。所以对于$n$个结点的二叉树，最小高度为$\lfloor\log_2n\rfloor+1$，最大高度为$n$。

从而最好时间复杂度为$O(n\log_2n)$，最坏时间复杂度为$O(n^2)$，平均时间复杂度为$O(n\log_2n)$；最好空间复杂度为$O(\log_2n)$，最坏空间复杂度为$O(n)$，平均空间复杂度为$O(\log_2n)$。

所以如果初始序列是有序的或逆序的，则快速排序性能最差（速度最慢）。若每一次选中的基准能均匀划分，尽量让数轴元素平分，则效率最高（速度最快）。性能与分区处理顺序无关。

所以对于快速排序性能优化是选择尽可能能中分的基准元素，入选头中尾三个位置的元素，选择中间值作为基准元素，或随机选择一个元素作为基准元素。

最好使用顺序存储，这样找到数轴元素与遍历时比较简单。

快速排序算法是不稳定的。

#### 快速排序特性

+ 快速排序不产生有序子序列。
+ 枢轴元素到达的位置是不确定的，但是每次都会到其最终的位置上。第$n$趟有$n$个元素到最终位置上。
+ 求快速排序趟数就是找到符合这种性质的元素个数。
+ 快速排序在内部排序中的表现最好。
+ 对于基本有序或倒序的序列，快速排序速度最慢。
+ 对于每次的数轴元素能尽量将表分为长度相同的子表，快速排序速度最快。
+ 排序的递归次数与初始序列和选择的枢轴变量有关，与分区处理顺序无关。

## 选择排序

### 选择排序特性

+ 分为已排序和未排序序列。选择排序就是每一趟在待排序元素中选取关键字最小或最大的元素加入有序子序列。
+ 选择排序算法的比较次数始终为$n(n-1)/2$，与序列状态无关。

选择排序与其他排序的区别：

+ 选择排序也需要交换，但是与交换排序的不断交换不同的是选择排序时选择出一个最后进行交换，一趟只交换一次。
+ 选择排序也需要插入，且也分为已排序和未排序序列，但是插入排序不需要选择，且元素移动方式是插入而不是交换。

### 简单选择排序

#### 简单选择排序过程

即每一趟在待排序元素中选取关键字最小的元素加入有序序列。交换发生在选出最值后，在每趟的尾部。经过$n-1$趟就可以完成。

#### 简单选择排序性能

空间复杂度为$O(1)$。

时间复杂度为$O(n^2)$。

简单选择排序是不稳定的。因为选择后会进行交换，影响顺序。

简单选择排序也可以适用于链表。

#### 直接插入排序与简单选择排序

插入排序和选择排序都是分为未排序和已排序两个部分，那么其中有什么区别？

如$18$、$23$、$19$、$9$、$23*$、$15$进行排序。

18 23 19 9 23* 15

插入排序：

```txt
18 23 19 9 23* 15
18 19 23 9 23* 15
9 18 19 23 23* 15
9 18 19 23 23* 15
9 15 18 19 23 23*
```

选择排序：

```txt
9 23 19 18 23* 15
9 15 19 18 23* 23
9 15 18 19 23* 23
9 15 18 19 23* 23
9 15 18 19 23* 23
9 15 18 19 23* 23
```

### 堆排序

#### 堆的定义

若$n$个关键字序列$L$满足下面某一条性质，则就是堆：

1. 若满足$L(i)\geqslant L(2i)$且$L(i)\geqslant L(2i+1)\,(1\leqslant i\leqslant\dfrac{n}{2})$则是大根堆或大顶堆。
2. 若满足$L(i)\leqslant L(2i)$且$L(i)\leqslant L(2i+1)\,(1\leqslant i\leqslant\dfrac{n}{2})$则是小根堆或小顶堆。

所以堆就是用顺序存储的完全二叉树。

堆的叶子结点范围是$\lfloor\log_2n\rfloor+1\sim n$。

#### 堆的建立

其实堆就是层序存储的完全二叉树。其中：

+ $i\leqslant\lfloor\dfrac{n}{2}\rfloor$的结点都是非终端结点。
+ $i$的左孩子是$2i$。
+ $i$的右孩子是$2i+1$。
+ $i$的父结点是$\lfloor\dfrac{n}{2}\rfloor$。

所以建立根堆过程是：

1. 按照关键字序列依次添加关键字到二叉树，按照层次遍历顺序添加。
2. 初始化成功后再从下往上、从左至右按逆层次遍历顺序不断调整位置。
3. 如果是大根堆则大元素往上，且当前结点与更大的孩子结点互换；如果是小根堆则小元素往上，且当前结点与更小的孩子结点互换。
4. 递归往上时父子结点不断交换位置。
5. 如果元素互换破坏了调整好的下一级的堆，则使用同样的方法对下一层递归调整。

如用堆排序对$(15,9,7,8,20,-1,7,4)$建立小根堆堆。首先将这组数据按层序初始化为无序堆，然后从最后向前开始调整：

![建立堆][heapbuild]

<!-- 1. 从$t<\lfloor\dfrac{n}{2}\rfloor$的结点开始往前遍历。
2. 检查当前结点$i$与左孩子和右孩子是否满足根堆条件，若不满足则交换。
   + 若是建立大根堆，检查是否满足根大于等于左、右结点，若不满足，则当前结点与更大的一个孩子互换。
   + 若是建立小根堆，检查是否满足根小于等于左、右结点，若不满足，则当前结点与更小的一个孩子互换。
3. 若元素互换破坏了下一级的堆，则采用同样的方法继续向下调整。
   + 若是建立大根堆，则小的元素不断下坠。
   + 若是建立小根堆，则大的元素不断下坠。 -->

<!-- 调整堆的时间与树高相关$O(\log_2n)$，建立堆的时间复杂度为$O(n)$。比较总次数不超过$4n$。 -->

#### 堆排序过程

由于选择排序是在每一趟都选择最大或最小的值进行排序，所以堆排序中就通过堆这个存储结构来完成对最值的选取——直接选择堆顶元素。

堆排序即每次将堆顶元素与堆底元素（堆最底层最右元素）进行交换，表示这个部分已经排序完成了不需要进行调整，第$i$趟表示倒数$i$个元素已经有序，所以无序的元素就是堆前面的元素。

1. 每一趟将堆顶元素加入子序列（堆顶元素与待排序序列中的最后一个元素交换）。此时后面的这个元素就排序好了。最右下的元素作为堆顶元素。
2. 此时待排序序列已经不是堆了（堆顶不能保证是最小或最大的元素），需要将其再次调整为堆（小元素或大元素不断下坠）。
3. 重复步骤一二。
4. 直到$n-1$趟处理后得到有序序列。基于大根堆的堆排序会得到递增序列，而基于小根堆的堆排序会得到递减序列。

调整堆从右边即序列末尾开始。

<span style="color:orange">注意：</span>题目如果说是给出序列，然后调整为堆，则证明他这个堆已经建立好了，只需要调整顺序，如果说的是依次插入，则要一边插入一边调整堆。

#### 堆排序性能

堆排序的存储就是它本身，不需要额外的存储空间，要么只需要一个用于交换或临时存放元素的辅助空间。所以空间复杂度为$O(1)$。

若树高为$h$，某结点在第$i$层，则将这个结点向下调整最多只需要下坠$h-i$层，关键字对比次数不超过$2(h-i)$次。

第$i$层最多$2^{i-1}$个结点，而只有第$1\cdots(h-1)$层的结点才可能需要下坠调整。所以调整时关键字对比次数不超过$\sum_{i=h-1}^12^{i-1}2(h-i)=\sum_{j=1}^{h-1}2^{h-j}j\leqslant2n\sum_{j=1}^{h-1}\dfrac{j}{2^j}\leqslant4n$。

所以建堆过程中，关键字对比次数不超过$4n$，建堆的时间复杂度为$O(n)$。

堆排序中处理时根结点最多下坠$h-1$层，而每下坠一层，最多对比关键字两次，所以每一趟排序的时间复杂度不超过$O(h)=O(\log_2n)$，一共$n-1$趟，所以时间复杂度为$O(n\log_2n)$。所以总的时间复杂度也是$O(n\log_2n)$。

堆排序是不稳定的。

堆排序适合关键字较多的情况。创如，在$1$亿个数中选出前$100$个最大值，首先使用一个大小为$100$的数组，读入前$100$个数，建立小顶堆，而后依次读入余下的教，若小于堆顶则舍弃，否则用该数取代堆顶并重新调整堆，待数据读取完毕，堆中$100$个数即为所求。

#### 堆的插入

新元素放到表尾（即最右下角元素），并与其$\lfloor\dfrac{i}{2}\rfloor$的父结点进行对比，若新元素比父元素更大（大根堆）或更小（小根堆），则二者互换，并保持上升，直到无法上升为止。时间复杂度为树高$O(\log_2n)$。

#### 堆的删除

被删除的元素用堆底元素（即最右下角元素）代替，然后让这个元素不断下坠，直到无法下坠为止。时间复杂度为树高$O(\log_2n)$。

#### 堆排序特性

+ 适合大量数据进行排序。
+ 在含有$n$个关键字的小根堆中，关键字最大的记录存储范围为$\lfloor\dfrac{n}{2}\rfloor+1\sim n$。这是小根堆，关键字最大的记录一定存储在这个堆所对应的完全二叉树的叶子结点中；又因为二叉树中的最后一个非叶子结点存储在$\lfloor\dfrac{n}{2}\rfloor$中，所以得到范围。

## 归并排序

归并是指把两个（二路归并）或多个（多路归并）已经有序的序列合并为一个。

该算法是采用分治法的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。

在较大数据进行排序时为了加快速度使用归并排序，用空间换时间。

### 二路归并排序

二路归并排序比较常用，且基本上用于内部排序，多路排序多用于外部排序。

#### 二路归并排序过程

1. 把长度为$n$的输入序列分成两个长度为$\dfrac{n}{2}$的子序列。
2. 对这两个子序列分别采用归并排序。
3. 将两个排序好的子序列合并成一个最终的排序序列。

归并排序趟数为$\lceil\log_2n\rceil$。

#### 二路归并排序性能

二路归并排序是一棵倒立的二叉树。

空间复杂度主要来自辅助数组，所以为$O(n)$，而递归调用的调用栈的空间复杂度为$O(\log_2n)$，总的空间复杂度就是为$O(n)$，无论平均还是最坏，所以这个算法在内部排序算法中空间消耗最大。

$n$个元素二路归并排序，归并一共要$\log_2n$趟，每次归并时间复杂度为$O(n)$，则算法时间复杂度为$O(n\log_2n)$

归并排序是稳定的。

## 分配排序

分配排序过程无须比较关键字，而是通过用额外的空间来“分配”和“收集”来实现排序，它们的时间复杂度可达到线性阶$O(n)$。简言之就是：用空间换时间，所以性能与基于比较的排序才有数量级的提高。

### 基数排序

基数排序不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

+ 只能对整数进行排序。
+ 元素的移动次数与关键字的初始排列次序无关。

#### 基数的定义

假设长度为$n$的线性表中每个结点$a_j$的关键字由$d$元组$(k_j^{d-1},k_j^{d-2},\cdots,k_j^1,k_j^0)$组成，其中$0\geqslant k_j^i\geqslant r-1\,(0\geqslant i\geqslant d-1)$，其中$r$就是基数。

#### 基数排序过程

有最高位优先$MSD$和最低位优先$LSD$两种方法。

若是要得到递减序列：

1. 初始化：设置$r$个空辅助队列$Q_{r-1},Q_{r-2},\cdots,Q_0$。
2. 按照每个关键字位**权重递增**的次序（个、十、百），对$d$个关键字位分别做分配和收集。
3. 分配就是顺序扫描各个元素，若当前处理的关键字位为$x$，就将元素插入$Q_x$队尾。
4. 收集就是把$Q_{r-1},Q_{r-2},\cdots,Q_0$各个队列的结点依次出队并链接在一起。

#### 基数排序性能

基数排序基本上使用链式存储而不是一般的顺序存储。

需要$r$个辅助队列，所以空间复杂度为$O(r)$。

一趟分配$O(n)$，一趟收集$O(r)$，一共有$d$趟分配收集，所以总的时间复杂度为$O(d(n+r))$。与序列初始状态无关。

基数排序是稳定的。

#### 基数排序的应用

对于一般的整数排序是可以按位排序的，也可以处理一些实际问题，如根据人的年龄排序，需要从年月日三个维度分别设置年份的队列、月份的队列（$1$到$12$）、日的队列（$1$到$31$）。

所以基数排序擅长解决的问题：

1. 数据元素的关键字可以方便地拆分为$d$组，且$d$较小。
2. 每组关键字的取值范围不大，即$r$较小。
3. 数据元素个数$n$较大。

### 计数排序

作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

#### 计数排序过程

1. 找出待排序的数组中最大和最小的元素。
2. 统计数组中每个值为i的元素出现的次数，存入数组C的第i项。
3. 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）。
4. 反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1。

当输入的元素是$n$个属于$[0,k]$的整数时，时间复杂度是$O(n+k)$，空间复杂度也是$O(n+k)$，其排序速度快于任何比较排序算法。

当$k$不是很大并且序列比较集中时，计数排序是一个很有效的排序算法。

计数排序是稳定的。

### 桶排序

桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。桶排序的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

#### 桶排序过程

1. 设置一个定量的数组当作空桶。
2. 遍历输入数据，并且把数据一个一个放到对应的桶里去。
3. 对每个不是空的桶进行排序。
4. 从不是空的桶里把排好序的数据拼接起来。

#### 桶排序性能

桶排序最好情况下使用线性时间$O(n)$，桶排序的时间复杂度，取决与对各个桶之间数据进行排序的时间复杂度，因为其它部分的时间复杂度都为$O(n)$。桶排序的平均时间复杂度为线性的$O(n+C)$，其中$C=n\times(\log n-\log m)$，其中$m$代表桶划分的数量。

很显然，桶划分的越小，各个桶之间的数据越少，排序所用的时间也会越少。但相应的空间消耗就会增大。

桶排序是稳定的。

## 内部排序

指在排序期间元素全部存放在内存中的排序。除了分配排序，其他的内部排序往往要经过比较和移动。

算法种类|最好时间复杂度|平均时间复杂度|最好时间复杂度|空间复杂度|是否稳定|趟数
:------:|:------------:|:------------:|:------------:|:--------:|:------:|:--:
直接插入排序|$O(n)$|$O(n^2)$|$O(n^2)$|$O(1)$|是|$n-1$
希尔排序|$?$|$?$|$?$|$O(1)$|否|$s$
简单选择排序|$O(n^2)$|$O(n^2)$|$O(n^2)$|$O(1)$|否|$n-1$
快速排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n^2)$|$O(\log_2n)$|否|初始序列
冒泡排序|$O(n)$|$O(n^2)$|$O(n^2)$|$O(1)$|是|初始序列
堆排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n\log_2n)$|$O(1)$|否|初始序列
二路归并排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n\log_2n)$|$O(n)$|是|$\log_2n$
基数排序|$O(d(n+r))$|$O(d(n+r))$|$O(d(n+r))$|$O(r)$|是|$r$

+ 每趟排序结束都至少能够确定一个元素最终位置的方法：选择、交换。（插入和归并则不行）

## 外部排序

指在排序期间元素无法全部同时存放在内存中，必须在排序过程中根据要求不断地在内、外存之间移动的排序。

### 外部排序的原理

#### 外部排序过程

磁盘的读写是以块为单位，数据读入内存后才能被修改，修改完成后还需要写回磁盘。

外部排序就是针对数据元素太多，无法一次性全部读入内存进行排序而进行处理的在外部磁盘进行的排序处理方式。

使用归并排序的方式，最少只用在内存分配三块大小的缓冲区（两个输入缓冲一个输出缓冲）即可堆任意一个大文件进行排序。然后对缓冲区里的数据进行内部排序。

外部排序过程：

1. 生成初始归并段（大小为输入缓冲区的总大小），需要读写并进行内部排序。
2. 重复读写，进行内部归并排序。填满输出缓冲就可以输出。输入缓冲空就可以输入新数据。

外部排序时间开销=读写外存时间（最大的时间开销）+内部排序所需时间+内部归并所需时间。

#### 外部排序的优化方法

优化方法就是使用更多路的多路归并，减少归并趟数。

$k$路平衡归并：最多只能有$k$个段归并为一个，需要一个输出缓冲区和$k$个输入缓冲区；每一趟归并中，若有$m$个归并段参与归并，则经过这一趟处理得到$\lceil\dfrac{m}{k}\rceil$个新的归并段。

对$r$个初始归并段，使用$k$路归并，则归并树可以使用$k$叉树表示，若树高为$h$，则归并趟数最小为$h=\lceil\log_kr\rceil+1$。

但是多路归并会带来负面影响：

1. $k$路归并时，需要开辟$k$个输入缓冲区，内存开销增加。
2. 每挑选一个关键字需要对比关键字$(k-1)$次，内部归并时间增加。

同时，若能增加初始归并段的长度$k$，也可以减少初始归并段数量$r$从而进行优化。

### 败者树

用于通过过去归并的经历减少归并次数。败者树可以看作一棵多了一个单个的根的完全二叉树。$k$个叶结点分别是当前参加比较的元素，非叶子结点用来记忆左右子树中的失败者，而让胜者往上继续比较，一直到根结点。

如要用败者树排序$27,12,1,17,2,9,11,4$，格式：元素值$($归并段索引值$)$：

```terminal
                   1(3)
                    |
                   2(5)
                    |
         ----------------------
         |                    |
        12(2)                4(8)
         |                    |
    ------------         ------------
    |          |         |          |
  27(1)      17(4)      9(6)      11(7)
    |          |         |          |
 ------     ------     ------     ------
 |    |     |    |     |    |     |    |
27    12    1    17    2    9    11    4
```

传统方法从$k$个归并段选出一个最大或最小元素需要对比关键字$k-1$次，而使用$k$路归并的败者树只需要对比关键字$\lceil\log_2k\rceil$次（败者树层数，不包括成功结点）。

构建败者树还是需要$n-1$次对比。

### 置换选择排序

如果内存工作区只能容纳$l$个记录，则初始归并段也只能包含$l$条记录，若文件共有$n$条记录，则初始归并段的数量为$r=\lceil n/l\rceil$。

用于构建更长的初始归并段，从而减少归并次数。

假设初始始待排文件为$FI$，初始归并段输出文件为$FO$，内存工作区为$WA$，$FO$和$WA$的初始状态为空，$WA$可容纳$w$个记录。置换选择算法的步骤如下：

1. 从$FI$输入$w$记录到工作区$WA$。
2. 从$WA$中选出其中关键字取最小值的记录，记为$MINIMAX$记录。
3. 将$MINIMAX$记录输出到$FO$中去。
4. 若$FI$不空，则从$FI$输入下一个记录到$WA$中。
5. 从$WA$中所有关键字比$MINIMAX$记录的关键字大的记录中选出最小关键字记录，作为新的$MINIMAX$记录。
6. 重复步骤三到五，如果新输入到$FI$的关键字小于$MINIMAX$的值，则驻留在$WA$中，直至在$WA$中填满选不出新的$MINIMAX$记录为止，由此得到一个初始归并段，输出一个归并段的结束标志到$FO$中去。准备输出新的归并段。
7. 重复步骤二到六，直至$WA$为空。由此得到全部初始归并段。

此时输出的初始归并段可以超过$WA$，且初始归并段长度是不一定相等的。

如$FI$：$4,6,9,7,13,11,14,22,30,2,3,19,20,17,1,23,5,36,12,18,21,39$，$WA$长度为$3$，$FO$为$4,6,7,9,11,13,14,16,22,30$、$2,3,10,17,19,20,23,36$、$1,5,12,18,21,39$。

^表示中断当前归并段，下一个$FI$开启新的归并段；√表示该$WA$值超过$MINIMAX$值，不能输出到当前$FO$归并段中，只能等待输出到下一个归并段。

FI|4|6|9|7|13|11|14|22|30|2|3|19||20
:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:
WA1|4|4|4|7|7|11|11|22|22|22|3√|3√|3|3
WA2||6|6|6|13|13|13|13|30|30|30|19√|19|19
WA3|||9|9|9|9|14|14|14|2√|2√|2√|2|20
MINIMAX|||4|6|7|9|11|13|14|22|30|30|2|3
FO|||4|6|7|9|11|13|14|22|30|^|2|3

FI|17|1|23|5|36|12||18|21|39||||
:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:
WA1|17|1√|1√|1√|1√|1√|1|18|18|18
WA2|19|19|23|23|36|12√|12|12|12|39|39|39
WA3|20|20|20|5√|5√|5√|5|5|21|21|21
MINIMAX|17|19|20|23|36|36|1|5|12|18|21|39
FO|17|19|20|23|36|^|1|5|12|18|21|39|^

### 最佳归并树

因为现实中的每个归并段的长度不同，所以归并的次序比较重要。

#### 最佳归并树的衡量

每个初始归并段可以看作一个叶子结点，归并树的长度作为结点权值，则归并树的带权路径长度$WPL$等于读写磁盘的次数。从而归并过程中的磁盘$I/O$次数=归并树的$WPL\times2$。

#### 最佳归并树的构造

所以就需要一棵类似哈夫曼树来成为最佳的归并树，不断选择最小的$k$段进行归并。

#### 添加虚段

对于$k$叉归并来说，若初始归并段的数量无法构成严格的$k$叉归并树，则需要补充几个长度为$0$的虚拟段从而能保证严格$k$叉归并，再进行$k$叉哈夫曼树的构造。

那么添加多少虚段呢？

$k$叉的最佳归并树一定是一棵严格的$k$叉树，即树中只包含度为$k$和$0$的结点。

设度为$k$的结点有$n_k$个，度为$0$的结点有$n_0$个，归并树的总结点树为$n$，则初始归并段数量+虚段数量=$n_0$。

所以$n=n_0+n_k$，$kn_k=n-1$，所以$n_0=(k-1)n_k+1$，所以$n_k=\dfrac{(n_0-1)}{(k-1)}$一定是可以整除的。如果不整除就要添加虚段。

[heapbuild]:data:image/png;base64,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EM+NNCKMGjiHjdZVF1I2GGF42XjU5ciq/yQ3suotKPkHhACmEs4k98hhl2MWlbGiRkdHGcpqP4hloaFjREAEohGI5kaaRlSHdcfwmPHWO0TfbGyswc32o7WpKhKB1Ah8OrJAlvlgYSfGGotFWYDKJLHYVVOAP7KQqk4EREAE2hLA9OHFPkncSEYwcyZJnbChjFMwiRYvXswbNvlwpLzHthj1pQiIQM0IkFZGzj8v/EnGRl4oeOfOHT6aphywZMkS3s8Poisb09DsAP0VARGoHIHYbmQjIIYS+9iU9tB4jN6LgAiIQIIEcBd5JSiYRBIBERCBEgngH/IiBaNEGVS1CIhAHAJBHvgRR3TVIgIiIAIiIAIiIAIiIAIikD4BNutyH5D05ZSE2QnIjczOSkeKgAiIgAiIgAiIgAiIgAiIgAgMyY1UJxABERABERABERABERABERABEeiDgNzIPmCFO5SNBNyV220WDVeRShYBERABERABERABERABERCBggTKvMVOQdHrdDpuZOgnO9UJl3QRAREQAREQAREQAREQAREokYBWI0uEr6pFQAREQAREQAREQAREQAREoHoE5EZWr80ksQiIgAiIgAiIgAiIgAiIgAiUSGAuqZVdeSRVliiEqhYBERABERABERABEfBF4Pnnn8e603O5ffFUOSIgAq0EFj169Kj1W30jAiIgAiIgAiIgAiIgAiIgAl4I8NxIVq0uXLjgpTQVkgIBJbWm0AqSQQREQAREQAREQAREQAREQAQqQ0BuZBJNde3atbVr1547dy4JaSSECIiACIiACIiACIiACIiACHQmIDeyM5uIvzx8+PDixYv37t2LWKeqEgEREAEREAEREAEREAEREIE8BORG5qGmc0RABERABERABERABERABERgYAk8diPJqFyU4TU+Pt5Kii2zGU5dVNa5k5OTrTJnEZhjop0L/1Yh9Y0IiIAIiIAIiIAI5CaQ0dohH6q1itznfvDBB4mfi4RN+kIgo8xlndskMB+zy9x6LvZtRn1zn4t30HTuiRMnDh061PSlPlaawNwDP3itXLnS3nT/2/a5IKtWrWr7fVNRbY+JcO4Xv/jFJkn4mPEW2JHPbVtdq/D6RgREQAREQAREQAR6Esho7fB0kNaicp/77LPPJn4uEjbpC4GMMpd1bpPAfMwuc+u5GJwZ9c19bqtNi83fWpq+qTQBPfCj0s0n4UVABERABERABERABERABEQgNgHtjYxNXPWJgAiIgAiIgAiIgAiIgAiIQKUJyI2sdPNJeBEQAREQAREQAREQAREQARGITUBuZGziqk8EREAEREAEREAEREAEREAEKk1AbmSlm0/Ci4AIiIAIiIAIiIAIiIAIiEBsAnIjYxNXfSIgAiIgAiIgAiIgAiIgAiJQaQJyIyvdfBJeBERABERABERABERABERABGITkBsZm7jqEwEREAEREAEREAEREAEREIFKE5AbWenmk/AiIAIiIAIiIAIiIAIiIAIiEJuA3MjYxFWfCIiACIiACIiACIiACIiACFSagNzISjefhBcBERABERABERABERABERCB2ATkRsYmrvpEQAREQAREQAREQAREQAREoNIE5EZWuvkkvAiIgAiIgAiIgAiIgAiIgAjEJiA3MjZx1ScCIiACIiACIiACIiACIiAClSYgN7LSzSfhRUAEREAEREAEREAEREAERCA2AbmRsYmrPhEQAREQAREQAREQAREQARGoNAG5kZVuPgkvAiIgAiIgAiIgAiIgAiIgArEJyI2MTVz1iYAIiIAIiIAIiIAIiIAIiEClCciNrHTzSXgREAEREAEREAEREAEREAERiE1AbmRs4qpPBERABERABERABERABERABCpNQG5kpZtPwouACIiACIiACIiACIiACIhAbAKfjl2h6gtP4N69e7du3epZz7PPPrtq1aqmw4qc+8H8q6nA1o9t641w7vPPP79y5comeTLW2/ZcIIOrqcDWj0XO/eIXv7h8+fKmMjPW2/bca9euPXz4sKnA1o9lnfuV+VeTPBllbnvulStXPv7446YCWz8WOZcGAldTmRnrbXvuxYsXm0pr+7Gsc7mI6NJNImWUue210FSUPoqACIiACIiACFSDwCO9akTg9OnTY2Njx44dy9L5MJ1bVS9yLlXnrjfCuWvWrGnVN2O9bc/dsmVLFn2LnEsVrTJnrLftuQiTReayzqU5WvXNKHPbc+nkWfQtci6XTKvMGette24WgTmmrHMvXLjQqm8WmfF7d+3a1XquvhEBERABERABEagigUUIncUC0DGVILB169bJycm7d+9qNbK1vdquhGg1shUU32g1EghFVhSLnJtxZa9yq5FtO1Xb7qcvRUAEREAEREAE0icgNzL9NupDQnMj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
