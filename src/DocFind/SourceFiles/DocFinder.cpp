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
        _documentOpenerFactory = std::make_shared<DocumentOpenerFactory>(DocumentOpenerFactory(dirPath));
    }

    // 添加关键字到文档
    void DocFinder::addKeyWordToDoc(std::vector<std::string> keys, std::shared_ptr<Document> doc) const 
    {
        for(auto key : keys){
            _documentManager->addKeyWordToDoc(key, doc->relativePath);
        }
    }

    // 根据关键字查找文档
    std::vector<std::shared_ptr<Document>> getDocForKey(std::vector<std::shared_ptr<Document>> docs, std::string key)
    {
        std::vector<std::shared_ptr<Document>> results;

        for(auto doc : docs){
            for(auto docKey : doc->keys){
                // docKey 和 key 转小写
                std::string docKeyLower = docKey;
                std::string keyLower = key;
                std::transform(docKey.begin(), docKey.end(), docKeyLower.begin(), ::tolower);
                std::transform(key.begin(), key.end(), keyLower.begin(), ::tolower);
                if(docKeyLower.find(keyLower) != docKeyLower.npos){
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
            FindResult result(doc, "");
            results.push_back(result);
        }

        return results;
    }

    void DocFinder::open(std::shared_ptr<Document> doc) const
    {
        open(doc->relativePath);
    }

    void DocFinder::open(std::string relativePath) const
    {
        _documentOpenerFactory->open(_documentManager->getFullPath(relativePath));
    }

    void DocFinder::registerExecPath(std::string execName, std::string execPath){
        _documentOpenerFactory->registerExecPath(execName, execPath);
    }
} // namespace DocFind