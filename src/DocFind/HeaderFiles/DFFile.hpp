#ifndef DFFile_H
#define DFFile_H

#include <string>
#include <regex>
#include <vector>

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
        DFFile(std::string relativePath, bool isDir, std::vector<std::string> keys):relativePath(relativePath), isDir(isDir), keys(keys)
        {
            fullPath = docFindDirPath + relativePath;
            
            static std::regex nameRegex("(\\\\|/)([^\\\\/]*?)$");
            std::smatch sresult;
            if (std::regex_search(relativePath, sresult, nameRegex))
            {
                name = sresult.str(2);
            }
            else
            {
                name = "";
            }
        };

        std::string fullPath;
        std::string relativePath;
        std::string name;
        bool isDir;
        std::vector<std::string> keys;

        // 当前文档查找目录路径
        static std::string docFindDirPath;
    };
}
#endif