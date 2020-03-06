cmake_minimum_required (VERSION 2.8)
project (DocFinder)

# 设置可执行文件和库文件的输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory("src/DocFind")
add_subdirectory("src/Program")
add_subdirectory(test)