# 栈

栈结构与线性表类似，是只允许一端（表尾）进入或删除的线性表。即后进先出LIFO。

栈顶就是允许插入和删除的一端，而另一端就是栈底。

进栈顺序：A->B->C->D，出栈顺序：D->C->B->A。

如果有$n$个不同的元素进栈，出栈元素不同排列的个数为$\dfrac{1}{n+1}C_{2n}^n$，这就是卡特兰数。

## 顺序栈

### 顺序栈定义

### 顺序栈操作

#### 顺序栈初始化

栈顶指针初始化为-1，因为索引最小为0。如果初始化为0也可以，不过其操作有所不同。

## 链栈

链栈基本上就是只能操作一头的链表，所以从定义上其基本上没有区别。

## 栈的应用

### 括号匹配

即需要括号成双相对，且大小一样。

括号匹配时会发现最后出现的左括号最先被匹配LIFO。所以就可以通过栈来模拟这个匹配过程。

自左至右扫描表达式，若遇左括号，则将左括号入栈，若遇右括号，则将其与栈顶的左括号进行匹配，若配对，则栈顶的左括号出栈，否则出现括号不匹配错误，如果需要匹配但是栈空说明有单独的左或右括号，也匹配失败。

### 表达式求值

一般使用的都是中缀表达式，例如：4+2×3-10/5，按照运算法则，我们应当先算2×3然后算10/5 ，再算加法，最后算减法。

表达式分为三个部分：操作数、运算符、界限符。

如果不使用界限符，如中括号或小括号，可以使用后缀表达式（逆波兰表达式）或前缀表达式（波兰表达式）。

常用的中缀表达式是将运算符如加减乘除放在两个操作数中间，而后缀表达式就是放在两个操作数之后，前缀表达式就是放在两个操作数之前。

#### 后缀表达式

中缀转后缀的手算方法：

1. 确定中缀表达式中各个运算符的运算顺序进行排序。
2. 选择下一个运算符，按照**左操作数 右操作数 运算符**的方式组合一个个新的操作数。
3. 如果还有运算符没有处理就重复2步骤。

如A+B*(C-D)-E/F就是ABCD-*+EF/-和ABCD-\*EF/-+。中缀转后缀的结果可以有不同的结果。

即使有不同的转换结果，但是如果我们要通过计算机实现这种转换算法，就必须保证算法的唯一性，所以规定后缀表达式中运算符的顺序就是中缀表达式中运算符生效的顺序，即结果是第一个而不是第二个。

所以后缀表达式转换必须遵循左优先的原则，能先计算左边的运算符就计算左边的运算符。

后缀表达式转换的程序实现：

1. 初始化一个栈，用于保存暂时不能确定运算顺序的运算符。
2. 从左到右处理每个元素。
3. 如果遇到操作数，直接加入后缀表达式。
4. 如果遇到界限符，如果遇到左括号直接入栈，如果遇到右括号依次弹出栈内运算符并加入到后缀表达式中，直到遇到新的左括号为止，不弹出左括号。
5. 遇到运算符，依次弹出栈中优先级高于或等于当前运算符的所有运算符并加入后缀表达式，若碰到左括号或栈空停止，之后再将当前运算符入栈。
6. 处理完所有字符后，将栈中剩余运算符依次弹出，并加入后缀运算符。

后缀表达式计算的程序实现：

1. 从左往右扫描下一个元素，直到处理所有元素。
2. 若扫描到操作数则压入栈，并回到1，若扫描到运算符则执行3.
3. 扫描到运算符则弹出两个栈顶元素，执行相应操作，运算结果压入栈，回到步骤1。
4. 先出栈的是右操作数，后出栈的是左操作数。

使用栈进行中缀表达式求值的程序实现：

1. 我们设定两个栈，一个用于存储运算符称之为运算符栈，另一个用于存储操作数称之为操作数栈。
2. 首先置操作数栈为空，表达式起始符“#”为运算符栈的栈底元素。
3. 依次读入表达式中每个字符，若是操作数则进操作数栈，若是运算符则和运算符栈栈顶元素比较优先级，若栈顶元素优先级高于即将入栈的元素，则栈顶元素出栈（优先级高的先出栈，再把优先级低的放进来），操作数栈弹出两个操作数和运算符一起进行运算，将运算后的结果放入操作数栈，直至整个表达式求值完毕（即运算符栈顶元素和要放入元素均为“#”）。

如果我们将后缀表达式转换为中缀表达式计算，可以从左往右扫描，每遇到一个运算符，就让运算符前面最近的两个操作数执行对应运算，合并为一个操作数。

#### 前缀表达式

中缀转后缀的手算方法：

1. 确定中缀表达式中各个运算符的运算顺序进行排序。
2. 选择下一个运算符，按照**运算符 左操作数 右操作数**的方式组合一个个新的操作数。
3. 如果还有运算符没有处理就重复2步骤。

遵循右优先原则，只要能计算右边就优先计算右边。

前缀表达式计算的程序实现：

1. 从右往左扫描下一个元素，直到处理所有元素。
2. 若扫描到操作数则压入栈，并回到1，若扫描到运算符则执行3.
3. 扫描到运算符则弹出两个栈顶元素，执行相应操作，运算结果压入栈，回到步骤1。
4. 先出栈的是左操作数，后出栈的是右操作数。

### 递归

函数调用的特点：最后被调用的函数最先执行结束LIFO。

函数调用时需要一个栈存储：调用返回地址、实参、局部变量。

递归可以将原始问题拆分为属性相同、规模较小的问题。但是如果太多层会造成栈溢出。

### 迷宫问题

+ 思想：以栈S记录当前路径，则栈顶中存放的是“当前路径上最后一个位置信息”。
+ 若当前位置“可通”，则纳入路径（入栈），继续前进。
+ 若当前位置“不可通”，则后退（出栈），换方向继续探索。
+ 若四周“均无通路”，则将当前位置从路径中删除出去。