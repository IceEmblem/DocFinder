cmake_minimum_required (VERSION 2.8)
project (DocFinder)

# 设置可执行文件和库文件的输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 如果是 window 系统，代码中的字符串使用 gbk 编码（中文所使用的编码）
# 原谅我，非中文版的 window 系统，将不能使用该软件，要怪就怪这sb的cmd
if(${WIN32})
    set(CMAKE_CXX_FLAGS "-std=c++11 -fexec-charset=GBK")
endif(${WIN32})

add_subdirectory("src/DuckX")
add_subdirectory("src/Infrastructure")
add_subdirectory("src/DocFind")
add_subdirectory("src/Program")
# 只有在 linux 下才生成测试项目
if(${UNIX})
    add_subdirectory(test)
endif(${UNIX})