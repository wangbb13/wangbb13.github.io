# Learn C++ from caffe source code

## keyword in class

1. 通过 `explicit` 定义显式构造函数

  

2. `virtual`

3. 

## `const` 



## A type-safe and branchless version of sign/signnum implementation

```c++
template <typename T>
int sign(T val) {
    return (T(0) < val) - (val < T(0));
}
```

## 宏定义

> 本质：替换

1. 特殊符号

   \##, 表示连接，例如

   ```c++
   #define Conn(x, y) x##y
   int n = Conn(123, 456); // n = 123456
   ```

   \#@, 表示加单引号，例如

   ```c++
   #define ToChar(x) #@x
   char a = ToChat(1); // a = '1'
   ```

   \#, 表示加双引号，例如

   ```c++
   #define ToString(x)
   char *str = ToString(123);	// str = "123"
   ```

2. **ANSI C** 标准中五个预定义的宏，可用于跟踪调试

   ```c
   __LINE__; // 当前代码行号
   __FILE__; // 当前文件名
   __DATE__; // 当前编译日期
   __TIME__; // 当前编译时间
   __STDC__; // 当要求程序严格遵循ANSI C标准时该标识被赋值为1
   __cplusplus; // 编写c++程序时该标识符被定义
   ```

   