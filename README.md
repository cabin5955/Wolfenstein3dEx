## Wolfenstein3dEx
基于LibEx代码在iOS平台上重新实现《德军总部3D》

### 上手指南
以下指南将帮助你在本地机器上安装和运行该项目，进行开发和测试。

### 安装要求
1. 操作系统：Mac OS X 10.12及以上
2. Xcode 9.0及以上

### 安装步骤
1. $ git clone https://github.com/cabin5955/Wolfenstein3dEx.git
2. 直接使用Xcode打开
3. Xcode点击运行

### 测试
game目录下包含2个测试类（场景）
1. GamePlatformer (game_platformer.hpp文件):简单的跳台演示
2. GameWolfenstein3d (game_wolfenstein3d.hpp文件)：《德军总部3D》地图入口


### 使用到的框架
+	stb - 纹理图片加载
+	glfm - 为移动设备和web创建并管理窗口和OpenGL上下文，同时还提供了简单的输入功能。
+	freetype2 - 字体
+	CocosDenshion - 声音播放
+	libtmx - 解析tmx文件（tmx由Tiled地图编辑软件生成）
+	Box2D - 物理引擎
+	dear imgui - 测试使用

### 作者
作者：cabin5955

### 版权说明
该项目签署了MIT 授权许可，详情请参阅LICENSE.md

### 鸣谢
+	Joey de Vries - learnopengl.com
+	thebennybox -  YouTube Wolfenstein 3D Clone Tutorial
