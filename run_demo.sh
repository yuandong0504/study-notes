#!/bin/bash
# Simple script to build and run the signal demo

set -e  # 出错立即退出

# 编译
echo "[build] Compiling signal.c ..."
make

# 提示
echo "[run] Starting demo. Press Ctrl+C to trigger SIGINT handler."

# 运行
./signal
