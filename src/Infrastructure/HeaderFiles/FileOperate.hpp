#ifndef FileOperate_H
#define FileOperate_H

#include <string>
#include <fstream>

namespace Infrastructure {
    class FileOperate
    {
    private:
        /* data */
    public:
        // 判断文件是否存在
        static bool isExistFile(std::string path);

        // 是否存在可执行文件（会查找环境路径）
        static bool isExistExecFile(std::string path);

        // 创建文件
        static void createFile(std::string path);

        // 读取文件
        static std::string getFileText(std::string path);

        // 写入文件
        static void writeFileText(std::string path, std::string text);

        // 获取文件最后修改时间
        static time_t getModifiedTime(std::string path);

        // 从文件路径中获取文件名
        static std::string getFileName(std::string path);

        // 从文件路径中获取目录路径
        static std::string getFileDirPath(std::string path);

        // 从文件路径中获取文件后缀
        static std::string getPostfix(std::string path);
    };
}

#endif