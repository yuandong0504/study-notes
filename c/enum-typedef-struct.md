# enum / typedef / struct 踩坑总结

## enum
- 一开始觉得就是一堆从 0 自增的 int 常量，没啥特别。
- 用 `enum State { OFF=0, ON=1 };` 时，每次定义变量还要写 `enum State s;`，觉得啰嗦。
- 后来发现 `typedef enum { OFF=0, ON=1 } State;` 可以直接写 `State s = OFF;`，省掉前面的 `enum`。
- 这个隐藏很深，不问一下会一直困扰。

## typedef
- 完全没用过，陌生。
- 看到 `typedef void (*action_t)(void);` 这种写法很绕。
- 一开始不知道为啥要这样搞，觉得直接声明也能用。
- 后来才明白：就是起别名，简化复杂声明，特别是函数指针。

## struct
- 和 enum 一样，没搞懂的时候一头雾水。
- 觉得为什么有时候要写 `struct Person p;`，有时候可以直接 `Person p;`。
- 后来才明白：如果用 `typedef struct { ... } Person;`，以后声明就不用再加 `struct`。

## 总结
- 踩坑点主要有三个：
  1. enum 默认要写 `enum` 前缀，直到理解 typedef 简化。
  2. typedef 用在函数指针上很绕，没用过时会卡很久。
  3. struct 和 enum 一样，typedef 后才好用。
- 这几个点跨度比较大，第一次接触时前所未有地宕机了这么久。
