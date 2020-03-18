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
        DFFile(
            std::string relativePath, 
            bool isDir, 
            time_t lastModifiedTime, 
            std::vector<std::string> keys):
            relativePath(relativePath), 
            isDir(isDir), 
            lastModifiedTime(lastModifiedTime),
            keys(keys)
        {
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

        std::string relativePath;
        std::string name;
        bool isDir;
        time_t lastModifiedTime;
        std::vector<std::string> keys;
    };
}
#endif