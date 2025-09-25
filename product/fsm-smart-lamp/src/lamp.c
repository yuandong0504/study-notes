#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifdef _WIN32
  #include <conio.h>
  static void raw_init(void)  {}
  static void raw_restore(void) {}
  static int  get_key(void)   { return _getch(); }   // 立即返回、无回显
#else
  #include <termios.h>
  #include <unistd.h>

  static struct termios g_old;

  static void raw_init(void) {
      tcgetattr(STDIN_FILENO, &g_old);
      struct termios t = g_old;
      t.c_lflag &= ~(ICANON | ECHO); // 关行缓冲 + 回显
      t.c_cc[VMIN]  = 1;             // 至少读1字节才返回
      t.c_cc[VTIME] = 0;             // 不超时
      tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }

  static void raw_restore(void) {
      tcsetattr(STDIN_FILENO, TCSANOW, &g_old);
  }

  static int get_key(void) {
      return getchar(); // raw 模式下立即得到一个字节
  }
#endif

/* 行为函数 */
static void act_on (void){ printf("lamp is on\n");  }
static void act_off(void){ printf("lamp is off\n"); }
static void act_dim(void){ printf("lamp is dim\n"); }

/* 事件与状态 */
typedef enum { E_SPACE, E_QUIT, E_ENTER, E_NONE, E_N } event_t;
typedef enum { OFF, DIM, ON, S_N } State;
typedef void (*action_t)(void);

/* 安全的事件读取：统一使用 get_key() */
static event_t read_event(void){
    int ch = get_key();
    if (ch == ' ')             return E_SPACE;
    if (ch == 'q' || ch == 'Q')return E_QUIT;
    if (ch == '\n' || ch == '\r') return E_ENTER;
    return E_NONE;
}

/* 状态展示 */
static void show_state(State s){
    const char *name = (s==OFF) ? "OFF" : (s==DIM) ? "DIM" : "ON";
    printf("[state]: %s\n", name);
}

/* 用信号标志位通知主循环退出 */
static volatile sig_atomic_t g_should_quit = 0;

static void handle_signal(int sig){
    (void)sig;               // 未使用参数
    g_should_quit = 1;       // 只做“设旗帜”的最小动作
    /* 注意：不要在这里调用 printf/scanf/tcsetattr/exit 等非异步安全函数 */
}

static void install_signal_handlers(void){
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;         // 想让被中断的 syscalls 自动重启可用 SA_RESTART
    sigaction(SIGINT,  &sa, NULL);  // Ctrl+C
    sigaction(SIGTERM, &sa, NULL);  // kill
    sigaction(SIGSEGV, &sa, NULL);  // 段错误（仅做收尾提示用，更推荐直接修bug）
}

int main(void){
    raw_init();
    atexit(raw_restore);   // 程序正常退出时恢复终端

    install_signal_handlers();

    State s = OFF;
    action_t actions[S_N] = { act_off, act_dim, act_on };
    State next[S_N]       = { DIM,    ON,     OFF    };

    printf("press SPACE to TOGGLE, ENTER to show state, q to quit:\n");
    fflush(stdout);

    while (1){
        if (g_should_quit) {
            printf("\n[signal] quitting gracefully...\n");
            break;
        }

        event_t ev = read_event();
        if (ev == E_QUIT) break;
        if (ev == E_NONE) continue;

        if (ev == E_SPACE){
            s = next[s];
            actions[s]();
        } else if (ev == E_ENTER){
            show_state(s);
        }
        fflush(stdout);
    }
    return 0;   // 触发 atexit → raw_restore()
}
