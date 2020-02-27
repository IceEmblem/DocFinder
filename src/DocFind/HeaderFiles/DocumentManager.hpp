#ifndef DocumentManager_H
#define DocumentManager_H

#include <string>
#include <vector>
#include <memory>
#include "./Document.hpp"
#include "./Directories.hpp"
#include "./KeyWordToDoc.hpp"

namespace DocFind
{
    class DocumentManager
    {
    private:
        std::shared_ptr<Directories> _dir;
        std::shared_ptr<std::vector<KeyWordToDoc>> keyWordToDocs = nullptr;
        std::shared_ptr<std::vector<std::shared_ptr<Document>>> keyDocument = nullptr;

        // 从文件中读取 KeyWordToDoc
        void readKeyWordToDocFromFile(std::string keyWordToDocFilePath);
        
        // 将 KeyWordToDoc 写入文件
        void writeKeyWordToDocToFile();

        // 将 KeyWordToDoc 中的关键字添加到 Document 中
        void addKeysToDocObject(std::vector<std::shared_ptr<Document>> &docs);
    public:
        DocumentManager(std::string dirPath);

        // 将关键字关联到文档
        void addKeyWordToDoc(std::string key, Document doc);

        // 获取文档
        std::vector<std::shared_ptr<Document>> getDocuments();
    };
} // namespace DocFind
#endif