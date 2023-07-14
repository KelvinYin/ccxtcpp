cmake_minimum_required(VERSION 3.5)

project(binacpp)

# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libccxtcpp/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libccxtcpp/lib)
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libccxtcpp/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加头文件搜索路径
include_directories(
    /usr/local/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 添加库文件搜索路径
link_directories(
    /usr/local/lib
)

# 添加源文件目录
add_subdirectory(src)
add_subdirectory(example)
