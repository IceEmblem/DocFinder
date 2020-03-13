#ifndef FileOperate_H
#define FileOperate_H

#include <string>
#include <fstream>

namespace DocFind {
    class FileOperate
    {
    private:
        /* data */
    public:
        // 判断文件是否存在
        static bool isExistFile(std::string path);

        // 创建文件
        static void createFile(std::string path);

        // 从文件路径中获取文件名
        static std::string getFileName(std::string path);

        // 从文件路径中获取目录路径
        static std::string getFileDirPath(std::string path);

        // 从文件路径中获取文件后缀
        static std::string getPostfix(std::string path);
    };
}

#endif