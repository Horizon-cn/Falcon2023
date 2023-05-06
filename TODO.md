# TODO

革命尚未成功，同志们仍需努力！！！

## 开发须知

- git push 前，注意将以下配置归为默认值：
	- gpuBestAlgThread.cpp 中，#define has_GPU false
	- 并行编译所用核数为4
	- 关闭 Client 的 Debug 信息，在 Client/CMakeLists.txt 中都不要注释
	```bash
	if (WIN32)
    message(${CMAKE_C_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	endif()
	```
- 国际化语言包：Client 每次编译后文件夹中都会生成 zh_CN.ts，这属于临时文件，不会上传到 git。生成 .qm 文件后将两者都复制到 bin/Language 里面，便于查错
  - [Linguist入门参考](https://gitlab.com/src-ssl/src/-/wikis/Software/Qt%E5%A4%9A%E8%AF%AD%E8%A8%80%E5%88%87%E6%8D%A2%E7%9A%84%E5%AE%9E%E7%8E%B0)

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
	- [x] 优化各种显示物体的大小，画面整洁易观察
	- [ ] Fields初始大小有时会有问题，填充不满
	- [x] 裁判盒优化，恢复next command
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
	- [x] 穿模问题解决
	- [ ] 视觉遮挡、环境噪声等现实情况模拟
- [ ] 视觉

## 未解决的顽疾

- [ ] 放大画面的操作放大倍数超过一定数量时，跑Core时会crash，现在限制了放大倍数
- [ ] 多线程之间的信号发射接收有时会有bug，visionmodule和rec_recorder之间
- [ ] 实车视觉有时候接不上，特别是电脑开机时间较长时，只能重启
- [x] 配置cuda后编过了打不开Core.exe：cuda版本不兼容
- [x] 系统极依赖电脑性能，明显卡顿：线程内计算不合理，无视觉时应处于静默状态，不占用cpu资源，添加信号量后解决。且线程之间的运算复杂度需要平衡，视觉接收线程决定Core的帧率，不应安排复杂运算
