cmake_minimum_required (VERSION 2.8)
project (DocFinderTest)
# 设置工作目录为上层目录
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/..)

add_subdirectory("DocFindTest")

# 指定连接库的搜索目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(test "main.cpp")

# 添加库依赖
target_link_libraries(test DocFindTest)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)