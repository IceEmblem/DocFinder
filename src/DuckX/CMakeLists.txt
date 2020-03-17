# 获取目录下的源文件
aux_source_directory(./src srcFiles)

add_library(DuckX ${srcFiles})