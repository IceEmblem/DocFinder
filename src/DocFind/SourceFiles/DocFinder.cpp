#include <vector>
#include "../HeaderFiles/DocFinder.hpp"
#include "../HeaderFiles/DFFile.hpp"

namespace DocFind
{
    DocFinder::DocFinder(DFFile &dir): _dir(dir) { 
        _keyWordToDocManager = KeyWordToDocManager();
    }

    void DocFinder::addKeyWordToDoc(std::vector<std::string> keys, Document doc) const 
    {
        for(auto key : keys){
            KeyWordToDoc keyWordToDoc(key, doc);
            _keyWordToDocManager.addKeyWordToDoc(keyWordToDoc);
        }
    }
} // namespace DocFind