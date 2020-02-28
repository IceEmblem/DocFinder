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
add_library(DocFind ${srcFiles})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)