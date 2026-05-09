# 微机原理 ATMega16 系列实验

## 准备工作

### 环境要求

- 硬件环境：ATMega16A 开发板 1 个，ISP 数据线 1 条。

- 软件环境：Windows 操作系统，PROGISP 1.72 烧写软件，ICCAVR 7.22 编译软件。

### 软件配置

- PROGISP：
  - 需要设置 Select Chip 为 ATMega16A。

- ICCAVR：
  - 需要设置 Compiler Options - Target - Device Configuration 为 ATMega16。
  - 需要设置 Compiler Options - Paths - Include Paths 为 ICCACR 软件安装目录的 include 文件夹。
  - 需要复制 [AVR_HJ-2G.H](AVR_HJ-2G.H) 文件到 ICCACR 软件安装目录的 include 文件夹。

- 文本编辑器：
  - 需要采用 GBK 编码。

### 示例程序

以下程序是开发板的 Hello World 程序，功能是打开 LED、关闭数码管，并点亮 BP 口的第 0 个引脚。

```c
#include "iom16v.h"
#include <macros.h>  //包含"位"操作头文件
#include <AVR_HJ-2G.H>

void main()
{
    LEDON();  //打开LED总开关
    SEGOFF();  //关数码显示管函数
    //DDRB=0xFF;  //BP口输出
    //PORTB=0xFE;  //11111110
    PORTB&=~BIT(0);
}
```

## 实验 1

### 实验要求

用两个按键 K1 和 K2 控制流水灯（查询方式）：

1. 当按下 K1 时，流水灯从左向右，依次亮一只灯、两只灯，……直至全亮，然后循环； 
2. 当按下 K2 时，流水灯从右向左，依次亮一只灯、两只灯，……直至全亮，然后循环。 

### 硬件连接

无需额外连接。使用开发板上的 K1 和 K2 按键即可。

### 源码设计

实验所用的源码位于 [exp1.c](exp1.c) 文件中。

## 实验 2

### 实验要求

将实验 1 的查询方式改为中断方式实现。

### 硬件连接

使用杜邦线连接 PD0 到 PD2（INT0）引脚，连接 PD1 到 PD3（INT1）引脚。

### 源码设计

实验所用的源码位于 [exp2.c](exp2.c) 文件中。
