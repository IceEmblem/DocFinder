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
    class FindResult
    {
    public:
        FindResult(std::shared_ptr<Document> doc, std::string matchText) : document(doc), matchText(matchText) { }

        std::string matchText;
        std::shared_ptr<Document> document;
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

        void addKeyWordToDoc(std::vector<std::string> keys, std::shared_ptr<Document> doc) const;

        std::vector<FindResult> find(std::vector<std::string> keys) const;

        void open(std::shared_ptr<Document> doc) const;
    };
} // namespace DocFind

#endif