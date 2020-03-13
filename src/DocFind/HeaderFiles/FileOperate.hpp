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
    };
}

#endif