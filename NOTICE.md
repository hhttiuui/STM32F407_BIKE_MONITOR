# 第三方组件与许可声明

本仓库的**自研部分**（`Core/Src/` 下除 CubeMX 生成文件外的模块、
`Core/Inc/` 里对应的头文件）由 hhttiuui 编写，以 [MIT](LICENSE) 发布。

用到的第三方库都是宽松许可，与 MIT 兼容，所以整个项目可以按 MIT 分发。
下面逐项说明。

---

## 1. STM32F4xx HAL Driver — BSD-3-Clause

路径：`Drivers/STM32F4xx_HAL_Driver/`

```
Copyright (c) 2017 STMicroelectronics.
```

许可原文见 `Drivers/STM32F4xx_HAL_Driver/LICENSE.txt`。要点是 BSD-3-Clause：
保留版权声明、不得用 ST 的名义为衍生产品背书、免责条款。

这部分由 STM32CubeMX 从 FW_F4 V1.27.0 复制进工程，**未作修改**。

---

## 2. ARM CMSIS — Apache-2.0

路径：`Drivers/CMSIS/`

许可原文见 `Drivers/CMSIS/LICENSE.txt`（Apache License 2.0）。

本仓库只保留编译真正需要的两个子目录：

- `Drivers/CMSIS/Include/` —— Cortex-M 内核头文件
- `Drivers/CMSIS/Device/ST/STM32F4xx/` —— 器件定义与启动文件

未包含的部分（`Lib/`、`DSP/`、`NN/`、`RTOS/`、`RTOS2/`、`docs/`、`Core_A/`）
本工程用不到，已在 `.gitignore` 里排除。需要的话从 ARM 官方或
STM32Cube FW_F4 里取。

---

## 3. STM32CubeMX 生成的文件

`Core/Src/main.c`、`gpio.c`、`adc.c`、`tim.c`、`usart.c`、
`stm32f4xx_hal_msp.c`、`stm32f4xx_it.c`、`system_stm32f4xx.c`、
`Core/Inc/` 下对应的头文件，以及 `MDK-ARM/startup_stm32f407xx.s`，
都是 STM32CubeMX 按 `Hal_USART.ioc` 自动生成的骨架代码。

它们属于 ST 的工具输出，按上面第 1 条的 BSD-3-Clause 处理。
业务逻辑是在这些骨架上手写的，改动部分归本项目。

**改外设请改 `Hal_USART.ioc` 并重新生成**，不要直接手改生成文件
——下次生成会被覆盖。

---

## 4. 构建工具（不入库）

- **Keil MDK-ARM V5** —— 商业软件，需自行购买或使用社区版限制
- **STM32F4xx_DFP** 器件支持包
- **STM32CubeMX** —— 免费，需 ST 账号

本仓库不包含编译器、器件包或任何 Keil 的二进制产物。
`MDK-ARM/Hal_USART/`（编译输出）已在 `.gitignore` 里排除。
