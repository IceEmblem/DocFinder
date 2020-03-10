#ifndef DocumentManager_H
#define DocumentManager_H

#include <string>
#include <vector>
#include <memory>
#include "./Document.hpp"
#include "./Directories.hpp"
#include "./DirectoriesOperate.hpp"
#include "./KeyWordToDoc.hpp"

namespace DocFind
{
    class DocumentManager
    {
    private:
        // 当前文档管理器使用的目录路径
        std::string _dirPath;
        std::shared_ptr<Directories> _dir;
        std::shared_ptr<std::vector<KeyWordToDoc>> keyWordToDocs = nullptr;
        std::shared_ptr<std::vector<std::shared_ptr<Document>>> keyDocument = nullptr;

        // 从文件中读取 KeyWordToDoc
        void readKeyWordToDocFromFile(std::string keyWordToDocFilePath);

        // 将 KeyWordToDoc 写入文件
        void writeKeyWordToDocToFile();

        // 将 KeyWordToDoc 中的关键字添加到 Document 中
        void addKeysToDocObject(std::vector<std::shared_ptr<Document>> &docs);

        // 生成目录
        std::shared_ptr<Directories> createDirectories(std::string relativePath, std::vector<std::string> keys);
    public:
        DocumentManager(std::string dirPath);

        // 将关键字关联到文档
        void addKeyWordToDoc(std::string key, std::shared_ptr<Document> doc);
        void addKeyWordToDoc(std::string key, std::string docPath);

        // 获取文档
        std::vector<std::shared_ptr<Document>> getDocuments();

        // 获取文件完整路径
        std::string getFullPath(std::shared_ptr<DFFile> file);
        std::string getFullPath(DFFile* file);
        std::string getFullPath(std::string relativePath);
    };
} // namespace DocFind
#endif