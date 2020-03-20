#include <vector>
#include <memory>
#include "../HeaderFiles/DocumentManager.hpp"
#include "../HeaderFiles/DocFinder.hpp"
#include "../HeaderFiles/DFFile.hpp"


namespace DocFind
{
    DocFinder::DocFinder(std::string dirPath) 
    {
        _documentManager =  std::make_shared<DocumentManager>(DocumentManager(dirPath));
        
        DocumentOpenerFactory::RegisterBuiltInOpener();
        _documentOpenerFactory = std::make_shared<DocumentOpenerFactory>(DocumentOpenerFactory(dirPath));
    }

    void DocFinder::addKeyWordToDoc(std::vector<std::string> keys, std::string docRelativePath) const {
        for(auto key : keys){
            _documentManager->addKeyWordToDoc(key, docRelativePath);
        }
    }

    // 添加关键字到文档
    void DocFinder::addKeyWordToDoc(std::vector<std::string> keys, std::shared_ptr<Document> doc) const 
    {
        addKeyWordToDoc(keys, doc->relativePath);
    }

    // 根据关键字查找文档
    std::vector<std::pair<std::shared_ptr<Document>, std::string>> getDocForKey(std::vector<std::shared_ptr<Document>> docs, std::string key)
    {
        std::vector<std::pair<std::shared_ptr<Document>, std::string>> results;

        for(auto doc : docs){
            for(auto docKey : doc->keys){
                // docKey 和 key 转小写
                std::string docKeyLower = docKey;
                std::string keyLower = key;
                std::transform(docKey.begin(), docKey.end(), docKeyLower.begin(), ::tolower);
                std::transform(key.begin(), key.end(), keyLower.begin(), ::tolower);
                if(docKeyLower.find(keyLower) != docKeyLower.npos){
                    std::pair<std::shared_ptr<Document>, std::string> p(doc, docKey);
                    results.push_back(p);
                    break;
                }
            }
        }

        return results;
    }

    FindResult DocFinder::find(std::vector<std::string> keys) const
    {
        std::vector<std::shared_ptr<Document>> docs = _documentManager->getDocuments();
        std::vector<std::pair<std::shared_ptr<Document>, std::string>> docAndKeys;
        std::string newKey;
        for(auto key : keys){
            auto newDocAndKeys = getDocForKey(docs, key);

            // 如果查找结果为 0，则放弃该次查找，接着查找下一关键字
            if(newDocAndKeys.size() == 0){
                newKey = key;
                continue;
            }
            
            docs = std::vector<std::shared_ptr<Document>>();
            for(auto docAndKey : newDocAndKeys){
                docs.push_back(docAndKey.first);
            }

            docAndKeys = newDocAndKeys;
        }
        
        std::vector<FindDocResult> results;
        for(auto docAndKey : docAndKeys){
            FindDocResult result(docAndKey.first, docAndKey.second);
            results.push_back(result);
        }

        FindResult findResult;
        findResult.docResults = results;
        findResult.newKey = newKey;

        return findResult;
    }

    OpenResult DocFinder::open(std::shared_ptr<Document> doc) const
    {
        return open(doc->relativePath);
    }

    OpenResult DocFinder::open(std::string relativePath) const
    {
        return _documentOpenerFactory->open(_documentManager->getFullPath(relativePath));
    }

    void DocFinder::registerExecPath(std::string execName, std::string execPath){
        _documentOpenerFactory->registerExecPath(execName, execPath);
    }
} // namespace DocFind