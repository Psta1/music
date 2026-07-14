# 🎵 音乐播放器

基于 Qt 6.11.1 开发的桌面音乐播放器，模仿网易云音乐界面风格。

## 功能特性

### 播放控制
- ▶/|| 播放/暂停（同一按钮切换）
- |◀ / ▶| 上一首 / 下一首
- 进度条拖动跳转
- 音量滑块调节

### 播放模式
- **顺序播放** — 按列表顺序播放，末尾循环回第一首
- **单曲循环** — 当前歌曲无限循环
- **随机播放** — 随机选取下一首（不重复当前歌曲）

### 歌词显示
- 自动加载同名 `.lrc` 歌词文件
- 播放时歌词同步滚动，当前行高亮（白色加粗）
- 支持标准 LRC 时间格式 `[mm:ss.xx]`

### 专辑封面
- 自动加载同名 `.jpg` / `.png` 图片
- 圆形裁剪显示，播放时旋转（黑胶唱片效果）
- 暂停时停止旋转，恢复播放时从当前角度继续

### 待播清单
- 右侧显示播放列表，包含缩略封面 + 歌名
- 双击切歌
- 可通过底栏 `≡` 按钮收起/展开
- "添加歌曲"按钮向列表中添加歌曲（不自动播放）

## 项目结构

```
music/
├── untitled/
│   ├── main.cpp              # 入口
│   ├── mainwindow.h          # 头文件
│   ├── mainwindow.cpp        # 主逻辑
│   ├── mainwindow.ui         # UI 布局
│   └── untitled.pro          # 项目文件
└── music/
    ├── 其实.mp3              # 音频文件
    ├── 其实.lrc              # 歌词文件
    ├── 其实.jpg              # 封面图片
    ├── 暧昧.mp3
    ├── 暧昧.lrc
    ├── 暧昧.jpg
    ├── 浮夸.mp3
    ├── 浮夸.lrc
    └── 浮夸.jpg
```

## 文件命名规则

歌曲、歌词、封面必须**同名**放在同一目录：

| 类型 | 格式 | 示例 |
|------|------|------|
| 音频 | `.mp3` `.wav` `.flac` `.m4a` `.ogg` | `浮夸.mp3` |
| 歌词 | `.lrc` | `浮夸.lrc` |
| 封面 | `.jpg` `.jpeg` `.png` `.bmp` `.webp` | `浮夸.jpg` |

## 环境要求

- Qt 6.11.1+
- 模块：`core` `gui` `multimedia` `widgets`
- 编译器：MSVC / MinGW（Windows）

## 编译运行

```bash
# 使用 qmake
cd untitled
qmake untitled.pro
make        # 或 nmake / mingw32-make

# 或在 Qt Creator 中打开 untitled.pro，直接构建运行
```

## UI 配色

参考网易云音乐深色主题：

| 元素 | 颜色 |
|------|------|
| 主背景 | `#1a1a2e` |
| 底栏背景 | `#1e1e3f` |
| 按钮/图标 | `#8b8b9e` |
| 按钮悬停 | `#ffffff` |
| 播放按钮背景 | `#2d2d4e` |
| 进度条/音量 | `#8b8b9e` |
| 播放列表背景 | `#16213e` |
| 当前歌词高亮 | `#ffffff` bold |
| 非当前歌词 | `#aaaaaa` |

## 技术要点

- `QMediaPlayer` + `QAudioOutput` 实现音频播放
- `connectSlotsByName` 自动连接按钮信号（按钮命名规范：`on_<objectName>_clicked`）
- `QTimer` 每 50ms 刷新封面旋转角度
- `QPainterPath` 圆形裁剪 + `QPainter::rotate` 实现旋转
- 通过 `positionChanged` 检测歌曲剩余不足 500ms 触发切歌（Qt 6.11.1 的 `EndOfMedia` 信号不可靠）
- `isSwitching` 标志位 + `QTimer::singleShot` 防止重复触发切歌
- 歌词偏移量 `lyricOffset = 1000ms` 解决歌词超前问题
- `setSource(QUrl())` 先清空再重设，确保单曲循环能重新加载同一文件
