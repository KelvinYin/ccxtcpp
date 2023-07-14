# 添加头文件
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

# 添加库文件搜索路径
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(example_ext example.cpp)
target_link_libraries(example_ext binacpp_dynamic)

add_executable(example_fut example_fut.cpp)
target_link_libraries(example_fut binacpp_dynamic)
