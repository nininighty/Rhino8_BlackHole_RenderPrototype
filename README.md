# Rhino8 BlackHole Render Prototype

基于 Rhino 8 C++ SDK 和 RDK（Render Development Kit）开发的黑洞引力透镜物理渲染器插件。本项目旨在结合数值积分算法与机器学习模型，实现高性能的时空扭曲视觉呈现。

## 1. 项目架构 (Project Architecture)

项目遵循 Rhino 标准的异步渲染管线，将 UI 交互、场景解析与像素计算解耦。

### 核心模块说明：

* **插件入口 (Plug-in Entry)**: 由 `CRenderPrototypePlugIn` 类负责。它管理插件的生命周期，并向 Rhino 注册渲染引擎身份。
* **渲染管线 (Render Pipeline)**: 由 `CRenderPrototypeSdkRender` 类负责。它继承自 `CRhRdkSdkRender`，是连接 Rhino 场景与自定义渲染算法的桥梁。
* **计算核心 (Computation Kernel)**: 位于 `ThreadedRender` 及其调用的 `CalculatePixel` 函数中。这是执行光线追踪、度规计算和 ML 预测的实际场所。

---

## 2. 文件目录解析 (File Index)

| 文件名 | 职能描述 | 核心开发点 |
| --- | --- | --- |
| **`RenderPrototypePlugIn.cpp`** | 插件主入口，负责初始化和命令分发。 | 修改插件元数据（名称、UUID、开发者信息）。 |
| **`RenderPrototypeSdkRender.cpp`** | **核心逻辑文件**。管理渲染线程、视口参数提取。 | 实现像素遍历逻辑，并将颜色数据写入输出通道。 |
| **`RenderPrototypeRdkPlugIn.cpp`** | RDK 适配器，处理材质、灯光和环境系统集成。 | 自定义渲染设置面板和吸积盘材质交互。 |
| **`RenderPrototypeEventWatcher.cpp`** | 场景监视器，监听模型变动以触发重新渲染。 | 优化实时预览下的场景更新频率。 |

---

## 3. 渲染流程逻辑 (Rendering Workflow)

1. **视图同步**: `CRenderPrototypeSdkRender::Render` 被调用，通过 `ON_Viewport` 提取当前相机的投影矩阵和视图矩阵。
2. **线程启动**: `StartRendering()` 开启异步线程，防止计算密集型的光线追踪导致 Rhino 界面假死。
3. **光线投射 (Ray Casting)**:
* `ThreadedRender` 循环遍历图像平面的每个像素 。
* 根据像素坐标生成初始光线向量 。


4. **物理/ML 计算**:
* 将光线参数喂给 `CalculatePixel`。
* **ML 阶段**：预测光线是否受黑洞显著影响。
* **积分阶段**：执行史瓦西（Schwarzschild）或克尔（Kerr）度规的数值积分，计算光线弯曲路径。


5. **结果反馈**: 使用 `IRhRdkRenderWindow` 将计算得出的颜色值填入 `chanRGBA` 通道，并实时刷新窗口。

---

## 4. 后续开发重点 (Roadmap)

* [ ] **相机模型优化**: 在 `ThreadedRender` 中接入完整的 `ON_Viewport` 转换，支持视角缩放与平移。
* [ ] **物理积分器实现**: 在 C++ 层编写基于 Runge-Kutta 算法的测地线方程求解器。
* [ ] **Python/ML 桥接**: 集成 `pybind11` 或 `Python.h`，实现 C++ 核心与 Python 预测模型的数据通信。
* [ ] **多普勒效应**: 计算由于吸积盘高速旋转产生的红移/蓝移效果。

---

## 5. 编译环境

* **IDE**: Visual Studio 2022
* **SDK**: Rhino 8 C++ SDK
* **依赖**: openNURBS, RDK
