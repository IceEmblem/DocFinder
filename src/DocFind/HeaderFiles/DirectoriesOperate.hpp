#ifndef DirectoriesOperate_H
#define DirectoriesOperate_H

#include <map>
#include <string>
namespace DocFind
{
    class DirectoriesOperate
    {
    private:
    public:
        // 获取目录下的文件和目录
        // 返回值：string为文件名称，bool 为 true 表示目录，否则为文件
        static std::map<std::string, bool> getFiles(std::string dirPath);

        static bool createDir(std::string dirPath);

        static std::string getDirPath(std::string filePath);
    };
} // namespace DocFind

#endif