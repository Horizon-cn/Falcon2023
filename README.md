
# Falcon_2023

2023年开始使用的新AI框架，希望拥有良好的跨平台能力

## 框架组成

- `3rdParty` -- 编译所用第三方库
- `bin` -- release版软件
	- `base` -- 可执行文件合集
	- `data` -- 重要参数和记录数据
	- `Formation` -- 机器人阵型文件
	- `Help` -- 更多使用教程
	- `Layout` -- 保存的界面排布设置
	- `LOG` -- log文件
	- `lua_scripts` -- lua脚本
	- `package.bat` -- QT自动打包脚本
	- `run.bat` -- 快捷运行程序脚本
- `cmake` -- cmake编译文件
- `Client` -- 可视化界面、调试工具、视觉处理模块
- `Core` -- 控制、决策算法
- `grSim` -- 物理仿真引擎
- `share` -- 共享代码

## 重构进度

- [x] windows上能编译通过，步骤比较简洁
	- [x] 统一工具集，适应vs2022
	- [x] 打包获取路径简单些
- [x] 可启动比赛，启动流程比较简单
- [x] 参数管理优化
	- [x] 参数共享（Core比较麻烦）
	- [x] Client参数显示可选择文件
	- [x] 参数分类整定，简洁化（大工程）
		- [x] `vision.ini` 视觉处理模块的参数
		- [x] `simulator.ini` 仿真引擎参数，包括世界和机器人模型
		- [x] `skill.ini` 决策算法参数，负责各类skill和比赛规则
		- [x] `cfg.ini` 系统内部不常变动的参数，固定的通讯端口、路径和数学常量
		- [x] `owl2.ini` 可视化界面的参数和经常要调整的参数
		- [x] `kickparam.ini` 踢球力度拟合
- [ ] Client界面优化
	- [x] 采用KDDockWidgets
	- [x] 优化界面的初始化排布，分界面可恢复
	- [ ] 优化各种显示物体的大小，画面整洁易观察
	- [ ] Fields初始大小有时会有问题，填充不满
	- [ ] 裁判盒优化，恢复next command
	- [ ] 解决关于KDDockWidgets的Warning
	- [ ] 分图层绘制，防止Fields崩溃
	- [ ] 与视觉模块解耦，分线程运行
- [ ] lua相关
	- [ ] 修改lua框架，可在Client上设置要跑的脚本（较难）
	- [ ] 自动标定脚本
- [ ] 串口通讯和Cray整合（回校后)
	- [x] ssl_fifa整合，实现实车通讯
	- [x] 实车踢球力度拟合
	- [ ] 老版Cray的PID等调试功能是否移植
- [ ] 仿真器
	- [ ] 穿模问题解决
	- [ ] 视觉遮挡、环境噪声等现实情况模拟
- [ ] 视觉

## 未解决的顽疾

- [ ] 放大画面的操作放大倍数超过一定数量时，跑Core时会crash，现在限制了放大倍数
- [ ] 多线程之间的信号发射接收有时会有bug，visionmodule和rec_recorder之间
- [ ] 实车视觉有时候接不上，特别是电脑开机时间较长时，只能重启
- [x] 配置cuda后编过了打不开Core.exe：cuda版本不兼容
- [x] 系统极依赖电脑性能，明显卡顿：线程内计算不合理，无视觉时应处于静默状态，不占用cpu资源，添加信号量后解决。且线程之间的运算复杂度需要平衡，视觉接收线程决定Core的帧率，不应安排复杂运算

## 编译工具

- 软件
	- [Qt ≥ 5.15](https://www.qt.io/)
	- [CMake](https://cmake.org/download/)
	- [Visual Studio](https://visualstudio.microsoft.com/zh-hans/?rr=https://www.microsoft.com/zh-cn/)
		- Visual Studio 2019, CMake ≥ 3.14
		- Visual Studio 2022, CMake = 3.22
- 依赖库
	- Eigen
	- kddockwidgets-1.5.0
	- lua
	- ODE
	- protubuf-3.17.2
	- tolua++
	- vartypes
	- zlib
	
## 编译方法

- Ubuntu(未尝试) : 具体编译方法见B站，搜索"Rocos环境配置",最后再加上下载Vartypes、KDDockWidgets
```bash
$ cd /tmp
$ git clone https://github.com/jpfeltracco/vartypes.git
$ cd vartypes
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```
- Windows : 
	- 注意检查是否有 3rdParty
	- 建议先修改 cmake/GetThirdParty.cmake 中的QT部分，输入电脑上的QT路径
		- set(CMAKE_PREFIX_PATH "D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5") 
	- 使用CMake Gui，输入源代码所在目录和编译目录，如：
		- Where is the source code : D:/Falcon_2023
		- Where to build the binaries : D:/Falcon_2023/build
	- 直接Configure
	- 完成后点击Generate，再点击Open Project
	- 在vs中选择Release x64模式
	- 开始生成，没有报错则完成
	- 如果觉得生成过慢，可以更改 cmake/Utils.cmake，下述用了4核并行编译，可以查看电脑有几核，适当设置多些，但不建议给满
	```bash
	ProcessorCount(N)
    if(N GREATER_EQUAL 4)
    	set(N 4)
    endif()
    ```
	- 如果需要使用GPU，按照 [wiki教程](https://gitlab.com/src-ssl/src/-/wikis/Algorithm/加入cuda的falcon编译) 配置
	- 运行 bin/package.bat，首次编译或更换qt路径时需删除package.txt重新输入路径,如：
		- Where is QT QML : D:\QT\5.15.2\msvc2019_64\qml
   		- Where is Client QML : D:\Nest_Run_2023\Client\src\qml

## 使用方法

- 启动run.bat
- 拖动调整界面排布到适合的形式或直接读入更好的Layout
- 开启新的分界面在Widget里面选择
- 键盘快捷键“r”重新载入某一.ini文件参数
- 其他操作与 [owl2操作手册](https://gitlab.com/src-ssl/src/-/wikis/Software/owl2操作手册) 中类似
- git push 前，注意将以下配置归为默认值：
	- gpuBestAlgThread.cpp中，#define has_GPU false
	- 并行编译所用核数为4

## 常见问题

- 如果软件不正常退出，重新打开后先Kill进程，杀掉未关闭的进程后再开启软件
- 裁判盒指令无法接入，需核查网络配置，虚拟机需将网络设置为桥连模式
- 下车的时候数字键/Ctrl+数字键，待软件反应后再做其他操作，否则容易崩溃
- 当分界面脱离主界面时，一些键盘快捷键会失效，需要将分界面拖回主界面
