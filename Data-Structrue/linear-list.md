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

### 顺序表特点

1. 随机访问，可以在$O(1)$时间内找到对应元素。
2. 存储密度高，只用存储数据。
3. 拓展容量不方便。
4. 插入删除操作不方便。

### 顺序表定义

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

### 顺序表操作

#### 顺序表初始化

```c
// 初始化静态顺序表
int InitStaticSequenceList(StaticSequenceList* list) {
    // 初初始化静态顺序表长度为0
    list->length = 0;
    return 0;
}
```

静态顺序表因为数组部分在创建时就已经设置好了，所以初始化就直接设置数据长度就可以了。

```c
// 初始化动态顺序表
int InitDynamicSequenceList(DynamicSequenceList* list) {
    // 初初始化动态顺序表长度为0
    list->length = 0;
    list->max_size = 0;
    // 申请一片连续的存储空间
    element_type* space = (element_type*)malloc(MAXSIZE * sizeof(element_type));
    if (space != NULL) {
        list->data = space;
        list->max_size = MAXSIZE;
        return 0;
    }
    else {
        list->max_size = 0;
        printf("InitDynamicSequenceList:初始化动态顺序表失败！\n");
        return 1;
    }
}
```

动态顺序表不仅需要设置数据长度与最大长度，还得分配数组初始空间。

#### 顺序表增长数据空间长度

只有动态顺序表才能增加。

```c
// 分配其他地址增长动态顺序表的数据空间长度
int OtherIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    if (len <= 0) {
        printf("OtherIncreaseDynamicSequenceList:申请空间应该大于0！\n");
        return 1;
    }
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)malloc(new_length * sizeof(element_type));
    if (space != NULL) {
        // 建立中间变量
        list->data = space;
        int* temp = list->data;
        for (int i = 0; i < list->length; i++) {
            list->data[i] = temp[i];
        }
        list->max_size = new_length;
        free(temp);
        return 0;
    }
    else {
        printf("OtherIncreaseDynamicSequenceList:重新分配地址增长动态顺序表空间失败！\n");
        return 1;
    }
}
```

```c
// 重新分配地址增长动态顺序表的数据空间长度
int ReIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    if (len <= 0) {
        printf("ReIncreaseDynamicSequenceList:申请空间应该大于0！\n");
        return 1;
    }
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)realloc(list->data, new_length * sizeof(element_type));
    if (space != NULL) {
        list->data = space;
        list->max_size += len;
        return 0;
    }
    else {
        list->max_size = 0;
        list->length = 0;
        printf("ReIncreaseDynamicSequenceList:分配其他地址增长动态顺序表空间失败！\n");
        return 1;
    }
}
```

#### 顺序表插入

倒序移动元素，最后将数据插入对应索引并长度减一。

插入时间复杂度为：$T(n)=O(n)$，空间复杂度为$S(n)=O(1)$。

```c
// 插入静态顺序表
void InsertStaticSequenceList(StaticSequenceList* list, int index, element_type elem) {
    if (list->length == MAXSIZE) {
        printf("InsertStaticSequenceList:静态顺序表空间不足，插入失败！\n");
        return 1;
    }
    if (index > list->length || index < 0) {
        printf("InsertStaticSequenceList:插入索引超过静态态顺序表索引范围！\n");
        return 1;
    }
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = elem;
    list->length++;
    return 0;
}
```

```c
// 插入动态顺序表
int InsertDynamicSequenceList(DynamicSequenceList* list, int index, element_type elem) {
    if (list->length == MAXSIZE) {
        ReIncreaseDynamicSequenceList(list, 1);
    }
    if (index > list->length || index < 0) {
        printf("InsertDynamicSequenceList:插入索引超过动态顺序表索引范围！\n");
        return 1;
    }
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = elem;
    list->length++;
    return 0;
}
```

#### 顺序表删除

正序移动元素并长度减一。

顺序表的删除时间复杂度为：$T(n)=O(n)$，空间复杂度为$S(n)=O(1)$。

```c
// 删除静态顺序表
int DeleteStaticSequenceList(StaticSequenceList* list, int index, element_type *elem) {
    if (index >= list->length || index < 0) {
        printf("DeleteStaticSequenceList:删除索引超过静态态顺序表索引范围！\n");
        return 1;
    }
    *elem = list->data[index];
    for (int i = index; i < list->length; i++) {
        list->data[i] = list->data[i+1];
    }
    list->length--;
    return 0;
}
```

```c
// 删除动态顺序表
int DeleteDynamicSequenceList(DynamicSequenceList* list, int index, element_type *elem) {
    if (index >= list->length || index < 0) {
        printf("DeleteDynamicSequenceList:删除索引超过动态态顺序表索引范围！\n");
        return 1;
    }
    *elem = list->data[index];
    for (int i = index; i < list->length; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return 0;
}
```

#### 顺序表查找

按位查找时间复杂度为$T(n)=O(1)$。

```c
// 按位获取静态顺序表元素
element_type GetStaticSequenceListElement(StaticSequenceList list, int index) {
    if (index >= list.length || index < 0) {
        printf("GetStaticSequenceListElement:查找索引超过静态顺序表索引范围！\n");
        return NULL;
    }
    return list.data[index];
}
```

```c
// 按位获取动态顺序表元素
element_type GetDynamicSequenceListElement(DynamicSequenceList list, int index) {
    if (index >= list.length || index < 0) {
        printf("GetDynamicSequenceListElement:查找索引超过动态态顺序表索引范围！\n");
        return NULL;
    }
    return list.data[index];
}
```

按值查找一般都是找到第一个元素等于指定值的元素，返回其位序，如果没有找到就返回-1。按位查找时间复杂度为$T(n)=O(n)$。

```c
// 按值获取静态顺序表索引
int LocateStaticSequenceListElement(StaticSequenceList list, element_type elem) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i] == elem) {
            return i;
        }
    }
    printf("LocateStaticSequenceListElement:未能定位到对应值的元素！\n");
    return -1;
}
```

```c
// 按值获取动态顺序表索引
int LocateDynamicSequenceListElement(DynamicSequenceList list, element_type elem) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i] == elem) {
            return i;
        }
    }
    printf("LocateDynamicSequenceListElement:未能定位到对应值的元素！\n");
    return -1;
}
```

## 单链表

每个结点只包含一个指针域，也称为线性链表。

通常用头指针来标识一个单链表，如单链表L。

### 单链表特点

+ 不要求大量连续空间，删除和插入方便。
+ 不可随机存取。
+ 要花费多余空间存放指针。

### 单链表定义

使用LinkNode表示一个单链表结点的结构体，而使用LinkList表示一个单链表，其实LinkList是一个指向LinkNode的指针变量。如定义LinkList L等价于LinkNode* L。

```c
// 链表结点
typedef struct {
    element_type data;
    struct LinkNode* next;
} LinkNode, *LinkList;
```

### 单链表操作

#### 单链表初始化

有带头节点与不带头节点的初始化的区别，带头节点代表第一个结点不存放数据，只是用于标识单链表的开始，但是区别不大，带头结点更好使用。

```c
// 初始化无头节点单链表
int InitLinkListWithoutHead(LinkList list) {
    list = NULL;
    return 0;
}
```

```c
// 初始化有头节点单链表
int InitLinkListWithHead(LinkList list) {
    list = (LinkNode*)malloc(sizeof(LinkNode));
    if (list == NULL) {
        return 1;
    }
    list->next = NULL;
    return 0;
}
```

#### 单链表插入

插入方式一共分为下面几种：

+ 按位序插入：
  + 带头点结。
  + 不带头结点。
+ 指定结点插入：
  + 前插入。
  + 后插入。

假定从第一个结点开始就是第0索引的结点。

带头结点的单链表头结点就是0号结点，不带头节点的第一个数据结点就是0号结点。

带头结点的单链表只能往头结点之后插入，所以插入索引必须从1开始。

```c
int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
    if (index < 1) {
        printf("InsertLinkListWithHead:插入索引值过小！\n");
        return 1;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkNode* p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != NULL && i < index-1) {
        p = p->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index-1) {
        printf("InsertLinkListWithHead:插入索引值过大！\n");
        return 1;
    }
    // 此时i==index-1
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    if (s == NULL) {
        printf("InsertLinkListWithHead:分配内存失败！\n");
        return 1;
    }
    s->data = elem;
    // 将p原来的后继给新的结点
    s->next = p->next;
    p->next = s;
    return 0;
}
```

不带头结点的单链表可以插入到第一个位置，所以插入所以插入索引可以为0。当插入索引为0时需要特殊处理，其他则基本不变。

```c
// 插入无头节点单链表元素
int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
    if (index < 0) {
        printf("InsertLinkListWithoutHead:插入索引值过小！\n");
        return 1;
    }
    if (index == 0) {
        LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data = elem;
        // 将s的后继设为list指针
        s->next = list;
        // 将list指针设置为s指针
        list = s;
        return 0;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkNode* p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != NULL && i < index - 1) {
        p = p->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        printf("InsertLinkListWithoutHead:插入索引值过大！\n");
        return 1;
    }
    // 此时i==index-1
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    if (s == NULL) {
        printf("InsertLinkListWithoutHead:分配内存失败！\n");
        return 1;
    }
    s->data = elem;
    // 将p原来的后继给新的结点
    s->next = p->next;
    p->next = s;
    return 0;
}
```

头插法建立单链表：

+ 每个结点的插入时间为$O(1)$，设单链表长为n，则总时间复杂度为$O(n)$。
+ 实现了输入数据的就地逆置。

尾插法建立单链表

+ 增设尾指针r。
+ 生成的链表中结点数据与输入数据顺序一致。
+ 总时间复杂度为$O(n)$。

```c
// 后插入单链表元素
int InsertNextLinkNode(LinkNode* node, element_type elem) {
    if (node == NULL) {
        return 1;
    }
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    // 如果分配空间失败
    if (s == NULL) {
        printf("InsertNextLinkNode:分配内存失败！\n");
        return 1;
    }
    s->data = elem;
    s->next = node->next;
    node->next = s;
    return 0;
}
```

插入有/无头节点单链表元素函数的后面代码可以使用后插入单链表元素函数来替代。

使用前插入的方法插入元素，可以使用头指针来得到整个链表信息，从而就能找到链表中的这个结点，但是如果没有头指针那么就无法实现了。且这种遍历的时间复杂度是$O(n)$。

还有另一种方式实现前插法，先后插一个元素，把前面结点的数据移动到这个新加的结点，把要新加的数据放在原来的结点，这就实现了后插，虽然地址没有变化，但是从数据上看就是前插，且时间复杂度是$O(1)$。

```c
// 前插入单链表元素
int InsertPriorLinkNode(LinkNode* node, element_type elem) {
    if (node == NULL) {
        return 1;
    }
    LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
    // 如果分配空间失败
    if (s == NULL) {
        printf("InsertPriorLinkNode:分配内存失败！\n");
        return 1;
    }
    s->next = node->next;
    node->next = s;
    s->data = node->data;
    node->data = elem;
    return 0;
}
```

#### 单链表删除

基本的方式和插入类似，都是转移next结点。

带头结点的也只能删除从1开始的结点，0的头结点不能删除。

时间复杂度为$O(n)$。

```c
// 删除有头节点单链表元素
int DeleteLinkListWithHead(LinkList list, int index, element_type *elem) {
    if (index < 1) {
    printf("DeleteLinkListWithHead:删除索引值过小！\n");
    return 1;
    }
    // p指向当前扫描的结点
    LinkNode* p;
    // i表示当前指向的是第几个结点
    int i = 0;
    // 指向头结点
    p = list;
    while (p != NULL && i < index - 1) {
    p = p->next;
    i++;
    }
    if (p == NULL || p->next == NULL) {
    printf("DeleteLinkListWithHead:删除索引值过大！\n");
    return 1;
    }
    // q指向被删除的结点
    LinkNode* q = p->next;
    // 获取删除的元素数据
    *elem = q->data;
    // 将q结点从链表中断开
    p->next = q->next;
    free(q);
    return 0;
}
```

无头结点需要额外处理第一个结点

```c
// 删除无头节点单链表元素
int DeleteLinkListWithHead(LinkList list, int index, element_type* elem) {
    if (index < 0) {
        printf("DeleteLinkListWithHead:删除索引值过小！\n");
        return 1;
    }
    // p指向当前扫描的结点
    LinkNode* p;
    // i表示当前指向的是第几个结点
    int i = 0;
    // 指向头结点
    p = list;
    // 如果删除第一个第0号结点
    if (index == 0) {
        list = p->next;
        free(p);
        return 0;
    }
    while (p != NULL && i < index - 1) {
        p = p->next;
        i++;
    }
    if (p == NULL || p->next == NULL) {
        printf("DeleteLinkListWithHead:删除索引值过大！\n");
        return 1;
    }
    // q指向被删除的结点
    LinkNode* q = p->next;
    // 获取删除的元素数据
    *elem = q->data;
    // 将q结点从链表中断开
    p->next = q->next;
    free(q);
    return 0;
}
```

如果删除指定结点而不知道其前驱，也可以使用之前前插结点的方式，把该结点后继的结点的数据复制到本结点上，然后把后继结点删除，就相当于删除了本结点。时间复杂度为$O(1)$。

```c
// 删除单链表元素
int DeleteLinkNode(LinkNode* node) {
    if (node == NULL) {
        printf("DeleteLinkNode:本结点是空结点无法删除！");
        return 1;
    }
    // 如果该结点为最后一个结点，无法找到前驱结点，无法操作
    if (node->next = NULL) {
        printf("DeleteLinkNode:后继结点为空无法操作！");
        return 1;
    }
    // 指向后继结点
    LinkNode* p = node->next;
    // 交换数据
    node->data = p->data;
    // 断开结点
    node->next = p->next;
    free(p);
    return 0;
}
```

所以单链表还是不算方便。

#### 单链表查找

按位查找时间复杂度为$O(n)$。

```c
// 按位查找单链表元素
element_type GetLinkListElement(LinkList list, int index) {
    if (index < 0) {
        printf("GetLinkListElement:查找索引值过小！\n");
        return NULL;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkNode* p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != NULL && i < index) {
        p = p->next;
        i++;
    }
    // 如果查找索引大于当前扫描索引
    if (i < index) {
        printf("GetLinkListElement:查找索引值过大！\n");
        return NULL;
    }
    return p->data;
}
```

```c
// 按位查找单链表结点
LinkNode* GetLinkListNode(LinkList list, int index) {
    if (index < 0) {
        printf("GetLinkListNode:查找索引值过小！\n");
        return NULL;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkNode* p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != NULL && i < index) {
        p = p->next;
        i++;
    }
    // 如果查找索引大于当前扫描索引
    if (i < index) {
        printf("GetLinkListNode:查找索引值过大！\n");
    }
    // 如果索引值过大，其p也会指向最后一个NULL，所以返回值都是一样为NULL，不需要单独处理
    return p;
}
```

这样插入元素函数InsertLinkListWithHead只用`GetLinkListNode(list,i-1)`和`InsertNextLinkNode(p,elem)`两个函数完成。

```c
// 按值查找单链表结点
LinkNode* LocateLinkListNode(LinkList list, element_type elem) {
    LinkNode* p = list;
    while (p != NULL && p->data != elem) {
        p = p->next;
    }
    return p;
}
```

#### 单链表建立

可以使用尾插法建立单链表，从后面不断插入元素。