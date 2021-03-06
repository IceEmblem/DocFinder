#ifndef DocumentManager_H
#define DocumentManager_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "./Document.hpp"
#include "./Directories.hpp"
#include "./KeyWordToDoc.hpp"
#include "./DocumentReaderFactory.hpp"
#include "./DocumentTitle.hpp"

namespace DocFind
{
    class DocumentManager
    {
    private:
        std::shared_ptr<DocumentReaderFactory> _documentReaderFactory;

        // 当前文档管理器使用的目录路径
        std::string _dirPath;
        std::shared_ptr<Directories> _dir;
        std::shared_ptr<std::vector<KeyWordToDoc>> keyWordToDocs = nullptr;
        std::shared_ptr<std::map<std::string, DocumentTitle>> _documentTitles = nullptr;
        std::shared_ptr<std::vector<std::shared_ptr<Document>>> keyDocument = nullptr;

        // 从文件中读取 KeyWordToDoc
        void readKeyWordToDocFromFile();
        // 将 KeyWordToDoc 写入文件
        void writeKeyWordToDocToFile();
        // 将 KeyWordToDoc 中的关键字添加到 Document 中
        void addKeysToDocObject(std::vector<std::shared_ptr<Document>> &docs);
        // 删除不存在对应文档的KeyWordToDoc
        void deleteKeyWordToDocOfNoExistDoc(std::vector<std::shared_ptr<Document>> &docs);

        // 从文件中读取文档标题
        void readDocTitleFromFile();
        // 将 documentTitles 写入文件
        void writeDocTitleToFile();
        // 读取文档内容，将文档内容的标题作为关键字添加到文档对象中
        void addTitleToDocObject(std::vector<std::shared_ptr<Document>> &docs);
        // 删除不存在对应文档的标题
        void deleteTitleOfNoExitstDoc(std::vector<std::shared_ptr<Document>> &docs);

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