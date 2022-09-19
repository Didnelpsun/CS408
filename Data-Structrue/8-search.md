# 查找

## 基本概念

+ 查找：在数据集合中寻找满足某种条件的数据元素的过程。
+ 查找表（查找结构）：用于查找的数据集合，由同一类型的数据元素或记录组成。
+ 关键字：数据元素中唯一标识该元素的某个数据项的值，使用基于关键字的查找，查找结果应该唯一。
+ 静态查找表：只查找符合条件的数据元素。（顺序查找、折半查找、散列查找）
+ 动态查找表：出来要查找，还要进行删除或插入，除了查找速度还要考虑插入删除操作是否方便。（二叉排序树查找、散列查找）
+ 查找长度：查找运算中，需要对比关键字的次数。
+ 平均查找长度$ASL$：所有查找过程中进行关键字比较次数的平均值。$ASL=\sum_{i=1}^nP_iC_i$。其中$P_i$表示查找第$i$个元素的概率，$C_i$表示查找第$i$个元素的查找长度。

## 线性表查找

### 顺序查找

又称为线性查找，常用于线性表，从头到尾逐个查找。

#### 一般查找

在算法实现时一般将线性表的$0$号索引的元素值设为查找的值，从表最后面开始向前查找，当没有找到时就直接从$0$返回。这个数据称为哨兵，可以避免不必要的判断线性表长是否越界语句从而提高程序效率。

$ASL$查找成功为$\dfrac{1+2+3+\cdots+n}{n}=\dfrac{n+1}{2}$，$ASL$查找失败为$n+1$，时间复杂度为$O(n)$。

#### 顺序表

可以让数据集变为有序的，这样对比数据大小也可以知道是否还需要遍历从而减少查找时间。这样顺序结构从逻辑上就变成了一个二叉树结构（一般是顺序的），左子树代表小于（失败结点），右子树代表大于（需要继续向右查找），所有数据结点挂在右子树上。

对于顺序查找，无论顺序表还是乱序表，查找成功的时间都是相同的。$ASL$也是相同的。

若有$n$个结点，则有$n+1$个查找失败结点。

查找情况还要比普通乱序查找加上一个大于最大值的情况。

虽然有$n+1$个失败结点，但是失败结点都是不存在的，如果结点失败只会在一个不存在的区间上，所以查找平均概率是$\dfrac{1}{n+1}$而不是$\dfrac{1}{2n+1}$。同理，查找成功查找失败都会在那个区间停下，一旦判断所在区域不存在就会退出，所以查找失败的次数跟最坏查找成功次数一样都是$n$查完所有。

$ASL$查找失败为$\dfrac{1+2+3+\cdots+n+n}{n+1}=\dfrac{n}{2}+\dfrac{n}{n+1}$。成功结点的查找长度等于自身所在层数，失败结点的查找长度等于其父结点所在层数。

注意，有序线性表的顺序查找和后面的折半查找的思想是不一样的（有序顺序查找是从两端开始向右比较，折半查找从中间开始不断取中间值比较）。且有序线性表的顺序查找中的线性表可以是链式存储结构。

#### 查找概率不等

当数据元素查找概率不等时，可以将查找概率更大的元素放在靠前的位置，以减少大概率元素被遍历的时间。

$ASL$查找成功为$\sum\limits_{i=1}^nP_ii$，$P_i$为第$i$个元素出现概率。

但是此时数据是乱序的，所以查找失败的时间复杂度与没有优化的是一样的。

### 折半查找

也称为二分查找，只适用于有序的顺序表，链表无法适用，因为链表很难折半找到元素。

#### 折半查找的结构

定义三个指针，$low$指向查找范围的最小值，$high$指向查找范围的最大值，$mid$指向查找范围的中间值，$mid=\lfloor(low+high)\div2\rfloor$。（也可以向上取整，过程会有所不同）

#### 折半查找的过程

1. 定义左边界$low$，默认为$0$，右边界$high$，默认为$length-1$，循环执行折半查找（2，3两步）。
2. 计算出$mid=\lfloor(low+high)\div2\rfloor$。
3. 判断中间索引值$data\lbrack mid\rbrack$是否与搜索值$target$相等。
   + 若$data\lbrack mid\rbrack=target$，返回中间索引。
   + 若$data\lbrack mid\rbrack<target$，则将$high=mid-1$。
   + 若$data\lbrack mid\rbrack>target$，则将$low=mid+1$的值。
4. 当查找最后$low>high$则查找失败。

$ASL$查找成功为$\dfrac{1+2+3+\cdots+n}{n}=\dfrac{n+1}{2}$，$ASL$查找失败为$n+1$，时间复杂度为$O(n)$。

#### 折半公式优化

在对$mid$进行取值时，如果数据量太大，查找到右侧时计算$mid$进行两数相加$low+high$可能会数值溢出。那么如何解决？

+ 变幻公式：$(low+high)\div2\rightarrow low\div2+high\div2$或$\rightarrow low-(low\div2-high\div2)\rightarrow low+(high-low)\div2$。
+ 无符号右移运算：$mid=(low+hight) >>> 1$。直接将除以$2$变为右移运算，速度更快，且舍去了小数位不需要进行取整运算。

#### 折半查找判定树

折半查找的过程可用二叉树来描述，称为判定树。树中每个圆形结点表示一个记录，结点中的值为该记录的关键字值；树中最下面的叶结点都是方形的，它表示查找不成功的情况。从判定树可以看出，查找成功时的查找长度为从根结点到目的结点的路径上的结点数，而查找不成功时的查找长度为从根结点到对应失败结点的父结点的路径上的结点数。

构建判定树方式：

+ 若当前$low$和$high$有奇数个元素，则$mid$分割后左右两部分元素个数相等。
+ 若当前$low$和$high$有奇数个元素，则$mid$分割后左部分元素个数小于右部分一个。
+ 数值结点为圆形，末端结点后再加一层方形的叶子结点，表示查找失败。

判定树性质：

+ 折半查找判定树一定是一个平衡二叉树。只有最下面一层不满，元素个数为$n$时树高与完全二叉树相等$h=\lceil\log_2(n+1)\rceil$。
+ 根据折半查找判定树可以计算对应的$ASL$：查找成功的$ASL$=($\sum\limits_{i=1}^n$第$i$层的成功结点数$\times i$)$\div$成功结点总数，查找失败的$ASL$=($\sum\limits_{i=1}^n$第$i$层的失败结点数$\times i$)$\div$失败结点总数。
+ 折半查找判定树也是一个二叉排序树，失败结点$=n+1$（成功结点的空链域节点数）。
+ 折半查找判定树的中序序列应该是一个有序序列。

$ASL$查找成功查找失败都一定小于折半查找树的树高，时间复杂度为$O(\log_2n)$。

查找的折半查找判定树和排序的二叉排序树都是同样的二叉逻辑结构，但是不同的是折半查找判定树是已知完整序列，所以总是从中间开始，时间性能为固定的$O(\log_2n)$，而二叉排序树的构造是根据输入来的，如果输入的序列正好是从中间切分的，则时间性能为最好的$O(\log_2n)$，如果输入的序列恰好有序，则为单枝树，时间性能为最坏的$O(n)$。

### 分块查找

分块查找又称为索引顺序查找，需要对数据进行一定的排序，不一定全部是顺序的，但是要求在一个区间内是满足一定条件的，即块内无序，块间有序。即$n$块内的元素全部小于$n+1$块内的任意元素。

将查找表分割为若干子块，其中分割的块数和每块里的数据个数都是不定的。

#### 分块查找结构

除了保存数据的顺序表外还需要定义一个索引表，保存每个分块的**最大关键字**、每块的存储空间，第一个元素的地址。

很明显这种定义方式定义了两个顺序结构，并且如果插入删除时需要大量移动元素，所以可以采用链表的形式。

定义一种最大元素结点，包含数据、指向后继最大元素结点的指针、指向分块内元素的指针；定义一种块内元素结点，包含数据、指向后继分块内元素的指针。但是这时候就无法折半查找，只能顺序查找。

所以总的来说分块查找还是一种静态查找，动态插入删除的效率较低。

#### 分块查找过程

在查找时先根据关键字遍历索引表，然后找到索引表的分块（可以顺序也可以折半），再到存储数据的顺序表的索引区间中查找。

若适用折半查找查找索引表的分块，索引表中若不存在目标关键字，则折半查找索引表最终会停在$low>high$，要在$low$所指向分块中查找。

#### 分块查找的效率

$ASL$查找成功失败的情况都十分复杂，所以一般不会考。

假设长度为$n$的查找表被均匀分为$b$块，每块$s$个元素，假设索引查找和块内查找的平均查找长度$ASL$分别为$L_I$和$L_S$，则分块查找的平均查找长度为$ASL=L_I+L_S$。

使用顺序查找索引表，则$L_I=\dfrac{(1+2+\cdots+b)}{b}=\dfrac{b+1}{2}$，$L_S=\dfrac{(1+2+\cdots+s)}{s}=\dfrac{s+1}{2}$。所以$ASL=\dfrac{b+1}{2}+\dfrac{s+1}{2}=\dfrac{s^2+2s+n}{2s}$，当$s=\sqrt{n}$时，$ASL_{min}=\sqrt{n}+1$。

使用折半查找索引表，则$L_I=\lceil\log_2(b+1)\rceil$，$L_S=\dfrac{(1+2+\cdots+s)}{s}=\dfrac{s+1}{2}$。所以$ASL=\lceil\log_2(b+1)\rceil+\dfrac{s+1}{2}$。

## 二叉查找

### 二叉排序树

即$BST$，是一种用于排序的二叉树。

#### 二叉排序树定义

二叉排序树也是二叉查找树。左子树上所有结点的关键字均小于根结点的关键字；右子树上所有结点的关键字均大于根结点的关键字；左右子树又各是一棵二叉排序树。

中序遍历二叉排序树会得到一个递增的有序序列。

#### 二叉排序树查找

1. 若树非空，目标值与根结点的值比较。
2. 若相等则查找成功，返回结点指针。
3. 若小于根结点，则在左子树上查找，否则在右子树上查找。
4. 遍历结束后仍没有找到则返回$NULL$。

遍历查找的时间复杂度是$O(\log_2n)$，则递归查找的时间复杂度是$O(\lceil\log_2(n+1)\rceil)$，其中$\lceil\log_2(n+1)\rceil$代表二叉树的高度。

查找成功的平均查找长度$ASL$，二叉树的平均查找长度为$O(\log_2n)$，最坏情况是每个结点只有一个分支，平均查找长度为$O(n)$。

#### 二叉排序树插入

+ 若原二叉排序树为空，就直接插入结点。
+ 否则，若关键字小于根结点值，插入左结点树。
+ 若关键字大于根结点值，插入右结点树。

#### 二叉排序树删除

+ 搜索到对应值的目标结点。
+ 若被删除结点$p$是叶子结点，则直接删除，不会破坏二叉排序树的结构。
+ 若被删除结点只有一棵左子树或右子树，则让该结点的子树称为该结点父结点的子树，来代替其的位置。
+ 若被删除结点有左子树和右子树，则让其结点的直接后继（中序排序该结点后一个结点，其右子树的最左下角结点，不一定是叶子结点）或直接前驱（中序排序该结点前一个结点，其左子树的最右下角结点，不一定是叶子结点）替代该结点，并从二叉排序树中删除该的结点直接后继、直接前驱，这就变成了第一种或第二种情况。

二叉排序树删除或插入时得到的二叉排序树往往与原来的不同。

#### 二叉排序树查找效率

二叉排序树的查找效率主要取决于树的高度，若是平衡二叉树，则平均查找长度为$O(\log_2n)$，若最坏情况下只有一个单枝树，则平均查找长度为$O(n)$。

若按顺序输入关键字则会得到单枝树。

查找过程来看，二叉排序树和二分查找类似。但是二分查找的判定树唯一，而二叉排序树的查找不唯一，相关关键字插入顺序会极大影响到查找效率。

从维护来看，二叉排序树插入删除操作只需要移动指针，时间代价为$O(\log_2n)$，而二分查找的对象是有序顺序表，代价是$O(n)$。

所以静态查找时使用顺序表进行二分查找，而动态查找时使用二叉排序树。

### 平衡二叉树

为了限制判定树高增长过快，降低二叉排序树的性能，规定插入时要保证平衡。

即$AVL$树，树上任意一结点的左子树和右子树的高度之差不超过$1$。

树高即树的深度。

结点的平衡因子=左子树高-右子树高。

即平衡二叉树的平衡因子只可能为$-1,0,1$。

在插入一个结点时，查找路径上的所有结点都可能收到影响。

从插入点往回（从下往上）找到第一个不平衡的结点，调整以该结点为根的子树。每次调整的对象都是最小不平衡树。

#### 平衡二叉树结点

$h$为平衡二叉树高度，$n_h$为构造此高度的平衡二叉树所需的最少结点数。

+ 平衡二叉树最少结点数的递推公式为$n_0=0$，$n_1=1$，$n_2=2$，$n_h=1+n_{h-1}+n_{h-2}$。此时所有非叶结点的平衡因子均为$1$。

假设$T$为高度为$h$的平衡二叉树，其需要最少的节点数目为$F(h)$。

又假设$TL$，$TR$为$T$的左右子树，因此$TL$，$TR$也为平衡二叉树。

假设$FL$、$FR$为$TL$，$TR$的最少节点数，则，$F(h)=FL+FR+1$。那么$FL$、$FR$到底等于多少呢？

由于$TL$，$TR$与$T$一样是平衡二叉树，又由于我们知道$T$的最少节点数是$F(h)$，其中$h$为$T$的高度，因此如果我们知道$TL$，$TR$的高度就可以知道$FL$、$FR$的值了。

由平衡二叉树的定义可以知道，$TL$和$TR$的高度要么相同，要么相差$1$，而当$TL$与$TR$高度相同（即都等于$h-1$)时，我们算出来的$F(h)$并不能保证最小，两边都是$h-1$明显比只有一边$h-2$的节点数更多。

因此只有当$TL$与$TR$高度相差一，即一个高度为$h-1$，一个高度为$h-2$时，计算出来的$F(h)$才能最小。

此时我们假设$TL$比$TR$高度要高$1$，即$TL$高度为$h-1$，$TR$高度为$h-2$，则有$F1=F(h-1)$，$F2=F(h-2)$。

因此得到结论：$F(h)=F(h-1)+F(h-2)+1$。

+ 平衡二叉树最多结点数$2^n-1$。即该二叉树为满二叉树。

#### 平衡二叉树插入

最重要的是根据二叉排序树的大小关系算出从大到小的序列，然后把最中间的作为新根，向两侧作为左右子树。

即先找到插入路径上离插入结点最近的平衡因子的绝对值大于$1$的结点$A$，再对以$A$为根的子树，在保持二叉排序树特性的前提下调整各结点位置。

每次调整的都是最小不平衡子树。

#### 平衡二叉树删除

与插入操作类似，都是需要从下往上进行调整。

不同的是插入操作只对子树进行调整，而删除操作可能要对整个树进行调整。

在任意一棵非空二叉排序树$T_1$中，删除某结点$v$之后形成二叉排序树$T_2$，再将$v$插入$T_2$，形成二叉排序树$T_3$。

+ 若$v$是$T_1$的叶结点，则$T_1$与$T_3$相同。
+ 若$v$不是$T_1$的叶结点，则$T_1$与$T_3$不同（如果是一定不同则是错误的）。

#### 右单旋转

从结点的左孩子的左子树中插入导致不平衡：

```txt
           A(2)
            |
       ------------
       |          |
      B(1)      AR(H)
       |
 ------------
 |          |
BL(H+1)   BR(H)
```

$BL<B<BR<A<AR$

由于在结点$A$的左孩子$B$的的左子树$BL$上插入了新结点，$A$的平衡因子由$1$变成了$2$，导致以$A$为根的子树失去了平衡，需要进行一次向右的旋转操作。

将$A$的左孩子$B$向右上旋转代替$A$成为根结点，将$A$结点向右下选择为成$B$的右子树的根结点，而$B$的原右子树则作为$A$结点的左子树。

```txt
       B(0)
        |
   ------------
   |          |
BL(H+1)      A(0)
              |
         ------------
         |          |
       BR(H)      AR(H)
```

#### 左单旋转

从结点的右孩子的右子树中插入导致不平衡：

```txt
       A(-2)
         |
   ------------
   |          |
AL(H)       B(-1)
              |
        ------------
        |          |
      BL(H)     BR(H+1)
```

$AL<A<BL<B<BR$

由于在结点$A$的右孩子$R$的右子树$R$上插入了新结点，$A$的平衡因子由$-1$减至$-2$，导致以$A$为根的子树失去平衡，需要一-次向左的旋转操作。

将$A$的右孩子$B$向左上旋转代替$A$成为根结点，将$A$结点向左下旋转成为$B$的左子树的根结点，而$B$的原左子树则作为$A$结点的右子树。

```txt
            B(0)
             |
       ------------
       |          |
      A(0)     BR(H+1)
       |
 ------------
 |          |
AL(H)     BR(H)
```

#### 先左后右双旋转

从结点的左孩子的右子树中插入导致不平衡：

```txt
            A(2)
             |
       ------------
       |          |
     B(-1)      AR(H)
       |
 ------------
 |          |
BL(H)     C(-1)
            |
      ------------
      |          |
   CL(H-1)     CR(H)
```

```txt
            A(2)
             |
       ------------
       |          |
     B(-1)      AR(H)
       |
 ------------
 |          |
BL(H)     C(-1)
            |
      ------------
      |          |
    CL(H)     CR(H-1)
```

将$BR$拆分为$C$和$CL$、$CR$，假设插入的是$CR$部分，插入$CL$也同理。

$BL<B<CL<C<CR<A<AR$

由于在$A$的左孩子$L$的右子树$R$上插入新结点，$A$的平衡因子由$1$增至$2$，导致以$A$为根的子树失去平衡，需要进行两次旋转操作，先左旋转后右旋转先将$A$结点的左孩子$B$的右子树的根结点$C$向左上旋转提升到$B$结点的位置，然后再把该$C$结点向右上旋转提升到$A$结点的位置。

```txt
                C(0)
                 |
       --------------------
       |                  |
     B(1)                A(0)
       |                  |
 ------------       ------------
 |          |       |          |
BL(H)    CL(H-1)  CR(H)      AR(H)
```

```txt
                C(0)
                 |
       --------------------
       |                  |
     B(0)               A(-1)
       |                  |
 ------------       ------------
 |          |       |          |
BL(H)    CL(H)   CR(H-1)     AR(H)
```

#### 先右后左双旋转

从结点的右孩子的左子树中插入导致不平衡：

```txt
       A(-2)
         |
    ------------
    |          |
  AL(H)       B(1)
               |
         ------------
         |          |
        C(1)      BR(H)
         |
   ------------
   |          |
CL(H)     CR(H-1)
```

```txt
       A(-2)
         |
    ------------
    |          |
  AL(H)       B(1)
               |
         ------------
         |          |
        C(1)      BR(H)
         |
   ------------
   |          |
CL(H-1)     CR(H)
```

$AL<A<CL<C<CR<B<BR$

由于在$A$的右孩子$R$的左子树$L$. 上插入新结点，$A$的平衡因子由$-1$减至$-2$，导致以$A$为根的子树失去平衡，需要进行两次旋转操作，先右旋转后左旋转。先将$A$结点的右孩子$B$的左子树的根结点$C$向右上旋转提升到$B$结点的位置，然后再把该$C$结点向左上旋转提升到$A$结点的位置。

```txt
                C(0)
                 |
       --------------------
       |                  |
     A(0)                B(-1)
       |                  |
 ------------       ------------
 |          |       |          |
AL(H)     CL(H)  CR(H-1)     BR(H)
```

```txt
                C(0)
                 |
       --------------------
       |                  |
     A(0)                B(-1)
       |                  |
 ------------       ------------
 |          |       |          |
AL(H)    CL(H-1)  CR(H)     BR(H)
```

#### 平衡二叉树查找

含有$n$个结点的平衡二叉树最大深度为$O(\log_2n)$，平均查找长度为$O(\log_2n)$。

### 红黑树

#### 红黑树定义

为了维持二叉平衡树，需要反复对树整体进行插入合删除，代价巨大，所以引入为弱化版相对平衡的二叉排序树——红黑树：

1. 每个结点或是红色，或是黑色的。
2. 根结点是黑色的。
3. 叶结点（$n+1$个虚构的外部结点、$NULL$结点）都是黑色的，保证红黑树的内部结点左右孩子均非空。
4. 不存在两个相邻的红结点（即红结点的父结点和孩子结点均是黑色的）。
5. 对每个结点，从该结点到任一叶结点的简单路径上，所含黑结点的数量相同。

所以定义某结点出发到达一个叶结点的任一简单路径上的黑结点总数（**不含**该目的结点）称为该结点的黑高（记为$bh$），根结点的黑高就是红黑树的黑高。

#### 红黑树性质

从根到叶结点的最长路径不大于最短路径的两倍。

+ 由性质⑤，当从根到任一叶结点的简单路径最短时，这条路径必然全由黑结点构成（即第二层的结点）。
+ 由性质④，当某条路径最长时，这条路径必然是由黑结点和红结点相间构成的，此时红结点和黑结点的数量相同（非第二层的其他所有节点）。

有$n$个内部结点的红黑树的高度$h\leqslant2\log_2(n+1)$。

+ 若红黑树的总高度为$h$，则根结点黑高$\geqslant\dfrac{h}{2}$，所以内部结点$n\geqslant2^{\frac{h}{2}-1}$（假设没有红结点），所以$h\leqslant2\log2(n+1)$。

红黑树查找、插入、删除的时间效率都是$O(\log_2n)$。

+ 插入和删除：由于红黑树的每次操作平均要旋转一次和变换颜色，而普通二叉排序树如果平衡因子在指定范围内不会旋转，所以它比普通的二叉排序树效率要低一点，不过时间复杂度仍然是$O(\log_2n)$。
+ 普通查询：没有使用到红黑树的性质，所以红黑树和二叉排序树的效率相同。
+ 插入数据有序查询：红黑树的查询效率就比二叉搜索树要高了，因为此时二叉搜索树不是平衡树，它的时间复杂度$O(n)$。

#### 红黑树插入

红黑树的插入过程和二叉查找树的插入过程基本类似，不同之处在于，红黑树中插入新结点后需要进行调整（主要通过重新着色或旋转操作进行），以满足红黑树的性质。

+ 插入红黑树中的结点$z$初始着为红色。

假设新插入的结点初始着为黑色，那么这个结点质在的路径比其他路径多出一个黑结点（几乎每次插入都破坏性质⑤），调整起来也比较麻烦。如果插入的结点是红色的，此时所有路径上的黑结点数量不变，仅在出现连续两个红结点时才需要调整，而且这种调整也比较简单。

插入过程：

1. 用二叉查找树插入法插入，并将结点$z$着为红色。若结点$z$的父结点是黑色的，无须做任何调整，此时就是一棵标准的红黑树。
2. 如果结点$z$是根结点，将$z$着为黑色（树的黑高增加一），结束。
3. 如果结点$z$不是根结点，并且$z$的父结点 $z.p$是红色的，则分为下面三种情况，区别在于$z$的叔结点$y$的颜色不同，因$z.p$是红色的，插入前的树是合法的，根据性质②和④，爷结点$z.p.p$必然存在且为黑色。性质④只在$z$和$z.p$之间被破坏了。

插入全为红，是根则变黑；父黑无变化，父红看叔叔；叔红只变色，叔父爷全变，爷爷变儿子，重新来一遍；叔黑看平衡，看谁最后转，谁转谁变色。

![红黑树插入][red-black]

#### 红黑树删除

红黑树的播入操作容易导致连续的两个红结点，破坏性质④。而删除操作容易造成子树照高的变化（删除黑结点会导致根结点到叶结点间的黑结点数量减少），破坏性质⑤。

删除过程也是先执行二叉查找树的删除方法。若待删结点有两个孩子，不能直接删除，而要找到该结点的中序后继（或前驱）填补，即右子树中最小的结点，然后转换为删除该后继结点。由于后继结点至多只有一个孩子，这样就转换为待删结点是叶结点或仅有一个孩子的情况。

最终，删除一个结点有以下两种情况∶

+ 待删结点没有孩子。
+ 待删结点只有右子树或左子树

#### 红黑树与二叉排序树

由二叉排序树树的“高度平衡”，降低到红黑树的“任一结点左右子树的高度，相差不超过两倍”的“适度平衡”，也降低了动态操作时调整的频率。对于一棵动态查找树，如果插入和删除操作比较少，查找操作比较多，采用$AVL$树比较合适，否则采用红黑树更合适。

二叉排序树使用平衡因子来约束树高，而红黑树用黑高相同约束树高。

二叉排序树只要平衡因子不超过$1$的绝对值就不用每次调整树整体，而红黑树每次插入货删除都需要进行对树进行调整。

#### 红黑树与B树

红黑树在被发明之初被称为平衡二叉$B$树，所以红黑树与$B$树之间必然有联系。

+ 将红黑树的所有红色节点上移到和他们的父节点同一高度上组成一个$B$树结点，就会得到一棵四阶$B$树。
+ 红黑树的黑色节点个数与四阶$B$树的节点总个数相等。
+ 在所有的$B$树节点中，黑色节点是父节点，红色节点是子节点。黑色节点在中间，红色节点在两边。

## 树表查找

### B树

即多路平衡查找树，要求掌握基本特定点、操作。

#### B树定义

为了保证$m$叉查找树中每个结点都能被有效利用，避免大量结点浪费导致树高过大，所以规定$m$叉查找树中，除了根结点以外（根结点最小为$1$）：

+ 任何结点至少有$\lceil\dfrac{m}{2}\rceil$个分叉，即至少包含$\lceil\dfrac{m}{2}\rceil-1$个结点。
+ 至少有两棵子树。

为了保证$m$叉查找树是一棵平衡树，避免树偏重导致树高过大，所以规定$m$叉查找树中任何一个结点，其所有子树的高度都要相同。

而能保证这两点的查找树，就是一棵$B$树，即多路平衡查找树，多少叉，就是一棵多少阶的$B$树。

非叶结点定义：$\{n,P_0,K_1,P_1,\cdots,K_n,P_n\}$。其中$K_i$为结点关键字，$K_1<K_2<\cdots<K_n$，$P_i$为指向子树根节点的指针。$P_{i-1}$所指子树所有结点的关键字均小于$K_i$，$P_i$所指子树的关键字均大于$K_i$。

#### B树性质

+ 树的每个结点至多包含$m$棵子树，至多包含$m-1$个关键字。
+ 若根结点不是终端结点，则至少有两颗子树，任意结点的每棵子树都是绝对平衡的。所有结点的平衡因子均等于$0$的。
+ 除根结点以外的所有非叶结点至少有$\lceil\dfrac{m}{2}\rceil$棵子树，即至少包含$\lceil\dfrac{m}{2}\rceil-1$个结点。
+ 每个结点中的关键字是有序的。子树$0$<子树$1$<子树$2$<……。
+ 所有叶结点都出现在同一个层次上且不带信息。（可以视为外部结点或类似于折半查
找判定树的查找失败结点，实际上这些结点不存在，指向这些结点的指针为空）。
+ $B$树最底端的失败的不存在的结点就是常说的叶子结点，而最底端的存在数据的结点就是终端结点。（一般的树的叶子结点和终端结点都是指最底端的有数据的结点）
+ 携带数据的是内部结点，最底部的叶子结点也称为外部结点。

$B$树相关性质计算涉及多个单元，注意一定要区分：

+ 树高（默认是不包含无数据的叶子结点）。
+ 子树棵树。
+ 关键字。
+ 结点（结点数往往小于关键字数）。

#### B树树高与关键字

$B$树中的大部分操作所需的磁盘存取次数与$B$树的高度成正比。高度一般与关键字相关。

计算$B$树高度大部分不包括叶子结点。若含有$n$个关键字的$m$阶$B$树。

+ 最小高度：让每个结点尽可能满，有$m-1$个关键字，$m$个分叉，则一共有$(m-1)(m^0+m^1+m^2+\cdots+m^{h-1})$个结点，其中$n$小于等于这个值，从而求出$h\geqslant\log_m(n+1)$。
+ 最大高度：
  + 让各层分叉尽可能少，即根结点只有两个分叉，其他结点只有$\lceil\dfrac{m}{2}\rceil$个分叉，所以第一层$1$个，第二层$2$个，第$h$层$2(\lceil\dfrac{m}{2}\rceil)^{h-2}$个结点，而$h+1$层的叶子结点有$2(\lceil\dfrac{m}{2}\rceil)^{h-1}$个，且$n$个关键字的$B$树必然有$n+1$个叶子结点，从而$n+1\geqslant2(\lceil\dfrac{m}{2}\rceil)^{h-1}$，即$h\leqslant\log_{\lceil\frac{m}{2}\rceil}\dfrac{n+1}{2}+1$。
  + 让各层关键字尽可能少，记$k=\lceil\dfrac{m}{2}\rceil$。第一层最少结点数和最少关键字为$1$；第二层最少结点数为$2$，最少关键字为$2(k-1)$，第三层最少结点数为$2k$，最少关键字为$2k(k-1)$，第$h$层最少结点数为$2k^{h-2}$，最少关键字为$2k^{h-2}(k-1)$，从而$h$层的m阶B数至少包含关键字总数$1+2(k-1)(k^0+k^1+\cdots+k^{h-2})=1+2(k^{h-1}-1)$，若关键字总数小于这个值，则高度一定小于$h$，所以$n\geqslant 1+2(k^{h-1}-1)$，则$h\leqslant\log_{\lceil\frac{m}{2}\rceil}\dfrac{n+1}{2}+1$。

#### B树关键字与结点

树高与结点：

+ 对于已知树高和阶求最大最小关键字数量就是上面公式的逆运算。已知树高可以求出关键字数量。
+ 根据关键字数量和结点之间的关系相除。求最大高度就除以每结点最小关键字数，求最小高度就除以每结点最大关键字数。

关键字与结点：

+ 具有$n$个关键字的$m$阶$B$树，应有$n+1$个叶结点。

叶结点即查询失败的结点，对于$n$个关键字查找则可能的失败范围有$n+1$种。

+ 有$n$个非叶结点的$m$阶$B$树中至少包含$(n-1)(\lceil\dfrac{m}{2}\rceil-1)+1$个关键字。

除根结点外的$n-1$个$m$阶$B$树中的每个非叶结点最少有$\lceil\dfrac{m}{2}\rceil-1$，然后再加上根结点的一个，所以最少为$(n-1)(\lceil\dfrac{m}{2}\rceil-1)+1$个。

#### B树查找

$B$树的查找包含两个基本操作：

1. 在$B$树中找结点。
2. 在结点内找关键字。

由于$B$树常存储在磁盘上，因此前一个查找操作是在磁盘上进行的，而后一个查找操作是在内存中进行的，即在找到目标结点后，先将结点信息读入内存，然后在结点内采用顺序查找法或折半查找法。

在$B$树上查找到某个结点后，先在有序表中进行查找，若找到则查找成功，否则按照对应的指针信息到所指的子树中去查找，则说明树中没有对应的关键字，查找失败。

#### B树插入

新元素插入一定是插入到最底层的终端结点，使用$B$树的查找来确定插入位置。插入位置一定是最底层的某个非叶结点。

若导致原结点关键字数量超过上限溢出（$m-1$个关键字），就从中间位置$\lceil\dfrac{m}{2}\rceil$分开，将左部分包含的关键字放在原来结点，右部分包含的关键字放在一个新结点，并插入到原结点的父结点的后一个位置上，而在原结点的父结点连接后的结点后移一个连接让位给分割出来的右半部分结点，中间的一个结点$\lceil\dfrac{m}{2}\rceil$插入到原结点的父结点上，并考虑在父结点的顺序对指针进行调整保证顺序。

若父结点插入时也溢出了，则同理在父结点的中间进行分割，左半部分在原来父结点；右半部分新建一个父结点，并把中间结点右边开始的所有连接移动到新父结点上；中间的结点上移到祖父结点，如果没有就新建，然后建立两个指针分别指向原父结点和新父结点。

#### B树删除

若被删除关键字在终端结点，且结点关键字个数不低于下限，则直接删除该关键字，并移动后面的关键字。

若被删除关键字在非终端结点，则用直接前驱或直接后继来替代被删除关键字，然后后面的元素直接前移：

+ 直接前驱：当前关键字左侧指针所指子树遍历到最右下的元素。
+ 直接后继：当前关键字右侧指针所指子树遍历到最左下的元素。

若被删除关键字在终端结点，但是结点关键字个数删除后低于下限：

+ 右兄弟够借：若原结点右兄弟结点里的关键字在删除一个后高于下限，则可以用结点的后继以及后继的后继来顶替：
   1. 将原结点在父结点的连接的后一个关键字下移到原结点并放在最后面。
   2. 将原结点右兄弟结点的第一个关键字上移插入到下移的元素的空位。
   3. 原结点右兄弟结点里的关键字全部前移一位。
+ 左兄弟够借：若原结点里右兄弟的关键字在删除一个后低于下限，但是左兄弟的结点足够，则可以用结点的前驱以及前驱的前驱来顶替：
   1. 将原结点在父结点的连接的前一个关键字下移到原结点并放在最前面，其余元素后移。
   2. 将原结点左兄弟结点的最后一个关键字上移插入到原结点父结点的连接的前面。
   3. 原结点左兄弟结点里的关键字全部前移一位。
+ 左右兄弟都不够借：若左右兄弟结点的关键字个数均等于下限值，则将关键字删除后与左或右兄弟结点以及父结点中的关键字进行合并：
   1. 将原结点的父结点连接后的关键字插入到原结点关键字最后面。
   2. 将原结点的左或右兄弟结点的关键字合并到原结点（前插或后插），并将连接也转移到原结点上。
   3. 若父结点的关键字个数又不满于下限，则父结点同样要于与它的兄弟父结点进行合并，并不断重复这个过程。
   4. 若父结点为空则删除父结点。

### B+树

$B+$树考的并不是很深。用于数据库。

与分块查找的思想类似，是对$B$树的一种变型。

#### B+树定义

一个$m$阶的$B+$树需要满足以下条件：

1. 每个分支结点最多有$m$棵子树或孩子结点。
2. 为了保持绝对平衡，非叶根结点至少有两棵子树，其他每个分支结点至少有$\lceil\dfrac{m}{2}\rceil$棵子树。（不同于$B$树，$B+$树又重新将最下面的保存的数据定义为叶子结点）
3. 结点的子树个数与关键字个数相等。（$B$树结点子为树个数与关键字个数加$1$）
4. 所有叶结点包含所有关键字以及指向记录的指针，叶结点中将关键字按大小排序，并且相邻叶子结点按大小顺序相互连接起来。所以$B+$树支持顺序查找。
5. 所有分支结点中仅包含其各子结点中关键字的最大值以及指向其子结点的指针（即分支结点只是索引）。

#### B+树查找

无论查找成功与否，$B+$树的查找一定会走到最下面一层结点，因为对应的信息指针都在最下面的结点。而$B$树查找可以停留在任何一层。

$B+$树可以遍历查找，即从根结点出发，对比每个结点的关键字值，若目标值小于当前关键字值且大于前一个关键字值，则从当前关键字的指针向下查找。

$B+$树可以顺序查找，在叶子结点的块之间定义指向后面叶子结点块的指针，从而能顺序查找。

#### B+树与B树区别

对于$m$阶$B+$树与$B$树：

&nbsp;|B+树|B树
:--:|:--:|:--:
结点的n个关键字对应的子树个数|$n$|$n+1$
根结点的关键字数|$[1,m]$|$[1,m-1]$
其他结点的关键字数|$[\lceil\dfrac{m}{2}\rceil,m]$|$[\lceil\dfrac{m}{2}\rceil-1,m-1]$
关键字分布|叶子结点包含所有关键字，非叶结点包含部分重复关键字|所有结点的关键字不重复
结点作用|叶子结点包含信息，非叶子结点是索引作用|所有结点都包含信息
结点存储内容|叶子结点包含关键字与对应记录的存储地址，非叶子结点包含对应子树的最大关键字和指向该子树的指针|所有结点都包含关键字与对应记录存储地址
查找方式|随机查找、顺序查找|随机查找
查找位置|需要查找到叶子结点的最底层才能判断是否查找成功或失败|查找到数的任何地方都能判断
查找速度|非叶子结点不包含关键字对应记录的存储地址，可以使一个磁盘块含有多格关键字，从而让树的阶数更大，树更矮，读磁盘次数更是，查找更快|所有结点都包含存储地址，保存的关键字数量更少，树高更高，所以读写磁盘次数更多，查找更慢

## 散列表查找

线性表和树表中，数据位置与数据关键字无关，而散列表数据位置与关键字有关。

### 散列表定义

散列表又称哈希表，是一种数据结构，数据元素的关键字与其存储地址直接相关。一个散列结构是一块地址连续的存储空间。

### 散列函数

关键字与地址通过散列函数（哈希函数）来实现映射。即记录位置=散列函数(记录关键字)。

+ 直接定址法：可表示为散列函数(关键字)=$a\times$关键字$+b$，其中$a$、$b$均为常数。这种方法计算特别简单，并且不会发生冲突，但当关键字分布不连续时，会出现很多空闲单元，会将造成大量存贮单元的浪费。
+ 数字分析法：分析关键字的各个位的构成，截取其中若干位作为散列函数值，尽可能使关键字具有大的敏感度，即最能进行区分的关键字位，这些位数都是连续的。
+ 平方取中法：先求关键字的平方值，然后在平方值中取中间几位为散列函数的值。因为一个数平方后的中间几位和原数的每一位都相关，因此，使用随机分布的关键字得到的记录的存储位置也是随机的。适用于关键字的每位取值都不够均匀或均小于散列地址所需的位数。
+ 折叠法：将关键字分割成位数相同的几部分(最后一部分的位数可以不同)，然后取这几部分的叠加和(舍去进位)作为散列函数的值。例如，假设关键字为某人身份证号码$430\,1046\,8101\,5355$，则可以用$4$位为一组进行叠加，即有$5355+8101+1046+430=14932$，舍去高位，则有$H(430104681015355)=4932$。
+ 随机数法：对于存储位置给定随机数安排，查找起来会很麻烦。
+ 除留余数法：散列函数(关键字)=关键字$\%p$，$p$一般是不大于表长的最大质数。这种方法使用较多，关键是选取较理想的$p$值，使得每一个关键字通过该函数转换后映射到散列空间上任一地址的概率都相等，从而尽可能减少发生冲突的可能性。一般情形下，取$p$为一个素数较理想，如果是合数则因为可以被多个数整除从而多个关键字余数相同造成冲突。

### 映射冲突

一般情况下，设计出的散列函数很难是单射的，即不同的关键字对应到同一个存储位置，这样就造成了冲突（碰撞）。此时，发生冲突的关键字互为同义词。

#### 开放定址法

可存放新表项的空闲地址既向同义词开放也向非同义词开放。从发生冲突的那个单元开始，按照一定的次序，从哈希表中找出一个空闲的存储单元，把发生冲突的待插入关键字存储到该单元中，从而解决冲突。既指如果当前冲突，则将元素移动到其他空闲的地方。

$H_i=(H(key)+d_i)\mod m$。

+ $i$表示发生第$i$次冲突，$i=1,2,\cdots,m-1)$。
+ $m$为散列表长度，类似于循环队列，超出表长以后就循环到最左边。
+ $d_i$为增量序列，是指发生第$i$次冲突的时候，$H(key)$偏移了多少位。

增量序列选择：

+ 线性探测法：$d_i=1,2,3,\cdots,m-1$。线性探测法充分利用了哈希表的空间，但在解决一个冲突时，可能造成新的冲突。
+ 二次（平方）探测法：$di=1,-1,2^2,-2^2\cdots,(\dfrac{m}{2})^2,-(\dfrac{m}{2})^2$。对比线性探测法更不容易产生聚集问题。<span style="color:orange">注意：</span>散列表长度$m$必须是一个可以表示为$4j+3$的素数才能探测到所有位置。
+ 伪随机探测法：定义$d_i$是一个伪随机数。
+ 再散列法：$d_i=Hash_2(key)$，又称双散列法。需要使用两个散列函数,当通过第一个散列函数$H(key)$得到的地址发生冲突时，则利用第二个散列函数$Hash_2(key)$计算该关键字的地址增量。它的具体散列函数形式：$H_i=(H(key)+i\times Hash_2(key))\%m$。初始探测位置$H=H(key)\%m$。$i$是冲突的次数，初始为$0$。在再散列法中，最多经过$m-1$次探测就会遍历表中所有位置，回到$H_0$位置。

**聚集**：同义和非同义关键字都堆积到一起。原因是选取不当的处理冲突的方法。对查找长度有直接的影响。

<span style="color:orange">注意：</span>在开放定址的情形下，不能随便物理删除表中的已有元素，因为若删除元素，则会截断其他具有相同散列地址的元素的查找地址。因此，要删除一个元素时，可给它做一个删除标记，进行逻辑删除。但这样做的副作用是:执行多次删除后，表面上看起来散列表很满，实际上有许多位置未利用，因此需要定期维护散列表，要把删除标记的元素物理删除。

#### 链地址法

又称为拉链法或链接法，是把相互发生冲突的同义词用一个单链表链接起来，若干组同义词可以组成若干个单链表。思想类似于邻接表的基本思想，且这种方法适合于冲突比较严重的情况。

指针需要额外的空间，故当结点规模较小时，开放定址法较为节省空间，而若将节省的指针空间用来扩大散列表的规模，可使装填因子变小，这又减少了开放定址法中的冲突，从而提高平均查找速度。

每次冲突都要重新哈希，计算时间增加。

#### 公共溢出区法

为所有冲突的关键字记录建立一个公共的溢出区来存放。在查找时，对给定关键字通过散列函数计算出散列地址后，先与基本表的相应位置进行比对，如果相等，则查找成功；如果不相等，则到溢出表进行顺序查找。如果相对于基本表而言，在有冲突的数据很少的情况下，公共溢出区的结构对查找性能来说还是非常高的。

### 散列查找

先通过散列函数计算目标元素存储地址，然后根据解决冲突的方法进行下一步的查询。

如果使用拉链法通过散列函数计算得到存储地址为空，则可以直接代表查找失败，这时候一般定义查找长度这里不算。

而如果使用开放地址法计算得到空位置的时候，代表查找失败，但是这时候需要定义查找长度要算这个地址。

若散列函数设计得足够好，散列查找时间复杂度可以达到$O(1)$，即不存在冲突。

散列表的查找效率取决于三个因素：散列函数、处理冲突的方法和装填因子。

**装填因子**=表中记录数÷散列表长度。装填因子代表一个散列表中的满余情况，越大则查找效率越低。

若只给出了装填因子$\alpha$，则此时平均查找长度为：$ASL=\dfrac{1}{2}(1+\dfrac{1}{1-\alpha})$。

[red-black]:data:image/png;base64,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
