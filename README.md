
# 未命名

2023年开始使用的新AI框架，采用插件模式，拥有良好的跨平台能力

## 框架组成（暂时）

- Client : 可视化界面、调试工具、视觉处理模块
	- sim : 内嵌仿真器，grSim改进版
- Core : 控制、决策算法
- ZBin : LUA脚本和必要参数
- Controller : 遥控工具

## 重构进度

- [x] windows上能编译通过，步骤比较简洁
- [ ] 整理输出、生成文件的放置目录
- [ ] 代码重构，设置底层系统与插件

## 编译工具

- 软件
	- [Qt≥5.10](https://www.qt.io/)
	- [CMaket≥3.10](https://cmake.org/download/)
- 依赖库
	- protubuf
	- tolua
	- lua
	- zlib
	- ode
	- Eigen(remove)

## 编译方法

- Ubuntu : 具体编译方法见B站，搜索"Rocos环境配置"
- Windows : 
	- 注意检查是否有 3rdParty 
	- 使用CMake Gui，输入源代码所在目录和编译目录（一般是源代码所在目录/build）
	- 直接Configure，Qt需要输入路径，如D:\QT\Qt5.12.9\5.12.9\msvc2017_64\lib\cmake\Qt5，其他的都已设置好，无需手动输入
	- 完成后点击Generate，在点击Open Project
	- 在vs中选择Release x64模式，并设置Core项目属性，选择15工具集
	- 开始生成，没有报错则完成
	- 如果需要使用GPU，按照相应教程设置vs工具和项目属性

## 常见问题

- 如果软件不正常退出，重新打开后先Kill进程，杀掉未关闭的进程后再开启软件
- 裁判盒指令无法接入，需核查网络配置，虚拟机需将网络设置为桥连模式
- 开启对打，需将Core复制一份命名为Core2，不需要再设置Left/Right，直接开就好
- 下车的时候数字键/Ctrl+数字键，待软件反应后再做其他操作，否则容易崩溃
