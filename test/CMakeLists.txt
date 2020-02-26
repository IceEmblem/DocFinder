cmake_minimum_required (VERSION 2.8)
project (DocFinderTest)
# 设置工作目录为上层目录
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/..)

# 添加 -pthread 选项
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")

# 指定编译所 include 搜索路径
include_directories("include")

# add_subdirectory("DocFindTest")

# 指定连接库的搜索目录
# link_directories(${PROJECT_SOURCE_DIR}/test/lib)
link_directories(${PROJECT_SOURCE_DIR}/test/GTestLib)

add_executable(test "main.cpp")

# 添加库依赖
target_link_libraries(test gtest gtest_main)
# target_link_libraries(test DocFindTest gtest gtest_main)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/bin)