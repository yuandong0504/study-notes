# 状态机 v1.0

一个最小可用（MVP）的 **台灯状态机** Demo：  
- 状态：`OFF → DIM → ON → OFF …`  
- 事件：空格切换、回车查看状态、`q` 退出、`Ctrl+C` 优雅退出  
- 亮点：**函数指针数组** 驱动动作、**状态转移表** 解耦逻辑、**信号处理** 保证终端恢复

---

## 目录结构

```
.
├─ lamp.c           # 主程序
├─ README.md        # 你正在看的文档
└─ Makefile         # 可选：一键编译（见下文“可选 Makefile”）
```

---

## 功能概览

- **空格**：切换状态（OFF → DIM → ON → …）  
- **Enter**：打印当前状态名  
- **q**：退出  
- **Ctrl+C**：触发 SIGINT，**优雅退出**（通过信号标志位 + atexit 恢复终端）

示例输出：
```
press SPACE to TOGGLE, ENTER to show state, q to quit:
lamp is dim
lamp is on
[state]: ON
lamp is off
^C
[signal] quitting gracefully...
```

> 备注：`^C` 是终端显示的 Ctrl+C

---

## 设计要点

### 1) 有限状态机（FSM）
- `enum State { OFF, DIM, ON }`  
- `actions[]`：状态 → 行为函数指针  
- `next[]`：状态 → 下一个状态  
- 状态行为与状态迁移 **表驱动**，解耦清晰、易扩展

### 2) 事件驱动
- `read_event()` 将键盘输入转换为 `event_t`（`E_SPACE/E_ENTER/E_QUIT/E_NONE`）  
- 主循环只关心事件，不依赖具体 I/O 细节（提高可移植性）

### 3) 终端原始模式
- Linux/macOS 使用 `termios` 进入 **raw 模式**（无回显、无行缓冲）  
- 退出时通过 `atexit(raw_restore)` 恢复终端

### 4) 信号处理（更稳）
- 使用 `sigaction` 安装 handler  
- **只在 handler 里设全局标志位**：`volatile sig_atomic_t g_should_quit`  
- 回到主循环检测后再做恢复与退出（避免在 handler 里调用非异步安全函数）

---

## 构建与运行

### Linux / macOS
```bash
cc -Wall -O2 -o lamp lamp.c
./lamp
```

### Windows（可用 MinGW 或 MSVC）
- `#ifdef _WIN32` 分支使用 `_getch()`，无需 termios  
- MinGW：
  ```bash
  gcc -O2 -o lamp.exe lamp.c
  lamp.exe
  ```
- MSVC（在 Developer Command Prompt）：
  ```bat
  cl /O2 lamp.c
  lamp.exe
  ```

---

## 可选 Makefile

把下面内容存为 `Makefile`，在同目录执行 `make`/`make run`：

```make
CC      := cc
CFLAGS  := -Wall -O2

all: lamp

lamp: lamp.c
	$(CC) $(CFLAGS) -o $@ $<

run: lamp
	./lamp

clean:
	rm -f lamp
```

---

## 扩展路线图（v1.1+）

- **状态扩展**：`BLINK`, `ERROR`，把状态名改为数组映射：
  ```c
  static const char* kStateName[] = { "OFF", "DIM", "ON" };
  ```
- **定时事件**：`alarm(3)` + `SIGALRM`，实现每 N 秒自动切换  
- **更稳的 I/O**：用 `read()` 代替 `getchar()`（练习 async-signal-safe）  
- **日志与 UX**：加入日志文件、状态高亮/清屏、错误提示  
- **学习主线衔接**：  
  - 系统调用更多练习：`read/write/fork/exec`  
  - 进入 eBPF 阶段：把“事件→hook→动作”模型迁移到内核侧

---

## 常见问题（FAQ）

**Q: Ctrl+C 后终端乱了？**  
A: 正常流程会触发 `atexit(raw_restore)` 恢复；若程序被 `kill -9` 或系统断电，重启终端或系统即可回默认模式。

**Q: 为什么信号处理函数里不直接 `printf/exit/tcsetattr`？**  
A: 这些不是 *async-signal-safe*，在 handler 里调用存在风险。推荐只“设标志位”，回主循环做收尾。

**Q: Windows 下能跑吗？**  
A: 能。Windows 分支用 `_getch()` 实现“立即返回、无回显”的按键输入。

---

## 许可证

MIT License — Copyright (c) 2025
