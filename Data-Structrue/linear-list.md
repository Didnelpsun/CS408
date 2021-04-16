# 线性表

## 基本概念

### 逻辑结构

是具有相同数据类型的n个数据元素的有限序列。n表示表长。

$L=(a_1,a_2,\cdots,a_i,\cdots,a_n)$，其中$i$表示元素在线性表中的位序，从一开始。

+ 存在惟一的第一个元素。
+ 存在惟一的最后一个元素。
+ 除第一个元素之外，每个元素均只有一个直接前驱。
+ 除最后一个元素之外，每个元素均只有一个直接后继。

### 物理结构

+ 顺序存储结构：顺序表。
+ 链式存储结构：链表。

## 顺序表

把逻辑上相邻的元素存储在物理位置上也相邻的存储单元中，元素之间的关系由存储单元的邻接关系来实现。

### 定义

使用C语言的结构体定义顺序表，使用`typedef`定义一个ElemType表示数据基本类型，并定义最大长度MaxSize：

可以使用静态分配空间：

```c
// 静态顺序表
typedef struct {
    ElemType data[MaxSize];
    int length;
} StaticSequenceList;
```

也可以使用动态分配空间：

```c
// 动态顺序表
typedef struct {
    element_type *data;
    // 已分配的最大容量
    int max_size;
    int length;
} DynamicSequenceList;
```

max_size表示动态顺序表当前可以使用的最大存储空间。

### 特点

1. 随机访问，可以在$O(1)$时间内找到对应元素。
2. 存储密度高，只用存储数据。
3. 拓展容量不方便。
4. 插入删除操作不方便。

### 操作

#### 初始化

```c
// 初始化静态顺序表
void InitStaticSequenceList(StaticSequenceList* list) {
    // 初初始化静态顺序表长度为0
    list->length = 0;
}
```

静态顺序表因为数组部分在创建时就已经设置好了，所以初始化就直接设置数据长度就可以了。

```c
// 初始化动态顺序表
void InitDynamicSequenceList(DynamicSequenceList* list) {
    // 初初始化动态顺序表长度为0
    list->length = 0;
    // 申请一片连续的存储空间
    list->data = (element_type*)malloc(MAXSIZE * sizeof(element_type));
    list->max_size = MAXSIZE;
}
```

动态顺序表不仅需要设置数据长度与最大长度，还得分配数组初始空间。

#### 增长数据空间长度

只有动态顺序表才能增加。

```c
// 增长动态顺序表的数据空间长度
void IncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)realloc(list->data, new_length);
    if (space != NULL) {
        list->data = space;
        list->max_size += len;
    }
    else {
        list->max_size = 0;
        list->length = 0;
        printf("分配空间失败！");
    }
}
```

#### 插入

插入时间复杂度为：$T(n)=O(n)$，空间复杂度为$S(n)=O(1)$。
