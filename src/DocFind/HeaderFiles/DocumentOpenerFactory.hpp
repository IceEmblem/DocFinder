#ifndef DocumentOpenerFactory_H
#define DocumentOpenerFactory_H

#include <string>
#include <map>
#include "./DocumentOpener.hpp"

namespace DocFind
{
    class DocumentOpenerFactory
    {
    private:
        // 当前程序的执行目录
        std::string _currentPath;
        // 可执行程序路径列表
        std::map<std::string, std::string> _execPaths;

        // 从文件中读取可执行程序路径
        void readExecPathFromFile();
        // 将可执行程序路径写入文件
        void writeFileFromExecPath();
    public:
        DocumentOpenerFactory(std::string current);
        // 注册 文档打开器，TDocumentOpener必须继承DocumentOpener
        template<typename TDocumentOpener>

        // 注册打开器
        static void Register(TDocumentOpener* opener);
        
        // 注册可执行程序路径
        void registerExecPath(std::string execName, std::string execPath);

        // 获取 文档打开器
        std::shared_ptr<DocumentOpener> getDocumentOpener(std::string docPostfix) const;

        void open(std::string execPath);
    };    
} // namespace DocFind
#endif