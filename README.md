
# Nest_On_Ubuntu

我们一直想统一用鸟类命名各类软件，所以软件层面的AI框架就叫Nest(鸟巢)啦

## 框架组成

- Owl : 可视化界面、调试工具、视觉处理模块，希望和猫头鹰一样保持明亮的眼睛
- Crow : 控制、决策算法，乌鸦喝水，在鸟类里面应该算聪明的
- Pigeon : LUA脚本，信鸽的执行力和团体意识挺不错

## 编译工具

- 软件
	- [Qt≥5.10](https://www.qt.io/)
	- [CMaket≥3.10](https://cmake.org/download/)
- 依赖库
	- protubuf
	- tolua
- 具体编译方法见B站，搜索"Rocos环境配置"

## 常见问题

- 关闭Crow的时候，直接Kill进程，一起关闭Owl
- 裁判盒指令无法接入，需核查网络配置，虚拟机需将网络设置为桥连模式
