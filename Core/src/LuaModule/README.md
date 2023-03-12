# LuaModule

定义Cpp 与 Lua 之间的接口，实现数据传递和在 Lua 中调用 Cpp 定义的函数

## pkg

- 规定 Cpp 中的哪些函数提供给 Lua 使用，形式基本是把 Cpp 头文件的定义部分复制过来，再做适当修改
- 注意：
    - 每个 pkg 要引用对应的头文件，**$#include "xxx.h"**
    - 只接受 Enum、Class 和 Struct 定义，不接受 typedef 
    - Class 定义中，提供给 Lua 调用的函数必须是 public，且不能带有 static 和 inline 属性，不需要提供函数定义，但必须有定义
    - 不需要提供成员函数，所以若传参有默认值，最好直接写数字，不能是另一个变量值；如果有自定义类型的传参，传递的参数变量必须有名称
    - 不支持 > < >> << = () 的操作符重写函数
    - 函数模板必须指定 T 的类型，如**TOLUA_TEMPLATE_BIND(T,double)**，无法解析 template 语法
- 需要生成接口的 pkg 写进 Zeus.pkg，**$pfile "xxx.pkg"**，生成 lua_zeus.cpp
- 在 Lua 中调用，Class 或 Struct 定义的为 xxx : f()，需要在 global 里定义了单例指针，xxx 用指针的名称，可完成实例化；namespace 定义的为 xxx . f()，xxx 为类型和名字空间的名称
