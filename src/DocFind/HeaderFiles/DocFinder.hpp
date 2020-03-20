#ifndef DocFinder_H
#define DocFinder_H

#include <string>
#include <vector>
#include <memory>
#include "./Document.hpp"
#include "./DFFile.hpp"
#include "./DocumentManager.hpp"
#include "./DocumentOpenerFactory.hpp"
#include "./DocumentReaderFactory.hpp"

namespace DocFind
{
    class FindDocResult
    {
    public:
        FindDocResult(std::shared_ptr<Document> doc, std::string matchText) : document(doc), matchText(matchText) { }

        std::string matchText;
        std::shared_ptr<Document> document;
    };

    class FindResult {
    public:
        std::vector<FindDocResult> docResults;
        std::string newKey;
    };

    class DocFinder
    {
    private:
        // 当前文档查找路径
        std::string _dirPath;

        std::shared_ptr<DocumentManager> _documentManager;

        std::shared_ptr<DocumentOpenerFactory> _documentOpenerFactory;

        std::shared_ptr<DocumentReaderFactory> _documentReaderFactory;

    public:
        DocFinder(std::string dirPath);

        void addKeyWordToDoc(std::vector<std::string> keys, std::string docRelativePath) const;
        void addKeyWordToDoc(std::vector<std::string> keys, std::shared_ptr<Document> doc) const;

        FindResult find(std::vector<std::string> keys) const;

        OpenResult open(std::shared_ptr<Document> doc) const;

        OpenResult open(std::string relativePath) const;

        void registerExecPath(std::string execName, std::string execPath);
    };

} // namespace DocFind

#endif