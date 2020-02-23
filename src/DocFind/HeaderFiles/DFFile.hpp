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
        DFFile(std::string fullPath, bool isDir, std::vector<std::string> keys):fullPath(fullPath), isDir(isDir), keys(keys)
        {
            static std::regex nameRegex("(\\|/)(.*?)$");
            std::smatch sresult;
            if (std::regex_search(fullPath, sresult, nameRegex))
            {
                name = sresult.str(2);
            }
            else
            {
                name = "";
            }
        };

        std::string fullPath;
        std::string name;
        bool isDir;
        std::vector<std::string> keys;
    };
} // namespace DocFind
#endif