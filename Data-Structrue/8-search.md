# 查找

## 基本概念

+ 查找：在数据集合中寻找满足某种条件的数据元素的过程。
+ 查找表（查找结构）：用于查找的数据集合，由同一类型的数据元素或记录组成。
+ 关键字：数据元素中唯一标识该元素的某个数据项的值，使用基于关键字的查找，查找结果应该唯一。
+ 静态查找表：只查找符合条件的数据元素。（顺序查找、折半查找、散列查找）
+ 动态查找表：出来要查找，还要进行删除或插入，除了查找速度还要考虑插入删除操作是否方便。（二叉查找树查找、散列查找）
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
+ 结点索引从$0$或$1$开始，相加除以二后向下取整，并且两端要移动一位，否则会有问题。
+ 数值结点为圆形，末端结点后再加一层方形的叶子结点，表示查找失败，失败的叶子结点是虚拟的，所在层数跟上层圆形结点是一样的，所以在计算查找长度时该点层数为其父结点成功结点的层数。

判定树性质：

+ 折半查找判定树一定是一个平衡二叉树。只有最下面一层不满，元素个数为$n$时树高与完全二叉树相等$h=\lceil\log_2(n+1)\rceil$。
+ 根据折半查找判定树可以计算对应的$ASL$：查找成功的$ASL$=($\sum\limits_{i=1}^n$第$i$层的成功结点数$\times i$)$\div$成功结点总数，查找失败的$ASL$=($\sum\limits_{i=1}^n$第$i$层的失败结点数$\times i$)$\div$失败结点总数。
+ 折半查找判定树也是一个二叉查找树，失败结点$=n+1$（成功结点的空链域结点数）。
+ 折半查找判定树的中序序列应该是一个有序序列。

$ASL$查找成功查找失败都一定小于折半查找树的树高，时间复杂度为$O(\log_2n)$。

查找的折半查找判定树和排序的二叉查找树都是同样的二叉逻辑结构，但是不同的是折半查找判定树是已知完整序列，所以总是从中间开始，时间性能为固定的$O(\log_2n)$，而二叉查找树的构造是根据输入来的，如果输入的序列正好是从中间切分的，则时间性能为最好的$O(\log_2n)$，如果输入的序列恰好有序，则为单枝树，时间性能为最坏的$O(n)$。

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

### 二叉查找树

即$BST$，是一种用于排序的二叉树。

#### 二叉查找树定义

二叉查找树也是二叉排序树。左子树上所有结点的关键字均小于根结点的关键字；右子树上所有结点的关键字均大于根结点的关键字；左右子树又各是一棵二叉查找树。

中序遍历二叉查找树会得到一个递增的有序序列。

#### 二叉查找树查找

1. 若树非空，目标值与根结点的值比较。
2. 若相等则查找成功，返回结点指针。
3. 若小于根结点，则在左子树上查找，否则在右子树上查找。
4. 遍历结束后仍没有找到则返回$NULL$。

遍历查找的时间复杂度是$O(\log_2n)$，则递归查找的时间复杂度是$O(\lceil\log_2(n+1)\rceil)$，其中$\lceil\log_2(n+1)\rceil$代表二叉树的高度。

查找成功的平均查找长度$ASL$，二叉树的平均查找长度为$O(\log_2n)$，最坏情况是每个结点只有一个分支，平均查找长度为$O(n)$。

#### 二叉查找树插入

+ 若原二叉查找树为空，就直接插入结点。
+ 否则，若关键字小于根结点值，插入左结点树。
+ 若关键字大于根结点值，插入右结点树。

#### 二叉查找树删除

+ 搜索到对应值的目标结点。
+ 若被删除结点$p$是叶子结点，则直接删除，不会破坏二叉查找树的结构。
+ 若被删除结点只有一棵左子树或右子树，则让该结点的子树称为该结点父结点的子树，来代替其的位置。
+ 若被删除结点有左子树和右子树，则让其结点的直接后继（中序排序该结点后一个结点，其右子树的最左下角结点，不一定是叶子结点）或直接前驱（中序排序该结点前一个结点，其左子树的最右下角结点，不一定是叶子结点）替代该结点，并从二叉查找树中删除该的结点直接后继、直接前驱，这就变成了第一种或第二种情况。

二叉查找树删除或插入时得到的二叉查找树往往与原来的不同。

#### 二叉查找树查找效率

二叉查找树的查找效率主要取决于树的高度，若是平衡二叉树，则平均查找长度为$O(\log_2n)$，若最坏情况下只有一个单枝树，则平均查找长度为$O(n)$。

若按顺序输入关键字则会得到单枝树。

查找过程来看，二叉查找树和二分查找类似。但是二分查找的判定树唯一，而二叉查找树的查找不唯一，相关关键字插入顺序会极大影响到查找效率。

从维护来看，二叉查找树插入删除操作只需要移动指针，时间代价为$O(\log_2n)$，而二分查找的对象是有序顺序表，代价是$O(n)$。

所以静态查找时使用顺序表进行二分查找，而动态查找时使用二叉查找树。

### 平衡二叉树

为了限制判定树高增长过快，降低二叉查找树的性能，规定插入时要保证平衡。

即$AVL$树，树上任意一结点的左子树和右子树的高度之差不超过$1$。

树高即树的深度。

结点的平衡因子=左子树高-右子树高。

即平衡二叉树的平衡因子只可能为$-1,0,1$。

在插入一个结点时，查找路径上的所有结点都可能收到影响。

从插入点往回（从下往上）找到第一个不平衡的结点，调整以该结点为根的子树。每次调整的对象都是最小不平衡树。

#### 平衡二叉树结点

$h$为平衡二叉树高度，$n_h$为构造此高度的平衡二叉树所需的最少结点数。

<span style="color:orange">注意：</span>平衡二叉树最少结点数（所有非叶结点的平衡因子均为$1$的）的递推公式为$n_0=0$，$n_1=1$，$n_2=2$，$n_h=1+n_{h-1}+n_{h-2}$。此时所有非叶结点的平衡因子均为$1$。

假设$T$为高度为$h$的平衡二叉树，其需要最少的结点数目为$F(h)$。

又假设$TL$，$TR$为$T$的左右子树，因此$TL$，$TR$也为平衡二叉树。

假设$FL$、$FR$为$TL$，$TR$的最少结点数，则，$F(h)=FL+FR+1$。那么$FL$、$FR$到底等于多少呢？

由于$TL$，$TR$与$T$一样是平衡二叉树，又由于我们知道$T$的最少结点数是$F(h)$，其中$h$为$T$的高度，因此如果我们知道$TL$，$TR$的高度就可以知道$FL$、$FR$的值了。

由平衡二叉树的定义可以知道，$TL$和$TR$的高度要么相同，要么相差$1$，而当$TL$与$TR$高度相同（即都等于$h-1$）时，我们算出来的$F(h)$并不能保证最小，两边都是$h-1$明显比只有一边$h-2$的结点数更多。

因此只有当$TL$与$TR$高度相差一，即一个高度为$h-1$，一个高度为$h-2$时，计算出来的$F(h)$才能最小。

此时我们假设$TL$比$TR$高度要高$1$，即$TL$高度为$h-1$，$TR$高度为$h-2$，则有$F1=F(h-1)$，$F2=F(h-2)$。

因此得到结论：$F(h)=F(h-1)+F(h-2)+1$。

+ 平衡二叉树最多结点数$2^n-1$。即该二叉树为满二叉树。

#### 平衡二叉树插入

最重要的是根据二叉查找树的大小关系算出从大到小的序列，然后把最中间的作为新根，向两侧作为左右子树。

即先找到插入路径上离插入结点最近的平衡因子的绝对值大于$1$的结点$A$，再对以$A$为根的子树，在保持二叉查找树特性的前提下调整各结点位置。

每次调整的都是最小不平衡子树。

#### 平衡二叉树删除

与插入操作类似，都是需要从下往上进行调整。

不同的是插入操作只对子树进行调整，而删除操作可能要对整个树进行调整。

在任意一棵非空二叉查找树$T_1$中，删除某结点$v$之后形成二叉查找树$T_2$，再将$v$插入$T_2$，形成二叉查找树$T_3$。

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

为了维持二叉平衡树，需要反复对树整体进行插入合删除，代价巨大，所以引入为弱化版相对平衡的二叉查找树——红黑树：

1. 每个结点或是红色，或是黑色的。
2. 根结点是黑色的。
3. 叶结点（$n+1$个虚构的外部结点、$NULL$结点）都是黑色的，保证红黑树的内部结点左右孩子均非空。
4. 不存在两个相邻的红结点（即红结点的父结点和孩子结点均是黑色的）。
5. 对每个结点，从该结点到任一叶结点的简单路径上，所含黑结点的数量相同。

所以定义某结点出发到达一个叶结点的任一简单路径上的黑结点总数（**不含**该目的结点）称为该结点的黑高（记为$bh$），根结点的黑高就是红黑树的黑高。

#### 红黑树性质

从根到叶结点的最长路径不大于最短路径的两倍。

+ 由性质⑤，当从根到任一叶结点的简单路径最短时，这条路径必然全由黑结点构成（即第二层的结点）。
+ 由性质④，当某条路径最长时，这条路径必然是由黑结点和红结点相间构成的，此时红结点和黑结点的数量相同（非第二层的其他所有结点）。

有$n$个内部结点的红黑树的高度$h\leqslant2\log_2(n+1)$。

+ 若红黑树的总高度为$h$，则根结点黑高$\geqslant\dfrac{h}{2}$，所以内部结点$n\geqslant2^{\frac{h}{2}-1}$（假设没有红结点），所以$h\leqslant2\log2(n+1)$。

红黑树查找、插入、删除的时间复杂度都是$O(\log_2n)$。

+ 插入和删除：由于红黑树的每次操作平均要旋转一次和变换颜色，而普通二叉查找树如果平衡因子在指定范围内不会旋转（如果要旋转则可能旋转多次），所以它比普通的二叉查找树效率要低一点，不过时间复杂度仍然是$O(\log_2n)$。
+ 普通查询：没有使用到红黑树的性质，所以红黑树和二叉查找树的效率相同。对于二叉平衡树而言，平衡树的效率更高。
+ 插入数据有序查询：红黑树的查询效率就比二叉查找树要高了，因为此时二叉查找树不是平衡树，它的时间复杂度$O(n)$。

#### 红黑树插入概述

假定当前结点为$x$，其父结点为$p$，叔父结点（父结点的兄弟结点）为$u$，祖父结点为$g$。

红黑树的插入过程和二叉查找树的插入过程基本类似，从右至左，右上至下。不同之处在于，红黑树中插入新结点后需要进行调整（主要通过重新着色或旋转操作进行），以满足红黑树的性质。

+ 插入红黑树中的结点$x$初始着为红色。

假设新插入的结点初始着为黑色，那么这个结点质在的路径比其他路径多出一个黑结点（几乎每次插入都破坏性质⑤），调整起来也比较麻烦。如果插入的结点是红色的，此时所有路径上的黑结点数量不变，仅在出现连续两个红结点时才需要调整，而且这种调整也比较简单。

父结点|叔结点|插入类型|操作
:----:|:------:|:------:|:--:
黑|-|-|无需操作
红|黑|左左|右旋，变色
红|黑|右右|左旋，变色
红|黑|左右|左旋，右旋，变色
红|黑|右左|右旋，左旋，变色
红|红|-|父叔变黑，祖父变色，祖父变为当前结点，递归调整

+ 父叔同色：只进行变色操作。
+ 父叔异色，需要平衡二叉树同样的旋转：
  + 父亲是左儿子，自己是左儿子，进行$L$旋转。
  + 父亲是右儿子，自己是右儿子，进行$R$旋转。
  + 父亲是左儿子，自己是右儿子，进行$LR$旋转。
  + 父亲是右儿子，自己是左儿子，进行$RL$旋转。

以$1\sim7$的序列构建红黑树：

![红黑树插入][red-black]

虽然有六种情况，但是由于两种是镜像的，所以归纳为四种。

#### 父结点黑

默认插入结点为红色，且父结点为黑，所以此时插入后不影响黑高和平衡，从而不需要调整。

插入$2$，只有一个父结点为根结点，没有叔结点，直接插入到$1$的右子树位置，没有其他变化。

#### 父结点红叔结点黑同侧插入

即插入类型为左左或右右，即在其祖父结点的左子树的左侧插入元素或其祖父结点的右子树的右侧插入元素。

由于插入结点为红色，父结点也为红色，不能出现连续的红色，所以就要变色，此时就应该先旋转。

由于是同侧插入，所以应该往另一侧旋转，旋转方式与二叉查找树一样，旋转完成后重新涂色。

插入$3$，$3$插入$2$的右子树位置，其父结点$2$为红色，而叔结点为$1$的左$NULL$结点为黑色，所以需要旋转，由于插入的是$2$的右侧，而$2$是其父结点的右子树，所以是同侧插入，需要反方向向左旋转，$2$结点上升变为根结点，$2$的左侧$NULL$结点给$1$结点的右侧，$1$下沉，$3$同样上升，完成旋转。然后涂色，根结点$2$为黑色，$NULL$为黑色，所以中间的$1$和$3$都涂成红色。

#### 父结点红叔结点黑异侧插入

即插入类型为左右或右左，即在其祖父结点的左子树的右侧插入元素或其祖父结点的右子树的左侧插入元素。

此时红黑树末端会不平衡，此时就需要向插入的同侧方向旋转一下，从而变成父结点红树结点黑同侧插入的情况，再按照这个类型的处理方式进行处理。

插入$5$，注意此时图中是按同侧插入，即$5$是插入到$4$这个右子树的右侧的，而现在我们将$5$插入到$4$的左子树位置。$5$的父结点$4$是红色的，其叔结点$3$的左$NULL$结点是黑色的，而$5$插入的位置是$4$所在右子树的结点左侧，所以符合异侧插入的处理方式。首先对$4$和$5$这个子树进行右旋，将$5$右侧的$NULL$给$4$的左子树位置，$5$上升变成$3$的子结点，$4$下沉变成$5$的子结点。此时就是同侧插入插入的情况。再进行左旋，$5$的左$NULL$结点给当前父结点$3$的右子树位置，$5$上升变为父结点，变成$2$的子结点，$3$、$4$下沉变为$5$的子结点。此时红黑树形态一样，但是$2$的子结点从$1$和$4$变成了$1$和$5$。

#### 父结点红叔结点红

由于插入结点为红色，父结点也为红色，不能出现连续的红色，所以就要变色。

这种情况是不需要进行旋转的。

由于父结点和叔结点都是红色，不能连续红色，所以将父结点和叔结点都涂为黑色；由于父结点和叔结点都是红色，所以其祖父结点一定是黑的，涂为黑色。此时将当前结点移动到祖父结点上，查看先祖结点的涂色是否正确，递归这个逻辑直到根结点，根结点一定是黑色的。

插入$4$，$4$插入$3$的右子树位置，由于不能连续的红色，所以其父结点$3$和叔结点$2$都变为黑色，祖父结点变为红色，由于祖父结点$2$为根结点，所以重新变成黑色。

#### 红黑树删除概述

红黑树的播入操作容易导致连续的两个红结点，破坏性质④。而删除操作容易造成子树黑高的变化（删除黑结点会导致根结点到叶结点间的黑结点数量减少），破坏性质⑤。

所以红黑树删除要比红黑树插入更复杂。

删除过程也是先执行二叉查找树的删除方法。若待删结点有两个孩子，不能直接删除，而要找到该结点的中序后继（或前驱）填补，即右子树中最小的结点，然后转换为删除该后继结点。由于后继结点至多只有一个孩子，这样就转换为待删结点是叶结点或仅有一个孩子的情况。

+ 前驱结点为二叉查找树中序遍历中当前点的前一个结点，往往在其左子树的最右测。
+ 后继结点为二叉查找树中序遍历中当前点的后一个结点，往往在其右子树的最左测。

对于二叉查找树删除而言有三种情况：

1. 被删除结点无子结点， 直接删除。
2. 被删除结点只有一个子结点，用子结点替换要被删除的结点。
3. 被删除结点有两个子结点，可以用前驱结点或者后继结点进行替换删除操作。

第一种情况不用多考虑，融合后两种情况并结合红黑树特性分为三种情况。

以完成所有插入后的红黑树为例。

$x$为父亲的左儿子：

+ 兄弟为红色：将兄弟变成黑色，父节点变成红色；对父节点左旋，恢复左子树的黑色高度，左侄子成为新的兄弟。
+ 兄弟为黑色，左右侄子为黑色：兄弟变成红色，$x$指向父节点，继续进行调整。
+ 兄弟为黑色，右侄子为黑色（左侄子为红色）：左侄子变成黑色，兄弟变成红色；兄弟右旋，恢复右子树的黑色高度，左侄子成为新的兄弟。
+ 兄弟为黑色，右侄子为红色：兄弟变成父节点颜色，父节点和右侄子变成黑色；父节点左旋，$x$指向整棵树的根节点，结束循环

#### 填充结点红

即删除后用来填补该位置的结点为红色结点。

此时无论当前结点是什么颜色，删除后不影响黑高，所以不影响红黑树平衡。

1. 当前结点为红：删除$4$，后继结点$5$为红结点，所以直接$5$替换$4$的位置并变红，其他不变。
2. 当前结点为黑：删除$6$，后继结点$7$为红结点，所以直接$7$替换$6$的位置并变黑，其他不变。

#### 填充结点黑且为左结点

即删除后用来填补该位置的结点为黑色结点，且该结点为其父结点的左子结点。

1. 填充结点的兄弟结点是红结点：删除$2$，前驱结点$1$为黑结点，其兄弟结点$4$为红结点。
2. 填充结点的兄弟结点是黑色，同时兄弟结点的右子结点是红色的，左子结点任意颜色：删除$4$，前驱结点$3$为黑结点，其兄弟结点$6$为黑结点，$6$的右子结点$7$为红结点。

#### 填充结点黑且为右结点

即删除后用来填补该位置的结点为黑色结点，且该结点为其父结点的右子结点。

#### 红黑树与二叉查找树

由二叉查找树树的“高度平衡”，降低到红黑树的“任一结点左右子树的高度，相差不超过两倍”的“适度平衡”，也降低了动态操作时调整的频率。对于一棵动态查找树，如果插入和删除操作比较少，查找操作比较多，采用$AVL$树比较合适，否则采用红黑树更合适。

二叉查找树使用平衡因子来约束树高，而红黑树用黑高相同约束树高。

二叉查找树只要平衡因子不超过$1$的绝对值就不用每次调整树整体，而红黑树每次插入货删除都需要进行对树进行调整。

#### 红黑树与B树

红黑树在被发明之初被称为平衡二叉$B$树，所以红黑树与$B$树之间必然有联系。

+ 将红黑树的所有红色结点上移到和他们的父结点同一高度上组成一个$B$树结点，就会得到一棵四阶$B$树。
+ 红黑树的黑色结点个数与四阶$B$树的结点总个数相等。
+ 在所有的$B$树结点中，黑色结点是父结点，红色结点是子结点。黑色结点在中间，红色结点在两边。

![red-black-b]

## 树表查找

### B树

即多路平衡查找树，要求掌握基本特定点、操作。

#### B树定义

为了保证$m$叉查找树中每个结点都能被有效利用，避免大量结点浪费导致树高过大，所以规定$m$叉查找树中，除了根结点以外（根结点最小为$1$）：

+ 任何结点至少有$\lceil\dfrac{m}{2}\rceil$个分叉，即至少包含$\lceil\dfrac{m}{2}\rceil-1$个结点。
+ 至少有两棵子树。
+ 数据最下面的为终端结点，查询失败的结点为叶节点。

为了保证$m$叉查找树是一棵平衡树，避免树偏重导致树高过大，所以规定$m$叉查找树中任何一个结点，其所有子树的高度都要相同。

而能保证这两点的查找树，就是一棵$B$树，即多路平衡查找树，多少叉，就是一棵多少阶的$B$树。

非叶结点定义：$\{n,P_0,K_1,P_1,\cdots,K_n,P_n\}$。其中$K_i$为结点关键字，$K_1<K_2<\cdots<K_n$，$P_i$为指向子树根结点的指针。$P_{i-1}$所指子树所有结点的关键字均小于$K_i$，$P_i$所指子树的关键字均大于$K_i$。

#### B树性质

+ 树的每个结点至多包含$m$棵子树，至多包含$m-1$个关键字。
+ 若根结点不是终端结点，则至少有两颗子树，有一个关键字。
+ 任意结点的每棵子树都是绝对平衡的。所有结点的平衡因子均等于$0$的。
+ 除根结点以外的所有非叶结点至少有$\lceil\dfrac{m}{2}\rceil$棵子树，即至少包含$\lceil\dfrac{m}{2}\rceil-1$个结点。
+ 每个结点中的关键字是有序的。子树$0$<子树$1$<子树$2$<……。
+ 所有叶结点都出现在同一个层次上且不带信息。（可以视为外部结点或类似于折半查
找判定树的查找失败结点，实际上这些结点不存在，指向这些结点的指针为空）。
+ $B$树最底端的失败的不存在的结点就是常说的叶子结点，而最底端的存在数据的结点就是终端结点。（一般的树的叶子结点和终端结点都是指最底端的有数据的结点）
+ 携带数据的是内部结点，最底部的叶子结点也称为外部结点。

$B$树相关性质计算涉及多个单元，注意一定要区分：

+ 树高（默认是不包含无数据的叶子结点）。
+ 子树棵数。
+ 关键字。
+ 结点（结点数往往小于关键字数）。

#### B树树高与关键字

$B$树中的大部分操作所需的磁盘存取次数与$B$树的高度成正比。高度一般与关键字相关。

计算$B$树高度大部分不包括叶子结点。若含有$n$个关键字的$m$阶$B$树。

+ 最小高度：让每个结点尽可能满，有$m-1$个关键字，$m$个分叉，则一共有$(m-1)(m^0+m^1+m^2+\cdots+m^{h-1})$个结点，其中$n$小于等于这个值，从而求出$h\geqslant\log_m(n+1)$。
+ 最大高度：
  + 让各层分叉尽可能少，即根结点只有两个分叉，其他结点只有$\lceil\dfrac{m}{2}\rceil$个分叉，所以第一层$1$个，第二层$2$个，第$h$层$2(\lceil\dfrac{m}{2}\rceil)^{h-2}$个结点，而$h+1$层的叶子结点有$2(\lceil\dfrac{m}{2}\rceil)^{h-1}$个，且$n$个关键字的$B$树必然有$n+1$个叶子结点，从而$n+1\geqslant2(\lceil\dfrac{m}{2}\rceil)^{h-1}$，即$h\leqslant\log_{\lceil\frac{m}{2}\rceil}\dfrac{n+1}{2}+1$。
  + 让各层关键字尽可能少，记$k=\lceil\dfrac{m}{2}\rceil$。第一层最少结点数和最少关键字为$1$；第二层最少结点数为$2$，最少关键字为$2(k-1)$，第三层最少结点数为$2k$，最少关键字为$2k(k-1)$，第$h$层最少结点数为$2k^{h-2}$，最少关键字为$2k^{h-2}(k-1)$，从而$h$层的$m$阶$B$树至少包含关键字总数$1+2(k-1)(k^0+k^1+\cdots+k^{h-2})=1+2(k^{h-1}-1)$，若关键字总数小于这个值，则高度一定小于$h$，所以$n\geqslant 1+2(k^{h-1}-1)$，则$h\leqslant\log_{\lceil\frac{m}{2}\rceil}\dfrac{n+1}{2}+1$。

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

若导致原结点关键字数量超过上限溢出（$m-1$个关键字），就从中间位置$\lceil\dfrac{m}{2}\rceil$（如果是偶数则默认是$\lceil\dfrac{m}{2}\rceil-1$）分开，将左部分包含的关键字放在原来结点，右部分包含的关键字放在一个新结点，并插入到原结点的父结点的后一个位置上，而在原结点的父结点连接后的结点后移一个连接让位给分割出来的右半部分结点，中间的一个结点$\lceil\dfrac{m}{2}\rceil$插入到原结点的父结点上，并考虑在父结点的顺序对指针进行调整保证顺序。

若父结点插入时也溢出了，则同理在父结点的中间进行分割，左半部分在原来父结点；右半部分新建一个父结点，并把中间结点右边开始的所有连接移动到新父结点上；中间的结点上移到祖父结点，如果没有就新建，然后建立两个指针分别指向原父结点和新父结点。

#### B树删除

若被删除关键字在终端结点，且结点关键字个数不低于下限，则直接删除该关键字，并移动后面的关键字。

若被删除关键字在非终端结点，则用直接前驱或直接后继来替代被删除关键字，然后后面的元素直接前移：

+ 直接前驱：当前关键字左侧指针所指子树遍历到最右下的元素。
+ 直接后继：当前关键字右侧指针所指子树遍历到最左下的元素。

若被删除关键字在终端结点，但是结点关键字个数删除后低于下限：

+ 右兄弟够借：若原结点右兄弟结点里的关键字在删除一个后高于下限，则可以用结点的后继以及后继的后继来顶替：
   1. 将原结点在父结点的连接的后一个关键字（后继元素）下移到原结点并放在最后面。
   2. 将原结点右兄弟结点的第一个关键字上移插入到下移的元素的空位。
   3. 原结点右兄弟结点里的关键字全部前移一位。
+ 左兄弟够借：若原结点里右兄弟的关键字在删除一个后低于下限，但是左兄弟的结点足够，则可以用结点的前驱以及前驱的前驱来顶替：
   1. 将原结点在父结点的连接的前一个关键字（前驱元素）下移到原结点并放在最前面，其余元素后移。
   2. 将原结点左兄弟结点的最后一个关键字上移插入到原结点父结点的连接的前面。
   3. 原结点左兄弟结点里的关键字全部前移一位。
+ 左右兄弟都不够借：若左右兄弟结点的关键字个数均等于下限值，则将关键字删除后与左或右兄弟结点以及父结点中的关键字进行合并：
   1. 将原结点的父结点连接后的关键字插入到原结点关键字最后面。
   2. 将原结点的左或右兄弟结点的关键字合并到原结点（前插或后插），并将连接也转移到原结点上。
   3. 若父结点的关键字个数又不满于下限，则父结点同样要于与它的兄弟父结点进行合并，并不断重复这个过程。
   4. 若父结点为空则删除父结点。（兄弟合并，父亲下沉）

### B+树

$B+$树考的并不是很深。用于数据库。

与分块查找的思想类似，是对$B$树的一种变型，多用于索引结构。

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
+ 除留余数法：散列函数(关键字)=关键字$\%p$，$p$一般是**不大**于表长的最大质数。这种方法使用较多，关键是选取较理想的$p$值，使得每一个关键字通过该函数转换后映射到散列空间上任一地址的概率都相等，从而尽可能减少发生冲突的可能性。一般情形下，取$p$为一个素数较理想，如果是合数则因为可以被多个数整除从而多个关键字余数相同造成冲突。

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

#### 查找实现

先通过散列函数计算目标元素存储地址，然后根据解决冲突的方法进行下一步的查询。

如果使用拉链法通过散列函数计算得到存储地址为空，则可以直接代表查找失败，这时候一般定义查找长度这里不算。

而如果使用开放地址法计算得到空位置的时候，代表查找失败，但是这时候需要定义查找长度要算这个地址。

若散列函数设计得足够好，散列查找时间复杂度可以达到$O(1)$，即不存在冲突。

散列表的查找效率取决于三个因素：散列函数、处理冲突的方法和装填因子。

**装填因子**=表中记录数÷散列表长度。装填因子代表一个散列表中的满余情况，越大则查找效率越低。

若只给出了装填因子$\alpha$，则此时平均查找长度为：$ASL=\dfrac{1}{2}(1+\dfrac{1}{1-\alpha})$。

#### 查找长度计算

以题目为例：

现有长度为$11$且初始为空的散列表$HT$，散列函数是$H(key)=key\%7$，采用线性探查 （线性探测再散列）法解决冲突。将关键字序列$87,40,30,6,11,22,98,20$依次插入$HT$。

首先构造散列表：

0|1|2|3|4|5|6|7|8|9|10
:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:
98|22|30|87|11|40|6|20

查找失败的平均查找长度：

+ 即获得一个新数据，在散列表中查找，发现找不到，那么如何判断找不到？**当前位置为空**，如比较到索引$8$后没有其他数据了，这时查询失败。（特别是有些题目数据存储位置是间断的，一定要注意到为空的位置就算查询失败）
+ 首先由于模是模$7$，所以数据插入的范围是$0\sim6$，所以查找的范围是$0\sim6$。
+ 比如查找一个值，模$7$后为$0$，从$0$开始一直对比到$8$这个位置，一共比较了$9$次。
+ 同理一直到$6$结束，因为模运算结果是从$0\sim6$，所以一共$9+8+7+6+5+4+3=42$次。
+ 由于是模$7$所以一共有比较七轮，所以最后平均查找长度为$42/7=6$。

计算查找成功的平均查找长度：

+ 计算成功的长度，就是记录下每个数值比较了几次找到可存储的空间。
+ 其中除了$20$前六个都是正好在对应的位置上，最后一个$20$本来应该在$6$位置上，因为冲突所以放在了$7$上，所以一共要对比$1+1+1+1+1+1+1+2=9$次。
+ 由于一共$8$个数据，所以总的要比较$8$次，所以平均查找长度为$9/8=1.125$。

[red-black]:data:image/png;base64,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

[red-black-b]:data:image/png;base64,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IECAAAECBAg0FRD7aypoeQIECBAgQIAAAQIECBAgQIAAAQJ1Coj91dkuSkWAAAECBAgQIECAAAECBAgQIECgqYDYX1NByxMgQIAAAQIECBAgQIAAAQIECBCoU0Dsr852USoCBAgQIECAAAECBAgQIECAAAECTQXE/poKWp4AAQIECBAgQIAAAQIECBAgQIBAnQJif3W2i1IRIECAAAECBAgQIECAAAECBAgQaCog9tdU0PIECBAgQIAAAQIECBAgQIAAAQIE6hQQ+6uzXZSKAAECBAgQIECAAAECBAgQIECAQFMBsb+mgpYnQIAAAQIECBAgQIAAAQIECBAgUKeA2F+d7aJUBAgQIECAAAECBAgQIECAAAECBJoKiP01FbQ8AQIECBAgQIAAAQIECBAgQIAAgToFxP7qbBelIkCAAAECBAgQIECAAAECBAgQINBUQOyvqaDlCRAgQIAAAQIECBAgQIAAAQIECNQpIPZXZ7soFQECBAgQIECAAAECBAgQIECAAIGmAmJ/TQUtT4AAAQIECBAgQIAAAQIECBAgQKBOAbG/OttFqQgQIECAAAECBAgQIECAAAECBAg0FRD7aypoeQIECBAgQIAAAQIECBAgQIAAAQJ1Coj91dkuSkWAAAECBAgQIECAAAECBAgQIECgqYDYX1NByxMgQIAAAQIECBAgQIAAAQIECBCoU+BDdRarllK98cbkypVaCnN9Of7Pf/3X//v7v7/+vSp+u/nmmz+RgrzzThWluaEQH/7w5Pbbb3jPrwQIDFvglVdeeeutt+qs4111Fiul0ltW2zQKRqBfAjmRzul0lT8v33TTO+++W2HR9s6lP7F3Nu2HAAEC9QhcuXLljVr78/SZ6TnrsaqzJCu7u7t1lqyKUj377OTs2SpKsq8Q/+sf//F//+lP+95e/hu33nrrqynFa68tvyj7S3DXXZOXXtr/tncIEBiwwN13333p0qU6K1jvAVhvWeceo1QEeieQE+mcTlf5c9s//dNrf/xjhUXbO5d+de9s2g8BAgTqETh79uyztfbn6TPTc9ZjVWdJjPmts12UigABAgQIECBAgAABAgQIECBAgEBTAbG/poKWJ0CAAAECBAgQIECAAAECBAgQIFCngNhfne2iVAQIECBAgAABAgQIECBAgAABAgSaCoj9NRW0PAECBAgQIECAAAECBAgQIECA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BAgQIECAAAECBAjsFxD722/iHQIECBAgQIAAAQIECBAgQIAAAQJDEBD7G0IrqgMBAgQIECBAgAABAgQIECBAgACB/QJif/tNvEOAAAECBAgQIECAAAECBAgQIEBgCAJif0NoRXUgQIAAAQIECBAgQIAAAQIECBAgsF9A7G+/iXcIECBAgAABAgQIECBAgAABAgQIDEFA7G8IragOBAgQIECAAAECBAgQIECAAAECBPYLiP3tN/EOAQIECBAgQIAAAQIECBAgQIAAgSEIiP0NoRXVgQABAgQIECBAgAABAgQIECBAgMB+AbG//SbeIUCAAAECBAgQIECAAAECBAgQIDAEAbG/IbSiOhAgQIDAYQJ/+ctfDvuT9w8TuALtMBrvEyBwEoEr//mfJ/m4z+4J/O1vf3vnnXdYECBAgACBFgXE/o7CvHTlSp0H3pTq9b/+9aiiL+9vOV+58t//vbztH7XlXM2+8cYbR33C3wgQGJBArp3uueeeX//619XWqc7+KIeYO37zmzvuuOOtt96qlk7BCBCoX+Ds2bMff+65V6os6JXJ5K+1nku//vrrH//4x1977bUq5RSKAIGRCtR8HX358uWRtspJqr2yu7t7ks+P5bMvv/zyww8/nH+f+sxnHvznf66t2g//7GdPvvzy1772tVtuuaW2sv30pz/9v//xH68+9NBH6ivb//i3f5v83d898cQTX/ziF2tzUx4CBNoVSNzq85///IsvvvjZz3729ttvb3flraztG9/4xv+8/fYcZVpZW7sr2Xzlla1///e4vfTSSx/+8IfbXbm1ESAweIHcejl37tyzzz77xX/91+/9y79UWN+Pf+c7k3/4hzOf/3yFZfv973//wx/+8NZbb00PnH8rLKEiESAwKoFERdKlv/LKK/fff//a2lptdX/hhRd+85vffPrTn37qqaf0mUe1TmJ/fmYF3nzzza9+9ashu/nmm7/+9a+//fbbs3+t4fVvf/vbFO/ee++toTD7y/Dcc8+leDHc/6elv5NTqI985CMpXrqG3FNdenkUgACBjgTSk5d438bGRkebaL7a9EW5D9F8PR2tIXQpYRiD2dEmrJYAgUEK5OQ5J1qVd3G5Przrrruq9f/e974XwBTy1VdfrbaQCkaAwOAFcsn8uc99Lt1RtbGRNEHOVEtmT82FrGFXmdRQiHrKkANtiQ3lbOB3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
