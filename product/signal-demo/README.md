# 🛠️ Signal Demo (C)

这是一个最小可用的 **C 语言信号处理实验**，展示如何安全地捕捉 `SIGINT` (Ctrl+C) 并优雅退出。  

---

## ✨ 功能
- 捕捉 `Ctrl+C` (SIGINT)
- 输出提示信息
- 使用 `volatile sig_atomic_t` 标志位保证安全
- 宏 `WRITE_LIT` 简化安全写入

---

## 📂 目录结构
```
product/signal-demo/
 ├── signal.c       # 核心源码
 ├── Makefile       # 构建脚本
 ├── run_demo.sh    # 一键运行脚本
 └── README.md      # 项目说明
```

---

## ⚡ 编译 & 运行

### 方法 1：手动
```bash
make        # 编译
./signal    # 运行
```

### 方法 2：一键运行 🚀
```bash
chmod +x run_demo.sh   # 赋予执行权限（只需一次）
./run_demo.sh
```

---

## 📋 示例输出
```
Running... press Ctrl+C to stop.
tick...
tick...
^C[SIGINT]: signal catched
Exiting cleanly.
```

---

## 🧠 说明
- 信号处理函数应尽量**简单**：只设置标志位或调用安全函数（如 `write`）。
- 不要在信号处理器里调用 `printf` 之类的 **非异步安全**函数。
- 主循环检查标志位后，进行清理并退出。
- 这是 **安全信号处理的基本模式**。

---

## 📜 License
MIT
