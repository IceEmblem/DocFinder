# 要编译的源文件
set(srcFiles )
macro(getSrcFiles dir)
    # 获取目录下的源文件
    aux_source_directory(${dir} curSrcFiles)
    # 将源文件添加到列表中
    set(srcFiles ${srcFiles} ${curSrcFiles})
    unset(curSrcFiles)

    # 遍历子目录
    file(GLOB childFiles ${dir}/*)
    foreach(f ${childFiles})
        if(IS_DIRECTORY ${f})
            string(REPLACE ${CMAKE_CURRENT_LIST_DIR}/ "" newf ${f})
            getSrcFiles(${newf})
        endif()
    endforeach()
endmacro()

getSrcFiles("./SourceFiles")

# 添加 -pthread 选项
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread ${CMAKE_CXX_FLAGS}")

# 指定编译所 include 搜索路径
include_directories("include")

# 指定连接库的搜索目录
link_directories(${PROJECT_SOURCE_DIR}/test/lib)
link_directories(${PROJECT_SOURCE_DIR}/test/GTestLib)

add_executable(test "main.cpp" ${srcFiles})

# 添加库依赖
target_link_libraries(test gtest gtest_main ProgramTestLib DocFind)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/bin)