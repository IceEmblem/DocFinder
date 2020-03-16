#ifndef DocumentReaderFactory_H
#define DocumentReaderFactory_H

#include <string>
#include <memory>
#include "./DocumentReader.hpp"

namespace DocFind
{
    class DocumentReaderFactory
    {
    private:
        static std::vector<std::shared_ptr<DocumentReader>> _docReaders;
    public:
        // 注册 文档读取器
        static void Register(std::shared_ptr<DocumentReader> reader);

        // 注册内置的文档读取器
        static void RegisterBuiltInReader();

        std::shared_ptr<DocumentReader> getDocumentReader(std::string docPostfix) const;
    };    
} // namespace DocFind
#endif