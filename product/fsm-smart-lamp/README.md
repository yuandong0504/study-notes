# FSM Smart Lamp

> 阶段 1 · 最小版 README

## 设计目标（Step 1）
- 台灯“开/关”切换；**每次切换打印一条日志**。

示例日志（仅示意）：
```
OFF -> ON  | 开灯
ON  -> OFF | 关灯
```

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
