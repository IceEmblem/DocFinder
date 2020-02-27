#include <vector>
#include <memory>
#include <regex>
#include "../HeaderFiles/DocumentManager.hpp"
#include "../HeaderFiles/DocFinder.hpp"
#include "../HeaderFiles/DFFile.hpp"


namespace DocFind
{
    DocFinder::DocFinder(std::string dirPath) 
    {
        _documentManager =  std::make_shared<DocumentManager>(DocumentManager(dirPath));
    }

    // 添加关键字到文档
    void DocFinder::addKeyWordToDoc(std::vector<std::string> keys, Document doc) const 
    {
        for(auto key : keys){
            _documentManager->addKeyWordToDoc(key, doc);
        }
    }

    // 根据关键字查找文档
    std::vector<std::shared_ptr<Document>> getDocForKey(std::vector<std::shared_ptr<Document>> docs, std::string key)
    {
        std::vector<std::shared_ptr<Document>> results;

        for(auto doc : docs){
            for(auto docKey : doc->keys){
                if(docKey.find(key) != docKey.npos){
                    results.push_back(doc);
                }
            }
        }

        return results;
    }

    std::vector<FindResult> DocFinder::find(std::vector<std::string> keys) const
    {
        std::vector<std::shared_ptr<Document>> docs = _documentManager->getDocuments();
        for(auto key : keys){
            docs = getDocForKey(docs, key);
        }
        
        std::vector<FindResult> results;
        for(auto doc : docs){
            FindResult result(*doc, "");
            results.push_back(result);
        }

        return results;
    }

    void DocFinder::open(Document doc) const
    {
        static std::regex postfix("\\.(.+)$");
        std::smatch sresult;
        if (std::regex_search(doc.fullPath, sresult, postfix))
        {
                throw std::logic_error("文档不存在后缀，无法找到合适的程序用于打开文档");
        }

       std::shared_ptr<DocumentOpener> docOpener = _documentOpenerFactory->getDocumentOpener(sresult.str(1));
        if(!docOpener){
            throw std::logic_error("无法找到合适的程序用于打开文档");
        }

        docOpener->open(doc.fullPath);
    }
} // namespace DocFind