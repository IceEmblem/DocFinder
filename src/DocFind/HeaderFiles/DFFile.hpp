#ifndef DFFile_H
#define DFFile_H

#include <string>

namespace DocFind
{
    // 文件
    // 抽象类，不允许直接实例
    class DFFile
    {
    private:
        /* data */
    protected:

    public:
        std::string name;
        bool isDir;
        DFFile *parent;

        std::string getCurrentFullPath();
    };
} // namespace DocFind
#endif