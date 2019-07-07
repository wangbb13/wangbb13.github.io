# C++ Primer (5th Edition)

## chapter 3  String, Vector and Array

> **一些原则**
>
> 1. 头文件中不应包含`using`声明，因为可能会产生名字冲突。
> 2. 解引用迭代器的方法：`(*it)`，可以类比于指针来理解。
> 3. 访问数组元素时，一般使用`size_t`类型，但要注意这是**无符号类型**，如果从大到小遍历，注意写法，避免死循环。
> 4. 尽量使用标准库类型而非数组，因为容易引发一些繁琐细节的错误（除非C基本功非常扎实）。

> **理解内容**
>
> 1. 理解复杂的数组声明：
>
> a. 存放指针的数组：`int *ptrs[10]; // 定义一个含有10个整型指针的数组`
>
> b. 定义数组的指针：`int (*p_array)[10] = &arr; // 指向一个含有10个整数的数组`
>
> c. 定义数组的引用：`int (&r_array)[10] = arr; // 引用一个含有10个整数的数组`
>
> d. ***注意***   不存在定义引用的数组。
>
> 如何理解？
>
> 理解顺序：由内向外（括号里是内），从右向左
>
> 例如：`int *(&array)[10] = ptrs;` 首先，`array`是一个引用，引用的是一个大小为10的数组，数组内容是整型指针。
>
> 2. 在大多数表达式中，使用数组类型的对象其实是使用一个指向该数组首元素的指针。
>
> 3. 使用范围 `for` 语句处理多维数组时，除最内层的循环外，其他所有循环的控制变量都应该是引用类型。
>
>    ```c++
>    int array[10][10] = {0};
>    // correct
>    for (auto &row : array) {
>    	for (auto &col : row) {
>            // do sth.
>        }
>    }
>    // incorrect
>    for (auto row : array) {
>    	for (auto col : row) {
>            // 编译器会将 row 初始化为指向数组首元素的指针，在此例中，row 为 int* 类型。
>        }
>    }
>    ```
>
> 4.  

> **注意**
>
> 1. 使用数组时，检查下标不要溢出。一定要***小心谨慎！！！*** 

> **概念**
>
> 1.  `decltype` 关键字：选择并返回操作数的数据类型，编译器分析表达式并得到它的类型，但不进行计算。
>
>    ```c++
>    decltype(f()) sum = x;  // sum 的类型就是函数 f() 返回的类型，decltype部分相当于一个数据类型，比如 int。
>    ```
>
>    ***切记：*** `decltype((variable))` 的结果永远是引用！
>
> 2.  

## Chapter 6  Function

> **一些建议或原则**
>
> 1. C程序中通常使用指针类型的形参访问函数外部的对象，在C++中，建议使用引用类型的形参代替。
>
> 2. 如果函数无须改变引用形参的值，最好将其声明为常量引用。
>
>    原因：如果仅声明为引用，1、会给调用者以误导，可以修改实参的值；2、极大地限制函数所能接受的实参类型，我们不能将const对象、字面值或需要类型转换的对象传递给普通的引用形参。
>
> 3. 

> **理解内容**
>
> 1. 数组形参
>
>    ```c++
>    // 以下三个函数等价
>    void print(const int*);
>    void print(const int[]);
>    void print(const int[10]);	// 期望数组长度为10，但实际不一定
>    ```
>
>    数组形参的性质：1、不允许拷贝数组；2、使用数组时通常会将其转换成指针。
>
>    ```c++
>    // 多维数组的形参
>    void print(int (*matrix)[10]);	// matrix 指向数组的首元素，元素是由10个整数构成的数组
>    void print(int matrix[][10]);	// 等价定义
>    ```
>
>    
>
> 2. 

## Misc

1. lvalue and rvalue 

   简单理解左值和右值：左值指向某一处内存空间；右值不指向任何一处内存空间，是临时的

   左值 $\Rightarrow$ 右值：例如，若干个左值进行加减乘除等运算，转变为右值（能够出现在等号右边）。

   右值 $\Leftarrow$ 左值：不行。

   左值引用：顾名思义，对于左值的引用，例如：

   ```c++
   int y = 10;
   int& refy = y;
   refy++;
   ```

   问题1:

   ```c++
   void func(int& x) {
       // ....
   }
   int main() {
   	func(10);	// error: invalid rvalue to lvalue conversion
       int a = 10;
       func(a);	// OK, but not convenient, any elegant solution ?
   }
   ```

   可行的方式：

   ```c++
   const int& ref = 10;	// OK
   void func(const int& x) {
       cout << x << endl;
   }
   func(10);	// OK
   ```

   问题2：右值只读，不可改变。所以引入**右值引用**。

2. rvalue references

   > 思想：利用临时变量，可以对其进行修改，减少复制大对象的操作。

   可以将右值引用与 `const ` lvalue 绑定，但不能以右值引用来初始化一个非 `const` 引用，如下：

   ```c++
   int& x = 666;			// Error (VS的报错信息：无法从 int 转为 int&)
   const int& x = 666; 	// OK
   ```

   但是这样适用却无法修改rvalue，因此C++11后引入右值引用。

   不使用右值引用进行对象间的赋值运算时，会出现两次内存分配：

   1）发生在临时对象创建时；2）发生在将临时对象的内容拷贝到目标对象时。

   使用右值引用就可以利用临时对象已经分配的内存空间，避免上述的第二次内存分配。

   > 理解：Don't copy, just move. 

   例如：

   ```c++
   string str1 = "hello, ";
   string str2 = "world";
   string&& ref_s = str1 + str2;	// reference to a temporary object
   ref_s += "!";
   cout << ref_s << endl;
   ```

   How to move lvalues?

   Ans: use `std::move` 

3. move semantics

   a) move rvalue 

   例如：

   ```c++
   MyClass mc1;
   void func(MyClass&& mc) {
       mc1.x = mc.x;
       mc.x = 0;
   }
   ```

   

   b) move lvalue 

   ```c++
   MyClass mc1(10);
   MyClass mc2(mc1);	// copy constructor 
   
   MyClass mc1(10);
   MyClass mc2(std::move(mc1));	// move copy constructor (move lvalue)
   ```

   

4. Rules of Three：如果类中定义了以下一个或多个方法，应该显式地定义所有的三个方法

   - **析构函数（destructor）** 

   - **拷贝构造函数（copy constructor）**：用一个已存在对象创建一个新的对象 ，例如

     ```C++
     class MyClass {
     public:
         MyClass(int n) {
             x = n;
         }
     private:
         int x;
     };
     MyClass mc1(100);	// constructor
     MyClass mc2 = mc1;	// copy constructor
     MyClass mc3(mc1);	// copy constructor, alternative syntax
     ```

     

   - **拷贝赋值运算符（copy assignment operator）**：用一个已存在的对象替换另一个已存在的对象，例如

     ```c++
     MyClass mc1(100);
     MyClass mc2(1000);
     mc1 = mc2;		// assignment operator
     ```

   - **Limitations**:

     例如：

     ```c++
     MyClass createClass(int size) {
         return MyClass(100);
     }
     MyClass mc1 = createClass(100);	// two memory allocation: a) constructor for temporary object; b) copy constructor for mc1, 编译期会做优化，省略第二项
     mc1 = createClass(200);	// two: a) constructor; b) assignment operator
     ```

     两倍的空间分配和释放，想法：能否将临时对象直接移动到目标对象，减少copy操作。引入右值**引入用概念**。

5. Rules of Five：现代C++的规则，增加如下两个方法

   - **the move constructor** 	（从临时对象移动数据，构造新对象）
   - **the move assignment operator**     （从临时对象移动数据，替代已有对象数据）

   PS：一般情况下，move constructor从未被调用，这是因为现代编译器使用 **Return Value Optimization（RVO）** 技术检测到程序通过返回一个对象构造新对象，会省去调用构造函数进行创建新对象的操作。在gcc中，可以使用 `-fno-elide-constructors` 省去这一优化，打开这一开关后，会发现构造/析构次数明显增加。

   既然RVO技术已经能够优化，为什么还要实现move？

   **Ans**：RVO仅对返回的右值 (output)，但不会对函数参数 (input) 做优化。

6. C++ keyword `typename` 用法及含义

   case 1：用于定义模板中的类型名，与 `class` 关键字含义相同

   case 2：To **specify that the following identifier is a type** . Otherwise the identifier may be regarded as a static member. For example:

   ```c++
   template <typename T>
   class MyClass {
       typename T::SubType * ptr;	// ptr is a pointer to the type T::SubType
       T::Subtype * ptr;	// may be a multiplication of value SubType of T with ptr
   };
   // TODO：不过不加好像也没事？是否是仅为了可读性而加的typename
   ```

7. template SFINAE

   SFINAE stands for: "Substitution Failure Is Not An Error". 

   意思是当编译期匹配一个模板失败时，应该继续匹配，而不是停止。

   场景：函数重载，在编译期进行函数匹配时，如果由多个普通函数或模板函数满足匹配条件，那么无法通过编译。而引入type-traits后，会有满足条件的模板函数缺少某一字段，引发错误，由于SFINAE机制，不会报错，转而与另外合法的重载函数进行匹配。经典示例：

   ```c++
   struct Test {
       using type = int;
   };
   
   template <typename T>
   void func(typename T::type) {}	// definition 1, # 1
   
   template <typename T>
   void func(T) {}	// definition 2, # 2
   
   func<Test>(10);	// call # 1
   func<int>(10);	// 与#1进行匹配时，T::type显然是语法错误的(int::type)，但由于SFINAE原则，不会报错，转而与#2匹配
   ```

   

8. type-traits

   在编译期判断，如果条件不满足，则在编译期会出现错误。
   
9. `explicit` 关键字

   > The `explicit` function specifier controls unwanted implicit type conversions. It can only be used in declarations of constructors within a class declaration.

   **motivation**  考虑如下应用场景：

   ```c++
   class MyArray {
   public:
       MyArray(size_t count);
   };
   MyArray m_array = 123;	// OK, 隐式转换 (implicit conversion)，问题在于，这种隐式转换可能发生在其他地方，例如：
   void print(const MyArray& array);	// #1
   void print(int);	// #2
   print(123);	// 问题：1.代码可读性; 2.这样做会引发意外的调用构造函数
   // 如果希望打印"123"，print(123)，结果却调用print() #1 函数，调用MyArray的构造函数。所以需要将MyArray类的构造函数定义为显示构造函数以避免这种问题。
   class MyString {
   public:
       String(int n);
       String(const char* p);
   };
   MyString m_string = 'x';	// 3.调用时可能会出现意外情况，'x'转换为int，进而调用String(int n)构造函数。
   ```

   声明为`explicit`的构造函数，可以使用的调用方法如下：

   ```c++
   class A {
   public:
       explicit A();
       explicit A(int);
       explicit A(const char*, int = 0);
   };
   A a1;
   A a2 = A(1);
   A a3(1);
   A a4 = A("Venditti");
   A* ap = new A(1);
   A a5 = (A)1;
   A a6 = static_cast<A>(1);// static_cast Syntax: static_cast<new_type> (expression)
   ```

   

10. 

### 参考

[1]. https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c

[2-5]. https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners

[7-8]. <https://shaharmike.com/cpp/sfinae/>

