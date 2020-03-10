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
# 指定连接库的搜索目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 添加一个可执行程序
add_executable(main ${srcFiles})
# 添加库依赖
target_link_libraries(main DocFind)

# 只有在 linux 下才生成测试项目
if(${UNIX})
    # 为了单元测试main需要生成一个库文件
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/lib)
    add_library(ProgramTestLib ${srcFiles})
    target_link_libraries(ProgramTestLib DocFind)
endif(${UNIX})
