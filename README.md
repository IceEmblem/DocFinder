# DocFinder
文档查找程序

### 为什么做这个程序？
统计了一下，我所记录的文档数已经有2000多个了，每次要查找一个答案，我都要来回翻文档，因为文档太多，我也记不清要查看哪个文档，所以我需要这么一个程序帮助我查找文档<br>
<br>

### 如何查找
查看文档的关键字是否包含输入的关键字，如果包含，则将文档筛选出来<br>
示例，打开程序，执行如下命令：<br>
> find git 创建分支<br>
<br>

### 文档的关键字有哪些
1. 路径：如路径 /Dir1/Dir2/File.txt，那么 File.txt 的关键字有 Dir1，Dir2，File.txt<br>
2. 文档标题：对于 txt 文件，其根据 某一行小于15个中文字符 且 该行上一行是空行，则该行为标题，对于 docx 文件，某一行小于15个中文字符 且 为粗体<br>
3. 在查找过程中添加的关键字：如果输入的关键字不是完全匹配到文档，则在打开文档时，程序会询问你是否将关键字关联到文档<br>
<br>

### 平台与IDE
目前对可以运行在 Windows 与 Linux 上，IDE 使用 VSCode <br>
<br>

### 环境
使用 CMake 进行 MakeFile 文件生成 <br>
Linux 请安装：CMake + g++编译器 <br>
Windows 请安装：CMake + mingw64编译器，并将其 bin 目录下的 mingw32-make.exe 拷贝一份命名为 make.exe <br>
<br>

### 使用源代码
测试项目：使用 gtest <br>
Docx 文档读取：使用 DuckX，github 地址：https://github.com/amiremohamadi/DuckX <br>
<br>

### 技术使用
使用c++，原因是跨平台，当然，更重要的是我要学c++<br>
<br>
