# 📝 函数指针：typedef vs 不用 typedef

## 1. 不用 typedef
    #include <stdio.h>

    void hello(void) { printf("Hello\n"); }

    int main() {
        void (*fp)(void);  // 定义函数指针变量
        fp = hello;        // 赋值
        fp();              // 调用函数
        return 0;
    }

---

## 2. 用 typedef 简化
    #include <stdio.h>

    typedef void (*action_t)(void);  // 给函数指针起别名

    void hello(void) { printf("Hello\n"); }

    int main() {
        action_t fp = hello;  // 用别名
        fp();                 // 调用函数
        return 0;
    }

---

## 3. 在数组和参数中的差别

### 数组
    // 不用 typedef
    void (*actions[2])(void) = { f1, f2 };

    // 用 typedef
    action_t actions[2] = { f1, f2 };

### 函数参数
    // 不用 typedef
    void run(void (*fp)(void)) {
        fp();
    }

    // 用 typedef
    void run(action_t fp) {
        fp();
    }

---

## ✅ 总结
- 两种写法功能完全相同。  
- 区别在于可读性和维护性。  
- **心法**：  
  - 单次使用可不用 typedef。  
  - 如果涉及数组、参数、返回值 → 强烈建议 typedef。
