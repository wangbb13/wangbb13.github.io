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

#### 5.2  printf函数 

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

### 第6章  预处理、const与sizeof

