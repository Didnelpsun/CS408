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

+ 若当前$low$和$high$有奇数个元素，则$mid$分割后左右两部分元素个数相等。
+ 若当前$low$和$high$有奇数个元素，则$mid$分割后左部分元素个数小于右部分一个。
+ 折半查找判定树一定是一个平衡二叉树。只有最下面一层不满，元素个数为$n$时树高与完全二叉树相等$h=\lceil\log_2(n+1)\rceil$。
+ 根据折半查找判定树可以计算对应的$ASL$：查找成功的$ASL$=($\sum\limits_{i=1}^n$第$i$层的成功结点数$\times i$)$\div$成功结点总数，查找失败的$ASL$=($\sum\limits_{i=1}^n$第$i$层的失败结点数$\times i$)$\div$失败结点总数。
+ 折半查找判定树也是一个二叉排序树，失败结点$=n+1$（成功结点的空链域节点数）。
+ 折半查找判定树的中序序列应该是一个有序序列。

$ASL$查找成功查找失败都一定小于折半查找树的树高，时间复杂度为$O(\log_2n)$。

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

遍历查找的时间复杂度是$O(\log_2n)$，则递归查找的时间复杂度是$O(\log_2n+1)$，其中$\log_2n+1$代表二叉树的高度。

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

为了限制树高增长过快，降低二叉排序树的可能性，规定插入时要保证平衡。

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

由于$TL$，$TR$与$T$一样是平衡二叉树，又由于我们知道T的最少节点数是$F(h)$，其中$h$为$T$的高度，因此如果我们知道$TL$，$TR$的高度就可以知道$FL$、$FR$的值了。

由平衡二叉树的定义可以知道，$TL$和$TR$的高度要么相同，要么相差$1$，而当$TL$与$TR$高度相同（即都等于$h-1$)时，我们算出来的$F(h)$并不能保证最小，两边都是$h-1$明显比只有一边$h-2$的节点数更多。

因此只有当$TL$与$TR$高度相差一，即一个高度为$h-1$，一个高度为$h-2$时，计算出来的$F(h)$才能最小。

此时我们假设$TL$比$TR$高度要高$1$，即$TL$高度为$h-1$，$TR$高度为$h-2$，则有$F1=F(h-1)$，$F2=F(h-2)$。

因此得到结论：$F(h)=F(h-1)+F(h-2)+1$。

+ 平衡二叉树最多结点数$2^n-1$。

即该二叉树为满二叉树。

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

为了维持二叉平衡树，需要反复对树整体进行插入合删除，代价巨大，所以引入为二叉排序树的红黑树：

1. 每个结点或是红色，或是黑色的。
2. 根结点是黑色的。
3. 叶结点（$n+1$个虚构的外部结点、$NULL$结点）都是黑色的，保证红黑树的内部结点左右孩子均非空。
4. 不存在两个相邻的红结点（即红结点的父结点和孩子结点均是黑色的）。
5. 对每个结点，从该结点到任一叶结点的简单路径上，所含黑结点的数量相同。

所以定义某结点出发到达一个叶结点的任一简单路径上的黑结点总数（**不含**该目的结点）称为该结点的黑高（记为$bh$），根结点的黑高就是红黑树的黑高。

可见，红黑树的"适度平衡"，由$AVL$树的"高度平衡"，降低到"任一结点左右子树的高
度，相差不超过两倍"，也降低了动态操作时调整的频率。对于一棵动态查找树，如果插入和删除操作比较少，查找操作比较多，采用$AVL$树比较合适，否则采用红黑树更合适。

#### 红黑树性质

+ 从根到叶结点的最长路径不大于最短路径的两倍。

由性质⑤，当从根到任一叶结点的简单路径最短时，这条路径必然全由黑结点构成（即第二层的结点）。由性质④，当某条路径最长时，这条路径必然是由黑结点和红结点相间构成的，此时红结点和黑结点的数量相同（非第二层的其他所有节点）。

+ 有$n$个内部结点的红黑树的高度$h\leqslant2\log2(n+1)$。

若红黑树的总高度为$h$，则根结点黑高$\geqslant\dfrac{h}{2}$，所以内部结点$n\geqslant2^{\frac{h}{2}-1}$（假设没有红结点），所以$h\leqslant2\log2(n+1)$。

#### 红黑树插入

红黑树的插入过程和二叉查找树的插入过程基本类似，不同之处在于，红黑树中插入新结点后需要进行调整（主要通过重新着色或旋转操作进行），以满足红黑树的性质。

+ 插入红黑树中的结点$z$初始着为红色。

假设新插入的结点初始着为黑色，那么这个结点质在的路径比其他路径多出一个黑结点（几乎每次插入都破坏性质⑤），调整起来也比较麻烦。如果插入的结点是红色的，此时所有路径上的黑结点数量不变，仅在出现连续两个红结点时才需要调整，而且这种调整也比较简单。

插入过程：

1. 用二叉查找树插入法插入，并将结点$z$着为红色。若结点$z$的父结点是黑色的，无须做任何调整，此时就是一棵标准的红照树。
2. 如果结点$z$是根结点，将$z$着为黑色（树的黑高增加一），结束。
3. 如果结点$z$不是根结点，并且$z$的父结点 $z.p$是红色的，则分为下面三种情况，区别在于$z$的叔结点$y$的颜色不同，因$z.p$是红色的，插入前的树是合法的，根据性质②和④，爷结点$z.p.p$必然存在且为黑色。性质④只在$z$和$z.p$之间被破坏了。

插入全为红，是根则变黑；父黑无变化，父红看叔叔；叔红只变色，叔父爷全变，爷爷变儿子，重新来一遍；叔黑看平衡，看谁最后转，谁转谁变色。

![红黑树插入][red-black]

#### 红黑树删除

红黑树的播入操作容易导致连续的两个红结点，破坏性质④。而删除操作容易造成子树照高的变化（删除黑结点会导致根结点到叶结点间的黑结点数量减少），破坏性质⑤。

删除过程也是先执行三叉查找树的删除方法。若待删结点有两个孩子，不能直接剧除，而要找到该结点的中序后继（或前驱〉填补，即右子树中最小的结点，然后转换为删除该后继结点。由于后继结点至多只有一个孩子，这样就转换为待删结点是叶结点或仅有一个孩了的情况。

最终，删除一个结点有以下两种情况∶

+ 待删结点没有孩子。
+ 待删结点只有右子树或左子树

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

[red-black]:data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAABWsAAALVCAIAAAA51SQ1AAAgAElEQVR4Aey9Ycwdx3mYez5HbfXDrQXDqJjGiESEsqTAjcnWiCU6gMgigUj7B6miCEngNpLyg6LuH5I/LigBzaWIBiUF/yAJBBClAiV1i0SUi4CkA4kU0FzJdSQyQApRuK5FWwxENSpEpYBNtcW1bPjqu8/HEVdH5/vOOXvOzuzO7j4HxMc9e3Zn3nnemdl533lndmFxcXHgRwISkIAEJCABCUhAAhKQgAQkIAEJTCRw08RfG/jxlesfMn7nnXeuXLlSSHDLLbd85Stf4etdd921adMmvhY/edBqApcuXTp9+vSHH374wQcfXLx4cbgs9913H19XrVq1detW/g7/5LEE+kZgat+4du1a+sabb765b2QsrwSyJcDTLTzXfvjDH169erWQkyfanXfeyVeaLQ+44rwHEpBA5wnQJ9AzUMz333+fMXBRXh7fX/va1/h6++230y1o6RRkPMiQwEImMQgMjp9//nla1PAjdgIvmtaWLVtsYBMQZf4THWjQ+HDvOUHmDRs2BI3TsU64zJ8k0DEC9IovvfRSyb6R8UfoG3WzdqwaWJwWEcAhXjTba9euTZUcO4Fme//99/NXD+BUXF4ggZYSwNI5c+YMncPw/OiEshTdglNoEyj5U1MEGvYg8KA9dOjQ008/XdJxsBzT9u3b9+/fT2DC8p88kyeBEydOHDhwoGQHurwIuBLQOH+X/+QZCXSGAIbHkSNHjh49WsYCWbHUDz30EC1Fj9uKcDwpgRQEGMk8+eSTx44dY2wzR/q4D3bt2rVv3z4NhjnoeYsE8iRAb0CfQM8wt6WDK4GnOfFKeRZQqfpJoEkPAi0KS3LuFjWsMB66tC4fusNMMjzG8/r444+XDDqYLD9TrAcPHrQ/nUzJX9tIIIw26Bvn9h0UpQ4GCX2jwZAFEw8kkIJAcPlhJMznOxgWiWaLE2HPnj0222EsHkugjQSYM2PcG8XSYcaUca+zAm2sBp2UuRkPApE8Dz/88Nyz0CtqgocuT1xa14q/erJZAqxZ2Lt3L3qPKwazrIcPH3aYFZeqqTVIAC8bLSVu30gDwSB57LHHGiyXWUugwwQiTocUlJgRwffH7EhxxgMJSKBFBBjx8jQP26DEEjvMCmDpcBArTdORwHwEGvAgEJpLo5pP3Kl3Edx+6tQpTcqpoOq8AKMIh1H1CdUVZWYBCxp3GcuKcDzZLgJPPPEEoQeJZGb64vjx4w47EuE12X4SIOKA8QwehETFx4OAl9xmmwivyUogEQH6BHqG6hFJK4p3zz33MO417HpFOJ6sjUCtHoTUz9pATZOyttpTJqOkDqMgAA4jOlN3RiijDq/JkwB9I162kydPJhWPVT+0FGMgk0I28f4QwC3+wAMPRI+tGwHovMgIEL9KIHMC+A4Y+iYVkuc4T3NX8iaFbOKTCdTnQajnWRtKq0k5Weu1/YpRxBqwerJjfpVFDfXkZS4SiEiAvnHjxo1xYx3HicesxdmzZx12jOPjeQmUJMBSI5pt3AVH47LGWnj55Zf1/Y3j43kJZEKAyQC8iufOnatBHkKTcCKwKVgNeZmFBJYTqM+DsHnz5noaVSgkToTz588b3L5c5bWdqcELO1IWOlN2rB056VcJ5EyAAQd2yIULF2oTkr7x9ddf1xqpDbgZdY8AXr9169bV4z4I9GiwNFsab/dgWiIJdIYA7gPW7dZWHJwI+BZZ1FBbjmYkgYLAZ4qjpAcYk3W6DygLD3h8FvxNWi4TH0eA0IPUQVzLs96xY0eUFz0sT9kzEkhE4NFHH63TfUApQt+I5yJRiUxWAp0ngJ1Qp/sAnmRHpp0HawEl0F4C7GRUp/sAUCHkIcqLHtqLXcmbIlCHB6ERYxKgPnGbqlVYRNhF9edOZ6rbqH7s5jg3AbxstS3zGRYSRxvutuEzHktAAiUJMCOSeu+DFSUJW7uv+JMnJSCBZgngO0i3EfKEouE+wLfolMAERP6UiMAv4TNLlHRIlsW9VO5f/OIXSXMZlzhOhJ/97Ge//du/Pe4Cz0cnQHdGVHZT0R/k+5d/+ZduiBBdrSYYnQD2QINmfIjWcf/R6Go1wW4TwOXH292bKiPeeZYzuI9JU/zNVwIrEuB5+ju/8ztNWTrvvvvuf/tv/801vCuqxpPpCCTfB+Hee++tOUZ3BBbLhNgQwSfuCJZ0X+vf/mB5WdwQYTkTz+RGgHXU9eyeOK7g9I1vv/22b4Qax8fzEhghwETf6tWrm40ZpsHSbGm8I7L5VQISaIoAE6U1r19YXlL2SdHSWY7FM+kIpF3FQItq1n0AOB75jUQWpdNZzinjiE33ZuzyBWeOyJiu8ri8sn4CzGQ26z6gyLSRJ598sv6ym6MEWkrg0KFDzboP4IYAiNFSgIotge4RIJywcfcBVJm96x5bS5QzgYQxCAxPCUBofJQc6BOG4G6lNVTEHByxoZiHDx/es2dPDUU2CwnMSoC+sfGZzCCzIVqz6s7re0sA051mm4Nv2uih3lZCC54hgcbDCQsmht8WKDyogUDCGATmojNxH8CxkY39atBfVlmg7hwcsYEJk6s5DPWyUpDCZEKAvrHxmcyAgjZiiFYmtUIxMieQzzOFZmv0UOa1RfF6QoBBbz6Wjk/zntS6TIqZMAbh7rvvDpt1ZVJUwxBSK4Jt4U6ePJk6l/LpP/XUU7t27Sp/vVdKoB4Cv/zLv5yJByGU97333nM3hHpUby4tJcAevTTbfLzShCHQbG+55ZaW8lRsCXSDQON7vY1gPHv27KZNm0ZO+lUCKQikikHAd5CV+wB2Z86cSUHQNAMBhlbnzp3LioYaz0odChMIsDVMVu4DpMondMhKIoE8CfB0y8d9AKIMH7h5Kk6pJJCOAI/yxvd6Gymd494RIH5NRyCVByHDIWmGIqXTa/0ps5dMU29wHFfYDEUaJ6rn+0Mgwwf8888/3x/+llQCcxDIsNlmKNIcYL1FAu0lkKFZkaFI7dWvkk8mkMqDkOGzLcOwiMm6adevGWrcWZp2VaGeSJvhAx5fW25hET2pDBazFQTyfJTkFhbRClUqpAQiEshw3JthWERE4CaVFYEkHoSYNXj9kbcWFz96cWcUahmO3aOUK4dEorGNqvEM+/cclKUMTRGI5Mfc+QK94sf/3jq8PkJporXfCLKYhATyIhApnC1ysyXoD8HyIqU0EugNgUgNMHK3AH7Hvb2pgw0XNIkHIdYOCPceeeujV3f/WjxEP/zhD+MlZkqfEKAnjTKHGV3jsariJ0X1SAIVCMSokOsPv/X04JGFzyzw7+tHL6/Z/WoED6t9YwWtemvHCWTbbGMI1nHdWTwJJCJw5cqVynujJHma2y0k0rjJjhBI4kGgXY1kM8/XnS++unvN2UcWdp2d5+4V74li5a6Ycs9PxgGrxntejXpQ/Bgt5bW9dyx885kA67W936J/3LylcpBWDMF6oD+L2EsC77//fuVyJ2m2MQSrXDITkEAvCcR4aCbpFmII1kuNWugZCSTxIMTZUe+ZbzDJdmOgPGOxxlxuuxoDpurpOGDVeFU9eH/uBOK0lOFSfv9Hfz24/KPvD5+a5zi+YPNI4T0SyJFA/NZhs81Rz8okgRkI2C3MAMtLu0ggiQchW794/AbfxToxR5niRJ3MkXGJW3KWrYT4XtIpAu+8807c8tz7u9/8tcFbb75WNVWbSVWC3t9dAtFbh822u5XFkvWFgN1CXzRtOccQuGnM+UqnszXUsxWsEu4Mbo4TdZKmIDnLlqbEppovgdi1cee/2r3mr48++PGahgrlji1YBVG8VQKZEYjdOmy2mSlYcSQwO4EPPvhg9psm3BGtWyAPuqxbbrllQmb+JIHqBJJ4EKqLZQrtIlB5O5mExc1ZtoTFNuksCUStjUubMG2+fPTreypHIAwGUQXLEr1CSWBeAlFbh812XjV4nwRyIpBttwCkqLLlBF1ZciKQZBXDqlWrcirjJ7JkK9gnIrbzKGewOcvWTm0r9fwEItbGsPHorjv2nJ9fnE/ujCjYJ4l6JIFOEIjYOmy2nagRFkICg1tvvTUWhbjdAlJF7LJildF0ukcgiQfhc5/7XJ6kjOpJpJfbb789UcrVk81ZtuqlM4V2EbjtttuiCMx7T48thR98o/r6hSCPzSSKXkykkwRitQ6bbSerh4XqJwG7hX7q3VIXBJJ4ELL1fmUrWKGPlh5kCzZbwVqqaMWuSCBKhcQOeXX34OjX79gbYfnCxwWKIlhFON4ugTwJRGkdNts8latUEpiPgN3CfNy8qzMEkngQ4njmdr740eIi/45t5n3nT18/frHiW8/jCNYZ5ccrSJSedJBA43EEiwfKlHpOIEaFXNpvaTBYs/vVpe7x439vHbm3GtkYglWTwLslkCuBGOHKSZptDMFyha5cEsibQIyHZpJuIYZgeaNXujwIJNlJMY6h/sw3PhMrQvcG61ghxDfS8/+PCbA8hD6r6qsuEmj8rrvuUkkSyIdAjAr5zDcXYveMg8Gdd96ZDyUlkUBWBLJttjEEy4q0wkigNQSwdG6++eZqexYmeZrbLbSmDrVc0FQxCGvXrs2QzPbt2zOUqhsibdq0KcOC3H///RlKpUi9JcCjPY6DNTbBrVu3xk7S9CTQEQIbNmzAVMitMIiEYLlJpTwS6AkBZs7uueeeDAvruDdDpXRSpCQeBEht2bIlN14M3PXMpVNKhhqnsNpF6TRuyvMRyLBOMgwy7nE+bXpXHwhgq2foIkekDP0afagPllECgUCG4178GjoWrZ/1EEjlQchwlJyhSPXouJ5cMhzN0I369o16tG8u5QlkOObIUKTyPL1SAjUQyLCNZChSDYowCwnkQyBDsyJDkfLRl5LEJZDKg8AqhtyCdX3cxq06I6llOEujxkd05NccCGTo2HJ5Vw4VQxlyJpDhuDxDkXLWoLJJIDoBzJzclmw77o2uZRMcRyCVB4H8HnnkkXG51n+eRm5gT2rsDz74YOosyqePR0O7qDwur6yTwEMPPVRndpPzwg7Jzds7WWB/lUD9BAhny8piRxgj7OqvBuYogRECWY17WY2Y4XqrEWJ+7QyBhcXFxUSFYYfS1atXV92fP5Jwp06dyurxH6lY2SWzefPmc+fO5SDWwYMHH3vssRwkUQYJjBC4du3a3XffnUnf+Prrr+c2izKCy68SyIHAlStXaLbVtl6PUw7842+++aaOvzg0TUUCFQjQIdx7770XL16skEa0W5977jlnzqLRNKFpBBLGIPCQO3z48DQB6vgdn5zugzpADwbY7fVkNDkXHLF79uyZfI2/SqApAkwe7tu3r6nch/OlY9R9MAzEYwmMI4DFvmvXrnG/1nkeMXQf1AncvCQwjgCWzv79+8f9Wud5HuW6D+oEbl4JYxAC3HXr1jXunHOSrc6K/vDDD584caLOHJfndfz48awCxZdL6JmeE2Digr7x0qVLDXJg6PP222/7FoYGVWDW7SJA3BDNttnoIRosQxqbbbtqjtJ2m8DGjRtfeeWVZsv48ssvu1i7WRX0LfeEMQgBZeNhCFiSTrLVWa0JQ2h2fSavptN9UKfGzWsOAjmEaBGnox0yh+68pbcEaC+NzzcigM22tzXQgudJAEuHZ3qDshF9oPugQf79zPqXnnjiiaQlJ9YOe/Kll15Kmsu4xDEm/8N/+A833XTTuAs8H53AZz/7WbA/++yz0VMukyBDKxyxyFDmYq+RQIME1qxZQ+7f/e53G5GB0ca///f/vpGszVQC7SXw1a9+9Z133mkqshLn+B/+4R+2l56SS6CTBBh5fvGLXzxz5kwjpbvrrrvOnj2rpdMI/D5nmtyDAFzsyR/+8Iff//73awZNk6ZRfeELX6g5X7Nrym2EDxiN05mqAgm0ggBm/BtvvFH/WgZaKI62ZudMWqEghZTAcgLsrPTnf/7n77777vKfkp5xRiQpXhOXQBUCBDt/8MEHFy5cqJLIHPcyR/u9731PS2cOdN5SkUDyfRCCfCz6ZZlQnU2LwTFDZJ64FQF5+9wEduzYcfLkyblvn+PGp556KpOdruYQ3lv6SYD3MrCTc51OBPrG8+fPu7arn/XNUkchwHsZaLZ1bojAjAjN1g0Uo6jPRCSQggCWDu8jq3lDBKbNfINjCm2a5lQCyfdBCBIwZuUtI7VNDpMdxqTug6nqT3oB2xnWuS6L1aG6D5Iq1MRTEGACgXfN1mYY0DeSne6DFKo0zf4QoMHSjmrb8YeMsBNq6yX6o0dLKoGIBIKlU+fjlWG27oOIGjSpmQjU5EFAJh5+eNBreKtiWAnvXnoz1YMUF9OZEgZSw1sVQ6+dekePFIhMUwIQwLXK5uo1uNtCJ+yAw1ongeoEmKKo5zVPGCT1ZFSdiSlIoOcEQqxQDW9VxKvIAFtLp+f1rdni17EPQlFCLD3a1c9+9rO/+Iu/KE7GPeBZy4qg2oId4grfydQwV7Bb2ErzF7/4RYoCBofRb//2b6dI3DQlUA8B+kaGAu+///5f/dVfJcoRDwUDDhpjovRNVgJ9I8Agnmb7X/7Lf0m3ColJF7dz6lu9srytJsCOhv/iX/wLnunslpKoINg4WDp1BjskKojJtppAfTEIBSbe9seKBgy/4kysA4LYCXNIkXIsCfuZDmMsTJcUnR2jKydn+lmpOllq1l4RlBi9B2Mo89hjj9EGawu67qR2LJQElhOgcbGcIcU7jGmtJEviZLE8X89IQAI5E+CZm2jlUbB0nAzIWfs9ka2mnRSX02THkSNHjjz55JNsJLb811nPYEnyOlZb1Kzcar7+xIkTBw4cYA+q6vkyocrGBzUEflcX1RQkMBMBukT6xqNHj0bpG/HfYYdE90rMVCIvlkDnCbCrIuOZY8eOMbapWFhcBhgJ+/bts9lWJOntEmiWAL0BfQI9Q5RdV7F0GPemmI1rlpK5t5RAYx6EwIshMk2L4fLcD11sSHwHtqi21L/Qn+JHmNs6Qtf0ofSkbSmyckpgDgLBIKFvnOPecIujjbnReaME5iOAf/zxxx+v8hIiXH484JwOmY+/d0kgQwJhVgBjp4ql45xZhprtuUgNexACfRrV6dOnz5w5c+7cuZKGJZsYbdu2jSGyD9qW1mBeePP888+j95KuWdZ9oXH20XCTi5ZqXLHnIFD0jbSUkoMPnKqhb3QCcw7g3iKB6gQYxtBgGdLwt2RqDGa2bNnCX5calSTmZRJoHYGiWyhp6TBh9uCDD2rptE7RPRE4Cw/CMGsa2MWLF9lt8cKFC5znL+Nm/AXE9eEsuO222xgW05wcHA9Da/UxrgQ+FOEv//Iv0fUPfvCDv/3bv123bt3nPvc5tHznnXeiejSu46DVWlb4igRoGvSNbNgW+kbGH7QUdif99V//9S984Qu0jltvvZUeUgukImdvl0BEAsGVQGDCBx98wMDmxz/+Mc2W9Gm2n//85zEPeMzZbCMCNykJtIJAsHQQ9bvf/S4j3rfffptH/K/8yq/8o3/0j+gcsHTwJPI0d4q0FdrsrZDZeRAKTdCcHn30UVbOc4ZWxJYk2pAFnK4e8EZGFjj80i/90mc/+1l6WLc56KqiLdfcBAiQZouE4GBlz2ecCNghu3fvJvh57jS9UQISSEqAkQzNFidCkYvL8QoUHkighwR4iD/77LM80EM8AoPe//W//hccsHSIOyDeVvdBD2tFu4rcwLsYygDCffDAAw/w0GVY/O1vf5tA93vvvXf46VsmEa9pF4G9e/fiPmBcxabxCwsLmzdvZlVLu4qgtBJIRIAukQ2ZVq9evWPHDnrCPXv2MGvxN3/zN6yNZIbz4Ycf5ic6TC5LJIDJSkACsxLANmArk1/+5V+mhdJOabbvvfceLZcD4okY5Nx9991hmmTWlL1eAhJoIwH6AabKeF5j1PBMx03AO5joFv7n//yfvEuOLVTpNNhLhQs2btzIBcG/0MaSKnP3CSzm9/nJT37CsgXQ85QN0oX3kBHVQyRCfvIqUVUCP/3pT8MM6qZNmzgmOd7RiLpZv6DGq8L1/pYTYGyBmyCsjmZdD8f0kMNl4isnw8Iu/rKzbGhEw9d4LAEJ1EmAZsvr3IpmS6scabbDFwQrwmZbp4LMSwJ1EqD54ykIpg3WDU2e/uHNN99cUQbe4cqQmAFwMEFZzvDcc8/ZP6zIypMNEhg0mPeKWeOeZxaaZsOYePiCwqSkIQ2f97jtBOgWcRygcXrM4S6SmkAny/njx4+3vYzKL4E5CNAEmJEIwwjaAg1huIGMJMhPWCnBj4DdstzRMHK9XyUggRQEsAqCQ5yHF4OZyc+v4P6b4GhIIaFpSkACtRHAZmFJAr0BH57mdA7MiZbJnWc6vQfug3AvvQT3OqlWBp3X1EMgLw/CZKNx8q/18DKXuAQYPwWnLJbS8pTV+HImnukDAaIZi3EDu4EwI1G+1Iw5guuNAUeImi5/r1dKQAJzE8AwCN5wRvwclB/r6/6bm7k3SiBPAmFJQnAOhg5h8hzAhFIQr0T8QphbJSnmCXiyM6s64RZ/kkANBDLyIJSJMsCkXDFCoQZSZhGdAN3iVG0W1zC/Gl0AE5RAbgRwFhSBjjgRGIXMJyHzHqFxMemBe46ec750vEsCEphKANugGN8zTzjf4D5MOQb3H81W999U7F4ggdwI8KglADC0Yqx9tkVk7Mo4NoqcIfFiU3kOyMuHexS2JjIHgVw8CHjr8dXxmeq2L2ateb7OUWBvyYQAvV7oZPGtThYJjU91NExOwV8lkDmBEeMhls2PP6J4oQmGjUONzKuB4rWLQIgdGA75idLECn+E7r921Qel7S0BhqnD2xyEMIFx2xxUp4SPkkFCWLSIn4JZB3KP5aeoLp4p9IRAFh4Ehrk8KXEflPTc89heceV8T3TWgWKWiTcZLmbhNmLvmeHzHkug7QSo20wjhKEAfzmOPg4guLrwIxDXULKbbTtY5ZdAOgI00uGNEg8ePEhDjpvdcDgS7r901khcsU1NAr0isHybg6nzoBH5kBedA9YTfgQ+PN/nXisRUSqT6gmB5j0IVHfqPV78mR6QOBFoNtyIK4HjnmirG8UMb9bAZzRTPzvsNuoGB0vRcwJMVzKNQEMIHSBzCEm7MhwHxd4KdJslN3PquY4svgRGCISNEkOzJYqYAczIBXG/6v6Ly9PUJBCFQMRtDqrLw8gBR0bxfKd3wj7CBVk9ZVOQwAQCDXsQ8NwzeuYxPF/sH+NvbieAJ7r7fwIyf6pCAK8BvVv5eJPhvHQiDNPwuL0EMOaLzZnpvup80gf7h26Tz6x7NLYXuJJLoDoBjPlijE7bmckDXjH3YfcfWev+q8jT2yUwHwFMFeIEw8IlnqEYLxG3OZhPpOG7MIVGFlNgJRl1OIzI44gEmvQgsJEBLZAl7lXsfxpzSGQ+H0RElCY1lUARbzJ3j4YTIcSeMJJLOmE7tSxeIIE5COAswACgy+JDHW7KEhgOf6AHZvpijrJ4iwR6QqDYl5Rmi+9v7udXRVzD7r+aPY8VJfd2CbSawHLLHPtlprjpmovPI54JWhwc18caS1He2Eo5C1wzH7OLQqAxD0LENQiFXaoTIUqdSJRIxXiTYakiVp7hZD2WQCICeLvopsLjPEQY5tBZsZabYVBYQskII3U8diK2JiuBRARotkzohflGmi2NJYdmiwzF6ifcfzbbRNo3WQlAAKd/ETAYnt11Bh9VVwFeAzquYs9Fegz6tOh7LVWX0xTaSKABDwJP5bAPIs0y1jQyUwRzx8a3UW2tk5lNp3CFVow3GS51WMBCRaoSwDKcoMcSSEGA+onvLDy/sdWZB8jt4Y2ESBX8CMhJTGasbjkFT9OUQA0EaKTDjYImnNuDJrj/GPbwYNX9V0OVMIteESDOiEFmYXgz1MRV1+onIwGPzL2FBz2dRgdK1KsKmWdh6/Yg8BgOQbxU5bhEigX2TQUGxy1Ol1IrQgbiDsIY4cX1SnSJuWVpnABThcMz/Jlb5oyNkDAMmPhL44rbWhtXhwJIoAwBmi0PrGCZEzSUudlAIx32dGTeyZTh7zUSaJAAzX84+D+3bQ6qk+FBz4TrcFQFx3XuxFS9CKaQD4FaPQh4zZmFxurjmZcCAV5DHGw8+20PKfDOkSa9Vdh6KmK8ybAYOhGGaXicCQE6ouA1Cx6uFu0yQIMtwrbpSwkdyi1iIhMVK0b3CDD3MLxRYotGEfgRdP91r0JaotoI0ILwFRZbFOFDx/vf7V0DRorM456YC14wURtzM+oAgfo8CPj2wnpCRqjpwNHmQy4uDkwHuWTK9FCJ4k2GBUDR2Gm4iqlgw+c9lkD9BIiEKkYhDW6UWL3gNKti1wbGUvoRqiM1hWwJ4CxgY0KeI3xwdrd0GK37L9sKpmDZEqDt0+RDzBF/cf23a5uD6mAZOeN/DI97OkAMKGYOuu09qQ7NFAKBmjwITMrh1aN91mDY0x5CYyAYSTU3RQD3QdJ4k+FyBScCHZ9OhGEsHtdJgEoYKjzPYEYh3XgAM7oaLpTtq84aZV6pCQyb3AxOmILrRg0fcf91o1CpK4Pp94rAyDYH+P1pNYxaewVhpLAMWvAdhClYhjGYUXgWnDwYoeTXYQJ1eBDw6IfFBbX59grzlfYwXFqP6yHAkCV0Q3RA9eQYttIkUx4M9eRoLhKAAF0NlTxsH9DVsH+iu4vACqZrbGLW/LYTYFjMCrjQbPnLcfeMB91/ba+lyh+dAEPTkW0O+KqLbYQzT3zcqYxn8CPw0b0ywsevBYHkHoRig8OaIwMZEIQ3PjAfWJTWgxoIYGBgydcTbzJcnKKmaeEMY/E4EQGMkJGNErtnhAyjowMvVom3eoHGcKE87hsBrAUGxzyeGBnznGLikUiEDkPQ/ddh5Vq0kgR4NNPSCz84TkM6AQeKU+mFPRdDb8lf5g9atKnT1NJ5QXUCaT0INNrwnG6krTIyoMYjAK6Ebo8SqteDWCnUH28yLLlOhGEaHiciQG+GX5KOhQ9B/nHGJmwAACAASURBVPRyiTLKMFnKHjpVys6ArLawsgxRKFK7CAy7wNj1gCn6dslfRdrhsuv+q0LSe9tFYGSbAx5evWr4UZQV/C9hRpbnPrEJjH9wTUZJ3ERaTSChB4HgXmobbv5mY4TCWJ/BbrdnCHOohYUBz3ilKXmwcGpeMtNUSc23fgI8NYvnKAe9tZ/p0od9KI7J6q+K5lieAPWzmH7Efm7w8VRe5hRXDrs+df+lIGyamRCgqhNlEJYpBWc3jn5NgIraIe4Ss67YGgnjrvNvrKhIrPO3p/IgZPWavayE6WqVooMmzIkum7672TLqRGiWfydzp3oXD06M58YreQ6QwzqO4YDwHKRSBgkEAgQe0mwZ5mJCUEuxKJqdzMhEL7r/MlGEYkQnQN12m4PoVJcnyJ6LWFWha6V3Zc9Ft5NYTqkPZ5J4EDKc9s8kIKKrVSo3vBh49G6MGl211dUqV0+5mLWgbocnJbEtvtdwOfawKV3YdQlQ4HLJ2HJKnqmTAM2WAW6YgeQvx9TSOgXIPy/df/nrSAlLEqC94yss4oxo8m5zUBJdxcuI5xqJ9XjqqaeM9ahItUW3R/YgMHYMu23xN7dxZD6T5C2qH2VEzTPEA290MPzQe5lSeI0EhgkwwuZNLsEwZkSCi93n4jCfkWPggKiw2cQ1wsev9RCg22dEW8TFMJzNbRxSD4eSuYy4/8RVkpuXZUKAhYRMWIb2zl+3OWhKL8P7TRCVgCKYvbPvbUodteUb04PAIDIsEqZJ11aAmTLKYaH+TALnf3GG8SYFNEaThFfRnelEKJh4MJUAEXrFoIT6Y+WZSqy4gBEDMQjBj4DzBd+ibpcCjgdJCRB3VuzxyUaJRp+Vpz3i/qMJ22zL0/PK+gnwjCYeMDxoGOARfcBj2kpbvyJGcmQAgCLCLDJ6YQzAUKq320WNwOnk12geBFpvWCfMxF3OpIi6oVrjrbRaV1QTnUUYseE2ytbXWFRLjJmK5fX2zhNgo8Ti4edOY1XUzTAiRADR07r0owpJ751KYGSjRDcJn0psxQuC+69YsaX7b0VKnmyQACEzuLfCtBAGqsvvG9TF5KzRFAFNxdZR+HoYBrh71GRobfw1jgehmOwleDV/CtRjKjRDW2cX51YWlnnm8SZF0XQiFCg8GEeAGcviaYdfzEfdOFAznS+o0tkyF8FjYqbbvVgCEwiE+a5gTljBJoCa9Sfdf7MS8/qkBEJLDwNOHAeM3t3mICnwiInz0McXGfySOn0igs0kqQgeBEbbrVtwTrUOMuPRzEQTLRKjsMkzjzcpkBb+Dh48xUkPJMDQBE956ArCbLlWbvRaMTxFjB9B70x0wn1LkP682HQjLJZhyqtvEFKXl2YbnKp6Z1KjNv1xBIa3OcD+xLlPtRx3sedzJsBzf3jPRRaaMfSy385ZZWVkq+pBoFq0dFFAYQYb316mohTXYGKFaZ9WxJsUYmMrtiVoopDZg3QEeHTR8Om7wpyGO/+lQx1SJra8mERiqQiryVLnaPrdI8DTh2hYbFqaLY4/JgDo2LtXzHxKhAlXbHGP+4/15/nIpiRdJTCyzUGwNhmxd7W8vSrXiFeIwYB7Lra3AlTyIFAVeJYzCm/pykO6pPB05NHYXhXWKTk9e5iwbeMCEMaaYZU76nbcWWe1ySovjBAqQGGEUJOtDLUpCI/z8E4TLX1w1IbLjAoC1ByaLY4DPsyNu1FiQaaGA9pp0Ww5QBc1ZGoWfSOAW394mwOGmnj5eV73jUMfysugiz686FVCoJMBJq1T/fweBNSP1lmS1OrHSWFVEh+lITG5+qLoEG/S6nYehqFMh6ruyeru3q/MexdPLFyHra7GrdYOjshha1BFtFqbqYUfngan/ep1Sg18XPoMAIb7TxUxDpTnZyLASAw/fhGhxiCTcHeD1GZi2N6LmcdlOQNhJsE77CYX7VLlnB4EVI6+8RF2w0FYWJUGSo2rvm2PNxkuV6FunQjDWDp8jI1aPKLwFTo6yUHXPDsYKYZgEBZGtTGsKQeMHZaBKjG8UaIh9DnommZbuP/oVHX/5aCUlsowEtDOo9nYopaqsrrYdCwsJg0dfrAujUCpTjV1CvN4ENBriCTs0jYYbAoYCqUTYXmdC/Em+IZbHW8yXK6gbgZAqnsYS8eO8RDh6wzrbrBUsVe74fHskpp4iLCynb4lDBrQl369Lul3jrLQJw9vlEhf3aWRxhxAMryFjrTYkIJFJbr/MtRRtiK5zUG2qslBMKwM+haCERgS8KF7YVTgIyAH1SyXYWYPAqNwlNpJ04tRC0XDB6aZMVxRGByApTPxJkXRCkeYToSCSWcO0Cn6DQ8h/nKslnNWbtBX8COgL3fIy1lZ6WQbcSdRDWy26WhXTxl94d8p3H/6Eaoj7XAK1Ba3OeiwfqMXjXVShDuF7gUbhHUu9DBOMETnXCXB2TwInQ//LqxlPV6hVgWvCl7ATnpVeJ7RMVE6x6lVOpGs7qWiFrHxuL2c085KO5OFYXBAkwx+H8YN+n0m4+rSr8w7FbHxzmm3S7PB/Ve4a2nCjvLbpcGk0lIZGFe7zUFSyB1OnPpDEDQrXBir8yGYlGMXT2Wi8QXkQCvnzp178sknryto0p8LFy58/vOf/9KXvjTpousmWbDNJl9W/68nTpx49tlnJ+f74x//+Ac/+MGXv/zlwvU17vr7778/BMOPuyDn81evXt2xY8dUCS9evPjRRx/9xm/8xk033TThYkYPNPIJF2T009Wrg4sXBxcuLIn0zjsnLlzYe/nyywxav/zlwW23LZ1kT5e1awc3YqiWzvhpCYFjx449+uijCEuQ1L59+4p9v1oivmIuEfjwww/pqHkeXblyhU6YTSuKtZEC6iSBxx9//NChQxQNM4NmW7w+sJOF7WqhaLZ0vzRbhhaMB2i2YflYV8trucoQwGTYuHEjdYOLMfy2bNlSmIJlbvcaCRQErl27dvr0aSy4V155hZN0MiyHmWqmFbd7kILAxx4ERmwPP/xwrAwYARB/Eiu1iOk88cQTBw4ciJUgcyYhZiFWgnWmw+h89erVsXIMaxxipZYkHRwHp08Pnn9+cL33mZ7Fhg2DbdsGW7fqSpjOqqkrrlzB9zl4443BpUtLIly8ePLatTODwe7rHgSc1QNW13/lK0tKxCXkJ3MCjDLRJt697353SdKrV09cuvT8YMAaqlW33z7gHx+8eyh006YlzfppJ4FLly4xY/HGG2/wDKIE2BjBwOA4+A4YGn7lK1/Bm4Bft51F7JHU6I5hPdpEjxQbnfIJ5cfxhyo5vu+++1AlCg3bpoZf/ds9Ath4oWkvrwx33HHHr/zKr1gZuqf0Gko0Uq8uX7787rvvhnztZGrgPyELPQgT4Ez5SQ9CAShrDwIuA+JrME7m+2Cu7NvH2Ha+u70rPgH8BSdPDs6cWbI2S34YyOJHuP/+pb9+siJw7dqSaw9t0kKvT1WVko5WuWWLDr5SrPK4iHA2po8wMPAglJSIxwpm57Zt24JnoeRdXlYDAQINcBy89NJL/C2ZHe4DtMksNKFhzhyWhNaKy0JlOHPmDK27pMBWhpKg+nyZ9aoF2g+rKeLOpfO8z2SRxogYYfO8WFrBgzCSfou+slw8FgfSYaiXY9lff31x06bFwSDCP9IhNT/NEqiu0FWrFp97rtlCmPvHBH7yk8X9+xdvvrlS89yzZ/G990SaMwECEllVVOVxw0STC18zUTG7HrBTehVtYj26xUkm2qwoRtj61MpQEaO3jxCwXo0Ayfbrxzsp6kGYoxPUg1BAy86DgHGyfXsly2RFvwNpkrKf+glgJeKwW1Epc5xcu3bx5ZfrL4Q5fkLg8OFFvDlz6G75LbfcsuSJ+OlPP0ncozwIsE414l4kzEywuj6PkvVRCrY0Y2flWOEDLHBgt6w+cuxEmakMuIGsDJ1QZkaFsF5lpIwSouhBKKzgmQ/0IBTI8vIgMFNNTMRySyPKGVI2GKFEzxLzkoMHq85Ur6h6/UExlVQ6rUTNE3+EXqHSSqjhwooz1cXDZeSAxy6jzBrkN4thAol2RiS6hNdwDGfkcf4Ezp49G3a4GGmbFb9aGfJXfVIJrVdJ8aZI/DMV27y3SyAvAizL3LhxcGMzp/iykTLpl178GV+AXqXIwnjeGPL44zOskC/Ph80U7r33410Yy9/llVUIBOYpmidbpdIwjxypIp33RiHAxldswH4kjS7Y9fnee+8ttuuLIrCJTCbASxZQaArmbIqBNk/SLfhpCQHa9ebNm1mjHl1eK0N0pC1K0HrVImUVoupBKFB40H4CjFkfeGDA3mxJP6RPLmnGx0kFb1nijFGw8JMOLtnUjSz0B9VTM/AE4Q8qv13iHFLt3TvgpUJJs5hDqj7dghmwbt268MKtROVmU0ayCPu9J8rCZAsCvB+XT/G+jOJ8rANS5sXSvNEzVoKmk4gAmuKVbXvpY5N9rAzJ0OabsPUqX91Mk0wPwjRC/t4WAidODFI+20YxkBc5+klEgPcsrFs3w9sW5hZDf9Dc6Ga6EafboUMz3THnxbRKghF0IsyJr9JtOA7qCRAIYQ7OXVfS1rSbGdkz20wAwrQLI/x+6NChBx54gBwjpGUSCQigGuJQiABKkPZokqEyjJ71excJWK9arVU9CK1Wn8LfIMDLqB999MaXuv4nx+svwa4rv97kQ/QBBmeCOMmxBPEHGYkwlk7lH2rGS6sk2MFPvQSIcscIxLavJ1uGnsyIGomQjjZ4y7+fr7oYvBgy6fx2dQn7nAJxInW2NStDTyqb9arVitaD0Gr1Kfx1AiyrxuCsf/qCHMk3xaLuPiu2KarYnAQ++IlOgDnM+pf84A8yLjq6KscniOOA+era3AdBEJwI+CxSrM8fX9C+/MI8cP0hHsQ7JNo+oy9qS1NO1phg0qdJe2yq1IR64l/GSuAPiQlYrxIDTp68HoTkiM0gLYFgcNY5Xz1cHvJNvbR7OLs+HLOOvZHIjlCR6ppB7YMml8qIKutcWzSMlUUTtY96h/Pv1THz1eyAUH+R2dGNWSxcCfVn3eEcMReb2piAMIQ6Ax86rMRYRaMy4E6KldpM6VAZ6gx8mEk2L65IwHpVEWAOt+tByEELylCBADOczU4dYyPVslK0AqP23ArJpFsnTiZBOAn+Cz+xCASnTIPWHd69pnyLsRi2IR1mCxkONiUpNkZT5m5TRU6ab3DKJM1icuK4hFJs9T85U39dkUCzlSEEGekfXFE1rT5pvWq1+grh9SAUKDxoIQFmjJ98snm5kcG56+pqwNQ8cKB6MpVSwBA6d65SCt5cEGAdQbMGPDWq/u1RiuL344CxYOMGPC4MXtDQD97JS8nEb7M2G2thnszhsZ6cdAsySPoajjLlz6F7KSOn18xEwHo1E65sL9aDkK1qFKwEAQzOZk2UICMyNG76lqCV+yUEIOSgTdfPR6koqDKH2BxcQtqWURQ6JhGMvWYNziDXAXvgMQqa6TSOmPq3P1guIQvgMR2Xn/dMnQSoDA3GFhUltTIUKLpxYL3qhh4phR6EzqiyfwXJxEQJ4DOxfttbC9BmJqY7BmdzIdntVeCo5GizwfULw9I0tRHDsAwdPWbvg0x2O8PU4V2SHcVcX7EyccTgk2KWsr5im9NKBDJ5NQaVofEop5XweG5OAtarOcHld5sehPx0okQlCRw9mouJgsAYS8jjZ24ChK1mYnBSBOcz59ZjuBEvTC1vDi8lJoalLqFSpGa+iJF9DgEIQe5MBqYzQ8zmhkzmBgMPXELIkw2b3gmSlUvuxIkTVoZuVEHrVTf0GEqhB6FL2uxZWXKzCnKTp13VocENFJeDYuTqfOZyLOXPPP98+WvruDI3eeooc/I8WK+e1bb52BiNvA8iOei6MjiamRP8eZttXapfnk9u8HOTZzkxz5QhkJsec5OnDMN8rtGDkI8ulGQWAmyb38TLwyaJiDxI5WcOApjrua16dfA6hx6LW7LyByEV3r18IlwKSi0/YDYpnwCEwDKHNfwt1SqqRKFZCa82m1KHlaEp8t3O13rVMf3qQeiYQntTnNxMlAA+T6nyrxQZmuu+kWHuapOhKw33gUElcyt0zI0vvfTSmF8aO52hSI2xmDFjXopJUMmMN6W9/MqVK0iVNg9TX4kAW4rk5hykMhhhtJKu2nTOetUmbZWQVQ9CCUhekiGBCIPXnYuffN4arI9RyAhSxRCjdWlkNve1xI9wEgev81WkPP1oGXqp5sObx10ZziYBBoMTSyMPQi2TIs9o3jNnzrSMYyfEzbMyGJPS9splvWq7Bkfk14MwAsSvLSFQdY+l9YO3nh48snD98/WFy2sWX30xQsmrShVBhPYlgaEeawnD+iNLTqEXd8aB4OB1Po4R/GjD3r3FxSj6NKhkPm2OuSvmbNL6I28tLn4UqdlmtTXDGHg5no6xhGHnC+jxxr8XYjTbGFLlSDtzmaI1oqhN2wijzKvNVPGi1Sty2vni9a4mwmPDejVVceMu0IMwjoznMyZATHLVeMvXBncsLDwTyvja4FtnB4PNEQwVpHK59awVJ9acIWbIq7tnzXzS9bH8GpPy6OJvVRU67N1bWDh6efB0jBAhtRm1rsWa6r/3yFsfvbr71+LJdlVFzw6TiJLK3NYfvu6U/8zCAv++fvTy5qffOlw5si9WNZsdSX/viFEZlujZtPtbh1Yqeax6dT3tnS88vfmvL19eKZ+Zz1Xu+mbOsTM36EHojCr7VJDoY8Tv/2gwuLzw/RgMo8sWQ6is04hCbOeLi7vXLAWV4AuK9alqCceSo23pVFXosHdvMNjzrcFgzeKXY0BQoTEohjTijLp2vvjq7jVnH1nYFa/ZvvPOO/FK2ZeUYmjztb13LHzzY6f84PwevPJrvlS52WJ15LY7Q+frRIzKsDRFHL1p605qdd2LU6+uI9j54tObzz7yey/E4WG9mpujHoS50XljcwSiWwK/+83B4K3BazFKFF22GEJlncb770cQ75lvLC1IuTF+jZAgSVS1hONI0bJUokNb/+vRCESXLZpk7Uvo/UjNlvnqwuyMQiHiODWKPK1IJD609b/+pUgljy9bJMG6mkwc4M98I3rTBngc2bqqubzLFU1364/8H5svH/3DmKO9aLLlrYLo0ulBiI7UBNMTqLqEYUTCnUvT10f/cOTsnF8jyzanFG26LVu7LlvBctZuZGjrB8/uHlw+Gsc3FFm2nNWQXLZsh1zZCpZcJRUyiA1t/eFnd/9apEF+bNkqYOrHrTkDz1m2ftSO+UsZSXdLfcvg6IN7o0z43ShNJNluJNeb//Ug9EbVXSpozL0Gri+6xkTZE6lDiilbl3Q2vizZ2nU6g8YrbewvcaAVOym+ujg4unDHnrHZzfRDHNlmyrKzF2cbW56tYDlXhUjQip0U2ZDm6Nfv2HM+Rpkd3MegOEMakSrDDDmWvzRn2cqXop9XxtHdzn/FurdvxRqu39BEHNlupNaf//Ug9EfXHSrpqlXRCvPiq4trzkYzURAromzRCpl3QjffnLd8Slc/gWfCW1KW/n7rS0vv1ziyvn4hzFECEpiFwDPfvL6N4tJmit/60quLi2/FaLY3+4CYRQdeK4HuEljaQPHsI9+IuYChu7BqKJkehBogm0VsArffHidFdu/ffHnh69+Ik1pIJZZsMWXKO61sfS6qco6KEx0aO1ywzd43f3cOWUZviS7baAY9+n57rjCzFSznyhEf2jPfYHfMX/vm795budirsn1AVC5angnErwzxypmzbPFK2c2UIuhu59bNvDXt6Y9fGctWnXw7FsNTGUG2biptSqn0IEwB5M85EogypMB9sHuw8PU74mygWGCKIluRWh8Obr0101LeckumguUsVgpoP4rz0qZBCtly1kVK2W7JFWa2gqXURtW0U0D7fyI1Wz0IVbU74/0pKsOMIoy9PGfZxgrtD9cJRNDd9e05l0KcbrwydjA4u2uBGOKqa5AjyNZLLetB6KXa215owhqrRjZe3z2Rt8QRall83jpSFUwEwaqK0L77c53MdEHKPHUJw7Ji21x/ZHHxxU+y5itTDS98+5Mzcx/p3Zsb3bIbb83V8afBuUxX009EgLYel/yLO4us1h/5v3av+esXvl19KwSnBwuo9RxEqAxpBGU9i5ZeGrR1pGq9qoNyvXnoQaiXt7nFInDXXdVSGlpoXSy5rr5hW1WpqpWppXdHset2vvixIyhEuS19GbJC5yMTRbD5sm71XRW5vbZn4egdhVtvkU3ZHlmIs9FpRcFarZTYwscZDu588aPFpZDUY9eb7fXjISt0LpmzdW3MVZqaboqgzdf2/N7RO4goDgr96NXdP3okwtxgBMFqQtidbOIwT9C04wjWHUW1rCTZqi9bwfJXsB6E/HWkhCsR2LJlpbNNn8tTqqapTMl/7dopF5T5mdXyo5/K21t87WtlcvaaUQL33DN6Ztbve+74lDKj7JtUXapZS9Hp6++JwvPTUanXY1Or7pIVR7BO627FwlXndn7PHUWAMQffjNFs10Z5OqxYYE+OJ1C9Mgxs2uPx9vaXCPVqiN31Dqfq84L04ko1JGD3D/UgdF/H3Szh1q05litPqXIkNSQTM8MbNgx9z+ZQbc6nivvvn+++tHfp3YvK96677sowvJwg5w15diZR4adIbEuWDWTbtm0pCmuakwncn2UfnmcVnUzSX4cJWK+GaXTgWA9CB5TYyyIwNZHb+nnkccJkvsqY4XgFO8Sg9/m0ieel4lYI8+U7+S79QZP5zP7r9u3bZ78p7R2bNm3y5X/zIc5QmxQEhc5XHO+qQiDDykC7tjJU0WkO91qvctBCRBn0IESEaVL1EsjNJMhNnnq1USm3/EyRQZYzcpUg13YzmylGCXGPKDDePfcoicjzelIZTihlKFJs6qnSI6IktyUDhJO4RDmVviemm2GEEaHmbqM4UWkt+NF61QIlzSKiHoRZaHltVgQefDArcQa5yZMXnYnSZBi+oT9oosam/Jib/yVDF9UUgi34GQMvqzE9s5RbbbYVKk5uUeIuYaigzKq35taUrAxVNZrH/darPPQQRwo9CHE4mkoDBFgy8NBDDeS7YpZI4hKGFcmUPLl/f8kL67gMOyS3NTJ1FDteHrt2ZbQGhCUVu3fHK5spfUJgf07NdteuXVl5ND7B1JIjAOazBoTog4fyeb63RIMRxdy3b5+VISJPkwoErFddqgl6ELqkzf6V5eDBLFZcY6IgiZ8qBDDaM3HBoM3Dh6sUxXuXWuW+fblwyMqdkQuUOHJgc2YSZ461w9g0Tqn6mgqqzMcllJWl0cMaQWWgdWdScCtDJoqoLob1qjrDfFLQg5CPLpRkdgLsdZfDQ04TZXbVrXBHJl4YtGkAwgrqmfHUnj1ZuIToIjKpVzPya8Xl2O1PPfVUDqIePHgwE19GDjTmlmHPnj05YGRThnzM17lhtv3GTNoU23NQLdsOU/kLAtarAkXbD/QgtF2DvZcf86BZe4/cNVGiVEO23W58GXNWk+dRqDaYSA4h7sxLo1M/yQiwrrXxHfiymtdKRrqOhDMJ5Th8+HA+IfR1cM8yj0wqQz5xMVlqqX1CWa/ap7MxEutBGAPG020hgHnw3HONGQnN5t4WHZWXE18MO/k3+EEAX+IYiz/+oGZdQrwSIocYpVg8c02HMIRm7b3GBchVM/PIxeQ/+97Pc2eke3hpX27brUUqWfuSabwyUBOsDO2rN9Mktl5NI9SO3/UgtENPSjmJAMOd48cnXZDuN/JtdLCVrmTNpMwr9/AHNfVh4y6jJePCR5tNvUYRT9CpU435FuNizDs1DM4G1zIwRamNEbGC4Aw6deoU6wgiplk+Kd739lyDj4DygvbjylAZmlrYYmXoai2zXnVDs3oQuqHH3peCt7U99ljdFMjRt8RFh85ahkZWheAJymNFd3SiTSZIkM7Zsw3ElZAv7gPDSerSPdvmN7JWGd/BE088UVcp+5IPFiNOhPrjSniVBvn6Qo2s6lmDleHs2bP1V8Ks4HdYGOtVB5SrB6EDSrQI1wlgdtZpzzNf3Yih2wdt1++acb46Xb1iMhNjvuYPziCDg+plztr1DRs21JmnU5TpaLO3Rf2xAOSITtMVypTnI9BIkFGDgTDzUfKuWQlYr2Ylltv1ehBy04jyVCBA9GM97+Ejl6bWTVTA06ZbwVubPwgTl3ly56vT1Q8MS9omcQH1fGievkm+HtSfzoVBf21OBExcpyg/jT/yN+I7attggqlm3AfsgBC5DCYXiQBBRrgIIyU2JZlQGWrrSaZI488pCVivUtJNnrYehOSIzaBWAqxjTxo1zT5/pO9q+dRKDVtU1jBkwbh9/fUs3juYGmmz6eMPOn8++WtTaJ4vv2zzbErVxJ+//PLLNSxn2L59+/nz55taq98U3vrzZcMzFJp6GTx6RJvotP4CmmN5ArRrKkPqNSZWhvIa6caV1qv26lEPQnt1p+RjCDCPga2SIoaZNEnZeZIx4OOfTu0PIn0Mzmbf/hCfWq4prl275KxJ0TBDiYl/Jn1cQn4aJcBc5fHjx9MtYOZ14sxXp0u/UXjZZU6kMeZ9uhd2kv7rr7+eLv3sgLZZIOICUFa6lSZWhjbXjvllt17Nz67RO/UgNIrfzBMRwJbA1Gf1dawNpcNabtJ0lWYilY1LNviDor8UED0SS1JDjMO4cvXzfIgR2L8/steGiBWcQTTPWO29n9qJV2piU5mujB6HHFYuPFb/prnxyLQxpTAtzDsv4nptmM0mzRqmtdvIPFuZQ2Vg3tjKkK2O2iiY9aqNWhssXv8wYxBResYNIdnc/vK4ilhMBkm5FbC8PG+//XZEFDT+8lnXfeXhw4urVi0OBnP+415S8NM4gfPnF+lY5tZjcSMKfeqpxkvTdwF+8pPFPXsWb745gkLph997r+88cy0/WxVEmV7mEUPcQa6l7Itc7733Husaqo8cMD4xQX9CJ+CntQSo3f4BoQAAIABJREFUDIyBrQytVWCmgluvMlXMSmIZg1C9AzSFvAkwOfnee0sTzgx9yk9RciXXcxf3koKfxgkQ/c6KAzQyd5g6OsWHiO8sxiC4cR7tFoBgBAJA0AVj0PlWkRB3wMLpN99c2tPUXTBzrQ3sjUfYM8b/3H4EQqZZFoHL23XyjSuZDRHYW/HNN99EF/NNQRN3gNmJNtFp6hX1jePqtgBUBqYerQzd1nL9pbNe1c987hxvmvtOb5RAmwgQDB/2L7h4cXD69JLkb7wxuHbtuXff/d8vX/4/b7tt7+rVS5bMV76y9BMx86zZ9pMhgaDHq1eXlPjSSx+rckjOa4PBLUNflw5ZsLBtmzodoZLFVyx/7H/+FdpEs0OfFbRJI6V53n//0t/aXu4wJJKHcxDA4ORz5cqV06dPnzlz5pVXXpmaCB6Hbdu28TqAdIuup8rgBSsSQCO4hD788MNz586hTXR67RotddIHqwBV3n///fyddJ2/tY1AURmoBi+99JKVoW0KzFRe61Wmivm0WAsEJnz6jN8k0BcCDIAY0Pz85z+nFTAlQlxlX0remXIycsUl9OGHgwsXrn344R1Hjvz45z//89/7vQ2EG+A4wEDln1tXtEjdFy4saROdXru26zvfefr113/nV3/1O//yX9782c9+vAXj3BEoLYLQdVGvXr166dIlzM6LFy/y94/+6I8++uij3//93//iF7/IwBFrkzULfLqOoTvlCy6hoE3mpf/rf/2vd9999z//5//8C1/4Ap4gohXYIa87pbUkEwmEynDhwgV8TP/u3/27v/mbv6EObNmyhZATK8NEcv44iUBRr6ha/+k//SfWQN12222/9Vu/9dWvftV6NQlc0t9WWtrgOQl0n0B4lzhPtZMnT4bRKis8u1/sjpaQsFieInSVjFb5MIrtaEH7UqywZ80/+Af/AJ2ysY5LpjupeJpt6Hv/zt/5OzRbdzpou5bDwvjPf/7zNFu8Bjbbtiu0ivyhMoQ+nBCkn/70p1VS896eE2B/BEYF+JfpWz73uc/943/8jzngw8DP8V5TdePjnRSbyt58JdAIAXocBqwMXhnCIgB9U7A/WbXroKcRjVTJtLBDeM0bx0xj8lxhw/YqaXpvgwTCZvvBAgk7t6HT0FQblMqs4xJgBTU9cPD3sVdCGBrShOPmYmr1EMA+DBYjz1COQ7NFv2i2HgHMJR8CRWUgxpMBVVi6okcpHwW1SxLeJhv6FsZ1jATYioUKRhEYtxM4HLZT4fFBHLGj95o1qwehZuBm1zwB3Af0RIX7IAhElxSec7gStFWaV1JpCQr3QeGH5inCrDUqdt6jNMWMLhy2Q4JYjAzQJgMFrZGM9FRNFFSJQnEfEAsWUqIhBzcuFaBa2t5dNwGenjgOaKTBfRCyZ6CPfvkYWlK3PhrNr6gMww05LBEdGXQ1KqaZt4AAg7piARTj8+JhMSw64z1GCMEBzTOFmoZnYfgCj9MR0IOQjq0p50gguA/GTWmG5xydkbZKjspbJhNqCk+Own0QLmEQEwxR5z2WMcv6xHL3QRD31KlTwRrhIOsCKFwJAsvdB+EmxoKFIepsUgmQWVyyosUYJGPyMPTPPFizkFUhEhOYUBnwKAVHMLUisRQm324CwwsWglOgzKweg8Dgg6aaMZBwDF9DJdCDUANks8iFQFhcTS8zYXhaPOdW9HfmUhLlWFws7JBxc1whGJ55D+KlBZY5gcLpMy5ypPAWMeGQeVkUbwIB7AcGhXxefvnl5ZcV1cBYsOVwMjxTOH0Ysq8oXrFCMAS0r3iNJ7tBoKgM4xxGjKlo+IaldEPdKUoxvGCBkRuj8Qlj9RUFoI4FN3QIiXIYvyKlWCf1IMQiaTq5EyjjPghlCM85OiD6r9xL1Vf5CvfB5CcEbmnGK+PMlb7Cy67cE2auhmUtAt3d9HQYS4uOaa2hPU6eIGI3BLpfY8Ey1yyD+zDpN7k90rpxC6JQQv905mau07nFKyoDA60JidDwsQypDO54MoFSD39iqFYsWMAFMHlcN5UP1SzEM1LT6KNGYlSn3u4FJQnoQSgJysvaTSBMR5ff1L14zo3zprcbR8ulD3YIpkiZxwxTnWHew6dInmov6T4IwhfTXAwyZp2dyLP4/ZGqpPsgACGwiAbOx3UredaQkhZjIXyxm0mZTru4y4NWEJipMhRhKdh4dP6tKKBCJiJAZcCXFNY6MU7DF1lmwUJJYUickT/J4kcgC7ogxwwl0ZW8TA9CSVBe1mICwRmJyTHT46p4zhF+OdONLSbVBtELO6T8csqw6ztPER4nbShij2TkiR62vZxJNaFFG+jeoooSPAIzLSkK6x1otq5byU3RRTTQ5AnnEbGDM1eFjmBp+9eiMpSP2Sy8xuUnddpOSflHCIQwAXzEdAg8F9KZ94wxSDxEvuBNYFKQsf2IMH6dj4AehPm4eVdrCMznPgjF4zlXvKDBTicHlYcd9XgM8PiZSR6eIiFGznmPmbglvRilhCjomeyQIJKB7klVEzdxwn/CMHHW+SWuJ/SdeyfHyceV1tQmE0ApYTg+h2cHZ25Q6LjtTiZn7a+5ESgqwxwhfjRqmva4ba1zK6nyxCKAN3l4wUJtUWZU0TDeoNYxDpx1DBmr+F1KRw9Cl7RpWT5FAPs/LL+saDTiswzDX3ucT/Gt/UuwQ+ZwHwRJi/rgvEftqlshwyrug5Ccge4rYM3v1Nzug1AU6kmIUnHdSg66rWIxFgot/PKklkOhlGE+AtUrA04oBlc808tHFM4nqnc1ToBJuGLBAqEH+I8a2RWFSCgeJdQ6Phy4qKpKxdCDUIWe9+ZLoAiTw31QXUpf0FCdYcUUKtohRe5hRwznPQogjRww9AxTkai1igAGulehV8O9IVSEmR8cAXNnR2dON86Az3UrczOMciM+9LBiuWKzRRjCjlAoqWk6RlFN/YmEyoApWNEGC3GFpINHuP5SmGMNBKgqdOA1LFgoXxacF+GZQi/EUKR6h1Y+6y5dqQehS9q0LB8TiOs+CInymMRTTndjX1N/PQszFYTORpmzQoM8zJz3qF+PIcfqM1fDkhfOCAPdh7HkcBysxIrug6IgrlspUDRygBlAnxnR0itMx/Lr5xspuJkuJ1BUhorug5BycEYwuKKNL8/LM+0lMLxggVCy3JxEhEUMb7VI9avi6W6vmuaWXA/C3Oi8MVMCdAFhkdUci6snF4nnXFj/OdOub5PT9NepBIIdEjdqoHhBQ26PtKk02n5BcB9gh0T0xBnonmGtCM2WrjjimIzWSs3hU9vS2QzBNiJSXIuxKELxSMX9h9+/OO9BzgRCZcCdFMV9EErKcyGsUWdm2JqQs/bLyDayYAGdNrJgoYyoXMMTijmq4a0WqY0l7+35ZXoQel4BulZ8+oLwHIruPgik6BlD+m4EVU/VCXZIrGnMYZl5pIVnhvMew1iSHieyQ5DZQPekips18RAgOuvrb8rk4rqVMpTiXoOhGBw3ES3GQsLC/ef2NAWTnA9CZcB9QGceV05qQligbk2IC7bO1KgVdP50F0SUML5q16w+sxpheI/wlCJ6Da9TEfXkpQehHs7mUgeB1O6DUAZslbARVNzptToAtS2PsIdlCvdBIEGFCeEqPC2c90hdO9K5DwrJGa/w7Gdxtc/+gkn9B7QmtJDCfRDK4rqVOnVaWIxJNyxwu+I6dTp3XkVlSNfBEo1C7xE35HDu8npjeQIEiIUtb1Efw6r2RncOb7VIiVK4TctTzfxKPQiZK0jxyhII0dF0XhGjoyfkXYx4co7OmiB//j8FOyT1dASOg/DCjtQZ5Q88qYRh6piZKx7PSTMKge5xI2yTCtylxItIkNQhWsXENc5cfX/pqlDYqiDFhPNymdkNIUQ6tNf2WF6oLp0JlYGJ5XTug4ArbHukI7gVlYeuGMd9COek/XZm6t6tFstUPz0IZSh5Te4EanYfBBzFCxpSG0W5008gX+ppzBGRgz/IeY8RLLG+1jBzNSxqEejuDm3DWFIfY8mHIGQab+q8SL/w/RGjxOKyGnLsWxb44vHI1+M+CGxpueFdD4kWIfZNgxHLGyoDhmI9S8SLXTbd8SSiEuMmFWzssGCBZosfoXv9MCVyq8UJ1UYPwgQ4/tQOAmFBOx1ZPdEHw1AwjRhgNZL1sBhdOsYwCItE0kVBr4ir8AclDdZdMetun6zZfRBgFoHu+Ia6jTeT0tXsPihKHV7OWsO8aJFjTw5qthgLqgzZw8oyngJMbxbnPWiQQCOVgUiH4E4iJKHBspv1cgKdWbCwvGgrnqEjcqvFFcnoQVgRiydbQ4DHTLDhm1qthAAhgssXNFSvNMN2CMfVE5wphcIfZBjtTNwmXBzWFNBA6l/sY6D7BL3E/alA3UgfiHmDD5enQFOPgLgwc0gthJHXNuE8UmR6/rCyjKCw+vuNEWH8GipDI5E+OILDzna+qTeHekg/XyxYIDqJWLO+TbcwngkVMhQ/9XKeHJQ+WQY9CJP5+GvWBBp3HwQ6TJuEboUutX67N2sNzSLcsPtglvtiXlv4g3hSxky3l2k1MnM1TJoaRZPkYd/I8HdYkg4fM6wMvV+Dkefh5awo2nUr1WtaeP1N40u6guGKY8hFgtV1OncK6d6FVFIkupewNoq/HJe8y8viEhhZsECt6N6ChfLE6JFCnCxPnJ5vtagHoXy18cq8CITVzpmMMLBVQp/ihnzz1ZLCDsHkmy+FWHfpD4pCsnH3QVEKnEE86ZlQdcagYBLroGi2DboPQlnCWjYU7bqVKspt3GIcFr5wDOFNGD7vcT0E8qkM4QUNeCrr2YWhHrytyGVkwQKP9VaIXYOQw14V/K39JKMHoYaaZhbxCTSyuHpqMdyQbyqiFS8o7JBGoqCXi1T4g5z3WA6nzJlgtOcz8x8WUxjoXkZ35a8pNpvIZOafbqRYQk8TLl8QrwwECjsNkpkwKeLYU7/dI5Py5iNGqAz5PAFDTIovaKinhtADABy3Oz5ZPrS+vi1YKMmZCSdGrQwtoBS2k8yn8yxZhCqX6UGoQs97myGQp/sgsHBDvlnrRDHn3/g05ojkwR/kvMcIlqlf85m5GhY1hCzxmM/E3B2WrY3HmHZhfJnV3AuOg7CEPh/vVVuUG9b7ZBhDx4g8xPep09rqUqgMuA+y8sT5goYaKgBT6ziP2FkmmMSYx31esFASOM2kcLiAjqFjT4Jl9CCUrCFelguBBvdmK4nADflKguKywg7JzX0QihD8Qc57lFdonu6DID+VjWhDBkYGupdX6IpXFs02K/dBISqjXrTsupUCyNSDPC3GYbFDx0JX7FzoMJYUxzlXBlaiUQdo3RhsKcre5zRx0OAzgi0fvHX07Vn5j1qhmuGtFvFld37hpB6EVlRLhfyYAJ0avRtDQ4awOUNxQ74y2sncDglFKPxBvph6qk6LwNdsRx7MZzLLSh/CrGa2Qk7l3OwFYRDPTAtNo1lJJuTOkwIJXbcyAVH4iVYQZvhzm3BeLjk9MApFrYYRLYcT5UxRGXAiREkwRSIMG7Bv6cN53KRIv29pumAhusZHtlrs8NBRD0L0ymOCqQi0xX0Qyl8E5/Mw1lZZXicKJwtqXf5rVmcKUZ33mKCXnGeuhsWmMQZRDYoexlLymLYQrLic3QehLMU+fBqc45RLWwizjm15SBVdsdbjOJ3OfX64MsydSD03YvSGestfjuvJtHu5DC9YoFcndCvzmbl2qWD5VovdMwT0ILSrTvZX2mJvthY9MOgvfEHDilW2sEPydx8E+Qt/kCPXFRUabPIWTez7goYV9Tj5ZGi2LZrYZwxHwBrTla5bWa7ZFlmMw8IzAAhhRBlu2TAsZ7uOi8rQogccotK0cQRr985a2YYXLIT3CHTPuJ2VSaLrGTp2eKtFPQiJqo3JxiSQ8+LqqeX0OTeCqHAf5D+NOSx54Q9y3mMESzGNOXw+/2Nf0DCTjmitYV0A7XemG5u9GIPTFzQsVwFYQig4vr/lv+Z/Jmxz61YXUTRVVIY8dyOaUEaiAnEiuFHRBETDP6FoiAWnKtxYqE+g1vAFHiciwOixIM9jtDNbLepBSFRhTDYageA+YBRI9xct0XoT8jlX8MYOaUsUdCHz8EEYuTrvEZgUM1cttUPCCxp4orclFma4KtZ53FL3QVFLwwsaWv0Qiaju9lqMwxBos7RcPh1eZjxc3kTHba8MaJ860KLAqER6nJwsYRpMZQEKxwGsOmPBTi51hr8ybxE82sGD0y53/HKeehCWM/FMRgRCdDSTnG0PsgrPuZ4Pdwo7pNWeb/1BoYNg6BmiDxiOZNRlzCgKQ6vwggZCDWe8tS+Xh76r7fO9wfdHKVja0BfNrVTOYkFW6yacl5cGD2DYmb8DZVleuhrOFJWBh1oN2SXKAjMsVAN3PFlOmEFXeExjsvKkA1Hbx9LLy9i6M53ZalEPQuvqXo8E7oz7IOiseM61+mk9d/0r3Adtd7tCQH9Q22euhqsxZQkrq5mpdnQ1TIZjZnoZemJ4d2CxMaPnMAXXag/miIJm+ooSUSUQOmNyYwMXq1RoyDPR6PnFRWXoQAQWZQmrclrtzo5YIWkLdHehsdPe2aKIAVjE9E2qOgEqLTZOCAxp6W4UehCqVwNTiE+AcXxwH3RsTF8851q0X1EU7QY7hPC5DrgPApA++4O65D4I2iw6HAPdh9t7l9wHoVwMo8Mqqg5YTcOaKnPcJYtxuLw03rDZEKNwyjj8k8fjCHSvMvBUCpPtLdrQd5x2qpxHszQHerngLXXBQhWYNdyLDxR/btAXoTTs8dwiT6gehBpqiFnMRoABQXgS4ESY7c42XF085yhji3qKKmgLO6Rj8cM8qsO8R6/8QUWpuxcyWrygoWMVdb7GG1brUMMZ4syXQp534fsLU3O9WrdSlLqrrpNQXRmI23intrtQGTq5pjL4krrXa03VabggTLzhO6CL4wHdkxFmSTg5X4bVU8SM0DDZLiFnaQvZFjiitvmRQD0ELly48OGHH07O69/+23/7J3/yJxjY+/btm3wlE4YhBGjyZfX/+sorr0zOlOHOd77znX/2z/7ZH/zBH0y+kl9DiPXUy/K84NixY48++ijPMyKHw8A9Tznnk+ratWs7duw4d+4c1TUsbZgvnbbcdeXKlY0bN/IXO6QYrLRF+DJynjx58uGHHw5j61a3uzKFnXDNE088ceDAAQbiNNswPTLh4tb9dPXq1c2bN1+8eJEYN2pyng+RiFQpKc2WJy+D1E4120uXBqdPDxhR/PCHg6tXX7l27cDFi/vXrNnwxS8O2DTua19bYrhhw9I/PzcIFJWBB1aYqrnxS0f+P3LkyN69exlsUMDg4u9IwZYX4+rVpfrP33feGVy5wu8PfO97g7/39x5Zs2bT5z8/uO++pTvWrmUNw9KBnzwJXLu2pETU9/77g0uXTv7t3z771lv3876Gf/pPl+RFfZ/7HDtYLCnx+kaYWRVCD0JW6ui+MKtXr8b8iFXOIhIvVoKx0llYWIiVFOnk6eZDjydOnJhazCeffJIB+oMPPjjZDuF5n+fQlvHWafr3iZ8XXnjhr/7qr+6///5il91xlzOgIcZy3K/NnmfghUNksgwvvfQSTsAtW7ZMHZmhTXQ6ObVGfsU2npzvu++++8d//MdU10ceeWTylfxKjOjkij01hZovKFOfMTVptkRU0mwnW9fZNlt8uJPduL/4xS/+9E//9NKlS9u2bQtbaU5QRM7Ndmp9plzPP//85cuXKemaNWsmFJOf2lGfcRycPEmpGHBPLs7Hv65atTT+3rat866EPlQGHlI8qibrnXZN66a2U+cnX8mvZaBNTaTWCxhCMyah/l+4UCpfVjRQ/++/P08rtFQRundR8P6cOTM4d65U4XAfbNo02LJlSYnXl6iUuiv1RUU0ggcSqIFAXKMCD0INMs+RRdxmO4cANdzC5GTEYjLfW4PMc2QRlmDEKil29Rwy1HNL3LaZ7WZ1sVQZ0sm2CxpXZ+LW52ybLStLIyo652YbsZgklXt9PnVq8a67iJud89+qVYu8dOCnPx3XOtp+vg+VgSoat5htUvrrry8yUpq7/t988yKvHHLD0WZVjtmydev8SkT7u3Yt5rG08DNxm6KpSUACEpCABCQgAQlIIBoBFgZu3Dh44IGycQcrZsy83969g7vvHpSInlsxAU9KoBkCxB1Q+detG0xbITtJPNb7HDo0WL16QBDHtNXEk9Lxt/kI0P88+ugS/2lhrVOSP3ZsKZHHHx9MCxqdkk7ln/UgVEZoAhKQgAQkIAEJSEAC0Qkw7MZ2wn1QxXYalgpj7OGHl4yxkkHgw/d6LIGaCWDqRzE7C7ExO4MfrWT8fHGjB1UIYPBj9mP8R/kMO4OiJDhXInoQ5sLmTRKQgAQkIAEJSEAC6QhcvDi4996qU3YrikfKeCXYT8GPBLIlgPuMWhrL7BwuJn60zZuXQhL8pCaAywYfKKijx30EZxAOpugpl2OiB6EcJ6+SgAQkIAEJSEACEqiHALG+uA8wdRJ9GHbv2LEUDOxHAhkSCO6zpJEyVH6aQEP2Z4bI44tE94UPqOKyhcli4WDCGdTEigY9CJM1468SkIAEJCABCUhAAjUSYMqOibsabJvaMqoRnlm1ngBLDJK6zwpAhOGQURP2ZyFCZw/wAbFair+pP6zwIqN0ztYx8utBGAPG0xKQgAQkIAEJSEACNRPAqqkzNIAZQlaG+5FAJgSIO6jHfRbKi4nLJHYN3rpM8NYjRog+qM01U3N21xnqQainKpmLBCQgAQlIQAISkMBEAphP7HRY84dIYDao9yOBxgmw90H9KwtodDrRIqoedww+oNrcB0FynAjUnBo/ehBqhG1WEpCABCQgAQlIQAIrEmjEfAqSEPUQ63UPKxbNkxKYSiBYnrWHoy/JpRNtqnbKX4AlX8PiheXysPilRk+QHoTlGvCMBCQgAQlIQAISkEC9BJi4a8R8opTBeMOF4UcCTRFgX/2kWydOLhfGp060yYjK/PrEE2m3TpwsA7FUJ05MviTWr3oQYpE0HQlIQAISkIAEJCCBuQgw8G3QfEJkoo7r3H9hLkje1FkCzFrXZfuNZVjjDPZYGVr9Ay7IJ59suAR0YrXsaqEHoWFFm70EJCABCUhAAhLoNQGGvDlY75hwjYQf91r3Fv46gRzqP5U/6asHO6/qAwfqsd4ngcSLUcuuLnoQJmnB3yQgAQlIQAISkIAE0hJgyJvJCoIcDLm0rE09PwLY7Sxiz+FT1wx2DmWNLAP+F7aTyOGDIyN9d6oHIQdVK4MEJCABCUhAAhLoJQEGuwx5M/lgyDkNm4kueiIGATj51P9Ll3Ixg1un/Xycj9So9Isp9CC0roYqsAQkIAEJSEACEugKgZMnmw/9HWb57LPD3zyWQFoCbP+R1dqZp59OW95Ops4WsJlEkQS8REMk3g1BD0InK7KFkoAEJCABCUhAAm0gcOZMXlJiCSQefOdVXqVplkBu9Z8whKZeidKsIqrknlvgEj1YYo+GHoQq9cV7JSABCUhAAhKQgATmJcAbEHJ7h1z6wfe8sLyviwRyMz5hTFiQn5kI5OYGQvjEIulBmKmCeLEEJCABCUhAAhKQQCQCGZpPlCzx4DsSO5NpPwHWL2Q44W/9n6lmZegGRX5jEGZSohdLQAISkIAEJCABCbSDwEsvRZNz54uLS58XIySYePAdQUKT6AaBOB60nddr/o0/OyujYWuGDP0alYuVKoEoSjzy1g393fi/oh7ZoTZleJcxCKmqk+lKQAISkIAEJCABCUwiwKLrOJ+di09vHly+HCcxBt/MK/qRQGoC77xTOYf1g7eeHjyy8PHn6OXB028N1ldOVQ9CeYSxWF0+ekOL1/9/prwEY66MJdhKyetBWImK5yQgAQlIQAISkIAEUhOI9d7yF58enH1k4YV44sYSLJ5EptRBAhFsvNcGdywsFNbmnm8NBmsWv1wZVQTBKsvQlgQiuIHSFDWlEvUgpNGZqUpAAhKQgAQkIAEJTCYQxVBff2Rx8+WFPyysqMlZlvs1imDlsvKq/hKIXs3W/3ocmNEFiyNWlqlky+r999Px0oOQjq0pS0ACEpCABCQgAQmMIRBnimz94Nndg6MPDl4bk8t8p+PINl/e3tUbApEXy1xvCwTDV3emffBBb3RQuaCxlLhm940tEBYXj6yvLNYg6VIsPQgRFGQSEpCABCQgAQlIQAKzEYgyd7fzXy2uObuwJ67/YDCIIttsOLy6fwTiVLNiJ8VXFwdHF+7YE4FjHMEiCNKCJKKw2sNalBufR84Odr8awYkQRbAxCtCDMAaMpyUgAQlIQAISkIAE0hG4+ebKaV/fQPGRb1ROZ1kCEWRblqYnJJCEwDM3TM+FhW99aWkeO8oMdhJRTbQEgWe+sXB2MPjm75a4tLFL9CA0ht6MJSABCUhAAhKQQH8J3HJL1bLv3LqUwtM3gn93rxkMNsexoKrLVrVs3t8DAqtWRS5kLOMzumCRy5lTcilY/ejyYM2XqhYyhWA3ZNKDcIOE/0tAAhKQgAQkIAEJ1Ebg9turZoW9NPzhVXaDs0snqi9qqC5b1bJ5fw8IpLDxMD6rf269tXoafUkhhRK/tGZw+UdVAaYQ7IZMehBukPB/CUhAAhKQgAQkIIE6CaQc41YqR7aCVSqVN2dGoHqoCy8iWXzxk1LxlUicF779yZn5jqz/5blVV+Jg/eCtt/jz8Wfni4ubB4NvVd7PIqUb6KYbwvq/BCQgAQlIQAISkIAEaiSAoZJyu6/5S6IFNT877yxNoHqoy2t7Fo6+xcqdT7J8ZCHCuxis/58AnXZ0223Trpj6+2uDFwaL7IP58efywtcXIrxcJqUSjUG4oSz/l4AEJCABCUhAAhKok8Bdd8XMbWk/8xi7KjLyjjCvGLNkptVNAnfeGaFcw9v4s4Sn+qsckSluw4xQyIyTiMLqU0q8I4L7ILFg6gi6AAAgAElEQVQS9SBkXCMVTQISkIAEJCABCXSYwJYtORZu6/UNGnOUTJm6RSDPmrZhwyDl9HW3VDgYbNo0yPDVLWjwnnvSodaDkI6tKUtAAhKQgAQkIAEJjCeQ5+A7T7/GeIr+0lYCTF9HmcGOW37r/0w8iVfC55LbJ7FzSg9CbgpXHglIQAISkIAEJNAPAhkOvjMUqR91oaelTGzpzUM1Q5HmKUaN92Toc0kskh6EGquXWUlAAhKQgAQkIAEJDBNIPNIdzqrUcZ5hEaVE96IWEsit/hP6Xn1/xxbqoZLIuflc0rtB9SBUqjDeLAEJSEACEpCABCQwP4GHHspr0fW+ffOXxTslMCsBLPa1a2e9KeH11v854LLpQFZOBDrVxFsz6EGYo5p4iwQkIAEJSEACEpBADAKMdPMxWjADsjLnYgA2jdwJPPVULhJS+bOyhHPhUkKOw4dTG+0lhLh+Ce6M/fvLXjzvdXoQ5iXnfRKQgAQkIAEJSEAC1Qns2pXFfnL4Mg4erF4aU5DAbAQIQ8jEbk9vec5GpkVXs/SDfiyHDw5ZVjEk/uhBSAzY5CUgAQlIQAISkIAEJhDIxHTPxJExAZQ/dZUApnvisPPp5DZsyMWRMV3WLK+oxXSfUvK6HBl6EKYowp8lIAEJSEACEpCABNISYA4WA6bBD6G/+SymaJCDWTdCgOUDe/Y0kvPHmeK/IA7fTxUC9CGNBzGxIqYWV5QehCo1xXslIAEJSEACEpCABGIQOHWqsU3gGXOTOwaAHwk0RQDjs0EnGpanO4BUVz1xTOxi2NSHSBZeJVPLRw9CLZjNRAISkIAEJCABCUhgAgHW7p49W88E2qgUmE+sRfcjgWYJNOVEI/yhQbu3WebRc2+qMyGM64knopdmXIJ6EMaR8bwEJCABCUhAAhKQQI0E7rpr8NxzNeZ3PSvNp7qJm98YAsGJln4bvE9lz6y16xc+RaTalxDQxH4EdX6IH6m359SDUKd6zUsCEpCABCQgAQlIYDwBZtKOH68vEoGoY82n8drwl7oJ4EQjEqE2JwLrJuq1POvm2Uh+rIeqM5wE9wHZ1bL9QYFTD0KBwgMJSEACEpCABCQggaYJEFDNcoYajCh8B4Qc+5FAVgSw6l9/vY73mxJ98/LLdTS0rPDWIwxWPUqsYW0ULtfz5+vfQUYPQj31yFwkIAEJSEACEpCABMoRCEZUuq3dcE9gOzW7+305El7VRwLEwGMWYhwm+jBfTeiB0TeJ8IZkQydDlFO6D1sn1h59EEqjByGdVk1ZAhKQgAQkIAEJSGAuAsGISmHks/Cb6UGcFH4kkC0B7E+MQ0zE6ME4TIzjnti+Pduid0cwPDVEOfEv+nte6B4J1Kpx68QRpehBGAHiVwlIQAISkIAEJCCBDAgw/maa9O23o03GEtRA6AEj75r3OcuApSK0kgAm4ptvRguWodoTeoD7IF10TyspJxaaMASUiDMoylYFeJToFUmwrhc3rkhHD8KKWDwpAQlIQAISkIAEJJABAcweJmOx/KtEDZAIGzQaepCBPhVhNgJMXwc/WpWoARI5eHDJ7KySyGxye/UQAcx+nEE4Q/EmzO1HIJHHHltKhMisuRMZEqrKoR6EKvS8VwISkIAEJCABCUggPQHcBzgR3ntvKSS4/OQbc61M/WE4Mez2jffptWQOqQiE8IGf/GTJEYYXoKQByZsdsDYJOqDhYHyWvCtVGXqfLn4cui+USCQI3VHJ9Snchd8BLyo34gYqeVdi2DclTt/kJSABCUhAAhKQgAQkEINAGEwznr52bXDx4uCVV5YSff/9P/3e97b94Afb/uE//OONGwd33rl0Et8B/7C7/EigMwSwHrE8gy+Myk8ToCH87GcX/+N//M3//J+/+vf//v993303/5N/slRcfAfUf/76yY0Afhx8QPzDGXThwpISr15Fxmt//ue/duHCZ2+66Y2vf/2W3/qtJanpvkI/llsRBgM9CPnppNMS7d69+xqdXaTPLXn44ZaXZj8zHn4kIAEJSEACEkhEgAEAUQnX1zWcO3fufztxYvCZz/zJ++//vx9++Nxjj93sXGsi7CabD4Eb9f/ixYsbjx37/xYWzv+P/7Hxv//3s3v2ZDs8zgdeLpKwq+X1Nz5evXp185kzP/7FL/i37q//+uwf/dFdeXt/FhYXF3OBqBwSkEB7COAJ4qEVS16edmvxs+b3oU+/dOlSLLlWrVqV7SPhwoULH374YaySos08RzCvhBnLSOW855572mWoxK3P2TbbK9c/kZTMFtr5Ntue1+egYtwHDzzwALXx29/+9r/5N/+GrzTMs2fP5tkFxaqWy9PpQ2XgIcWjannZ5z6z4boHau7bc7hxyX2wcSNkTp06debMmWPHjjHMoP7fbvRNDuopJwOPLJTI3+PHj/OYfvzxx+m+UGjO9VMPQjndepUEJCABCUhAAhKQQE4ETpw48fDDD2Msvfzyy8FkevTRRzGiOMaIytZjmxNCZWkxAfxlO3bsCO6DTdc3Bzly5MjevXuxP6n/uNJaXLbeiD7sPnjo+vqUkydP0q0B4KmnngpnMoTxmQxlUiQJSEACEpCABCQgAQlMILDcfcDFjLkPHz7MoPzee++NOy0/QRJ/kkD9BEL0DfniPgvuA4737NnD3DU+Bea0MUTrl8ocZyIQQkiIO0BrhbNg+/bt6JQIR/wIxCPMlGBtFxuDUBtqM5KABCQgAQlIQAISiECAQAPCDVgwxch7ecD26dOnmZslm5wn8SJQMIm+EgjuA4xMTM3li0CxSzdv3oxdevDgwcd4BYOfLAkMr0ApfECFpLhBUSILaXEosLohtyWTxiAUmvJAAhKQgAQkIAEJSCB3Ak888URwHxSLF0Yk3rp16/nz54nlznkSb0Rmv0qgJAGib7Atx7kPSASfAvWfv8xg0wQISSiZspfVRmCy+wAxcIyiRLZCIJYEdUfchz5KGY1BiILRRCQgAQlIQAISkIAEkhPAfXDgwAGsI9wHk7dLZBKPTRYZqec5iZeclBl0kcCKi3dWLCg2J5E4RCtghRKqM7mxrJiCJxMRCBtYkPiKISTDmeL9wVuK0nPbINMYhGE1eSwBCUhAAhKQgAQkkCkBdonDfYBFNNV9QAGYxOOyMInHsvDcJvEyRaxYGRMo7z6gEGE/xV27drEhCNuC4FDLuGQ9Em14A4vlK1BGQBBpwhIGVqOwnGHdunVx30UyktdMX/UgzITLiyUgAQlIQAISkIAEGiBAPDZbzbNguPzLGoMRxRZljLwZf2tENaA2s4xEgOgbmgBz0fjF8I6VTDXsLRrsT+JxSt7lZYkIBPcB/dLU6INhAdjM4rnnnstqg0w9CMMK8lgCEpCABCQgAQlIIDsC2E5MwOI+IB57pk3Fikk83AdZTeJlh1iBMiZQLN5hbXx590EoUPGCBiIR2GQ041J2XDR6MHY0WLVqVdilYqbSFi9oYGXKoUOHZro3xcV6EFJQNU0JSEACEpCABCQggQgEmHlj0Mzgm1CCWd0HRfYZTuIVsnkggckE2BCx5N4f49Ip9hZlZxACecZd5vl0BGZagbKiGPfcc8/rr79OEEoOG2S6k+KKOvKkBCQgAQlIQAISkEDDBHAfYPMQ+ov7gPXAFaVhLUPY1dy33FUk6e21EQjRN1F2Qyz2FmVzBFY31FYEM5r89tmZ+LCfC10ie1tEqRIzZT18sR6EYRoeS0ACEpCABCQgAQlkQSCu+yAUCSMKJwLLwnFJYETNtCAiCygK0ScCcy/eGQepeEEDC4JYWu8LGsaBini+WIFSZv/XMvnSMTb+ggZXMZTRlNdIQAISkIAEJCABCdRHAFOHFygQfbB///7q0QeF3KwhD29ZD2uSfUFDQcaDrAhgJUZ3H1DAYm9RWhbty71FUys9uvsAgcPeLnSMeELZ26KRDTL1IKSuOaYvAQlIQAISkIAEJDADgeA+YNEBo2SG4DPcWeLSwojyLXclaHlJAwRC9E3FvT8myB1eEIjl2ZT9OUG2Lv0U3j5LuEes6INhOHSM6JGuspENMl3FMKwLjyUgAQlIQAISkIAEmiQQ3AeYN6l3K2BLc/YkCw4FdilrsszmLYEbBFIs3rmR9qf+P3nyJGEOnGI5A1stfuo3v1QmkCKEZLlQuEHZFoE+8/Dhw7x0Y/kFic7oQUgE1mQlIAEJSEACEpCABGYjQFh1CK5meo2tCma7efarNaJmZ+YdCQlgCvLmkVhbh04VtNhblD1B2F5x6vVeUJJAPe6DIAxrGdjbhZ6zzg0yXcVQsiZ4mQQkIAEJSEACEpBAQgI1uw8oSfGWdd9yl1CvJl2OQIi+wX3Ay0cj7v0xIfPiBYHszEfI/YQr/akkgdQrUJaLwfsdecsjquSND+FdM8uviX7GGIToSE1QAhKQgAQkIAEJSGA2AmEm7erVq9hOGPaz3VztajwX4QUNdU7iVRPZu7tGoFi8k2Lvj8mwyDq8IJC1DKxo8AUlk3FN+LW2FSjLZSBrAh8Iqlq7du2pU6fYMnb5NRHPGIMQEaZJSUACEpCABCQgAQnMTCBs6ob7gLFvze4DZA0vaKh5Em9mRt7QXQIh+oZWUL/7AKjF3qKnT59mWz6aYXdJJyxZg+4DSoXfB+8P0Sv1bJCpByFhTTJpCUhAAhKQgAQkIIHJBBjysvcB42/cB+xbPvniRL9iRLFfOs4L33KXiLDJjiNQuA+Ivon+5pFxmY6cDy8IZO/SeuzPkdw78LVYgYIPqJ4VKCtCQ4PkjjB4gujKVrwmykk9CFEwmogEJCABCUhAAhKQwMwE2Esc9wG3YcA35T4IQtc8iTczKW/oIoH69/6YQJEZbOaxiUGgSSa1PyfI0Mafgvsg0dtnZwXCBrRnz56lN2NlFjsjzHp7yev1IJQE5WUSkIAEJCABCUhAAjEJYKUwzCVF3AeZvE9xeBKPoO6YpTUtCXyaQIi+CXt/1PDmkU9nvvK3sLcovyW1P1fOu51ng/sAVdJ1NBVCMkJuw4YN58+fZ3FWug0y3UlxhLlfJSABCUhAAhKQgASSE8B9wP5tzJXhPmD3r+T5zZJBU29Zn0VGr203gRwW74wjWOwtumfPnsOHD4+7zPNZhZCMqAPXBm4gIiNSbJBpDMIIbb9KQAISkIAEJCABCaQlcOLECdwHq1at4j1kubkPKHkxiccr7nzLXdqq0MvUc3YfoJCwtyit4MiRIzt27GCPkl5qaUqhc3YfIHqxt0uKDTL1IEypHP4sAQlIQAISkIAEJBCRAO4DXjyG+4DoA2yViClHTKp4yzpGFM4OjaiIbHueFNE3Ye8P1qs3u/fHBEUUL2jgBYFIy4T2hIt7+BNvnwULK1DYOSKTFSjLtZBubxdXMSyn7RkJSEACEpCABCQggSQEgvsAx0HO7oOi5DgOiresY+/h9Sh+8kACcxDIefHOisV5/PHHDx06RIOl/uNWW/Gavp3MPIRkuTrYUpE9EfAK4e+I4rQyBmE5ZM9IQAISkIAEJCABCcQnwE5jGOQsW2DxQrbRB8PFTjeJN5yLxz0h0Dr3AXoJe4sy2c4LAtkfpCeamlDM1rkPKMuuXbtwAHEQa4NMPQgTaog/SUACEpCABCQgAQnEIYD74MCBA7gPiD5gNixOorWkUhhRvuWuFt7dzKTY+4N98jPc+2MC9PCCQC7A/qQUE67s/E/5vH12VtSEHoSwL4IRiCuZ9faR6/UgjADxqwQkIAEJSEACEpBAZALBfcArG1vnPgggho2odG9Zjwzd5LIhMLz3RxvXAoS9RVnFQwxRdfszG7XMJgghJPhQuIdOLJO3z85UAPxWwXvFspSKG2S6D8JM5L1YAhKQgAQkIAEJSGA2AlgdWFBMgp06dYp1AbPdnNPVbJ+GCcEe7L7lLie15C5LcB+0Ze+PCTSLFwRu3779+PHjrW7LE4q54k9tXIGyYkHY2wX3AS9owAnC0ob5wsGMQViRrSclIAEJSEACEpCABCIQ6Iz7ABa+oCFChehZEsz3tmvvjwn6wdpk+h33Qd9e0IAPKOe3z05Q2fKf8PvgycUHeuHChXXr1uEVXX7N1DN6EKYi8gIJSEACEpCABCQggZkJhBcZMPjG5Gh79EFR+GBEbd26lUk833JXYPFgRQIs3iHmv417f6xYHE4We4tif7K3IvE4467szPkQQpL522dnpX348OGnnnoK9c23QaYehFmBe70EJCABCUhAAhKQwBQCuA+YtWPwzQ4CvEKsSwHPUSbxpuDz5/YTaPveHxM0EPYWxf5kEhtXwoQr2/5TcB8QfBS2IWx7cYblH35BA8Uc/mnqsfsgTEXkBRKQgAQkIAEJSEACnxDAZsBB8Mn3lY4Ykj777LPsfbBv376Vfv/kHDO0863F/SSJNEdT3133ne98h6m8X/3VX6WkU0Vg1XGX3ChTy9vhCwj85u2Gkwv4F3/xF3/wB3/wm7/5m//6X//rv/t3/+6Ei7FOmd+ecEFTP/HaQjY+mJA7F1DGn//853/2Z382uYwkklszx/3BZ0Lp+Akts2XAmjVraOaf/exnJ1yMBvPcIHNqXb18+TJKpKT4eafWQ/by4AMHPQgTKoM/SUACEpCABCQgAQmMEli9evXUwffoPeO/M7nHTu/jf2/sl4WFhYh5v/3222HwHTFNk2qEQNjaI1bWbElInE6s1CKmwyKdqU608tnl1sxDhEh5+SdfiQbR4+RrGvk1bl3dv38/3CiIqxga0aaZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjoQWgEu5lKQAISkIAEJCABCUhAAhKQgARaRkAPQssUprgSkIAEJCABCUhAAhKQgAQkIIFGCOhBaAS7mUpAAhKQgAQkIAEJSEACEpCABFpGQA9CyxSmuBKQgAQkIAEJSEACEpCABCQggUYI6EFoBLuZSkACEpCABCQgAQlIQAISkIAEWkZAD0LLFKa4EpCABCQgAQlIQAISkIAEJCCBRgjc1EiuZioBCUhAAhKQgAQk0FICu3fvvnbtWizhb7/99lhJxU1n//79ERO85ZZbIqZmUg0S2LJly2233RZLgLVr18ZKKm46Dz744H333Rcrzdya+YYNG2IVjXSyVWLculpAW1hcXIyIz6QkIAEJSEACEpCABCQgAQlIQAIS6CQBVzF0Uq0WSgISkIAEJCABCUhAAhKQgAQkEJmAHoTIQE1OAhKQgAQkIAEJSEACEpCABCTQSQJ6EDqpVgslAQlIQAISkIAEJCABCUhAAhKITEAPQmSgJicBCUhAAhKQgAQkIAEJSEACEugkAT0InVSrhZKABCQgAQlIQAISkIAEJCABCUQmoAchMlCTk4AEJCABCUhAAhKQgAQkIAEJdJKAHoROqtVCSUACEpCABCQgAQlIQAISkIAEIhPQgxAZqMlJQAISkIAEJCABCUhAAhKQgAQ6SUAPQifVaqEkIAEJSEACEpCABCQgAQlIQAKRCehBiAzU5CQgAQlIQAISkIAEJCABCUhAAp0koAehk2q1UBKQgAQkIAEJSEACEpCABCQggcgE9CBEBmpyEpCABCQgAQlIQAISkIAEJCCBThLQg9BJtVooCUhAAhKQgAQkIAEJSEACEpBAZAI3RU7P5CQgAQkMEXjllVeuXr166dIlzr3xxhvXrl27+eabv/a1r/H19uuftWvX3nLLLUN3eCgBCUhAAg0QoKOmu75w4cKHH374wQcfXLx4ESHuuuuuW2+9lYMNGzbQV9NjNyCZWUpAAhKQQE4EFhYXF3OSR1kkIIHWE8BNcO7cuTNnzpw+fZqR6NTyMDDdtm3bpk2bcClMvdgLJCABCUggIgE8Bc8++yyddnD1Tk6ZXpq+mh6bfnvylf4qAQlIQAJdJaAHoauatVwSaIAAI9Enn3zy5MmT8+V9zz337Nu3b+vWrfPd7l0SkIAEJFCSAO7dI0eOHD16lLiDkrcMX0Y8wq5du+ixDSIbxuKxBCQggT4Q0IPQBy1bRgkkJ8AY9PHHHz9x4kT1nJjaOnjwIN6E6kmZggQkIAEJLCdAX02PPZ/vYDg13Af79+/HlcDytOHzHktAAhKQQIcJ6EHosHItmgTqIMBE1qFDhwg9KLNgobxA27dvP3z48KpVq8rf4pUSkIAEJDCZAHvT7N27N+xxMPnK8r+ytIHu2vCx8sS8UgISkECrCehBaLX6FF4CDRNgCuuBBx5g560UcuA+OHXqlMEIKdiapgQk0EMCLFvAfZCo4Hv27MGPkChxk5WABCQggXwI6EHIRxdKIoGWEWAWC/fBlStX0slNZOzx48eJR0iXhSlLQAIS6DwBYsQeffTRKAvNJrBik8XnnnvOnREmIPInCUhAAh0goAehA0q0CBJogADbJT788MNxVy6MK4ZTW+PIeF4CEpDAVAK8H2fz5s2JgsVGcuftj2fPnvXFOiNY/CoBCUigSwT0IHRJm5ZFAjURYCXtxo0ba8rsejZs1vXEE0/UmaN5SUACEugAAfy8dNf1uA8CLtwHr7/+upEIHag8FkECEpDAigT0IKyIxZMSkMBYAixbWLduHZNaY69I8wN7IrhTVxq0pioBCXSWwI4dO+Z+w+7cUHilDpEIvqBhboDeKAEJSCBnAp/JWThlk4AEciMQomHrdx/AgXFw3P3Dc2OrPBKQgATiEmDrxPrdBxSBODXeFhm3LKYmAQlIQAKZEDAGIRNFKIYE2kGAxbTnzp1rSlaDY5sib74SkEDrCNS/3GwEEfvgPvTQQyMn/SoBCUhAAm0noAeh7RpUfgnUR+D06dO8fKG+/FbKyV0VV6LiOQlIQAKjBFhu1mzcFm/kffvtt13LMKoYv0tAAhJoOQFXMbRcgYovgRoJHDhwoMbcVs7q2LFjV69eXfk3z0pAAhKQwHUCrF9o1n2AFPTVrmWwPkpAAhLoHgFjELqnU0skgSQEMN15nXiSpGdMdPv27bxyfMabvFwCEpBAXwjw/oXVq1fn4GwlAIEwBIIR+oLeckpAAhLoAQFjEHqgZIsogcoEGI/mEIAQysHGYI3PrVUmagISkIAEUhE4dOhQDu4DisezwzCEVGo2XQlIQAINEdCD0BB4s5VAqwhgtGcyHg3Yjh492ip+CisBCUigJgIY7Vn1kCdOnMjq8VGTGsxGAhKQQHcJ6EHorm4tmQTiEXj++efjJRYhJfZ0ZJQcISGTkIAEJNAtAhcuXGjkhbsTKDb4Bp8JUvmTBCQgAQnMR0APwnzcvEsCPSKArc5bwbIqMONjRslZiaQwEpCABHIgkJvDFyYZipSDppRBAhKQQEsJ6EFoqeIUWwL1Echzwt8haX01wJwkIIH2EMhwwh8ftFFj7alBSioBCUhgCgE9CFMA+bMEJPDSSy9VhrDzhcXFjz7+99bh9ZXTGwwyHCVHKJVJSEACEqhAgOCsK1euVEgg3Bq5x8Z9YI9dWSkmIAEJSCAXAgbNTOYAACAASURBVHoQctGEckggWwKVX3yw/vBbTw8eWfjMAv++fvTymt2vvrizcmkZJee21rdymUxAAhKQQCUCly5dqnT/0s1JeuzKz5HKxTIBCUhAAhKIREAPQiSQJiOB7hKovI32a3vvWPjmMwHQa3u/dXYw2LylugthMKgsWHd1ZskkIIFeEojRKybpsd9///1eKsRCS0ACEuggAT0IHVSqRZJAXAIxhqRDEn3//2/v/WPuOqpD7eM0QhFFvWmFLi5CN05vgBQh4QhU7ECF3a9VYhB1rJYbW6ogrtTYVtVru9Inx2pRHLWSE/GH7b8c80/sr63i3CvkRBWxo9vWjlqwQW1jVC4xJChui8DhIjC3kTBRiL/nzSQ7x++P8+5z9uy91977OYqc8+4ze2bNs2bPnlmzZs23vj16/ltfH7sy69fMgs0qhvdJQAISCEIg/0Q9U49tdx2khSiGBCQggeoEtCBUZ2gOEugzgezDvrX/7RP/dfTcs1/OAC27bBlkMgsJSEAC7RHI3ivm6rGzC9YeY0uWgAQkMHQC1w8dgPWXgAQmEsg97Lv3T3fe8u1Dn3l9T8PEopf9MbdsyxZoAglIQAKhCeTuFbP12LkFC60FhZOABCTQbwJaEPqtX2sngaoEsh7BNRega8Pzhz6yK4cHwmiUVbaqoLxfAhKQQOsEsvaKmXvs1uEogAQkIAEJZCGgBSELRjORQG8JrFy5Mlfd7n3ySztvObl9xa6zmXLMKFsmicxGAhKQQJsEMvaKeXvsG2+8sU0uli0BCUhAAvkIGAchH0tzkkAfCaxatSpLtdYefO7hOfeDj2fZv5BEyiVblgqaiQQkIIHWCeSyIGTvsXMJ1jphBZCABCQgAS0ItgEJSGAZAtXXjhiMfmnn6NBH3r07z/aF1wWuLtgyNfdnCUhAAp0i8I53vKO6vHX02FoQquvFHCQgAQkEIaAFIYgiFEMCcQlUHvnNxeIajW7Z+aWrr15947/nDq6tXOPKglWWwAwkIAEJRCKQwzOrlh77pptuisRJWSQgAQlIYHYCxkGYnZ13SmAgBG699dYLFy5UqOznP7Ei496F1wXBAUELQgWleKsEJNBDAjl6xVp67BymjR7qyypJQAIS6CIBfRC6qDVllkCjBO64445GyytX2J133lkuoakkIAEJDIXAunXrYm7vssceShO0nhKQwAAIaEEYgJKtogSqEbjrrruqZVDL3Rs3bqwlXzOVgAQk0FkCN9xwQ8C5+po1a3I4R3RWKwouAQlIoF8EtCD0S5/WRgI1EGDkx/ivhoxnzzLmKHn2+ninBCQggUwEAlpXA4qUCbbZSEACEhgiAS0IQ9S6dZbAtASijf/CeupOC9b0EpCABPISwAcBG2vePCvmFtORrWKlvF0CEpDAYAloQRis6q24BKYgcM8994Qakm7btm0K6U0qAQlIYDAEiIMQasaOCxvheAeD34pKQAIS6D8BLQj917E1lEB1Amxk2L59e/V8suSwevXqUOPjLJUyEwlIQAK5CBw4cCCOzffw4cO56mU+EpCABCQQgYAWhAhaUAYJdIDA/v37g4TCeuSRRzrASxElIAEJtEQgjs0Xay8235YwWKwEJCABCdRCQAtCLVjNVAL9I8CK1p49e1qvl+PR1lWgABKQQHwC999/f+s2X94aeEPEZ6WEEpCABCQwFQEtCFPhMrEEBk2AjQyrVq1qEQHjUVwhWhTAoiUgAQl0ggDREDAitCvqrl272n1ltFt9S5eABCTQVwIrrl692te6WS8JSCA7gQsXLqxdu/by5cvZcy6T4aOPPrp58+YyKU0jAQlIQAJbtmw5fvx4Kxw4MefkyZNxwjG0AsFCJSABCfSSgD4IvVSrlZJAXQQIqc00vq7cJ+Z73333aT6YSMgfJSABCVxDgKgxrYQhwPWAN4Xmg2uU4R8SkIAE+kJAC0JfNGk9JNAUAQ4bb35rK+EP3L/QlIYtRwIS6AkB5vAnTpxoOCBCK4X2RGFWQwISkEAXCGhB6IKWlFECwQiwu7XJwx05TtzzF4I1AcWRgAS6QQB3AHYTEBahGXGT+aAVx4dmKmgpEpCABCSgBcE2IAEJzEKAI775NOCkiqni9OnTjQ1/Z2HhPRKQgAQCE2A+/8wzzzQwq8dacfbsWfzUAsNQNAlIQAISqErASIpVCXq/BIZM4MyZM5s2baovsCLbJfB3GDJh6y4BCUggCwE66q1btz7++ONZcluYCc5ize+YWCiGVyQgAQlIoG4C+iDUTdj8JdBnAkTbZmmLf7NXkrUsXA80H2QHa4YSkMAwCeDJxQyfIx7r8B2jr6bHbjjgwjD1aK0lIAEJtE5AC0LrKlAACXSbQJrqMzDlS5aaMMwlaOKzzz5bh2Eii4RmIgEJSKCjBPbt2/fCCy/cc889ueQnzC3dNf5idRgmcglpPhKQgAQkkJGAuxgywjQrCQydwMGDBx966KFLly7NBoIBKFEPWCIz6sFsAL1LAhKQQEkC58+f37t376lTp0qmX5iMbQtYezX1LiTjFQlIQAL9JqAFod/6tXYSaIEA+2yfeuop/i1pSsBwwCrWHXfcwb/aDlpQmEVKQAJDJXDhwgWMCMeOHcOgUJLBrbfeevfdd9NdNxCasaRIJpOABCQggSYJaEFokrZlSWBYBM6dO8fY9MUXX2SQ+vLLL//zP//zlStXfu7nfu6DH/zgW9/6VnY93HTTTYxBCdyt++uwWoa1lYAEghHA4JvMvl/5yleIufid1z7I+M53vvOWW2657rrrPvaxj2HhxXCQa8NaMACKIwEJSEACZQlcXzah6SQgAQlMSQAfVwwEx48fv3jxIqc2cDfmg5/97Gdf/epXWcXauHGjg9EpiZpcAhKQQC0ECIJIt/zNb36T7hqbb1HGd7/73R/+8IebN2+mP/eYxgKLXyQgAQkMmYA+CEPWvnWXQI0E8D547LHHMB/gd0AxDEAxGfAvjgl4zHI9nQHJHtrPfOYzmBLcv1CjMsxaAhKQwGIEcD2gr2bfGf+mPjk5GrCtLNkL6Kvpsem3uRsrA331tm3b3L+wGEuvSUACEhgKAS0IQ9G09ZRAMwRYvDpy5AiDzhQEgWUrDAQYDhYaCPCYxcTAv+MmBoan7mhoRlOWIgEJDJYAUQ8wGTzxxBPJNACHtKEMOy+d9kIsOCYkU0JyT0ihEDjQwR0NC1l5RQISkEDvCWhB6L2KraAEmiCAvYDxJbaDNL5kWInhoMz4klWvZEpgOIugafmLe43v3YTaLEMCEhgMAWy1dLPjYW4x1+JokNwNStoCMD0kJ7JxGzGWX9wTBgPSikpAAhIYOgEtCENvAdZfAlUIMCTFcIArQTH/x92A+f+iq1iTC2I8iikBG0QKCc54lKxwl2Wxa/KN/ioBCUhAAksRwH2gMBykNBgLkuGAmf9Sdy17nTyTE1na+0BW6YAGnciWRWcCCUhAAl0noAWh6xpUfgm0Q4DIiGklanwPAnP+6tLgxZDcZRn4khsWhLQPouQSWXUBzEECEpBA1wmwPSHZdpNfGNXBsMskH9tBRrMs/X9yIuNfisB8wFsgRcntOkDll4AEJCCBpQhoQViKjNclIIFFCDAYTYaDNL2fEOZgkZunvIQzAi4JDEzH3WUZni4MqTBlxiaXgAQk0EMCaVPYUmERa+05KTpZfo252MOGZZUkIAEJXEtAC8K1PPxLAhJYjMC8LQblwxwsltnU1zAiEPGL4Wnyd9BddmqC3iABCfSXwLRhEWslMS/mYsMvi1qrZuYSkIAEJJAIaEGwJUhAAksSmOehyhIWLgCzhTlYsozSP8wTJrnLJqfc0nmYUAISkEAfCNAfpugG/Js8wmYIi1griHkxFznrgbg2xlyslbmZS0ACEmiGgBaEZjhbigQ6RiCFOWDxP0XJSltb+TdCNZJDhEeUR9CFMkhAAk0SwFiQDAcp7gBFs8hfPSxirVVA4HkxFwmUwNvEmIu1YjdzCUhAAvUR0IJQH1tzlkD3CMwLcxB81Uh32e61MCWWgASmJ9BMWMTp5ZrijkWdyIy5OAVBk0pAAhIIQ0ALQhhVKIgE2iOwMMxB2q2QMWR3rZXTXbZWvGYuAQk0T6DFsIi1VtaYi7XiNXMJSEACDRDQgtAAZIuQQFAC8xaFCHPAJlXCHKxbty6oxMuJNc9dFudeAiXoLrscNn+XgASiEAgVFrFWKDqR1YrXzCUgAQnUR0ALQn1szVkCcQnMC3PQs9MNkmUkHd+ADthtW1QwrkqUTAISGCqB+GERa9UMu+c4uJfTdvCGo6Dgu+dqRWHmEpCABDpBQAtCJ9SkkBLIQ6BbYQ6q1zm5yxLEC4sJua1cuTI5WaxZs6Z65uYgAQlIoAqBLoZFrFLfZe9daNo25uKy0EwgAQlIoHkCWhCaZ26JEmiaQNfDHFTnxUid0OUsc2FDITeil3cr0EN1AuYgAQkEIUBYRDyk6JFSd4RU2DTTwbRdCT1TK8mFTmR018ZcrJW5mUtAAhKYioAWhKlwmVgCXSLQvzAH1eknd1nG7tgUyA13WeI+MDzFPaF65uYgAQlIYFEC+EMRpQXDAf/ynTQp7swdd9xBuBa+L3rXwC8u6kS2bds2+u2Bk7H6EpCABNoloAWhXf6WLoFaCLDGdezYMbaVpqFqEQXA87cL3LjLsruhQETwSEwJgHIoXyDyiwQkUJEAJkvslRgO6JNTVsx+MRmwou5eqvJsF425iOVXl43yDE0pAQlIICMBLQgZYZqVBFomwDDr6NGj2A6KBXaWa5gVu8A+QTEYEZJHMS4bKeZi2nk74RZ/koAEJLAUgYGHRVwKS5bryYnMmItZYJqJBCQggZkJaEGYGZ03SiAKgeTqieEgLXO5yX8GxcCQpUK8EvAx5vbkYNzpgy1ngOAtEpDAzASw29J7PPXUU/yLEYF86IpxN0j7FPT/mhnsojfOi7nowb2LUvKiBCQggZoIaEGoCazZSqAJAmn9nH8pzElvFuJEnYQn5hhOZSdD5gA4ceDKobtsFrxmIoGeEVg0LGIK+2enUbeusdSkTSLpJejBvXUDN38JSEACiYAWBFuCBLpHYF6YA5Zf0h5+l7ky6hJ32RRLIm0JYTKQYi5iU8hYillJQAKdI4DLEo4G88IipugG/GssleYVmhzxPLi3efKWKAEJDJOAFoRh6t1ad5LAvDAHzGlZG/ccgbp1mew1rHThnkBZxFzk3DWwO0+om7z5SyAUgYVhEemE8VEyLGIcNfGWTE5kKAupMPgmy6/+IHF0pCQSkEAPCGhB6IESrULPCcwLc0BYRKav+tU3r/UUKIF/0yZntJB8lXX9aF4XliiBZgjwsBfRDZI7Es87jgYpuoEeSc1oYYZSjLk4AzRvkYAEJFCSgBaEkqBMJoEWCLCWgqNsscOTKSur3wxeWxDFIt8gwIwi6QVTAtdS+An18gYe/y+BPhDAWFAYDpLFEGNBYTjQaNghHRtzsUPKUlQJSKArBLQgdEVTyjkgAgvDHCS3eYetoRoBmxowIhw5ciTFXEy+IXjMct57KDkVRgISKEkghUXEdpAeau5as2aNYRFL0guebJ5Fnu0nvFj5N7jYiicBCUggIAEtCAGVokgDJWCYg44qPimOIF5p5y0bbhmY3nPPPXo4d1Shij0oAiksIqcwYhDkO3XHsQh3AwwH/Gu4k541BlSMoomSi28CVcPyixEByy+mop7V1OpIQAISqI+AFoT62JqzBEoRYEDD2ggDGpa/uMEwB6WohUzEuiUuCQxPU8xFhqQMTBmeotOQ8iqUBIZLAHsfvgYY/lLHCwjDIg6qNWD5pa+mxzbm4qD0bmUlIIEsBLQgZMFoJhKYhcA8p0rDHMwCMeQ9aWbC8DQtaWJEYD0T/boPJaS6FGpABHgqcTfgCWUCSbUNizgg3S9R1RRzkYaRmgTb0AhUrOV3CVpeloAEJDBHQAuC7UACTRNIK9WYD9L0EkdZwxw0rYNGyiMAG6NSFjn5lwKZqxTHNzRSvoVIQAJzBJgZYjJIhgPDItomliKwaMxFTAnuZFmKmNclIIHBEtCCMFjVW/GmCTCKTbsVit3yLHQwpdTFvWlNNF7ewo0qjErdedu4HixwWAQMizgsfeer7Tz3QLprYy7mo2tOEpBAHwhoQeiDFq1DZALMHlmCHo/bhNUA2wF7biOLrWx1EJhnRSLUInYE2oONoQ7a5jlAAvS3yd2AXpfvEDAs4gCbQZYqz3t305Doq7X8ZmFrJhKQQNcJaEHougaVPy4BhrDJgx2/2eTBzjoGexbiSqxkTRFIO29Z6UoxF9152xR4y+knAR4oDAeGReyndtuuFZZf3ubjMReTKUHLb9uasXwJSKA1AloQWkNvwX0lMC8gv2EO+qroLPVy520WjGYyTALM6wyLOEzVt1LrhTEXkxOZWxFbUYeFSkACLRLQgtAifIvuFYF5DuqsTqSxBZ7qvaqnlamHgDtv6+Fqrn0jQE+b9inwr2ER+6bdjtRHy29HFKWYEpBAXQS0INRF1nwHRWDLli3MAKkyaxFEXSLMAX7pgyJgZbMQWLjz9pFHHqFFZcncTCTQdQLr169n8pZqsWbNGg5J5enQmbzrau2u/PMsv/v379+1a1d3q6PkEpCABEoS0IJQEpTJJPAmAVwZ8Z798Y9/TKxvrrImxocv73nPe975zncSb+kDH/gArgcMbfn+5m1+k8BEAuPt6uWXX+bPH/7wh9zBTIk4GqldMVliX4ztaiJIf+wJAXaE4Wjw4osv8oUq8USkuCHve9/7fumXfuld73rXe9/7Xp4IeloekJ7U2Wp0hAAvfRonDfLpp59+5ZVXvv3tb3/ve99DdhYP6J9pkB/+8IfTioJ7HDqiUsWUgASmIKAFYQpYJh04AewFKTJisheUobFu3boUPdG9DGVwDTPNDO0KIwKrr/xruxpmm+l3rfEyeOKJJ7DSlu9pMSLccccd/Otsrd9to/XaJTsvI4Fk1SojDzaFdBikzjJlcJlGAhLoBAEtCJ1Qk0K2TICx7N69exk6zCwHoZvxb3S+NzPAXt5ou+qlWq3UzATwCaenLW84WFjQ9u3b77//fu0IC8l4pSIBTL00zmITzQy5saJw4MABdzjOgM5bJCCBaAS0IETTiPLEIlB90FDUB7fGNLrVBb1gMtgvedsVO2/37Nljuxpsc+pBxZmY7d69u/y67oQq09PyONx3331ubZhAyZ/KE8CkRePE4Fv+lgkpWU7AjqCRawIif5KABOIT0IIQX0dK2A4BYtrt2LEjxUfMKAHTPJwRMCVkzNOsOkSgvnZ1+PBhxqYdQqGoEoAAT8TWrVtzTc8KpMzQeCLY11Bc8YsEZiCA38HBgwfTqR8z3L7oLcnItW/fvkV/9aIEJCCB+AR+zi4svpKUsHkCbFj4rd/6rSr+ikvJzEDki1/8IrHBfvM3f/P6669fKpnXe0mg1nb1hS98geieBEfoJTor1UsCOB1wvAIuOdlr99JLL7FZnWxxHc+euRkOgQC2rQ0bNvzlX/4lgRLz1pcMib/4ta99je5aT5m8bM1NAhJohoA+CM1wtpQuEcBwsGnTJkYPtQrNuPbEiRN6ntcKOVTmtqtQ6lCY1gngd4D3Qd09LW4IHIlqT9u6urslANZehgFVgh+VqS+xFRkGGGGxDCvTSEACoQhcF0oahZFA6wSOHj3Kmljdg1qqyXzytttuqxIzrHVWClCegO2qPCtTDoHAgw8+2IChFpLYKdauXWtPO4RGlauOHNNIm6nbfIC0FEFBFJdLcvORgAQk0AwBfRCa4Wwp3SDAixyvxSZlZfHh7Nmzro81ybz5smxXzTO3xMgEmNVjPmhSwjVr1pw+fVqP8SaZd7SsNKtvYBWh4MMA4JlnnvGopgKIXyQggfgE9EGIryMlbIgA44YtW7Y0VNgbxbRS6BuF+/8mCLSi4lYKbYKmZXSfALEPmu9pCbXAjonuw7MG9RLAcMAqQpPmA+rTSqH1cjR3CUig7wSMpNh3DVu/cgR4hRM68Tvf+U655DlTPf/88z/96U8JrJgzU/OKQYB29eu//uuXLl1qXhzbVfPMLXFZAjwL9LQ/+MEPlk2ZPcHXv/51fBA++tGPZs/ZDPtBgDjHn/zkJ7McKTotEJ4IAiv+3u/93rQ3ml4CEpBAKwS0ILSC3ULDEWB5isAEbYn1D//wDzjZ3nLLLW0JYLk1ESCmBvOWmjJfNlvb1bKITNAwAcwHLT4Rf/u3f0sIW93FG1Z6V4r77Gc/y8kLbUmLzZeiPTqkLf6WKwEJTEXAOAhT4TJxPwng4Eo0o3brtnr1agIiuE23XS3kLb35zd4L5addscN24XWvSKB5Aj4RzTO3xJIE8I65+eabcUMomb6OZAwAXnjhhZUrV9aRuXlKQAISyEhAH4SMMM2qqwRwXGzFz3ycFwK8/e1vxxNh/KLfO02Azd4R2hXj0Q996EOdJqnw/SAQ5InArOb5ef1oURlr8Qd/8Aet7F8Yr8Irr7zys5/97M477xy/6HcJSEACAQnogxBQKYrUKIEIy2Kpwsz0WH/QDaFR9ddWmO2qNrRm3EkCBw8e3L17dwTRdcyJoIVQMmA74HDlCCLphhBBC8ogAQksS0AfhGURmaDPBFLkpIYDLy8F9KWXXmL9wZCKS/Hp0HXaFfu9UWgEmRFD95YIihiyDDwRn/rUp4I8EXgGcX6eDl9DbpDz6r5jxw7Or5l3sZU/cUP49re/vXnz5lZKt1AJSEACJQl4mmNJUCbrJwGiJ168eDFO3Y4ePRpHGCWZmQDtqvX9C+PCHzlyZPxPv0ugYQK45IR6Ih577LGGCVhcWAK0TNpnHPFOnToVZFUjDhMlkYAEohHQghBNI8rTKIEnnnii0fKWK4yhDGEdl0vl79EJRJufsLwWZIUtuuaUrx4C0XpautlQtuN6qJtrKQKhzAdIjMNONJFKcTSRBCQwJAJaEIakbeu6gEDA93S0ofYCZl5YnkDAdnX8+PHl5TaFBGogwIyIZdUaMq6UZcCHtFJ9vHlWAtEMvtTDYcCsyvQ+CUigIQJaEBoCbTEBCbAMFcqxNiFyXBuwqUwlElsYAvqgBhwlT0XVxN0lEPOJcJLW3RaVUXLGALTPjBlmyQqLG3a3LFmZiQQkIIE6CGhBqIOqeXaDQM4R5O0Hn7t69dUn761ec7zNda+tjrHFHHK2K6px75Ov0rSuVm1btqsWm8TAi37qqafyEMjXzSJPTLtGHlDmUppAZpN9pu46pttOaagmlIAE+k9AC0L/dWwNlyKQywFh7cHnXv3Szv+6VDHTX9eCMD2zQHdkjThw7xePbPj2889nqZ7tKgtGM5mWQJYnIns3Sy2yCDYtDdOHIpBrGPBapXJ21zbOUO1EYSQggXkEtCDMA+KfAyKQZ0J175Nf2nnLyW0rtp/Mhi6PYNnEMaPpCGQckt775JENJ7d9+ovTCbBUatvVUmS8XiuBDE9EDd0sVc4gWK3gzLx+Av/6r/+aq5C83fWLL76YSzDzkYAEJJCdgBaE7EjNsDME8gwfP//x61as+MTnc9Y6j2A5JTKvKQhkC4Jw+8H/d8Pzh/48W9uyXU2hRZPmI5Dhiaihm6V+GQTLR8mcWiGQrVfM3V3bOFtpDxYqAQmUJKAFoSQok/WQQLahQ242Lj7kJtpofpmW+m8/cGzn6NBndn85m/C2q2wozWgaApmeiGmKLJc2rGDlxDdVBgKZhgH5u2sbZwbtmoUEJFAbgetry9mMJRCaAJGKwtr4wwoWWqMxhMs0HiWA4p+yOWb7rnz2A1dcY7SQoUmR7YmoAZw2tRqgdizLPO2zhu46j2Ad04biSkACnSGgBaEzqlLQvARuuOGGvBmamwQgkKldzUXkIrhGtg0M6kYCLRHI9ETUIn1k2WqpsJkuIJCjDdTSXecQbEFtvSABCUggEwF3MWQCaTYdJLBy5cqYUocVLCauUFLdeOONGUZ+9961YTTacIRDHOf+I1Qnfz189epzB2+vUlnbVRV63jsbgTxPxGxlL3fXO97xjuWS+HvPCWToFe2ue95GrJ4EJLAIAS0Ii0Dx0kAIZBg61EPKcW09XBvKNUO7ei1uHBE6038fOcRpjie3r1jx7mqbGmxXDbUAi7mWQIYn4toMc/0VVrBcFTSfZQlkaAP1dNcZBFu28iaQgAQkMCsBLQizkvO+7hMI+4YOK1j3dd5EDcKqL6xgTWjFMtojELbhhRWsPV0NruSwbSCsYINrIlZYAhJYjIAWhMWoeG0YBPK8oe99MrmaP/ya3/lr35+8txrAPIJVk8G7ZyYQVn1hBZsZtTd2gkCGhldDNwu6DIJ1QgEKuTSBsJ5ZYQVbmqW/SEACAyKgBWFAyraq8wi8973vnXdllj+v9WB8ze384xUD4K1evXoWSbwnBoEPfOADeQU5u+vd162o2qgQyXaVVy/mVpJAhieihm6WeCW33nprySqYrK8EsrcBu+u+NhXrJQEJjBPQgjBOw+/DIrB58+aAFV63bh2xxwIKpkglCdiuSoIy2UAI3HnnnQFretddd2UIehqwYoo0DYGYzQDvGEYC09TDtBKQgAQaJaAFoVHcFhaKwKpVq7KvP1Sv4B133FE9E3NokQCNiqbVogCLFn333Xcvet2LEqibwJo1awI+Efa0deu9E/ljRcKIEE3UmEa3aJSURwISaJGAFoQW4Vt0+wQCTqtirmC3r6pOSRBQiQFHyZ1SqcJWIhBtRhRz3lgJsTfPSmDjxo2z3lrXfQFHJnVV1XwlIIFuEtCC0E29KXUmAtHGtTGXrzPBHlA20YakOMQaNG5A7S9eVaPNiNwsFq+NtCZRtI0MbGN0C0NrrcGCJSCBcgS0IJTjZKqeEsC9NtSres+ePT0lPaxq0a74xKnzzp074wijJAMkQDcbKpCnT8QAG+FSVcYhZfv27Uv92vx1hEGk5su1RAlIQALlCay4CYIw9QAAIABJREFUevVq+dSmlED/CJw/f/62226LUC9G2M8880wESZShOgHbVXWG5tAnAqdOndqwgTNv2/+w5nzixIn25VCCMAQuXbp08803X7lypXWJcBZ74YUXtCC0rggFkIAEJhPQB2EyH3/tPwHm7UG2iN9///39xz2YGsZpVwcOHBgMdSsalwBbxuxp46pn2JIxbw/iAIgYmg+G3RitvQS6QUAfhG7oSSlrJRBh/cFlsVpV3ErmEdwQbFetqN5CFyXgE7EoFi9GIIADAm4IDAZaFEYHhBbhW7QEJDAVgZ/bt2/fVDeYWAL9I/C2t73tlVdeefrpp9uqGmsO//N//s+3v/3tbQlguXUQYDj44osv/uM//mMdmZfJ03ZVhpJpGiPQ+hNBjDr2L/BvY1W2oK4QuP7663kFP/HEEy0K/Bd/8Rfvf//7WxTAoiUgAQmUJOAuhpKgTNZzApjSWvSwffTRRzmFoeeIB1m9w4cPt3jeh+1qkI0udKXZU9Ni8FqeiFWrVoUGpHDtEbjnnnt27drVVvn33Xdfi4OQtmptuRKQQEcJuIuho4pT7PwELl++vHbt2gsXLuTPemKOjBv2798/MYk/dpiA7arDylP0GgjwRBC89uLFizXkPSlLjBctzg8nSeZvkQgQ75Oonw1L5HazhoFbnAQkUJGAFoSKAL29VwQY1DK0ZYDbWK0cNzSGusWCbFctwrfogAQw1NLTNhn6nuXlRx55JCAKRYpGoHmbLx6IHMNkAMVoLUF5JCCBCQTcxTABjj8NjgAOrqdPn2azbjM1x3yAV20zZVlKiwRsVy3Ct+iABJgynTx5srF4BJs3b2Y/UUAOihSQAM2SxslhOs3IRkEUp/mgGdqWIgEJ5CKgBSEXSfPpCQFe56wGNDB6YPMCMb0cN/Sk3SxXjcbaFWeC2q6W04a/t0+AaAjN9LRsXsBQa0/bvsq7IwE237Nnz2J4qltkiqAgY3PUzdn8JSCB7AS0IGRHaoadJ4APQq2jB8ayjGiNfdD5hjJlBepuVynOvMfrTKkWk7dGIPnm1Bc9jicCnzJjH7Sm4C4XnF7TGGTrq4S2rfrYmrMEJFA3AU9zrJuw+XeSAAc7/e7v/i5Tvn/6p3966aWXMtaBlTcObvzN3/zNjHmaVVcI1NqucD346Ec/2hUUyikBCDBPYxmWqf5XvvKVvGERUoiZBrzJ1GOPCfC+XrNmDcOAH/zgBxmrSbNkFaEBH4eMMpuVBCQggXECRlIcp+F3CcwnQFClgwcPPvTQQ9VHt2z9xe+gvgW3+aL7d2ACedsVa1ktnhkZGLOidYYAT8QDDzzw8MMPV+9pmZ7xRLR4ZmRnoCtoaQJpGHDp0qXSdyyekGUJ/Bq2b9+++M9elYAEJNARAloQOqIoxWyVAOMGRrdHjx6dbXSLs+6ePXscNLSqw4iF264iakWZ2iPAqSX0tMePH5+tp8VKy/TMpd32FNjnkpPZ98iRI7PZEbAdbNu2jfhHhuTocyuxbhIYDAEtCINRtRXNQeDxxx9/4oknOCy6zBiCpbCNGzcynGVcm6Nw8+gtgWnb1d13340zi+2qtw1i2BXDfEAfS0/Lc8G0bVkY+JnzROCG4xOxLCsTVCdw7ty5xx57jMaJwWvZ3GiTtEzaJ6102cQmkIAEJNAVAloQuqIp5YxFgDEEQ1v+RSwiiv/1X//1W9/61h07dvz8z/88e3qxHeB3wCeW0EoTnkDRrth2+zd/8zff/OY33/KWt/zWb/3Whz70odSuGI+ylhW+HgoogTwEeCIw154/f57s/u7v/u7v//7vf+EXfuGP/uiPCCnCg8Dj4BORB7S5TE/gwoULNM4zZ87whSb6rW99a8WKFR/84Advv/12Gicmg9REp8/YOyQgAQlEJ6AFIbqGlC84AcYN69evJ9riK6+8guGAg50ZNASXWfEiE2BpC0dZ1mAR8l3vetePf/zj//iP/6BR7dy5k40w2BEiC69sEqiJACESMNHiAY6HAnMzelqfhZpQm21JAvTV454yN910009/+tPkn0gTZc8CnmK20pIwTSYBCXSLgKc5dktfShuLQDIfIBM+CMTu4s+1a9fybywplaYLBNIm25tvvnnTpk0sat1zzz34tvz7v//7v/3bv9G0mDjt3buXX3fv3l3GdbYLNVZGCZQlQLPHfICJ9tlnn2UnOY4Jt912Gwu/Ze83nQTyEcBwsHXr1l/8xV+kryY6Es6GdNEvvPACPfP3vvc9DhCl92YYQJpf/uVf5l/683yFm5MEJCCBEAT0QQihBoXoIgFWiRlAMLVjxMDQliowsNiyZQtXOKjJ2Phd1GkrMjPu5LCPFKcTXwNWrvA1WOjJQoJDhw4l+xQjVFwSUqtrRWYLlUAzBPA4oFOla6VHpV9NK7o8C8kfgRNMPXOhGUVYyjyPA7rfz3zmM3gZLLpdEYsw6fEmS1sdSUPHTlCkRRPLVgISkED3CFz1IwEJTE8AH1osBQxnWSgev5s/09zv8OHD49f9LoGFBGhFhaUJr9dHHnlkYZp5VzBXFbcwdyKHeQn8UwK9IcCKbjKTYVObVykeBLpfOuEyT828e/1TAuUJYKXCYltsRqBBJo+Dkjngm4DXTGERpvemxf7kJz8pebvJJCABCcQkMIopllJJIDIBhhSMXFlMmGc+SDIzYkij3l27dkWuhbK1ReBHP/oRBqZiMYrh6dmzZ6cSBl9u7koWayLJOYmaip6JO0GA3jU9I0zYFhWYpyAlYIa2aAIvSmA2AszwcXipYjhYWC7W3uKcUewRGMWm7fYX5ukVCUhAAm0RcBdD99xGlLhdAjjQsrORkSuLYMUkcJ5IeDDiecs2B1wcGYhgbpiXwD+HSSBtWOC4e1oIq1JLbVgoCYeQXexrIMJcys1QiyW5mSw+ATpPulC2MNB/0osuJTAtf8OGDTiKM9nDKmdPuxQor5chQHsrtirwnVtwDUtH5y71ri+T7XgaWiz9P7sb0n407L9pd0PhpDCe2O8SkIAE4hJoy3RhuRLoIgEWe3mYGUzgaLCs/GmVGH8EfHGXTWyCfhNgAaqYCNEkMjqy4tHAIm0a4LK0heeL7a3fban3tcMWQDdLY17UyWte9VkuTku7bOrhWZj3q39KYFkCyeOAVlRYoGhLNMJaO1I8aMbj3VA6xrJlRTWBBCQggSAE3MUQRBGK0QECzNMY105lEdi/f3+yOJQZCncAgSJOSYCxKSNRFppoBnwYJtbnuYpVIm2foSCsVza5KXVl8hAEMIHRgHlkylhpC4nZyDDDXcXtfhkggVYMBws5j3vZ4ImAWQHjwsJkXpGABCQQioAWhFDqUJi4BO6//35GqMzQpl3mSrsYWE8z6F1c7dYgGfMf5kLonWbDuJAZTq0rWkUNxkMtErXLVleQ8UtwAszokp/ObN4EWNBYQ+aJq89IFxyg4pUhEMRwME9U3g6sNxS2ZkYamJ6nHWzMy9M/JSABCdRHQAtCfWzNuT8EZjYfJASMaNNMkjFBf6BYkyUIMIcvNiwwIsy4YWGJAhe5PB5qkcEoMiySyEsSCEOAGVTyoMF9hjnebHIVBzToED4bwB7fFdNwsBA4owXcENKAAYsYbmtagRdS8ooEJNA6AS0IratAAaIT4HXOMjLLuTOPa6khK9JpeYF16egVVr6ZCNA8mKgXi0iM/JjPzJRTtpuYleH7UPhBsA3HRa1scM0oH4Hi2AWWYSvmWhzQUD2ripJ4ewQC9Hh0y4VJN73KMeU34xE2M4H0NikO7k1ebFPt65m5aG+UgAQkUIaAZzHwQvEjgSUJcOwChy/wIk8nOC6ZrsQPBGHetGnTmTNnGM2krQ0lbjJJBwhwwgKxtdOZCEzXMTkRXjtX7O7q9afh0YY5tQE5EY813j179hj6uzpYc8hCoDh2gZkedrfqeXpAQ3WGXc+BNlCcqpDqwmt348aN/Jssql2pIJ02vfexY8f4gsycDZHObiiCPnalIsopAQn0jUAZM4NpJDBMAsy1eOAreh+Mo2NhIeWJv27wNZBxsf2+FAG8DIo5T1sbFpaSbeF1ZmjJUZxWTTs01OJCRF5pmACrwbRGJnV5gxfQ06YHc7aQCg1DsLhcBBZ6HGAyoN/rge8V7xo67WQ44F++t+7jlktr5iMBCXSRgLsYuqg1Za6dAAPQ5EDIezp7YbjXMmhmjdopXHa2zWSYXEyL2TiD1A5tVWXcWTjH8qVDkjejXEtpjMBsxy6UF6/u/MtLYspaCfTYcDCPW6opnggMIdIoguGEuxvmUfJPCUigAQJaEBqAbBEdI1Cr+SCx8ICGjrWJN8RNkQXSFgAWTpmidHT0hvUK69hro9C5E0ZYpnujiv5fArUToI/F7kbzq9tHoCYfh9oBWUAJAsMxHCyEQbwPYtwUm9GwBTOo4LFamNIrEpCABOogoAWhDqrm2WEChfmA3ey1VsMDGmrFmz1z9DW+YYGZSQ+GaxhEMIKkjcEMRg21mL3ZmOFCArS65L+DDauBhwgvG1o4jt8e0LBQF128QvvB4pksUMkG2putCjOog+ZdvJho54xb8m4ImkEkb5GABIZAQAvCELRsHcsSYE0jDW05vrHsPRXSeUBDBXjN3ToePqCXbv80e2wH444VjNGb42tJQyKQ8diF8thaKbS8eKYsQ4BOCbstTivJaoBJiJmzC+8JHX04cIqTgPhCl243XqZdmUYCEpiNgBaE2bh5Vw8JNGw+SAQpNA2JWEVpYDmuh2qrrUoMvzAkFfNq1nY6umGhPKFxWwnrw8bpKI/OlGUItOgOwOPcpONDGRqmKUNAw0EZSkUadjfwqip2NyQjS/GrXyQgAQnkIqAFIRdJ8+k2gWJ8ieW+4ZpgOEg70hngIkbDpVvcQgJ4gRYxAgh4ydoOhp6Fyfp6hWmeoRb7qtwW68VzxOoxjtZteVnT0ybXd5r3oJ7oFpU+c9EaDmZGl27EO6PY6IFBAbMCxoWKeXq7BCQggYKAFoQChV+GS4C1ZSaKjG5bjCfHcjcCeEBDu62QBlCEue7lhoXyeA21WJ6VKZclkI5FoH9r3ZEnSYK5tnVJloU2wAQaDvIqHZ4c1lDsbqDZD80gnpenuUlAAgUBLQgFCr8MlEAE80FCz/SVvZ2s0bEIPFBltFTtNMxKnp+owOWaQg+QKUItMv3DQ8fF2wKOX8oQKFb+sc0FaTzJG4Ln3X06ZTTYQBoNB3VDxvGH9xqjCxYqUggJhxl1Mzd/CfSbwAqqR4fiRwLDJHD+/PlNmzZdunRp3OWvRRRnzpxBnsuXLzPG5X3foiQDKZoGcOjQoePHj1+5coUZ8s6dO9m/kIZZAyFQppo0yKNHjz700EM8KcChZQKq2GpbJgfTDJMADWbDhg08ZezHThbSIBxOnTq1ZcsWnvogPX8QLA2LcfHixccff/yxxx47d+4cRdO34Hi/cePGwv2+YXl6XxwNnpcdwGn/VJZXHg/mtm3b+NL7ultBCUggM4F+G0isnQQmEGABiiEL9vhQxng2K6bXOWu/E4T3p4oEmDmMb1g4ceJExQyHcDuTwBSOjvcQphY31g5B6TPXkQ42dWUcXD9zJvXdWIjXfOyb+irViZzx+4N50ZPwFqYzsQduUneogI2TheGAVyF9u7Gcm1SBZUmg6wTcxdB1DSr/jARimg9SZfD1TZNblmJ8qc+o4CVugy37QosNC06Dl+A06fK8UIunT5+elNrfBkmARpLss8xMwgLAeT7NY3GrCStkbwTTcBBQlTynvARZR8EozL98byvQaUA4iiQBCUwgoAVhAhx/6i2BNLplgIsdIWYlMRzgXshLnQEuw9yYQnZLKhbMi6ESay/YEYLsyu4WxkJanh140kT50EojTxQLmf3SDIHi2IX41qUiTIMHNNTUNjQc1AQ2Y7a8CunAC6e89H5EcRmLMCsJSKBnBLQg9EyhVmd5ApgPsLVHNh8UdcD7l+kZr/Owlo5C1Mhf2LCwbt26uZnuaMQX/owsbbdkM9Rit/TVgLTFsQsd2uTiAQ3ZG4aGg+xIG8iQZ5ZRRxHjBrMar0sdIRsgbxES6BwBIymmaYX/DoUAAYQIVYj5ADtCsQ8zcuWJYLdjxw5MHrzIeZ1HFjWabMT/e/jhh48cOUK8LgDi07Fnz57iXKto0nZaHkMtdlp9uYQnThvhCYmNx2Jm8vPKlXMD+Rw8eHD37t3MnbryamiAyQxFXLhwgZfssWPHCJ/J7fBMwRF9ec0As8VbUoRLwi4iA+OlFHCxE0OmFqFZtASGRaBzNg8FlsDMBPDT4/FmSb9b7nl4AvMKZw6so3hJ1bOQwsZmiKFuhrBsWHAnSEl0FZPRRAsbDXscOrQKXbHi3l5Eb2Gy0dFFS4L50WnwMarftO2ZJ53IfMWzT69LDxx/D8u01Rxaeh5qdiQVauULITB9mQ6tGVhfCSxKwF0Mi2LxYg8JdNR8kDTB+AzDB/PhmFHN4zQXhv7FYhcLoW5YaEU1rOIW20ZQhxOJVrTQZKG96aDYL8bsl57WAxrKtB8NB2Uo9SANisYkxEoGjwYfrIS+W3ugVqsggSoEtCBUoee9nSGQInvhg9ct74Nxvj1Y4huvTt7vwGHEn4wsLCGy+m3kiLyEZ8jNUIszQOviLT1zkuIdkby1PaBhqdao4WApMr2/juGAbSnJjoCtjQAiNIbe19oKSkACCwkYByH1hP7bZwL79u174IEHGBSmkW53q8o2461bt7I1sYvbjGvCToyDhx56iGgRwGFAs23bNsb9aRWxphLNdioCKOjQoUMoiFgJmHh27tyJfadYy5oqKxMHJFAEasH9p3A8CSjnVCLRVgnowH5+PGjS1oapbu9rYmIc8PZ57LHH+EId6WaZTN5999290XtfFZe9XpcuXeLBJ9pFagkMrnjz4phgx54dtRlKIC6BhUYFr0igTwTYnMnjxxuOZep+1Ks4oGHgtn9c5cc3LBgkInLz5ukjGkWy7DDKpA27mTayvkrK1u++CFtkencMvK3O8zjADsjK89mzZ0s2EpP1mADNoLAI4/2HEYH3co/ra9UkIIGCgLsYChR+6SGBdEYXKyS9MR8kJXXouPU6WhW+JGnDAuN7hi+OZeuAXFOe46EWeTxrKsVs6yZArERmC72fYLM3ijrS2wxzV9T405oMB8PkUPfT1PX86Q1oKoVBn6aCbbG7O0a7rg7ll0AzBNzFwPDATz8J4PCPo11f3VDxsMXPFtd9rAnMovupwqJWOM1yNthrrrOjr3xl34ULR7773W3vfOf2T35y5S/9EodN4WQyWreuSO6XiAQuXpxT4mtnvJ06c+ahr33t4pUrL6xZM6e7//SfRhycwXf+e+0EjYjyK9MbBHDy37Bhw7lz53BiZ180a49v/NLD/3OsHT0tdaSmxRyph/VMVUpPKI8qn698Zev582cuX77r7W//zCc+sZoAk/zH08pD6kcCixFgz1ra3cAXfme7Zdrd0O8uYjESXpNA/wloQei/jvtXQ4Z06azpCVX7+te//oUvfOGWW25hl+b1118/ISUeCnwmJGjrJ97E6TW8lADsRWRLKqP5PXv2LPuGZqzPVo6lsgp6/cyZ0RNPjB5/fJRGtJOlxI5w552jjRtHxHnq9ZRmMoZwvzIneeyxOSUmA9Bk+VBcUiL/vhYSf3Jyf81O4ODBg3Qpk7N96qmnMB8wPbjjjjsmp8TNJP7W6GWrTE/7V3/1V5hr/+RP/mRyffkVey5rsMsmi5WAx/Opp+Ye0kuXlheMnpY+FtXb0y4Pa6ApTh079hgxM/7u7668/PL+zZvv27ZtDkTIgdZANWS1JVCZgBaEygjNoHECybkgV7EESiDUYq7cMuazfv36M0yhM31wMuyMq8KVK6MHHxwdOjRabiazJBucMoh/0blx/JL16eYPDz88euihUtafReuHEWH//rk1Tz8NErj55psnGy6nkgVP5vjT6bxVZo9VTJP0Ioqjg+UJ5TmdrafF3pd6Wo19i8Ad3iUsUMni/0ZzwhJ5nihUo9GN4zCwIyRDvy/ocSx+l0DXCFzXNYGVVwIS6DUBhrM33zx64IEZB7WJzdGjo1/91dHevZUy6TXmeivHUBL+O3bMbj5AvlOnRrfdNtq6tdS6aL31MXcJ9IsAVtqDB+d6Wmy1b8z3pq4hmaTuGhP8zJlMXao3BCNAR00v/Yu/ONq0acSbd6wlYDhYN898gOysi+zePdf26N5phGPpg1VMcSQggUkEtCBMouNvEpBAcwQYWDCkYNpZxpN2WbGSIwPDFMa4fhojwJ6F9evnhpJl9iyUkYohKUoM6SVURnzTSCAcgWTgYxaXZfJGT4vBF4shj6qfQRFIvf2GDfMMB2UZcHsyJWDGohX5kYAEOkVAC0Kn1KWwEugrAeb5DEQYUuT9METGJLFliwOUvFwXz42ZCeaDfFtvXi8lTVHIOcuEZ3HRvSqBYRDAGIeBr0xkmal4YPZlIZrO1qngVNw6mpj2QyvC4l+9t6dXx1sQM7EWqI42BsUeKgEtCEPVvPWWQBwCjDtrHXoePz5auzb/oDkOwAiSsI7EmLK+SX5yUcluY4qAThkk0AAB5vY8ofgL1PfBEKylrz68QXJmqo/LCfbijJ9kgbLxZERqVhKomYAWhJoBm70EJDCBABNOBg0NbDRg5okRwfnnBF3M/BMzE7w8WEeq+8PCF0rEHuRHAhKYikB6dvLO+hYV4Ny5uaVpe9pF4fTgIvsOcDapydMEMzE9fK4dcD2gbRUkEJiAFoTAylE0CfSbQFoTq+4GWZISqxxYK7K775YsvcfJGFM2NqunzTB+bazN9FhrVm04BFJP29isPrm4ZwlnMxwdxa8p5n58WIh9WOsH8wFGBKIz+pGABGIT0IIQWz9KJ4EeE2Dm2fBUkDEQ0RZqWj/psaYmVI0BZQMuJOMCpOmQlqBxJn6XwAQCuAg1Zj5IYiQjgj3tBKV06ydUyauzAR8WsKTXdDNldUsLSiuBSAS0IETShrJIYDgEmp95JrYscTCe9pOFAAYgzEDNf7QENc/cEjtKgNCJrUzG2M5AdBs//SCA5xcKbfLTvNmrydpZlgS6T0ALQvd1aA0k0DkCbc08EyjG054OWL3N4KWMU2tbHyxBDGr9SEACEwjgDV5r6MQJRfMTIfcadlCaLI+/zkYAc39j+9QKCZOvGcZiPxKQQEgCWhBCqkWhJNBvAq0sXI8jfeihkdt0x4HM8B0ltju8Y1Db8C6YGSh5iwTaIsAcrHUvAAKs2tO21QCylIsRqq33tXthsmjQTCRQDwEtCPVwNVcJSGApArgANLwpd6EkjK0bODtgYbm9uYIGm1+VWkivraHtQkm8IoFoBFj/bz1cCEZGzLV+OkqAF2W7rl7YiHVj6WjjUey+E9CC0HcNWz8JhCLAiCTIrA8P29YNGaFUM5UwQewvaLCVPd5TsTKxBJonEGfqHsGQ0Tz/fpQYwYVEh8F+tCVr0TsCWhB6p1IrJIHIBEKNJlvcIRxZR8vKxqQ9zmlbKnFZfZlggAR4LoJsH4hjNR5gM6hSZdpPhPV/xNCNpYoevVcC9RDQglAPV3OVgAQWJXDkyKKX27nITJiAfH6mJRBKibghxDFnTEvS9BKogwCTdnys4nzoaYOYM+IwiS8J3oI0pAgfDBm2nwiKUAYJjBHQgjAGw68SkECtBJiuR5ux6wM/rcbxjo4Wv/Cxx6athOkl0GcCPKHtRjldCNeediGTyFd4U0eIdJMQYcjQDSFya1G2QRLQgjBItVtpCbRCIM6IpKj+E08UX/1SigAL/kEWpgpxnZwUKPwiAQgE7NYCimRTmUAgWqcacPAwgZ4/SWAABLQgDEDJVlECQQgEXCs+d073yOlaR8CZQEC3iOmYmloCWQlEm/5RuYBuEVmR9y2zaP08uxii+b71TeXWRwLTEdCCMB0vU0tAAjMSyLOF4d6r4597Z5TlmtsCjravkS/SH3gfVA86cPC5cR3Ofa+ux4DGqUh6U5YBEchjFc3d02bpOgakxVarynSdVhTtE82oEY2P8kigWQJaEJrlbWkSGCyBDBEQbh89d2S0bcXrn0PPj448N7q9MtBvfrNyFoPJgJFllv3Vzx96Q4uv/f/zlQFmaF2VZTADCUQgkOFZqKenzSBYBL4DkCGmmVhb/wCanlXsEAEtCB1SlqJKoMsEMsRS/vLo3StWFLPNXZ8bjW65+v7KTDIIVlmGrmRw8WJQSVViUMUoVuMEMjyk9fS0L77YOAsLnInA00/PdNu1N2U3E9OwM7Tta4X0LwlIYFYCWhBmJed9EpDAVASyz/Fuf99U5S+ZOLtgS5bU/R+yOCDUgUEl1kHVPLtI4Mc/ziy1PW1moOGzCztRDytYeJUqoASyE9CCkB2pGUpAAosR+Nd/XezqzNduHx3bOWKVo3BJmDknByXl0eWaqN+y881QCAerb0QZze2tiHZCRHmqppRARgK5HtLXRcrX02YWLCMys7qWQFhNhRXsWn7+JYEhENCCMAQtW0cJBCCQZ/m6iO/1paujQyvevStDxfIIlkGQDmSRZQC3i70ob3y2nRzt/NLVLEaELLJ1QAeKKIGJBPI8CDX0tHkEm1h3f8xCIIumspuJqVoWwbIgMhMJDJ6AFoTBNwEBSKAZAnmWiD//xtRzxYrPvWduHbv65DOPYM1A7F0pn//4ipOj0Sf+W+8qZoUk0GkCNfS0neYxHOF5IVa3qtdkJjaUxnDaoTUNT0ALQngVKaAE+kFg5crM9cg1+cwuWOZ6RsruxhvzS/Ot50e3vCdDtuoxA0Sz6D6B7A+pPW33G8UUNci+zp+r/VCH7LJNwcWkEpDANQS0IFyDwz8kIIG6CNx0U/6cmXxW/6xaVT2PoeRQxyz9PbeMnv9WVYA33DDiPz8SkEAdD2mWnja7aUNd10GgjhdiLjNxHaOIOhiapwQGQEALwgCUbBUlEIFA9XHt7QevXn3yzaoToyXUAAAgAElEQVTw585bRl/8H29eme1bdcFmK7eLd2VgxVHzz42K4In3Pnl1w2j0ucrxLDII1kV9KLMEFhB4xzsWXJrygj3tlMD6ljy7rSeLmRjK2QXrm+asjwSaI3B9c0VZkgQkMGQC1d/9X9614tBzhD54k+K2FRnOYqgu2JsC9f1bhuWpL4++OLpKHMzXP8+v+MiK0Zff+Gvm/2cQbOayvVECkQhUfxZq6mldQI7UTCbJgkG2UigEzMTHRp959+sdezITb6tsJkZiLcWT1OZvEmiUgBaERnFbmASGS+DWWzPUnfhMOcYh10jy3vde86d/TCDAAI7NAhVjT9ahxOqzpgm19icJdIhAlmfBh7RDGs8uKv38hQsVcq3HTIxAWhAqaMVbJZCXgLsY8vI0NwlIYAkCq1ePsgxtl8h+9st33TX7vUO7E/PBnXdGrPTdd0eUSpkk0DyBdeuCOnvb0zbfGGYrsfqbevwshhVvOCPMJsz4XdUFG8/N7xKQQAUCWhAqwPNWCUhgKgKbN0+VvInEYe0aTVR+pjI2bpzptjpvYh8KsyY/EpBAIhBwrh7WrmGbWUjgYx9beK39K5gPtCC0rwYlkMDrBLQg2BQkIIGmCAScfAYUqSltzFhOwMkJbhEexDCjOr2tjwQCdmsBReqj5vPUKWAnT8UCrkDkwW0uEugkAS0InVSbQkugkwTWrAm3hhBzqBRZuwEX/J2cRG4wytY8gYA2NXva5pvBzCUG7OSpi/38zAr1RgnUQEALQg1QzVICEliKwLZtS/3SwnW2MPCfn2kJhFIisbWcnEyrQdP3mwAuOffcE6iKPKH6nwfSRwlRok3XaT+sQPiRgATCENCCEEYVCiKBIRDYtStQOOUDB4aAPH8d8SaNY3nZs8ctDPlVbI5dJ3D//YGeC4Tx0y0CdPKhtoa5haFb7UdpB0BAC8IAlGwVJRCHAIMSpnwRPiyLrVsXQZBOyrB/fwixMWRgk/IjAQnMI4BvTpBHI5TBcR4l/1yKAO1n+/alfmz6OsOGnTubLtTyJCCBiQS0IEzE448SkEB2AoxLIni0uixWRbNstI6wd0AlVlGi9/abAE8H88B2P8z9dPVqVwUzlx7HvStCS54ZozdKoKcEtCD0VLFWSwJhCTCmPHy4Zenuuy+QH37LLGYtnlEdqmzxw7bYCFaMFglYtAQmEODxbN3EFmrb2gRW/rSQAOanCL5mcbxpFiLyigQGTEALwoCVb9Ul0BYBVrCZw7f1YebZ+sC6rbpnLJcdBI88kjG/6bLCjeXEieluMbUEhkYAh68WfdHp5yNMQYem9Iz1pfG07sYSxxUiI1izkkD3CWhB6L4OrYEEukiAkWUrC8hp5tnu4nkX9bWozOxwbsUShPowH7Q+tF2UiRclEIoAmwjWrWtBoltvHT36aAvlWmRGAvS0KLHF1yVGqCDhPDJSNSsJ9IKAFoReqNFKSKCLBBiaNBzS35ln9naCJYhBXsMffB8abjkNV9DiJJCLQJoENhx65sYb52x8/Oun6wQwP7UVyUIjVNcbj/L3moAWhF6r18pJIDKBNJ9nlNDMJxXnzDM7bSxBTZ7Ujc3Ck72yK9EMe0wAb50mfXYwHNAnNNax91hxQarWyl4YjVBBtK8YEliCgBaEJcB4WQISaIAAK2NnzzaxnSEV1PxqeQMMWy+Cod7p001st05jylb2TbQOWQEkUIUAltNnnmnC0ofhgC7dnraKsgLeixtCkzpNjjMaoQK2BEWSwBsEtCC8QcL/S0ACrRBoYFrICjmjZ70P6tMvAz7O16j1iI00M2kldkZ93MxZAo0RwBMBS98999RYIJNMzAdO/GpE3FLWyYOvGeevZJJu0mDRElSLlUCnCWhB6LT6FF4CfSGAazqOr3XExmPJmnEzgxI/dRPA2RXUdey4ZtrjzKRu9Zl/7wkwDySGCOvJ2ftDcqanPXkyf869V0pXKoiKeUfzpq7105izTK21MHMJDICAFoQBKNkqSqATBFjfePbZuXMWGalk+bBe/cILcyOeXBlmkarfmaxbN8ecKUouYxAZ4j/CtCf7nKffirB2EliKAMHteUj5N1fHiIEv9bRLlej13hDATkRMjVwtZx4WXtlYiuuwQc8ryD8lIIHKBLQgVEZoBhKQQC4CzBL37ZsbjFZ0tWXayUCEgY5jkVyqmSofJicYgxhrVhlo4guNBnFqcPvJVPBNLIFlCdDTYubjIa24Lagw8OWyGC4ruQlaJ5BM83icZfyk3r4+20RGUc1KAhJ4jYAWBBuCBCQQjACDUdacv/e9uX8ZrJSfhRLvIA2LmXY2eTpAMH4hxGGKgvfHj3405/iKPai8BwFDSUwP+B1Un96EAKEQEohKAAMrczZ6WiKYTGVKwHBAT4upVwNfVN3WKxfvaNpMli46Y1b11tncJSCBawhcf81f/iEBCUggCAEGFsw8+e/KldGpU6Pz50c//eno3DmkW3fu3IWXXz6/Zs3Kt7xlLmrXO94x5zPPCJh//YQigPWHzSn8hzEIJb6mvtHTTyPjp//5n//6//7fMx/60Afe9rY5V5GbbpqzMqBE3UZCaVBhek+AbjMd13f58txDeuHC6Mc/pr+98uqra7/85R+++urXbr/9xuuvf72n5fEkxJ09be9bRZkKJscBXs1Hjowef3x06VKZm95MQ0PauHHuFV9+keDNm/0mAQm0TEALQssKsHgJSGAZAgwvmFi+tkR25cqVHTt2PH3mDLes/e53T5w4sVoX92XwhfmZ8eIb4bX37t37F2fOXHfddeuefx4lrmNJ048EJNAuAUx4bwTbp6fdtGnT+VdeQaLbvvOdkydP3sp00Y8EFhLgFZwO4sGUcOzYnCnh4sWUCovCH49Gvz0abS7u4m2eDAe80Ms7phW3+0UCEghDYMXVq1fDCKMgEihF4MKFC5emtXYvnfGq1z5L/97aL+fPn7/MolCmD+O/lR1fOEqD2lOnTt15552///u//+lPf/qGG2549NFH+TMTJLNpgsDWrVuPHj2K6edzn/vcpz71KdR6+PDhe1iJ8hOAwLlz59BILkHWrFnDQ5ort5ryyVtlGvaNHZ8aFT0tT+WHP/xhjLbUSEtfTc2vl9kyejn0p396/H/9rysvv0wFb/0v/2XPH//x5m3b4vcGvVSHlZJAHQS0INRB1TwlIIHMBMYHtY/gEj/Czfb8hg0bsCUx/9yeN6pTZtnN7k0Chfng9OnTTEsuXryIErEJ3nffffvrPifsTSn8JgEJLE4As/X69evpXTEfpJ4Wo+2WLVu09C3Oy6vXEjh+/PihQ4ewynEZA+Jv//Zvf+tb3+Ii7YcOnzf1tm3bWLW59ib/koAEOkgAHwQ/EpCABCIT+NGPfpQc3RnUjsv5wgsvpF0Mu3btGr/u94AEfvKTnyRHA3xGUGghYaHczZs3k6a47hcJSKBhAjyMqUfFojde9DPPPJNmfZj5xq/7XQKJwPe+9z3aRuHnSFd/9uzZAg7til8LwwFd/fivRTK/SEACHSIw6pCsiioBCQyQQDGonWc+SCiK+eddd93l/DNs80A1abMJ/y5UE1cYU2KBZ80KhYathYJJoMcEip72/vvvX1hNpojJuEA/vPARXpjeKwMhgHWJJpG2J2BBoPHQVJaqO7sOi6g3NCecXGxLS7HyugSCE9CCEFxBiieBQROYPKhNaBiCMIJh/smIZMLYZdAcW608CppgPihEY9kTJbJO9eyzzxYX/SIBCTRAAH+utES8qPkgCcCDjKGWh5RJoJa+BpQSvAjMAdh8aQ98+II5oKTA9PDjRgd6fl/cJdGZTAJxCGhBiKMLJZGABK4hwKA2BQCfMKgtbsBJknEMg2CWRIqLfmmdADONYgfKsstNjEFZy2K7LFESWpdcASQwEAKF+YCYMstWmS1j9LT0zNy1bGIT9I8As/0JGxbK15dXg1sbyuMypQSiEdCCEE0jyiMBCcwRKAa1DDJKEmFJJM0/OXus5C0mq5VA4ULCilPJglKERfRYfkWrZM4mk4AEFhJgQTh5H5R/4jA0YETA0udu9oU8e3xlqg0L5Tm4taE8K1NKIA4BLQhxdKEkEpDA6wQK80H5QW26kxEt41pGt9PeKPrsBGYwHyQZiilNGd+T7GKboQSGQ4A54WwdJoc7Yubjw/RvOLgGW9OZNyyUJzZva8PkeArlszWlBCRQEwEtCDWBNVsJSGBGAjMPalN5WB/S3od54cRnlMbbZiKAFlLctdmsAFgf0g5bnBeW3fswk4DeJIGhE0g9LVaA2Zy2uD3F3i/vJjZ04l2rf64NC+XrPW9rA/2/fi7l6ZlSAk0S0ILQJG3LkoAEliFQDGqrOBEwCkl77z0gcBnc9fxcuJDMZj5IQmE4SAc0GLatHi2Z66AJFNuFZjMfJHaFoVBLX88aU+seAeNbG6YK09gzRVgdCYQloAUhrGoUTAKDI5D2IMy8JjbOi/kng1q2MzD4wKAw/pPfayVQmA+yrEymAxoM21arysx8aASwGtDNsn+hivkgQaN3TSetaOnrRysKNXVv3ZDRD51aCwnUQWAFmTLI9iMBCUigXQKnTp3atGkTMrDDNg1Jq8vz4IMP7t27lzhhDJTT1obqeZrDBALnz5/fsGHDpUuXcCFJFpwJiUv+dPTo0R07diS7UtraUPJGk0lAAgsJpJ6WBwo3hLTVaGGaaa/whD788MP0sfS0KS7jtDmYvl0Cly9fRoNHjhy5ePEiktB7b9u2LUh/G1m2drVm6RJok0AdZgnzlIAEJDAVgWJNLPsxfqyopNW27DlPVcEhJK4YwGICosLjGm1OSOZPEpDAZAKY9lJ/yNM6OeW0vx44cICxrAc0TMut9fQdWuen/y+MGnzxddB641GAIRNwF8OQtW/dJRCCQArrzdAz+6A2Va/YHFEltkIIUoGFKAJY1DSqY5ib1jazbI4IDFLRJFAXATpAJvk8RzX1tB7QUJfm6smXvjoFDKJVMCHvyvuR1ouLBIYwxCaWJ28EIj7WQ8hcJSCBJQloQVgSjT9IQAINEEiD2vrMB6kKbM73gIb6tIkLCRpkSMeX+kphx3VagGL46AEN9XE2514SKMwHdIb1VZDZXTqgAZeE+kox5yoE6EiZdRebTehOu3jewfg5Ebx6qEVNdrEqqL1XAj0moAWhx8q1ahKITqAY1Dbw7i/mnx7QkLdZpB0odZsPkswYDu666y6WngzblleJ5tZvApyKkrwPajUfJIYUkcIrbN++vd9UO1e7Dm1YKM/WrQ3lWZlSAhkJaEHICNOsJCCBKQikfbOshDQwqE1iFQcEspSNQWEKWU26BIEigEWTq1i7du1iOuQBDUvoxMsSuIZAMh8wq2/M2ZveNUXD5V972muU0dIfHd2wUJ6WWxvKszKlBLIQ0IKQBaOZSEAC0xFock1snmTpgEAsFyzIzPvJP6cigAsJrgd170BZVKTDhw9jRKDoJi0Xi0riRQlEJpC6O8wHzc/k8UHgIaXoxmzEkRXRimwovQcbFsqjW7i1wbd8eXqmlMBUBLQgTIXLxBKQQAYCxZpYWyPLYurrAQ0zqzPtQGnFfJBkLoIv1BS7cWYy3iiBIATYHJ7m8M2bDxKB5GhGZIQG9qkFYR5EjF5uWCjPdnxrA1vefEeUR2dKCZQkoAWhJCiTSUACeQgUC1NtDWpTNYoDApkJ56nYkHJJ5oMmd6AsSpdpSYoH5gENi/Lx4pAJJPMB+wjaDTtaHNDAlyGro7G6wzltIcF41KETFurgM761gTcFr4l2Rx111NE8JdAWAS0IbZG3XAkMkUDra2Lj0FmlSfNPfCLGr/t9MoEWd6AsFAy31RS2jaa18FevSGCABIqAL62bDxJ8JnIe0FB3O2RujMdHeqNhO6A/dIdXYu7WhrrbnvkPk4AWhGHq3VpLoAUCyXwQKrYWoy4PCJyqKSTzQagohsUBDaGa1lRUTSyBXAR4HNISNKeWtOt9MF4jD2gYp5H3O6ZwPPsISYPhAEsNXXRjITPzVqTu3NzaUDdh8x8UAS0Ig1K3lZVAOwSKQW2QNbFxCsjG+Y6MvTwgcBzLot+T+aCVqGyLyjN+MR3QYNi2cSZ+HxqBoqcN6JKDuTaZNrT05WqWbliYgeS8rQ04btAyZ8jHWyQwcAJaEAbeAKy+BGonUAxqA5oPisqniOWhltYL2YJ8SS4kMc0HCVE6oMGwbUEajGI0TICJEGbQ5MHecNHliyvi4LQVRre8qGFTomg3LFTUzrytDTRLT22oiNTbh0ZAC8LQNG59JdAoAcY6ad2J+SemhEbLnrKw4oAGt48uJJfMB+z4CL5cUxzQYNi2hUr0So8J8GCmgCDMhYJXk9lv8rdnNTi4qNHEc8NCdo2Mb21grOKLIzthM+wrAS0IfdWs9ZJA+wSKQW1Al9pF6RQHNHj4U8EHu08yH0R2ISmk5QvTkhROjInK+HW/S6CvBIqeln1Gnagj8zT27fNxwlZSX4BKtniMLwM/YaEksamSubVhKlwmlgAEtCDYDCQggVoIFIParpgPEoXigAYPCARIJ3agLGy+xQEN8ddjFwrvFQlMRYDtAGy/YmLZFfNBqh1zNg9oWFbRvEbdsLAspVwJ3NqQi6T5DIGAFoQhaNk6SqBpAkXk7W4NahMmBm0e0ACKwnxApMngO1AWtm8EJhY90yoW7lDowgRekUAPCNDTdtfjpnhNEAa1B7rIWwU3LOTlOVVu87Y2sDluqttNLIEhENCCMAQtW0cJNEqgGNR20XyQSBXzz8Ee0MCsOznNdsuFZF5DN2zbPCD+2ScCRU9LDJeO1qvoZ0KdPdkuTOarblhoVwWp9HlbG4jUqzE6gl6UIQgBLQhBFKEYEugJgWJQ213zQaGJdEDgAA9oYJyUorJ12nyQ9GjYtqI9+6VPBJje3HjjjXjZdNd8UKijsPThRl5cHNoXel3mqMmjBLXS9xrTN0IbGN/awBNHW2WQE0EwZZBAuwS0ILTL39Il0CsCxdbWHgxqk2LSAYGMG4YzmCvMB5xw2Y/Wadi2fujRWhQEkvmgT5EIk6WP+TNVK6o5kC/MSJmXJnsQsSEwvg/ZkhJW6W5tCKsaBWuFgBaEVrBbqAR6SKBPa2Lj6ikOCBzCAQ2MXJP3QQ9cSMaVWNi2mKiMX/e7BDpHAGsms03MBz3bnp0sfVStZ/Wa0MDcsDABTsyfeJXgHsLTh58IBi+3NsRUk1I1QEALQgOQLUIC/SfQV/NB0hy1S86l/T6goU87UBY+ctQuGUdY7rtKbMXTpxem8YoEghNgzsnshU8vp9mFpY+JWXBFVBHv8sWLT+zend4pblioQrKte8e3NqxaubItMSxXAi0SWEHZ9F9+JCABCSxK4PLly+fPn1/0p/GLn/zkJ19++eU/+7M/+7Vf+7Xx6/O+s76UZnHzrrf+56VLly5cuDBBjB/+8Id79ux5/vnnP/vZz/7Gb/zGhJT8hCdqOl9tcrLGfr1y5cq5c+eWLe4P//APv/GNb1DNIo7Xorcwe0lnVSz6a8SLaPb48dHTT19+5ZUtX/7yqVdfvX802lcIunLliMPwWFPauHHE8Q386UcCjRNYtgtCopdeeul3fud33vKWt+BKc8stt0yQMWxPe/G1zwTJ4UAfS0/70EMPTX6bkEm0nnbxer3R/8z9Sj985cp4slf/83++7n3vs/8ZZxL3O2Ohxx6bUyKfM2f45/hodGk02jX391xznHuVEJ3kjjt8lSQk/ttjAloQeqxcqyaBDATOnDmzfv36DBm9lgVHG5w+fTpXbhnzOXr06NatW3NliJcjkSBy5VY9HwbtN998c/V8Ug4snbGenyu3GvNhnMdo7/HHRxcvjpdycDRaNxqtHr80/n316tHdd482bx6tWjV+2e8SqJVA3i4obE+7b9++Bx54IBfJaD3tNfVaov+5Js3CP+x/FjJp/QrGAl4lp07Ne5UsI9eaNXOvEqzSvkqWIeXPnSRwXSelVmgJSEACEpDAUgRYKcLstXbt6ODBhWM+1ouWNB+QIffu3TvC4LJjx+gSy0t+JCABCUxDYGL/s0xG9j/LAGr2Z8xAvEd4mzz88MJXyTKicO/u3XOvEv69fHmZxP4sga4R0ILQNY0prwQkIAEJLEUAd4MtW0a33ZZcTJdKVeo6Q0YGf/v2OfgrhctEEpCA/U9v2gCq3LRpznyAIaDiB0M2r5IHH5y3gaVirt4ugXYJaEFol7+lS0ACEpBAJgIM1H71V+dCHuT6sGMZj2vyfG3La65czUcCEughAfuf3igVwzFzfnbA5frgg5Bc26rbI3KJZD4SqEZAC0I1ft4tAQlIQAKtE2CqTxgLnEWvjVKWRy72MiQv1jzZmYsEJNAvAvY/vdEnqsSLLV+ojmvApFdJRhv3Nbn7hwQaJaAFoVHcFiYBCUhAApkJpGHZ0aOZs52XHWER+K8OC8W8gvxTAhLoEAH7nw4pa7Ko7Fxg20KtM/xkocDY7UcCHSegBaHjClR8CUhAAkMmwJiPqAfNuIYSGYGdsRoRhtzerLsExgnY/4zT6PR3Dt3kVUIkywY+bHjZsKGBcixCAvUR0IJQH1tzloAEJCCBOgkwmWdKzxpgYx8O9HL5qDHaFiSByATsfyJrZyrZiFPAlL7JExN8lUylIBPHI6AFIZ5OlEgCEpCABMoQYMNqM0tG48LgicAKkh8JSGDgBOx/etMAUCXuJA1/eI/UumOi4epY3MAIaEEYmMKtrgQkIIF+ECBcdsZY2VMxwQ3B0xmmImZiCfSMgP1PbxRKf45HQCsfAgA3swWvldpZaK8JaEHotXqtnAQkIIFeEmDUVVO47JK4WLNq0uW1pFQmk4AEGiBg/9MA5GaKwAzdok9Z2ghjbJ1mdG0pWQloQciK08wkIAEJSKABAhyL0O6H4AvtmjDarb6lS2DIBOx/eqP91rtxXiXsjPMjga4R0ILQNY0prwQkIIGBE2DVqPnwBwuZM+xrMojjQgG8IgEJNE/A/qd55jWViPdBhFfJ3r2+SmrSsNnWR0ALQn1szVkCEpCABHITwOEzyGkIcSTJzdj8JCCBxQnEeerjSLI4qfBXAfjQQyGkjCNJCBwK0Q0CWhC6oSellIAEJCCBOQKs/DcfNHsp9ETSjrCEtZR4XpeABPISsP/Jy7PF3HBAiONEpkdbiy3BomcioAVhJmzeJAEJSEACrRB44olWil2y0LbOg1hSIH+QgARqI2D/UxvapjM+dqzpEieUhxvC0aMTfvcnCUQjoAUhmkaURwISkIAEliDAklG0YxQfe2wJWb0sAQn0i4D9T2/0iSPbhQuxavPUU7HkURoJTCSgBWEiHn+UgAQkIIE4BNo6tXsCAYahcXZVTJDTnyQggYoE7H8qAoxzOxvQon0wjsfZVRENjvLEI6AFIZ5OlEgCEpCABBYlEHPBP+BgdFF6XpSABKoQsP+pQi/UvTEX/AOaqEJpTWEiEdCCEEkbyiIBCUhAAhMI5NrC8OTVNz9P3juhwFI/Pf10qWQmkoAEOk3A/qfT6iuEv3w52264vK+SaFE2CmJ+kcACAtcvuOIFCUhAAhKQQDwCbBYg3FTVz+2j5750dXRoxYpdVXMq7o+2n7YQzC8SkEAuAvY/uUi2nk+ezQI1vEryCNY6XwUYBAF9EAahZispAQlIoPMEWDiq/jl4bM588O585gNEyiJY9aqZgwQkUB+BLI+5/U99Ciqfc5aJeh2qzCJYeQ6mlEAFAloQKsDzVglIQAISaIxAhtHV7aNP3DL64v/ILDJTiwzOEZmFMjsJSCAnAfufnDRbzStD7Nt6XiUZBGsVrIUPiYAWhCFp27pKQAIS6C6BDCP491+9ZTR6z5++GQTh6pN5eGSQLY8g5iIBCdRCIMMzbv9Ti2amzjSyKrO4ukxNxBskMDUBLQhTI/MGCUhAAhJogUCu9Zl3f2vF65+PrHh+w9UsRoRcsrWA1SIlIIESBHI94/Y/JWDXmySXy1gdqtSCUK/uzT0bAS0I2VCakQQkIAEJ1Ehg5co8mb+5i+HLo8+dHI3ePbq9csa5ZKssiBlIQAK1EMj1jNv/1KKeNjKtQ5Vt1MMyJTADAS0IM0DzFglIQAISaJzAjTfmL/Lr3xqNbrn6/soZ1yFbZaHMQAISyEagjmfc/iebeqbJaNWqaVKXS5tLlXXIVq4GppLAVAS0IEyFy8QSkIAEJNASgQxrgF9f8TxxEMYMBu9/z2h0csXnK9cog2yVZTADCUigPgIZnnH7n/rUM03OYVWZQbBpOJhWAhUIaEGoAM9bJSABCUigMQIZFmde27aw4cjVe5PQ9149smF08vGqNcggWFURvF8CEqiXQIbH3P6nXhWVzT2DO0k9qtSCUFaFpmufwPXti6AEEpCABCQggWUJZBldff7jK9733NUjV68eea28Qx9ZsevLy5a8TIIsgi1Thj9LQAKtEsjymNv/tKrD1wsPq8oMpo0IfJVhEAT0QRiEmq2kBCQggc4TuOGG0a23ZqjFrne/cRbDigzmAwRavTqDVGYhAQlEJmD/E1k7U8mGO0kGj5LRKPur5GMfm6oeJpZAiwS0ILQI36IlIAEJSGAaAnffPU3qptLGlKqp2luOBIZCIOaTHlOq4G3izjsjChhTqoiklKl9AloQ2teBEkhAAhKQQCkCAQdY+J2uWVNKeBNJQAKdJmD/02n1jQsf0OyCW4SvknEd+T02AS0IsfWjdBKQgAQkUBBggJXF+7TIsPqXu+4a4d7sRwIS6D0B+5/eqBhVRgs6ENA+1Rt1W5EaCGhBqAGqWUpAAhKQQE0EmLGH+mzcGEochZGABGokYP9TI9wGs8bsG02VAd0iGlSIRXWOgBaEzqlMgSUgAQkMmMCePYHW/ImhGG0YOuCmYdUlUDsB+5/aETdVwM6dTZVUohxeJevWlUhnEglEIaAFIYomlEMCEpCABJYnwEFc27cvn6yZFPff37+ZjZ8AABRVSURBVEw5liIBCYQgYP8TQg05hGDSvmtXjoxy5PHIIzlyMQ8JNEdAC0JzrC1JAhKQgAQyEGDenuVA74qisG1VB4SKDL1dAp0jYP/TOZUtJXAQjxLeIx4JvJSOvB6VgBaEqJpRLglIQAISWJQAEbAY+bX+2b+/dREUQAISaJqA/U/TxGsrD0t0668SIjL4KqlNw2ZcHwEtCPWxNWcJSEACEqiHABsZ2j34CvdXV43q0a25SiA6Afuf6BoqLd9997Xck+PScuutpcU1oQSiENCCEEUTyiEBCUhAAmUJsG5z4kRrJzuyf+HAgbKimk4CEugZAfuf3ig0qbKtkx3Zv4AJw48EOkhAC0IHlabIEpCABCSAA+qjj7ZwLsOqVXPl+pGABIZMwP6nN9qnS8cejSmh4Q9ebL5KGmZucfkIaEHIx9KcJCABCUigSQJsZGg4hDVLVSdPjtpasGqSrWVJQAKTCdj/TObToV/XrWvarQwLVCtmiw4pRVFjE9CCEFs/SicBCUhAAhMIbN7cnCcCS1WnT7tndYI2/EkCwyJg/9MbfRPb4vDhhjwRCHzAq4QXih8JdJaAFoTOqk7BJSABCUgAAgziGY2xpFPrh/XGs2dbjrlVawXNXAISmIGA/c8M0GLeghGhARcz/B14lRg9MWYbUKrSBLQglEZlQglIQAISiEmA6f0zz9R4OgMjywaMFDHZKpUEJDCZgP3PZD4d+pXpPa+S+s7Z4RAfXiXug+tQk1DUJQhoQVgCjJclIAEJSKBDBPBBYGTGwdp5B2cpyFZj3q0dAq6oEpBAQcD+p0DR9S9ptxqHLOaNrYjTAQ4OHuLT9eah/G8Q0ILwBgn/LwEJSEACnSbAgI+TsV54YcQ6T/UPlghGe+TGgVt+JCABCUwmYP8zmU+HfqXz37dvrvPH+6z6B+sSNuhnnx1xDLAfCfSFgBaEvmjSekhAAhKQAASKmf8998wYHIHFIhagclkiVIoEJDAcAvY/vdF1MfPnVYJaZ/jwKsEtLpclYgYBvEUCtRG4vraczVgCEpCABCTQEgE8UdNBj2fOjJ54YvT446OLF8dFeXI0+vj433xn7+vdd895HBjjah4Z/5SABKYisFz/87ej0f8zL0P7n3lAgvzJ64BXCf+dOjX3KuHfZV8lxMXgVYLHga+SIEpUjBoIaEGoAapZSkACEpBAEAJExuI/9iNcvjw6fx6hrvzLv/zan//5v3z/+5/+wAeOseuBhSY+pPEjAQlIIC8B+5+8PFvMDYtA2oYw9ir50J/92f/+P//nz9av/9P//t/n/BTYyYL5wI8EBkBAC8IAlGwVJVCBwKpVq+7HozvTh9wy5ZQ5m9WrV2esJrlllq9adjfeeGPG2pFbNXFauhux1627cuXKpocewnywcuXK/+9rX/v+sWOPPvpoV2vUEkiLrYNA3i4obE+7LqupLlpPO6lh2P9MotOp315T5eXLlzc98ADmA14lnz19+ts33XT48OEb8gZf7BQVhR0agRVXr14dWp2trwQkIAEJDJAAY74tW7acOnVq165d+/fv37Fjx9GjR5mEnDhxIuyMa4BqssoS6CUB+5/eqBVVrl+//vz585jm77vvPl4rjz/+ONYxXiXao3ujZSsymcB1k3/2VwlIQAISkEAPCKQxH+YDxnwHDhxgseiRRx7BjsAoMI0Fe1BHqyABCcQkYP8TUy8zSDVuPti3bx+vEgwHWKXPnDmzdu3ai9dGSZghf2+RQCcI6IPQCTUppAQkIAEJzE5g3phvPCPcEHBGYBTIdoY7PW1rHI3fJSCBHATsf3JQDJEHBoINGzZcuHABA/Q9nNEw9nn44Yd5leCDcPLkyTVGQxgj49deEtAHoZdqtVISkIAEJPA6AcZ8ycuAfaosGc3jwiiQAR8XGRcyBJz3q39KQAISqELA/qcKvVD3JlUuaj5Azu3bt6dXCa+b48ePh5JcYSSQnYA+CNmRmqEEJCABCUQhkMZ8/LtwyWhcRAaFWBBIhjMqexzGf/K7BCQggdkI2P/Mxi3gXUmVly5dwhI9z/tgXFq2xW3atInEbJEjRML4T36XQJ8IaEHokzatiwQkIAEJvEmg5PA93YCnMUaEc+fO3XXXXexoMKr2mxz9JgEJTE/A/md6ZkHvSOFyOMqHkAfLbnbDysCrhFvwSsDcELRKiiWBagTcxVCNn3dLQAISkEBIAgzgiGvFYI4x34Qlo0J29q+ePn168+bNRNVONxY/+UUCEpDAVATsf6bCFTnxVOYDKsL5jmfPnsUSzbY4TAnYpiPXTtkkMBsBLQizcfMuCUhAAhKISyCN+Ri6YT5gJFdS0BRPEdfTNPrn35I3mkwCEpBAQcD+p0DR9S94pRHXgFoQ42BZ74OissUBDZz+w+14oxQ/+UUC/SDgLoZ+6NFaSEACEpDA6wTS8L2kx+mi1DygYVEsXpSABJYlYP+zLKKuJGD+T1ADzAG4p61evXoGsdMBDXglYICYLYcZCvUWCTRAQB+EBiBbhAQkIAEJNEQgrflQGH6k5ZeM5gnnAQ3zgPinBCRQhoD9TxlKnUhT3XxANQmFgB8c3nDsjGN/XCcqrpASKENAC0IZSqaRgAQkIIEOEEhjPgSdecmoqOS6deuwQaxatYojvnfv3l1c94sEJCCBRQnY/yyKpYsXOY4R74MU0aCi7wDb6HiVEGeHDA8ePNhFGsosgYUE3MWwkIlXJCABCUigewTS8J2BWkZ/UQ9o6F47UGIJtEHA/qcN6rWUyS62rVu3Yj7GEs2/WcogFAIWBHa4eEBDFp5m0joBfRBaV4ECSEACEpBAVQKM+Yh6nWXJaFwUD2gYp+F3CUhgUQL2P4ti6eLFOswHcEj2CDbWeUBDF1uFMi8koAVhIROvSEACEpBAlwjUNOZLCDygoUtNQVkl0DgB+5/GkddV4IMPPoj3AdsWnnnmmVzeB4WsyT8OHwTcVTygocDil44S0ILQUcUptgQkIAEJzBFgSSeN+TJ6nC4ku3///kceeeTSpUuM/M6cObMwgVckIIEBErD/6Y3S9+3bt3fvXswHvEqY7ddUr8OHDx84cIDtDMRW5N+aSjFbCdRNQAtC3YTNXwISkIAE6iLAmI9Ih2nMl33JaJ7QHNBAVG0usl2CVcd5v/qnBCQwNAL2P73ROKp84IEH6jYfJFy7du3ygIbetJzBVkQLwmBVb8UlIAEJdJtAk2O+RIpdrCxPEW0BrwdWq7qNT+klIIEKBOx/KsCLdSv9OeYDuvd0aEIDwnlAQwOQLaJWAp7FUCteM5eABCQggVoIcMIiJ2Mx5nv00Ufr8zhdVHT2MuCGgAPq5s2b2dpAoIRFk3lRAhLoKwH7n95oFvMBPmW8SvALaLgz94CG3rSiAVZEC8IAlW6VJSABCXSbQItjvgTuypUrW7Zsefzxx9esWcPhkQ2bMLqtPKWXQMcJ2P90XIFvip9UiUcAluiGzQdJCA4M5lVCbMVWrOFvgvCbBKYk4C6GKYGZXAISkIAEWiXQ+vCd2jPWZMGK7aznzp277bbbLly40CoSC5eABBoiYP/TEOiai8EKnCLapAA3rZgPqKIHNNSsZ7Ovi4AWhLrImq8EJCABCeQlwJhv06ZNeJwy5mPlv60xX1EpQmoTWBtPVKJqe0BDgcUvEuglAfuf3qg1qZKVf14l7ERrvV4e0NC6ChRgWgJaEKYlZnoJSEACEmiBQBrzsXEgyJgvIeBwb2wZfPeAhhbahEVKoCkC9j9Nka69HDYOYInGfIATWQTzQaowwrCTAtmwR/Oaq52CBUigGgEtCNX4ebcEJCABCdRPoFgyYsYeZ8yX6s3+VQ9oqL8JWIIEWiNg/9Ma+twFM0Vfv3495oP7778fJ7Lc2VfKj9C8vErwrcPAQZzgSnl5swRqJmAkxZoBm70EJCABCVQjkMZ8nH3AmI8T1KplVtfdHtBQF1nzlUCrBOx/WsWfs/BOqJJtcXi0EVsHczm7G3LW37wkkI+AFoR8LM1JAhKQgARyE+jEmC9VmoVKD2jIrX/zk0CbBOx/2qSftezi6ESm5UzOs+adOTNaHW4IxNbxgIbMZM0uHwF3MeRjaU4SkIAEJJCVAAv7eJzifbB///6w3gdFjT2goUDhFwn0gID9Tw+UmKqA+SC9StgEF9x8gMDpgAYi/rDbArERvjeKsCK9IaAPQm9UaUUkIAEJ9IpAGvPxL2M+xlIdqtvDDz+8Y8eONApcs2ZNhyRXVAlIIBGw/+lNS+iuKh988MG9e/euXLmSeL2rV6/ujUasSA8IaEHogRKtggQkIIG+EejumC9pgrUj3FD5jvmD+Fh9U4/1kUCvCdj/9Ea9uLARVoB9ASdOnGBTQOfqdfz48a1btyI2JzXcddddnZNfgftKwF0MfdWs9ZKABCTQVQIEkcJ1Exdixkzd8j4oiDNUPXv2LG4IREZgHam47hcJSCA4Afuf4AoqLx7mA14l3TUfUFMPaCivblM2SUAfhCZpW5YEJCABCSxDII35iErY0SWj8eqxkoknAjXCDkL4LgIljP/qdwlIIBoB+59oGplZnqRKbscS3UXvg/GK8yrxgIZxIH5vnYAWhNZVoAASkIAEJPA6gT4N31OVWP7CDYFNDevWrcMmgleCypaABGISsP+JqZcZpEr7yDDanj59uh8RBDygYYZm4C31EXAXQ31szVkCEpCABKYgwOFVeJxyA2O+ri8ZFdVO8RSJ/k3t1q5dy1JS8ZNfJCCBOATsf+LooqIk/TMfACS9SjygoWLb8PZcBLQg5CJpPhKQgAQkMDsBxnx4aXI/5oP+nV/AFoYDBw6wv/q2225jnXN2TN4pAQnUQMD+pwao7WSZzAecX9Ab74OCIy4VhOblbGNeItijeaEUP/lFAg0TcBdDw8AtTgISkMCwCBAQETf+ZevMkOill17C3fRtb3vb5MSMCycnaOVX5N+9e/fkon/wgx984xvfYGj7nve8Z3JK0rB3d3Iaf5WABJYlYP9TIOp6/1NSlV/96ldfffVVXiXLxp3p7qvk+9//PuaDd73rXb/yK79S6HfRL75KFsXixeoEtCBUZ2gOEpCABCSwJAH89m+++eYlf57+h6tXr05/U+13FC7QWUpatWrVCy+8kCUrM5HAkAnY/8yg/Zj9j6rsjSpnqIi3RCPgLoZoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCGhBiKYR5ZGABCQgAQlIQAISkIAEJCABCUQkoAUholaUSQISkIAEJCABCUhAAhKQgAQkEI2AFoRoGlEeCUhAAhKQgAQkIAEJSEACEpBARAJaECJqRZkkIAEJSEACEpCABCQgAQlIQALRCKy4evVqNJmURwISkIAEJCABCUhAAhKQgAQkIIFoBP5/vUl+5PqjnbgAAAAASUVORK5CYII=
