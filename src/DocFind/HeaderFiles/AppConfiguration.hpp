#ifndef AppConfiguration_H
#define AppConfiguration_H

#include <string>

namespace DocFind
{
    class AppConfiguration
    {
    private:
        /* data */
    public:
        // 保存程序所需文件的相对目录
        static std::string DataFileDirPath;
        static std::string getDataFileDirPath(std::string currentDir){ return currentDir + DataFileDirPath; }

        // 保存文档标题文件的相对路径
        static std::string DocumentTitlesPath;
        static std::string getDocumentTitlesPath(std::string currentDir){ return currentDir + DocumentTitlesPath; }

        // 保存 可执行文件路径 文件的相对路径
        static std::string ExecPath;
        static std::string getExecPath(std::string currentDir){ return currentDir + ExecPath; }

        // 保存关键字文件的相对路径
        static std::string KeyWordToDocsPath;
        static std::string getKeyWordToDocsPath(std::string currentDir){ return currentDir + KeyWordToDocsPath; }
    };
} // namespace DocFind


#endif