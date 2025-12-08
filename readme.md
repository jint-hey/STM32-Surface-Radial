# STM32旋钮(Surface Radial)项目介绍

## 一. 项目简介

本项目使用ST公司的STM32F042F6P6单片机，模拟微软的Surface Dial产品部分功能。

Surface Dial产品链接：[Surface Dial-Surface Dial智能旋钮-微软Dial配件-微软官方商城 ](https://www.microsoftstore.com.cn/surface/surface-dial)

Surface Dial官方介绍：[Surface Dial 交互 - Windows apps | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows/apps/develop/input/windows-wheel-interactions)

主要实现功能如下：

- 长按旋钮显示Surface Dial 屏幕菜单

<img src=".\picture\surface-dial-menu-offscreen.png" style="zoom:80%;" />

- 点按旋钮可选择相应功能
- 旋转旋钮可编辑相应功能
- RGB彩灯效果

成品图：

<img src=".\picture\8f92d38e978af554f702f09a11d16235.jpg" style="zoom: 33%;" />

<img src=".\picture\620c4194e11f0f63d8fb1e02e46c7f43.jpg" style="zoom:33%;" />

功能展示：
[STM32 surface radial 旋钮_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Bq2rBwEm3/?spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=f520e124187138f8a0f86d9606e8b841)

## 二. 硬件部分

**参考来源：**

- [stm32+cubemx+platformio+usbhid-->surface dial，懂？ - 哔哩哔哩](https://www.bilibili.com/opus/709479763705593878)
- [surfacedial-stm32 - 立创开源硬件平台](https://oshwhub.com/areyouokman/surfacedial-stm32)
- [项目详情](https://lckfb.com/project/detail/lckfb-dkx-stm32f103c8t6?param=baseInfo)

### 1. 原理图和PCB

原理图和PCB设计使用嘉立创EDA标准版

<img src=".\picture\Schematic_Radial-Controller_2025-12-07.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_00-00-44.png" style="zoom:50%;" />

<img src=".\picture\Snipaste_2025-12-08_00-01-40.png" style="zoom:50%;" />

### 2. STM32主控部分

单片机采用ST公司的STM32F042F6P6

产品的用户手册可从立创商城获取：[STM32F042F6P6中文资料_最新报价_数据手册下载_ST(意法半导体)-单片机(MCU/MPU/SOC)-立创商城](https://item.szlcsc.com/82150.html?fromZone=s_s__%22C81000%22&spm=sc.gbn.xh1.zy.t&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcV1ZQR1BdVzsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

<img src=".\picture\Snipaste_2025-12-07_23-14-22.png" style="zoom:33%;" />

1. 商品特性

   - 核心：32位ARM Cortex-M0 CPU，频率高达48 MHz
   - 存储器：
     - 16至32 K字节的闪存
     - 6 K字节带硬件奇偶校验的SRAM

   - 两个SPI（18 Mbit/s），支持4至16位可编程帧，其中一个与I2S接口复用
   - 5通道DMA控制器
   - USB 2.0全速接口，能够使用内部48 MHz振荡器运行，并支持BCD和LPM
   - 九个定时器：
     - 一个16位高级控制定时器，用于六通道PwM输出
     - 一个32位和四个16位定时器，最多四个IC/OC、OCN，可用于IR控制解码
     - 独立和系统看门狗定时器
     - SysTick定时器

2. 使用USB 2.0接口模拟Surface Dial的部分功能，与电脑进行交互

3. 使用通用定时器的输入捕获通道获取旋转编码器的值

4. 使用SPI和DMA控制RGB灯

### 3. 复位

单片机复位引脚直接使用电阻上拉，取消手动复位

### 4. 5V转3.3V模块

<img src=".\picture\Snipaste_2025-12-07_23-32-04.png" style="zoom:33%;" />

LDO稳压模块使用ME6211C33M5G-N，实现5V稳压到3.3V，给单片机供电

产品的用户手册可从立创商城获取：[ME6211C33M5G-N中文资料_最新报价_数据手册下载_MICRONE(南京微盟)-线性稳压器(LDO)-立创商城](https://item.szlcsc.com/84106.html?fromZone=s_s__%22C82942%22&spm=sc.gbn.xh1.zy.t&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcV1xfTlFdVTsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

1. 商品特性
   - 最大输出电流：500mA（VIN = 4.3V，VOUT = 3.3V）
   - 压差电压：100mV（Iout = 100mA时）
   - 工作电压范围：2V ~ 6.0V
   - 高精度：±2%
   - 低功耗：40μA（典型值）
   - 待机电流：0.1μA（典型值）
   - 高纹波抑制：70dB（1kHz时，ME6211C33）
   - 低输出噪声：50μVrms
   - 线性调整率：0.05%（典型值）

### 5. TYPE-C供电&USB接口

<img src=".\picture\Snipaste_2025-12-07_23-33-35.png" style="zoom:33%;" />

TYPE-C使用16PIN母座

产品的用户手册可从立创商城获取：[TYPE-C 16PIN 2MD(073)中文资料_最新报价_数据手册下载_SHOU HAN(首韩)-USB连接器-立创商城](https://item.szlcsc.com/2901843.html?fromZone=s_s__%22C2765186%22&spm=sc.gbn.xh1.zy.n&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcVlJWQVhXUzsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

1. 商品特性

   - 安装方式：卧贴

   - 触点数量： 16P

   - 额定电流：3A
   - 额定电压：5V
   - 插拔寿命： 5千次

2. TYPE-C为电路实现5V供电

3. USB_DP接口接上拉电阻，可被电脑识别为全速USB设备

   USB 2.0 的电气特性解说参考此网站：[USB 2.0 详解（三）—— 电气特性 - 韦东山嵌入式开发者社区](https://100ask.net/article/910)

4. CC1和CC2接口接5.1K下拉电阻，可以实现A口->C口，也可以实现C口->C口供电

   CC1和CC2功能解说参考此网站：[Type-C电路CC1和CC2的下拉电阻_typec的cc1和cc2接电阻-CSDN博客](https://blog.csdn.net/zjb6668/article/details/147023512)

### 6. 旋转编码器

<img src=".\picture\Snipaste_2025-12-07_23-31-44.png" style="zoom:67%;" />

旋转编码器使用EC11E15244G1，模拟Surface Dial的旋转、单机和长按功能

产品的用户手册可从立创商城获取：[EC11E15244G1中文资料_最新报价_数据手册下载_ALPSALPINE(阿尔卑斯阿尔派)-旋转编码器-立创商城](https://item.szlcsc.com/344654.html?fromZone=s_s__%22C370970%22&spm=sc.gbn.xh1.zy.t&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcVldfRFZXUzsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

1. STM32F042F6P6的GPIO自带上拉电阻，所以可以去掉R6、R7
2. 电容实现硬件消抖

### 7. 晶振

<img src=".\picture\Snipaste_2025-12-07_23-42-39.png" style="zoom:33%;" />

晶振使用X32258MOB4SI，8MHZ，无缘晶振，为单片机提供时钟

产品的用户手册可从立创商城获取：[X32258MOB4SI中文资料_最新报价_数据手册下载_YXC(扬兴晶振)-无源晶振-立创商城](https://item.szlcsc.com/2777872.html?fromZone=s_s__%22C2682775%22&spm=sc.gbn.xh1.zy.t&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcVVVTQ1NcVDsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

### 8. WS2812灯

<img src=".\picture\Snipaste_2025-12-08_09-47-11.png" style="zoom:33%;" />

WS2812 RGB灯使用WS2812B，实现彩灯效果

产品的用户手册可从立创商城获取：[WS2812B-B/W中文资料_最新报价_数据手册下载_worldsemi-RGB LED(内置IC)-立创商城](https://item.szlcsc.com/115830.html?fromZone=s_s__%22C114586%22&spm=sc.gbn.xh1.zy.t&lcsc_vid=ElMIVQECTlVXAwFQFQVfU1UHE1FZXlIAQgdWBVcHTlExVlNQQlBcVVBeQlVcUjsOAxUeFF5JWA0NAgAHWQIASA%3D%3D)

## 三. 软件部分

**参考来源：**

- [stm32+cubemx+platformio+usbhid-->surface dial，懂？ - 哔哩哔哩](https://www.bilibili.com/opus/709479763705593878)
- [wuhuuu/SurfaceDial-STM32: Here is a simple demo achieving RadialController(surface dial) function with stm32.](https://github.com/wuhuuu/SurfaceDial-STM32)
- [STM32f407使用cubemx控制ws2812流水灯带（spi+dma方案）_ws2812 spi-CSDN博客](https://blog.csdn.net/m0_53440477/article/details/145701413)
- [Windows 径向控制器示例报告描述符 | Microsoft Learn](https://learn.microsoft.com/zh-cn/windows-hardware/design/component-guidelines/radial-controller-sample-report-descriptors)

### 1. STM32CubMax配置

#### 1. 引脚配置

<img src=".\picture\Snipaste_2025-12-08_09-50-55.png" style="zoom:80%;" />

#### 2. 使用ST-Link调试接口

<img src=".\picture\Snipaste_2025-12-08_09-53-00.png" style="zoom:80%;" />

#### 3. RCC时钟配置

<img src=".\picture\Snipaste_2025-12-08_09-54-17.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_09-55-21.png" style="zoom:80%;" />

#### 4. GPIO配置

<img src=".\picture\Snipaste_2025-12-08_09-56-49.png" style="zoom:80%;" />

PA2检测编码器是否按压

PA3控制User_LED灯

#### 5. TIM2配置

<img src=".\picture\Snipaste_2025-12-08_09-59-18.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_09-59-45.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_10-09-51.png" style="zoom:80%;" />

使用TIM2的编码器接口采集编码器的旋转信息

#### 6. TIM3配置

<img src=".\picture\Snipaste_2025-12-08_10-05-10.png" style="zoom:80%;" />

![](.\picture\Snipaste_2025-12-08_10-06-11.png)

使用TIM3定时器中断控制RGB彩灯的变化速度

#### 7. USB接口配置

<img src=".\picture\Snipaste_2025-12-08_10-03-51.png" style="zoom:80%;" />

#### 8. SPI+DMA

<img src=".\picture\Snipaste_2025-12-08_10-07-53.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_10-08-35.png" style="zoom:80%;" />

<img src=".\picture\Snipaste_2025-12-08_10-09-07.png" style="zoom:80%;" />

### 2. 代码

- Radial Controller文件夹是项目代码

- Hardware文件夹中是自己编写的代码
  - MyDial.h/c 是USB数据发送功能
  - MyEncoder.h/c 是编码器数据获取和处理功能
  - MyLED.h/c 是User_LED控制功能
  - WS2812.h/c 是WS2812驱动和显示功能

- 使用STM32CubMax配置好工程后，找到Radial Controller\Middlewares\ST\STM32_USB_Device_Library\Class\HID\Src\usbd_hid.c和Radial Controller\Middlewares\ST\STM32_USB_Device_Library\Class\HID\Inc\usbd_hid.h文件

  - 修改

    <img src=".\picture\Snipaste_2025-12-08_10-27-34.png" style="zoom:80%;" />

    <img src=".\picture\Snipaste_2025-12-08_10-28-32.png" style="zoom:80%;" />
