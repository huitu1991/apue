# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.8)

# 项目信息
project("apue")

# 全局变量
set(CMAKE_C_STANDARD 99)

# 设置#include搜索的目录
include_directories(lib)

# 添加需要链接的库文件目录
link_directories()

# 添加子目录
add_subdirectory(io)

