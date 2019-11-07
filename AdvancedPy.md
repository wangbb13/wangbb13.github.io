# Advanced Python

## Wrapping C/C++ for Python

### ctypes

>   python自带的标准库，因此更加稳定。只能访问C函数。

1.  定义C函数

    `extern "C"` 

    一般选择使用C++实现库，但因为ctypes只能访问C函数，所以在定义C API时，需要以 `extern "C"` 标识符。

    `extern "C"` 使得C++中的函数具有C语言链接规范，于是，客户端的C程序能够使用兼容C的头文件链接到定义的函数。

    主要区别在于：C++支持函数重载，可以定义具有相同函数名但不同个数或类型参数的函数（静态重载）；而C不支持。因此，C和C++编译器的编译后的函数名有所不同，C只需要有函数名就可以了。

    `__declspec` 关键字

    用于指定存储类信息的扩展属性语法。例如：

    `__declspec(dllexport)` 指示链接器从DLL导出符号

    `__declspec(dllimport)` 指示链接器从DLL导入符号

2.  生成静态链接库 

    编写CMakeLists.txt文件，示例如下：

    ````cmake
    cmake_minimum_required(VERSION 3.9)
    project(mylib VERSION 1.0.1 DESCRIPTION "mylib description")
    include(GNUInstallDirs)
    add_library(mylib SHARED src/mylib.c)
    set_target_properties(mylib PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER api/mylib.h)
    configure_file(mylib.pc.in mylib.pc @ONLY)
    target_include_directories(mylib PRIVATE .)
    install(TARGETS mylib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(FILES ${CMAKE_BINARY_DIR}/mylib.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
    ````

    

3.  (可选) 链接python库

    ```cmake
    find_package(PythonLibs REQUIRED)
    add_library(parsers SHARED ${SOURCE_FILES})
    include_directories(${PYTHON_INCLUDE_DIRS})
    target_link_libraries(parsers ${PYTHON_LIBRARIES})
    ```

4.  python传入str类型的参数

    ```python
    # c
    # void func(char *str);
    
    import ctypes
    param = ctypes.c_char_p(b'test')
    lib.func(param)
    
    # str to bytes
    a_str = 'hello, world'
    b_str = a_str.encode()
    ```

5.  C/C++函数返回数组

    ```c++
    extern "C" int* function(){
    int* information = new int[10];
    for(int k=0;k<10;k++){
        information[k] = k;
    }
    return information;
    }
    ```

    

    ```python
    import ctypes
    from numpy.ctypeslib import ndpointer
    
    lib = ctypes.CDLL('./library.so')
    lib.function.restype = ndpointer(dtype=ctypes.c_int, shape=(10,))
    
    res = lib.function()
    ```

    

6.  

**可能的错误**：

1.  不是合法的Win32应用程序

    python 位数问题，改为32bit版本。

参考

[1]  [Calling C/C++ from Python]( https://stackoverflow.com/questions/145270/calling-c-c-from-python ) 

[2] [Create a shared library with cmake]( https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake ) 

[3] [CMake linking Python]( https://stackoverflow.com/questions/28817266/cmake-not-linking-python ) 

[4] [Return array from C++ function to Python using ctypes]( https://stackoverflow.com/questions/14887378/how-to-return-array-from-c-function-to-python-using-ctypes ) 



