# Signal Demo (C)

这是一个最小的 C 语言信号处理实验，用来演示如何**安全地捕获 Ctrl+C (SIGINT)** 并优雅退出。

## 特性
- 捕获 `SIGINT` (Ctrl+C)
- 使用 `volatile sig_atomic_t` 标志与主循环通信
- 在信号处理函数中仅使用 `write()`（async-signal-safe）
- 提供宏 `WRITE_LIT`，自动计算字符串长度，避免 `strlen()`

## 编译与运行
```bash
make          # 编译
make run      # 运行
make clean    # 清理
```

或者手动编译：
```bash
gcc -Wall -O2 -o signal signal.c
./signal
```

## 示例输出
```
Running... press Ctrl+C to stop.
tick...
tick...
tick...
^C[SIGINT]: signal catched
Exiting cleanly.
```
## 🚀 一键运行

本项目提供了一个简单脚本 `run_demo.sh`，可以一键编译并运行：

```bash
chmod +x run_demo.sh   # 赋予执行权限（只需一次）
./run_demo.sh

## 说明
- 信号处理函数应尽量简单，仅设置标志位或调用 async-signal-safe 函数。
- 清理和退出逻辑交由主循环完成。
- 本 demo 展示了 **安全信号处理的基本模式**。
o
