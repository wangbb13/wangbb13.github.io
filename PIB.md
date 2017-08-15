### 第5章  程序设计的基本概念

> 编程风格、赋值语句、递增语句、类型转换、数据交换。

#### 5.1  赋值语句

```c
int i = 1;
void main() {
  int i = i;
  cout << i << endl;
}
// 可以在main函数或其他函数中定义与全局变量同名的变量。
```

#### 5.2  `printf`函数 

```c
void main() {
  int a[] = {1,2,3,4,5};
  int* ptr = a;
  printf("%d, %d", *ptr, *(++ptr));
}
// printf函数计算参数时从右到左压栈
// 所以结果为: 2, 2
```

#### 5.3  类型转换

```c
void main() {
  float a = 1.0f;
  cout << (int)a << endl;
  cout << (int&)a << endl;
  a = 0.;
  cout << (int)a << endl;
  cout << (int&)a << endl;
}
// (int&)相当于将a的二进制存储内容以int的方式读取
// 浮点数1的二进制表示方式为：0x3f800000, 而0.依然为0
```

```c
void main() {
  unsigned int a = 0xfffffff7;
  unsigned char i = (unsigned char)a;
  char* b = (char*)&a;
  printf("%08x, %08x", i, *b);
}
// 000000f7, fffffff7
// x86系列机器，小端存储
// char* b语句，发生了地址截断，截断后b只指向0xf7这个数据
// 由于是有符号char*型，因此扩展后为负数。
```

#### 5.4  位运算

````c
int x, y;
int c = (x & y) + ((x ^ y) >> 1);
// c为x和y的平均值。
````

```c
// 位运算实现加法
int add(int a, int b) {
  int sum, carray;
  sum = a ^ b;
  carry = a & b;
  while (carry) {
    int c = sum;
    int d = carry << 1;
    sum = c ^ d;
    carry = c & d;
  }
  return sum;
}
```

```c
// 交换
int a, b;
int c = (a ^ (a ^ b));
int d = ((a ^ b) ^ b);
// c == b; d == a;
// 浮点数不能进行位运算。
```

#### 5.5  C与C++的关系

**例1**:  在C++程序中调用被C编译器变异后的函数，为什么要加 *extern "C"*

C++支持函数重载，C不支持。函数被C编译器编译后名字与C++中不一致。extern "C" 用于解决名字匹配问题。

### 第6章  预处理、`const`与`sizeof`

#### 6.1  宏定义

> 宏定义，在编译时直接替换，注意这一点。

#### 6.2 ` const`

**`const`变量**

- case 1:  `const int* a = &b;`

- case 2: `int const* a = &b;`

  case 1和case 2相同，`const`均位于星号的左侧，用来修饰指针锁指向的变量，即指针指向为常量，不能用`*a = x;`来修改内容；可以不进行初始化。

- case 3:  `int* const a = &b;`

  `const`位于星号的右侧，修饰指针本身。不能对指针进行更改操作，比如 `a++;` 指针指向的内容可以改变：`*a = x;` 定义时必须初始化。

- case 4:  `const int* const a = &b;`

  指针本身和指向的内容均为常量。

**`const`成员函数**

> 在类的成员函数中，一些函数不修改类的成员变量，应该声明为`const`，以提高程序的可读性（理解为“只读”函数）和可靠性（一旦在`const`成员函数中修改成员变量或者调用非`const`函数，编译器会报错）。

声明方式如下：

```c++
class Point {
  int x, y;
  public:
  int getY() const;
};
int Point::getY() const {
  return y;
}
```

> 如果const放在函数声明前，意味着函数返回值是常量。

**`const`与`#define`有什么不同**

- 两者均可以定义常量。
- `const`常量有数据类型，编译器能够进行类型安全检查，而`define`只是进行替换。
- 在C++程序中购置使用`const`常量而不使用宏常量。

**const成员函数如果要修改变量，应该怎么办？**

用`mutable`修饰成员变量：

```c++
class C {
  public:
  C(int i): m_c(i) {}
  int incr() const {
    return ++m_c;
  }
  private:
  mutable int m_c;
}
```

#### 6.3  `sizeof`

> `sizeof(struct)`：当结构体内的元素长度均小于处理器位数时，以最长的元素作为对齐单位；如果存在大于处理器位数的元素，则以处理器位数作为对齐单位。

> 在VC中，用`pack`预处理指令来进制对齐调整：`#pragma pack(1)`。

**`sizeof`和`strlen`的区别**

- `sizeof`是运算符，`strlen`是函数；
- `sizeof`结果类型是`size_t`，定义为`unsigned int`；
- `strlen`只能以`char *`做参数，且必须以`'\0'`结尾；
- 数组做`sizeof`的参数不退化，传递给`strlen`则退化为指针；
- `sizeof`在编译时就计算了。

**`sizeof`使用场合**

- 存储分配；
- 动态分配对象时，确定所占用的内存大小。

**一个空类所占空间为1，多重继承的空类所占空间也是1**。

#### 6.4  内联函数和宏定义

> `inline`函数可以加快运行速度，在编译时直接嵌入到目标代码中，进行参数类型检查。

**应用场景：**

- 函数被不断重复调用；
- 只有简单的几行，不包含`for`,`while`,`switch`语句。

> *注意：声明内联函数需要将`inline`与函数体放在一起定义，而不要仅仅放在函数声明前；是“用于实现的关键字”。*

**不宜用内联的情况：**

- 函数体较大；
- 执行时间较长。

### 第7章  指针与引用

#### 7.1  指针基本问题

**指针和引用的差别：**

- 非空区别。不能使用指向空值的引用，一个引用必须指向某些对象。
- 合法性区别。在使用引用前不需要测试合法性；相反，指针则总是被测试，防止其为空。
- 可修改区别。指针可以重新赋值；引用则总是指向被指定的对象，不能改变，但内容可以改变。
- 应用区别。指针应用场景：可能不指向任何对象；需要发生变化，指向不同的对象。

**声明引用：**

```c++
int val=  9;
int &a; // 错误，引用不能为空。
int &b = val; // 正确
```

#### 7.2  传递动态内存

**一下两个函数不能实现两个数的交换：**

```c++
void swap(int* p, int* q) {
  int *t;
  *t = *p;
  *p = *q;
  *q = *t;
}

void swap1(int* p, int* q) {
  int *t;
  t = p;
  p = q;
  q = t;
}
```

**可行的解决方案：用指针改变内容、引用。**

**例题1：**

以下函数存在问题：

```c++
char *strA() {
  char str[] = "abc";
  return str;
}
```

分析：分配在栈帧，函数返回后，该栈帧不应该再访问。修改：

```c++
const char* strA() {
  char *str = "abc";
  return str;
}

// method 2
const char* strA() {
  static char str[] = "abc";
  return str;
}

// 字符串常量保存在只读的数据段，所以不能修改。
```

> *注意：不要手动为指针分配地址。*
>
> 比如：`int* ptr = (int*)0x8000;`

**例题2：**

```c++
struct S {
  int i;
  int* p;
}

main() {
  S s;
  int* p = &s.i;
  p[0] = 4;
  p[1] = 3;
  s.p = p;
  s.p[1] = 1;
  s.p[0] = 2;  // 在此处崩溃。
}
```

#### 7.3  函数指针

**例题1：**

```c++
// 修改程序
int max(int x, int y) {
  return x > y ? x : y;
}

int main() {
  int max(x, y);
  int *p = &max;
  int a, b, c, d;
  scanf("%d%d%d", a,b,c);
  d = (*p)((*p)(a.b), c);
  printf("%d", d);
  return 0;
}
```

```c++
// 修改后
int main() {
  int max(int, int); // first
  int (*p)(int, int) = &max; // second
  // ...
  scanf("%d%d%d", &a,&b,&c); // third
  // ..
}
```

#### 7.4  指针数组和数组指针

定义指向数组的指针：`int (*ptr)[]`。定义指针数组：`int *ptr[]`。

`int (*a[10])(int); // 指向函数的指针数组`。

> **注意：数组名本身是指针，再加`&`，则变为双指针，即二维数组，加1，就是数组整体加一行。**
>
> ```c++
> int a[2][3] = {1,2,3,4,5,6};
> int *ptr = (int*)(&a+1); // *ptr = 4
> ```
#### 7.5  迷途指针

> 也叫悬浮指针、失控指针。

> 对一个指针进行`delete`操作，在没有重新赋值的情况下再次使用该指针。会产生不可预料的后果，造成系统崩溃。

**空指针和迷途指针的区别：**

- 迷途指针：`delete`操作后；
- 空指针：`null`, `ptr = 0;`；

**`malloc/free`与`new\delete`：**

- 前者是`C/C++`标准库**函数**，后者是**运算符**，均用于动态申请和释放内存；
- 对于非内部数据类型的对象（如：类的实例），前者不能满足动态对象的要求，不能再创建时执行构造函数，也不能再释放前执行析构函数。

#### 7.6  指针和句柄

> 待学习……

#### 7.7  `this`指针

- `this`指针本质是函数参数，只是编译器隐藏了；
- `this`在成员函数开始前构造，在结束后清除，生命周期同函数参数一样；
- `this`指针传递效率较高，VC通过`ecx`寄存器传参；
- `this`指针会因编译器不同而由不同的存放位置，可能是堆、栈、寄存器；
- 只有在成员函数中`this`指针才有定义。

### 第10章  面向对象

#### 10.1  面向对象基本概念

**里氏代换原则：**子类型必须能够替换它们的基类型。

**开闭原则：**软件对扩展是开放的，对修改是关闭的（不对设计好的代码做修改）。

**C++的空类默认产生哪些成员函数：**默认构造函数、析构函数、复制构造函数、赋值函数。

#### 10.2  类和结构

- `class`默认是`private`，`struct`默认是`public`；

```c++
struct Test {
  Test(int){}
  Test(){}
  void fun(){}
}

int main() {
  Test a(1);
  a.fun();
  Test b();	// 声明了b函数，返回Test类型
  b.fun();	// 应写为：Test b;
  return 0;
}
```

#### 10.3  成员变量

> 静态成员变量在一个类的所有实例间共享数据。

> 如果把静态成员数据设为私有，可以通过公有的静态成员函数来访问。

**初始化列表的初始化变量顺序是根据成员变量的声明顺序来执行的，如下：**

```c++
class base {
  private:
  int m_i;
  int m_j;
  public:
  base(int i) : m_j(i), m_i(m_j) {}
  int get_i() { return m_i; }
  int get_j() { return m_j; }
};

int main() {
  base obj(98);
  cout << obj.get_i() << " " << obj.get_j() << endl;
  return 0;
}
// 结果输出 ?  98
// 若要输出 98 98，修改声明顺序即可
class base {
  private:
  int m_j;	// 
  int m_i;	// 
  public:
  base(int i) : m_i(m_j), m_j(i) {}	// 
  int get_i() { return m_i; }
  int get_j() { return m_j; }
};
```

**常量必须在构造函数的初始化列表里初始化或者设置成static，如下：**

```c++
class A {
  const int size = 0;
};

// 改正如下
class A {
  A() { const int size = 0; }
};
// 或者
class A {
  static const int size = 0;
};
```

#### 10.4  构造函数和析构函数

> 在生成派生类对象时，首先调用基类的构造函数，再调用子类的构造函数；再销毁子类对象时，先调用父类的析构函数，再调用子类的析构函数。

**如果将父类的析构函数改为虚函数，将避免出现内存泄漏的情况。如下：**

```c++
CBase *pB;
CChild c;
pB = &c;
delete pB;
// 如果父类析构函数不是虚函数，那么撤销pB时，将不会调用子类的析构函数，从而不会释放子类所占用的空间，造成内存泄漏。
```

**构造函数为什么不能为虚函数？**

**Ans：**虚函数的作用在于通过父类的指针或者引用来调用子类相应的成员函数。构造函数是在创建对象时自动调用的，不可能通过父类的指针或者引用去调用，因此构造函数不能是虚函数。

>  虚函数是有代价的，每个虚函数的对象都必须维护一个虚函数表，使用时会产生额外的开销。

> 析构函数可以是内联函数。

**注意以下问题：**

```c++
class B {
  private:
  int data;
  public:
  B() { cout << "default constructor" << endl; }
  ~B() { cout << "destructed" << endl; }
  B(int i) : data(i) { cout << "constructed by " << data << endl; }	// 带参数的构造函数，冒号后面是成员变量初始化列表。
};
B play(B b) { return b; }
int main() {
  B t = play(5);  // (1)
  return 0;
}

// (1)处合法，单个参数的构造函数如果不添加explicit关键字，会定义一个隐含的类型转换。
// 程序输出：
// constructed by 5	, 隐含的类型转换
// destructed       , play函数返回时，参数的析构函数被调用
// destructed       , temp的析构函数调用
```

#### 10.5  复制构造函数和赋值函数

**编写String类的构造、析构和赋值函数：**

```c++
class String {
  public:
  String (const char *str = null);
  String (const String &other);
  ~String (void);
  String & operate = (const String &);
  private:
  char *m_data;
}

String::~String(void) {
  delete [] m_data;
}

String::String(const char *str) {
  if (str == null) {
    m_data = new char [1];
    m_data[0] = '\0';
  } else {
    int length = strlen(str);
    m_data = new char[length + 1];
    strcpy(m_data, str);
  }
}

String::String(const String& other) {
  int length = strlen(other.m_data);
  m_data = new char[length + 1];
  strcpy(m_data, other.m_data);
}

String & String::operate = (const String &other) {
  if (this == other) {
    return *this;
  }
  delete [] m_data;
  int len = strlen(other.m_data);
  m_data = new char[len + 1];
  strcpy(m_data, other.m_data);
  return *this;
}
```

#### 10.6  多态

> 多台可以简单地概括为“一个接口，多种方法”，在程序运行的过程中才决定调用的函数。
>
> 允许将子类类型的指针赋值给父类类型的指针。pFather = pChild;

> 虚函数即允许被子类重新定义的成员函数。子类重新定义父类虚函数的做法，称为“覆盖”（override）。

> 重载（overload）与多态无关，在编译时就已经确定了，是静态的。体现多态的是“覆盖”。

> 封装：隐藏实现细节，模块化代码；-> 代码重用
>
> 继承：扩展已有的模块；-> 代码重用
>
> 多态：接口重用。
>
> **多态是面向对象最重要的特性。**

#### 10.7  友元

> 在对某些成员函数多次调用时，由于参数传递、类型检查和安全性检查等需要时间开销，影响运行效率，因此提出友元的方案。
>
> 友元，定义在类外部的普通函数，可以访问私有变量，破坏了封装性，需要在类内说明。用于提高程序运行效率。

```c++
class Point {
  private:
  float x, y;
  public:
  Point(float a = 0., float b = 0.) : x(a, b) {};
  friend float distance(Point& left, Point& right);
};

friend float distance(Point& left, Point& right) {
  return 0.; // ..
}
```

#### 10.8  异常

> 不应该在析构函数中抛出异常。

### 第11章  继承与接口

#### 11.1  私有继承

```c++
class A {
  public:
  void virtual f() { cout << "A" << endl; }
};

class B : public A {
  public:
  void virtual f() { cout << "B" << endl; }
}

int main() {
  A* pa = new A();
  pa->f();
  B* pb = (B*)pa;
  pb->f();
  
  delete pa, pb;
  pa = new B();
  pa->f();
  pb = (B*)pa;
  pb->f();
}
// A A B B
```

> 私有继承使对象不能被派生类的子类访问。

> 一个私有的或保护的派生类不是子类，因为他不能做基类能做的所有的事。

> **保护继承和私有继承在外部不能访问基类的成员。**

**三种继承方式：**

- `public`：对派生类来说，`public`和`protected`成员可见，保持原有的状态，不能访问`private`成员；对派生类对象来说，`public`成员可见，其他不可见。
- `private`：对派生类来说，`public`和`protected`成员可见，基类的`public`成员和`protected`成员作为派生类的`private`成员；对派生类对象来说，所有成员都不可见。
- `protected`：与`private`继承相同，只是基类的`public`成员和`protected`成员作为派生类的`protected`成员，能被其子类访问，但不能被其子类对象访问。
- 保护继承和私有继承不常见，只是在技术讨论时会出现。
- 如果不指定继承方式，默认是`private`。

#### 11.2  虚函数继承和虚继承

> 每个对象里有虚表指针，指向虚表，虚表里存放了虚函数的地址（顺序存放）。

```c++
class A {
  char a[3];
  public:
  virtual void aa() {};
};
class B : public virtual A {
  char b[3];
  public:
  virtual void bb() {};
};
class C : public virtual B {
  char c[3];
  public:
  virtual void cc() {};
};
// sizeof(A) = 8  : 由于有虚函数，所以有虚指针，外加3个字节对齐后的结果
// sizeof(B) = 16 : 8 + 父类所占的大小
// sizeof(C) = 24 : 8 + 父类所占的大小
// 如果不是virtual继承，那么结果是：8、12、16
```

**什么是虚继承？**

> 为解决多重继承而出现的，比如：A -> B ->D; A -> C -> D，在类D中两次出现A，为节省空间，可以将对A的继承定义为虚继承。

**为什么虚函数效率低？**

> 虚函数需要一次间接寻址，而一般函数可以在编译时定位到函数的地址，虚函数要根据运行时情况定位，因而效率低。

#### 11.3  多重继承

**如何明确的调用多个父类中的同名函数？**

```c++
class A {
  public:
  void foo() {}
};
class B {
  public:
  void foo() {}
};
class C : public A, public B {};
int main() {
  D d;
  d.A::foo() {};
  return 0;
}
```

```c++
class A {};
class B {};
class C : public A, public B {};
int main() {
  C* pc = new C;
  B* pb = dynamic_cast<B*>(pc);
  A* pa = dynamic_cast<A*>(pc);
  cout << (pc == pb) << endl;
  cout << ((int)(pc) == (int)(pb)) << endl;
}
// 1, 隐式类型转换
// 0
```

#### 11.4  纯虚函数

> 包含纯虚函数的类是不能实例化的。

> 虚指针，指向该类的虚函数表的指针。

**C++如何阻止类被实例化？**

- 构造函数声明为`private`
- 抽象类（包含纯虚函数）

**复制构造函数总是会默认生成的。**

#### 11.5  运算符重载与RTTI

> 待看。

### 第13章  数据结构基础

#### 13.1  单链表

**删除节点：**

```c++
node* del(node* head, int num) {
  node* p, *q;
  if (head == null) {
    return head;
  }
  q  = new node();
  q->next = head;
  p = head;
  head = q;
  while (p && p->val != num) {
    q = p;
    p = p->next;
  }
  if (p != null) {
  	q->next = p->next;
  	delete p;
  }
  return head->next;
}
// 增加新节点以简化编程
```

**逆置链表：**

```c++
node* reverse(node* head) {
  if (head == null || head->next == null) {
    return head;
  } 
  node *p, *q, *r;
  p = head->next;
  q = head;
  head->next = null;
  while (p) {
    r = p->next;
    p->next = q;
    q = p;
    p = r;
  }
  return q;
}
```

> 对于一次遍历就能确定某种值的问题，善于使用双指针。

#### 13.2  双链表

> 建立、删除、插入

#### 13.3  循环链表

> 建立、删除、插入

#### 13.4  队列

> 入队（push）、出队（pop）、是否为空（empty）、首元素（front）

#### 13.5  栈

> 压栈（push）、出栈（pop）、是否为空（empty）、首元素（top）

> 双栈实现队列，一个栈入队，一个栈出队。

#### 13.6  堆

**内存类别：**

- 栈：由编译器分配、释放，存放函数的参数、局部变量等，操作方式类似于数据结构中的栈。
- 堆：由程序员分配和释放，若不释放，在程序结束时由操作系统回收。（C，`malloc`函数；C++，`new`操作符）
- 全局区（静态区）：存放全局变量和静态变量，初始化的在一块，未初始化的在相邻的另一块区域，程序结束后由操作系统回收。
- 文字常量区：存放常量字符串。
- 程序代码区：存放函数的二进制代码。

> **注意：`char s[] = "abc"`直接在栈分配；`char *sp = "abc"`，`sp`在栈，`"abc"`在文字常量区。**

**堆和栈比较：**

- 申请方式：栈，由系统自动分配；堆，程序员自己申请。

- 申请后系统的响应：栈，申请的空间大于栈的剩余空间时，提示栈溢出，否则分配；堆，操作系统分配。

- 申请大小限制：栈，向低地址扩展，连续的内存，编译时就确定的常数（windows下，1/2MB）；堆，向高地址扩展，不连续，受限于有效的虚拟内存。

- 申请效率：栈，系统自动分配，速度较快；堆，较慢，容易产生碎片。

- 存储内容：栈，入栈顺序：参数（从右到左），下一条指令的地址，`EBP`，局部变量，出栈顺序相反；堆，堆的大小，程序员分配内容。

  - | 栈，向低地址延伸（var3的地址最小） |
    | :------------------ |
    | var3                |
    | var2                |
    | var1                |
    | EBP                 |
    | RET                 |
    | param1              |
    | param2              |
    | param3              |

- 存取效率：读取栈的内容更快一些。

#### 13.7  树、图、哈希表

**有向图拓扑排序算法基本步骤：**

1. 从图中选择一个入度为0的节点，输出该节点；
2. 从图中删除该节点及其相关联的弧，调整节点的入度；
3. 重复1、2，直至所有节点被输出。

**Trie树：**

- 单词查找树、字典树，多叉树结构
- 典型应用：统计和排序大量的字符串
- 优点：最大限度的减少无谓的比较，查询效率比哈希表高

**霍夫曼树：**从频率最小的开始，自底向上构造

**例题：**一个包含$n$个节点的四叉树，每个节点都有4个指向孩子的指针，这个四叉树有___个空指针。

**Ans：**$n$个节点，$4n$个指针，$n-1$个非空指针，故共计$4n-(n-1)$个空指针。

**海量数据处理的问题：**

1. 有1千万条短信，有重复，以文本文件的形式保存，一行一条，有重复。请用5分钟时间，找出重复上出现最多的前10条。

   **Ans：方法1，**采用哈希表的方法对1千万条分成若干组，边扫描边创建散列表。对于每一条短信，记录其地址、长度和重复次数。建立完成后，在线性时间里选择前10条短信。**方法2，**采用从大到小的排序方法，根据短信长度进行分组，在每组里选择前10条短信；对于长度较长的短信，可以采用hash的方法。**方法3，**采用内存映射的方法，不需要频繁使用文件I/O和分配小内存，提升加载速度，创建trie树。

2. 有1亿个浮点数，每个占4个字节，找出其中最大的1万个。

   **Ans：**分块查找，首先在100万数据里找出最大的1万个，然后以最小的数据为基准，在剩下的数据里找出比它大的数据或者1万条数据，不断更新基准。最后合并所有数据（不会超过100万），在其中找出最大的1万条数据。在找出前1万条数据时，采用快速排序的思想，不必准确的排序，只需要划分即可。

#### 13.8  排序

| 稳定的排序 | 时间复杂度                     | 空间复杂度           |
| :---- | :------------------------ | :-------------- |
| 冒泡排序  | 最差、平均都是$O(n^2)$，最好是$O(n)$ | 1               |
| 插入排序  | 最差、平均都是$O(n^2)$，最好是$O(n)$ | 1               |
| 鸡尾酒排序 | 最差、平均都是$O(n^2)$，最好是$O(n)$ | 1               |
| 归并排序  | 最差、平均、最好都是$O(n\log n)$    | $O(n)$          |
| 桶排序   | $O(n)$                    | $O(k)$          |
| 基数排序  | $O(dn)$($d$是常数)           | $O(n)$          |
| 二叉树排序 | $O(n\log n)$              | $O(n)$          |
| 图书馆排序 | $O(n\log n)$              | $(1+\epsilon)n$ |

| 不稳定的排序 | 时间复杂度                      | 空间复杂度       |
| ------ | -------------------------- | ----------- |
| 选择排序   | 最差、平均都是$O(n^2)$            | 1           |
| 希尔排序   | $O(n \log n)$              | 1           |
| 堆排序    | 最差、平均、最好都是$O(n \log n)$    | 1           |
| 快速排序   | 平均$O(n \log n)$，最坏$O(n^2)$ | $O(\log n)$ |

#### 13.9  时间复杂度

