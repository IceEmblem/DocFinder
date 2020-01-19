#ifndef DocFinder_H
#define DocFinder_H

#include <string>
#include <vector>
#include "./Document.hpp"
#include "./DFFile.hpp"
#include "./KeyWordToDocManager.hpp"

namespace DocFind
{
    class FindResult
    {
    public:
        FindResult(Document doc, std::string matchText) : document(doc), matchText(matchText) { }
        ~FindResult();

        std::string matchText;
        Document document;
    };

    class DocFinder
    {
    private:
        // 当前文档查找路径
        DFFile _dir;

        KeyWordToDocManager _keyWordToDocManager;

    public:
        DocFinder(DFFile &dir);
        ~DocFinder() = default;

        void addKeyWordToDoc(std::vector<std::string> keys, Document doc) const;

        FindResult find(std::vector<std::string> keys);

        void open(Document doc);
    };
} // namespace DocFind

#endif