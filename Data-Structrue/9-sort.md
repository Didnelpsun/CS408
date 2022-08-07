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

插入排序的排序序列分为非排序和已排序序列。插入排序就是将选定的目标值插入到对应的位置。

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
+ 直接插入排序进行$n$躺后能保证前$n+1$个元素是有序的，但是不能保证其都在最终的位置上（如最小的元素在最后一位，这是插入排序的共性）。

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
+ 二分插入排序进行$n$躺后能保证前$n+1$个元素是有序的，但是不能保证其都在最终的位置上（如最小的元素在最后一位，这是插入排序的共性）。

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

交换排序即根据序列中两个元素关键的比较结构然后交换这两个记录在序列中的位置。

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
+ 对于基本有序的序列快速排序不能发挥其特性。

## 选择排序

分为已排序和未排序序列。选择排序就是每一趟在待排序元素中选取关键字最小或最大的元素加入有序子序列。

选择排序也需要交换，但是与交换排序的不断交换不同的是选择排序时选择出一个最后进行交换，一趟只交换一次。

选择排序算法的比较次数始终为$n(n-1)/2$，与序列状态无关。

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

如18、23、19、9、23*、15进行排序。

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

#### 堆的建立

其实堆就是层序存储的完全二叉树。其中：

+ $i\leqslant\lfloor\dfrac{n}{2}\rfloor$的结点都是非终端结点。
+ $i$的左孩子是$2i$。
+ $i$的右孩子是$2i+1$。
+ $i$的父结点是$\lfloor\dfrac{n}{2}\rfloor$。

所以建立根堆过程是：按照关键字序列依次添加关键字到二叉树，按照层次遍历顺序添加；初始化成功后再从下往上、从左至右按逆层次遍历顺序不断调整位置。如果是大根堆则大元素往上，如果是小根堆则小元素往上，往上时父子结点不断交换位置。

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

每次将未排序记录中选择最值加入已排序序列末尾再调整。

1. 每一趟将堆顶元素加入子序列（堆顶元素与待排序序列中的最后一个元素交换）。此时后面的这个元素就排序好了。最右下的元素作为堆顶元素。
2. 此时待排序序列已经不是堆了（堆顶被换成最小或最大的元素），需要将其再次调整为堆（小元素或大元素不断下坠）。
3. 重复步骤一二。
4. 直到$n-1$趟处理后得到有序序列。基于大根堆的堆排序会得到递增序列，而基于小根堆的堆排序会得到递减序列。

调整堆从右边即序列末尾开始。

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

### 二路归并排序

二路归并排序比较常用，且基本上用于内部排序，多路排序多用于外部排序。

#### 二路归并排序过程

1. 把长度为$n$的输入序列分成两个长度为$\dfrac{n}{2}$的子序列。
2. 对这两个子序列分别采用归并排序。
3. 将两个排序好的子序列合并成一个最终的排序序列。

#### 二路归并排序性能

二路归并排序是一棵倒立的二叉树。

空间复杂度主要来自辅助数组，所以为$O(n)$，而递归调用的调用栈的空间复杂度为$O(\log_2n)$，总的空间复杂度就是为$O(n)$。

$n$个元素二路归并排序，归并一共要$\log_2n$趟，每次归并时间复杂度为$O(n)$，则算法时间复杂度为$O(n\log_2n)$

归并排序是稳定的。

## 分配排序

分配排序过程无须比较关键字，而是通过用额外的空间来“分配”和“收集”来实现排序，它们的时间复杂度可达到线性阶$O(n)$。简言之就是：用空间换时间，所以性能与基于比较的排序才有数量级的提高。

### 基数排序

基数排序不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

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

算法种类|最好时间复杂度|平均时间复杂度|最好时间复杂度|空间复杂度|是否稳定
:-----:|:------------:|:----------:|:------------:|:-------:|:------:
直接插入排序|$O(n)$|$O(n^2)$|$O(n^2)$|$O(1)$|是
冒泡排序|$O(n)$|$O(n^2)$|$O(n^2)$|$O(1)$|是
简单选择排序|$O(n^2)$|$O(n^2)$|$O(n^2)$|$O(1)$|否
希尔排序|$?$|$?$|$?$|$O(1)$|否
快速排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n^2)$|$O(\log_2n)$|否
堆排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n\log_2n)$|$O(1)$|否
二路归并排序|$O(n\log_2n)$|$O(n\log_2n)$|$O(n\log_2n)$|$O(n)$|是
基数排序|$O(d(n+r))$|$O(d(n+r))$|$O(d(n+r))$|$O(r)$|是

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

传统方法从$k$个归并段选出一个最大或最小元素需要对比关键字$k-1$次，而使用$k$路归并的败者树只需要对比关键字$\lceil\log_2k\rceil$次（败者树层数）。

### 置换选择排序

用于构建更长的初始归并段，从而减少归并次数。

假设初始始待排文件为$FI$，初始归并段输出文件为$FO$，内存工作区为$WA$，$FO$和$WA$的初始状态为空，$WA$可容纳$w$个记录。置换选择算法的步骤如下：

1. 从$FI$输入$w$个记录到工作区$WA$。
2. 从$WA$中选出其中关键字取最小值的记录，记为$MINIMAX$记录。
3. 将$MINIMAX$记录输出到$FO$中去。
4. 若$FI$不空，则从$FI$输入下一个记录到$WA$中。
5. 从$WA$中所有关键字比$MINIMAX$记录的关键字大的记录中选出最小关键字记录，作为新的$MINIMAX$记录。
6. 重复步骤三到五，直至在$WA$中选不出新的$MINIMAX$记录为止，由此得到一个初始归并段，输出一个归并段的结束标志到$FO$中去。准备输出新的归并段。
7. 重复步骤二到六，直至$WA$为空。由此得到全部初始归并段。

此时输出的初始归并段可以超过$WA$，且初始归并段长度是不一定相等的。

如$FI$：$4,6,9,7,13,11,14,22,30,2,3,19,20,17,23,5,36,12,18,21,39$，$WA$长度为$3$，$FO$为$4,6,7,9,11,13,14,16,22,30$、$2,3,10,17,19,20,23,36$、$1,5,12,18,21,39$。

### 最佳归并树

因为每个归并段的长度不同，所以归并的次序比较重要。

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

[heapbuild]:data:image/png;base64,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BBhzMMAC2RXkgjnrDgMyt3WHCmbgYSUyNrIZkpL766VfRUAE0iEwgihcugwH4WQinx7fb8Z6mrWfGNQY3bJUx+DCwe4GhiSbUVSWEyt3jNzIyjWZBG4OAVJP7ZFlDEEYTENZOe+//z7xVzYUmZHESDvU6c2BLE1FQAT8Enj77bcxugjB+y22tTQCbWbdEeUnTDashcbxnGUrBATshj29VRK9FwERKIXAzHMj582bh3FjnsysrxfkD7sZp6am2JxtpVPjs88+y3ssM16uSvIZePHxypUrrQevX7/exfLdwbV5w/112CuFz1xjHWvTWFKkgQS41w63DTt27JiNTniVhLdGR0dxDrGBXJgMMhxJ1j1vOLJtxNu2bRs3jWggPaksAiIQnwBDELuKcCND33eabeT79u2zrZIMiTY2WugNS69VcUwdPpIQa2OjbRbAgWRslPHTCkrvRaAqBOK5kUaEUQPnsNW66kPKBiMMLxuP+hxZ9Z/kRla9BSV/QwhgKuFMco8cdjlmURkramxsjKGs9oNYFho6RgREIBqBaG6kaUR1WHcMjxlvvUP0zcbGGtxsP1qbqiIRSI3ARyMLZJkPFnZirLFYlAWoTBKLXbUF+CMLqepEQAREoCsBTB9e7JPEjWQEM2eS1AkbyjgFk2j+/Pm8YZMPR8p77IpRX4qACNSMAGll5Pzzwp9kbOSFgjdu3OCjacoBCxYs4P3sILq0NQ3NDtBfERCByhGI7Ua2AmIosY9taQ+tx+i9CIiACCRIAHeRV4KCSSQREAERKJEA/iEvUjBKlEFVi4AIxCEQ5IEfcURXLSIgAiIgAiIgAiIgAiIgAukTYLMu9wFJX05JmJ2A3MjsrHSkCIiACIiACIiACIiACIiACIjAiNxIdQIREAEREAEREAEREAEREAEREIEhCMiNHAJWuEPZSMBdud1m0XAVqWQREAEREAEREAEREAEREAERKEigzFvsFBS9TqfjRoZ+slOdcEkXERABERABERABERABERCBEgloNbJE+KpaBERABERABERABERABERABKpHQG5k9dpMEouACIiACIiACIiACIiACIhAiQRmklrZlUdSZYlCqGoREAEREAEREAEREAFfBB599FGsOz2X2xdPlSMCItBJYN7du3c7v9U3IiACIiACIiACIiACIiACIuCFAM+NZNXq3LlzXkpTISkQUFJrCq0gGURABERABERABERABERABESgMgTkRibRVJcvX16xYsXZs2eTkEZCiIAIiIAIiIAIiIAIiIAIiEBvAnIje7OJ+MudO3fOnz//7rvvRqxTVYmACIiACIiACIiACIiACIhAHgJyI/NQ0zkiIAIiIAIiIAIiIAIiIAIi0FgC99xIMirnZXjt2rWrkxRbZjOcOq+sc48ePdopcxaBOSbaufDvFFLfiIAIiIAIiIAIiEBuAhmtHfKhOqvIfe4777yT+LlI2KYvBDLKXNa5bQLzMbvMnedi32bUN/e5eAdt5x4/fnz//v1tX+pjpQnMPPCD19KlS+1N/79dnwuybNmyrt+3FdX1mAjnfvrTn26ThI8Zb4Ed+dyu1XUKr29EQAREQAREQAREYCCBjNYOTwfpLCr3uQ8//HDi5yJhm74QyChzWee2CczH7DJ3novBmVHf3Od22rTY/J2l6ZtKE9ADPyrdfBJeBERABERABERABERABERABGIT0N7I2MRVnwiIgAiIgAiIgAiIgAiIgAhUmoDcyEo3n4QXAREQAREQAREQAREQAREQgdgE5EbGJq76REAEREAEREAEREAEREAERKDSBORGVrr5JLwIiIAIiIAIiIAIiIAIiIAIxCYgNzI2cdUnAiIgAiIgAiIgAiIgAiIgApUmIDey0s0n4UVABERABERABERABERABEQgNgG5kbGJqz4REAEREAEREAEREAEREAERqDQBuZGVbj4JLwIiIAIiIAIiIAIiIAIiIAKxCciNjE1c9YmACIiACIiACIiACIiACIhApQnIjax080l4ERABERABERABERABERABEYhNQG5kbOKqTwREQAREQAREQAREQAREQAQqTUBuZKWbT8KLgAiIgAiIgAiIgAiIgAiIQGwCciNjE1d9IiACIiACIiACIiACIiACIlBpAnIjK918El4EREAEREAEREAEREAEREAEYhOQGxmbuOoTAREQAREQAREQAREQAREQgUoTkBtZ6eaT8CIgAiIgAiIgAiIgAiIgAiIQm4DcyNjEVZ8IiIAIiIAIiIAIiIAIiIAIVJqA3MhKN5+EFwEREAEREAEREAEREAEREIHYBORGxiau+kRABERABERABERABERABESg0gTkRla6+SS8CIiACIiACIiACIiACIiACMQm8NHYFaq+8ATefffda9euDazn4YcfXrZsWdthRc59Z/bVVmDnx671Rjj30UcfXbp0aZs8Gevtei6QwdVWYOfHIud++tOffvzxx9vKzFhv13MvX758586dtgI7P5Z17udmX23yZJS567kXL1784IMP2grs/FjkXBoIXG1lZqy367nnz59vK63rx7LO5SKiS7eJlFHmrtdCW1H6KAIiIAIiIAIiUA0Cd/WqEYFTp07t3LnzyJEjWTofpnOn6kXOperc9UY497nnnuvUN2O9Xc/dsGFDFn2LnEsVnTJnrLfruQiTReayzqU5OvXNKHPXc+nkWfQtci6XTKfMGevtem4WgTmmrHPPnTvXqW8WmfF7JyYmOs/VNyIgAiIgAiIgAlUkMA+hs1gAOqYSBDZu3Hj06NGbN29qNbKzvbquhGg1shMU32g1EghFVhSLnJtxZa9yq5FdO1XX7qcvRUAEREAEREAE0icgNzL9NhpCQnMjFRoYApkOFQEREAEREAEREAEREAERGJKAbrEzJDAdLgIiIAIiIAIiIAIiIAIiIALNJiA3stntL+1FQAREQAREQAREQAREQAREYEgCciOHBKbDRUAEREAEREAEREAEREAERKDZBORGNrv9pb0IiIAIiIAIiIAIiIAIiIAIDElAbuSQwHS4CIiACIjA8AQmJye5j/Tw5+kMERABERABERCBFAnIjUyxVSSTCIiACNSMwIEDB44dO1YzpaSOCIiACIiACDSWgNzIxja9FBcBERABERABERABERABERCBPATkRuahpnNEQAREQAREQAREQAREQAREoLEE5EY2tumluAiIgAiIgAiIgAiIgAiIgAjkISA3Mg81nSMCIiACIiACIiACIiACIiACjSUgN7JWTb9kyZLnnnuuVipJGREQAREQAREQAREQAREQgcQIzLt7925iIkkcERABERCBuhFYuHDh5z73uXPnztVNMekjAo0k8M4775w+fXpqagrt79y5c/ny5VYMy5Yte3j2NTo6umbNmk9/+tOtv+q9CIhAPQjIjaxHO0oLEUiCwLVr1959911EMRsiCZkkRBoE5Eam0Q6SQgQKETDvkYf3tPqNS5cuffTRR3Ebn3rqqVdeeYUKmAiYDlxNzAhjY2P4k8SS3Jd6IwIiUHUCciOr3oKSXwRKI+Ci0Z2haJMJqwLrgTi0BaT5WJqsqrhsAnIjy24B1S8ChQjgN+7evZsV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
