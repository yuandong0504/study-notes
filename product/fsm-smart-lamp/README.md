# FSM Smart Lamp

> 阶段 1 · 最小版 README

# 💡 FSM Smart Lamp

一个最小可用的 **有限状态机（FSM）** 项目，用来模拟“智能台灯”的开关逻辑。  
通过这个 demo，你可以快速理解 enum、状态转移表、动作函数等核心概念。

---

## 🎯 项目目标

- 唯一交互：
  - `space` = 切换 ON / OFF  
  - `q`     = 退出程序
- 状态：
  - OFF
  - ON
- 行为：
  - 每次切换打印日志，例如：
    - `OFF -> ON  | 开灯`
    - `ON  -> OFF | 关灯`

---

## 📂 目录结构

## 目录结构
```
fsm-smart-lamp/
├── README.md
├── src/
│   └── lamp.c
└── Makefile       # 可选
```

## 编译与运行
使用 gcc：
```bash
gcc -Wall -O2 -o lamp src/lamp.c
./lamp
```
或使用 Makefile：
```bash
make
./lamp
make clean
```

---

> 说明：本 README 只描述 **Step 1 的最小目标**，后续功能（如键盘交互、长按/双击、模式切换等）将按阶段逐步加入，并在 README 中追加新的「Step」小节。
