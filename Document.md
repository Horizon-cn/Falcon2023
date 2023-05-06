# Document

整理一些技术积累和开发经验，如果写的特别好可以放到 Wiki 上

## Client

- `resource` 界面所需图片
- `src` **源代码**
    - `comm` 通讯模块
        - `actionmodule` 实车通讯，通过串口发送指令和接收机器人反馈（红外……）
        - `communicator` 与控制器通讯，接收指令并根据模式调用函数发出，传递反馈（红外……）
        - `crc` 循环冗余编码
        - `debugger` 接收控制器的Debug信息
        - `optionobject` 向控制器发送基础配置信息（选边、颜色、模式……）
        - `remotesim` 与仿真器通讯，通过网络发送指令和接收机器人反馈（红外……）
        - `simmodule` 同上
        - `simulator` 与仿真器通讯，发送放置机器人和球的指令
    - `interface` 程序内部接口类
        - `main` 程序主入口，设置qml和C++类的接口，启动界面和程序
        - `interaction` 主要的交互接口
        - `interaction4field` 场地区域的交互接口
        - `networkinterfaces` 网口设置接口
        - `paraminterface` 参数设置接口
        - `viewerinterface` 展示面板接口
    - `log` 记录、播放log组件
        - `rec_log` 队内自研格式
        - `rec_eventlabel` 给log打标签，标注重要事件
        - `rec_player` 播放log
        - `rec_recorder` 记录log
        - `rec_slider` 播放log的进度条
        - `worldcup` 世界赛格式（组成基本相同）
    - `other` 其他独立功能
        - `field` 场地视觉和调试信息的绘制、鼠标键盘事件响应
        - `display` 数据图表展示
        - `game` 游戏模式，或是自动裁判盒前身
        - `test` 测试模式，主要用于状态估计测试
    - `qml` 界面设计
        - `Components` 一系列自定义控件
        - `ComponentsKD` 浮动窗口相关的自定义控件
        - `Gamepad` 游戏手柄相关控件
        - `KDDockWidgets` 浮动窗口界面设计
            - `mainKD` 主界面
            - `ControlBoardKD` 控制面板
            - `RefereeBoxKD` 裁判盒
            - `SettingsKD` 参数配置界面
            - `ToolKitKD` 工具集界面  
            - `ViewerKD` 展示面板
            - `RemoteControl` 远程遥控界面
        - `Widgets` 普通窗口界面设计，结构与上述类似
    - `referee` 裁判通讯接口
        - `refereebox` 自带裁判盒的指令发送
        - `refereethread` 与GC通讯，注册队伍信息
    - `utils` 工具类
        - `globaldata` 全局数据
        - `globalsettings` 全局设置，主要针对场地
        - `messageformat` 自定义的重要类型
        - `parammanager` 参数管理器
        - `staticparam` 静态常量，一些很确定的数量（队伍数量、机器人数量……）
        - `translator` 翻译器
        - `……` 其他固有的类定义
    - `vision` 视觉处理
        - `ballrecords` 球基本信息记录格式（位置、时间戳、相机……）
        - `ballstate` 球状态记录格式（被踢出、争抢中、控球中……）
        - `chipsolver` 挑球的判断和轨迹分析
        - `collisiondetect` 碰撞模型
        - `dealball` 球信息处理的流程
        - `dealrobot` 机器人信息处理流程
        - `kalmanfilter` 卡尔曼滤波
        - `kalmanfilterdir` 针对方向的卡尔曼滤波
        - `maintain` 生成完整图像的流程
        - `visionmodule` 接收、发送视觉的接口
 - `Client.ico` 可执行文件封面图片
 - `Client.qrc` 存放qml、图片等路径
 - `Client.rc` 存放封面图片路径  
 - `qtquickcontrols2.conf` Qt Quick控件配置文件

## Reference

+ [Rocos](https://github.com/Robocup-ssl-China/rocos)
