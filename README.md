# STM32F407 骑行状态监控（车载）

大一时做的嵌入式竞赛作品，装在自行车上实时监控骑行状态。核心是**摔车检测**
——MPU6050 检测到剧烈冲击就点亮三面 LED 并鸣喇叭警示，同时 OLED 显示状态、
蓝牙把速度和骑行时长上报给手机。

STM32F407VGTx + STM32 HAL，Keil MDK 工程，外设初始化由 STM32CubeMX 生成，
业务代码都在 `Core/Src/`。

## 硬件平台

| 项目 | 说明 |
|---|---|
| MCU | **STM32F407VGTx**（Cortex-M4F，168 MHz，1 MB Flash） |
| 生成工具 | STM32CubeMX 6.9.2，固件包 FW_F4 V1.27.0 |
| 工具链 | **Keil MDK-ARM V5.32** |
| 调试 | SWD（PA13 / PA14） |
| 供电 | 电池，ADC3_IN13 采样电压 |

## 功能模块

| 模块 | 文件 | 说明 |
|---|---|---|
| **摔车检测** | `waring.c` | 读 MPU6050 加速度 AY 轴，\|AY\| > 1800 判定摔车，点亮左/右/前 LED + 鸣喇叭 + OLED 显示 `WARING`；正常时显示 `SAVE` |
| 姿态 | `MPU6050.c` + `MyI2c.c` | 软件 I2C 读六轴原始数据 |
| 测速 | `cesu.c` | 车轮转一圈计一次脉冲（PB1 / EXTI1），换算速度 |
| 骑行计时 | `main.c` | 秒 / 分累计，OLED 显示 |
| 超声波测距 | `chaoshengbo.c` | 定时器捕获回波宽度算距离 |
| 显示 | `OLED.c` + `OLED_Font.h` | SSD1306，软件 I2C，显示电压 / 温度 / 时间 / 状态 |
| 蓝牙上报 | `lanya.c` | 串口透传，把速度、骑行时长转成字符串发给手机 |
| 声光警示 | `led_laba.c` | 4 路 LED + 喇叭 |
| 按键 | `Key.c` | 5 个输入 |
| 电压采样 | `adc.c` | ADC3_IN13，监测电池电量 |

### 摔车判据

```c
MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
if (AY > 1800 || AY < -1800)
    return 1;   // 判定摔车
```

阈值是实车试出来的——正常骑行时 AY 在 ±1800 以内，摔倒瞬间的冲击会大幅超出。
这个判据很粗糙（没有滤波、没有持续时间窗口），但在当时的场景下够用。

## 引脚分配

来自 `Hal_USART.txt`（CubeMX 导出）：

| 外设 | 引脚 | 标签 |
|---|---|---|
| USART1 TX / RX | PA9 / PA10 | 蓝牙串口 |
| ADC3_IN13 | PC3 | 电池电压采样 |
| 测速输入 | PB1（EXTI1） | cesu |
| 按键 ×5 | PB2 / PE7 / PE8 / PE9 / PE10 | KEY |
| LED ×4 | PE12 / PE13 / PE14 / PE15 | LED |
| 喇叭 | PE11 | LA_BA |
| OLED I2C | PB8（SCL）/ PB9（SDA） | OLED |
| 备用 I2C | PB10 / PB11 | I2C |
| 备用 IO | PC4（输出）/ PC5（输入） | |
| SWD | PA13 / PA14 | |
| 晶振 | PC14 / PC15 | 32.768 kHz |

## 目录结构

```
.
├── Core/
│   ├── Inc/            用户头文件 + CubeMX 生成的 main.h / usart.h / tim.h 等
│   └── Src/            用户源文件 + main.c / stm32f4xx_it.c / hal_msp.c
├── Drivers/
│   ├── STM32F4xx_HAL_Driver/   ST 官方 HAL（BSD-3-Clause）
│   └── CMSIS/                  ARM CMSIS（Apache-2.0），只保留工程用到的部分
├── MDK-ARM/            Keil 工程（.uvprojx）与启动文件
├── Hal_USART.ioc       CubeMX 工程文件，改引脚/外设从这里改
├── .mxproject          CubeMX 缓存
├── Hal_USART.txt       CubeMX 导出的引脚清单
└── Hal_USART.pdf       CubeMX 导出的配置报告
```

## 构建

1. 安装 **Keil MDK-ARM V5**，并装好 **STM32F4xx_DFP** 器件支持包
2. 打开 `MDK-ARM/Hal_USART.uvprojx`
3. `Build`（F7），产物在 `MDK-ARM/Hal_USART/`

要改外设或引脚，用 **STM32CubeMX** 打开 `Hal_USART.ioc` 重新生成代码。
CubeMX 只覆盖它自己管理的文件，`waring.c` / `cesu.c` / `chaoshengbo.c`
这些手写模块不受影响。

## 踩过的坑

- **`Drivers/CMSIS` 原本 115 MB**，绝大部分是 DSP 的预编译数学库
  （每个 `.lib` 13 MB，四个架构各一份）和 DSP 示例。这个工程根本没用 DSP，
  已加入 `.gitignore`，仓库里只保留编译真正需要的 `Include` 和
  `Device/ST/STM32F4xx`。加上 Keil 构建输出，跟踪内容从 199 MB 降到 6.5 MB。
- **Keil 的 `*.uvguix.<用户名>` 不要提交**，那是窗口布局，换台机器就失效，
  文件名还带 Windows 用户名。
- **源文件编码**：`main.c`、`chaoshengbo.c`、`waring.c`、`stm32f4xx_it.c`
  原本是 GBK，其余是 UTF-8。为让 GitHub 上中文注释正常显示，已统一转成
  UTF-8。Keil 里中文显示异常的话，把编辑器编码设为 UTF-8。
- **摔车判据是单轴阈值**，没有滤波也没有持续时间判断。想做成能日常用的产品，
  至少要加：加速度低通滤波、持续时间窗口（避免过坑误报）、摔车后的自动
  求救（蓝牙发消息）。

## 许可

[MIT](LICENSE)。用到的第三方库都是宽松许可（ST HAL 是 BSD-3-Clause，
CMSIS 是 Apache-2.0），可以自由使用。详见 [NOTICE.md](NOTICE.md)。
