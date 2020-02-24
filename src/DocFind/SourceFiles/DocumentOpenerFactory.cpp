#include <memory>
#include <vector>
#include "../HeaderFiles/DocumentOpenerFactory.hpp"

namespace DocFind
{
    static std::vector<std::shared_ptr<DocumentOpener>> openers;

    template<typename TDocumentOpener>
    void DocumentOpenerFactory::Register(TDocumentOpener* opener){
            openers.push_back(std::make_shared<DocumentOpener>(*opener));
    }

    std::shared_ptr<DocumentOpener> DocumentOpenerFactory::getDocumentOpener(std::string docPostfix) const{
        for(auto opener : openers){
            if(opener->isCanOpen(docPostfix)){
                return opener;
            }
        }

        return nullptr;
    }
} // namespace DocFind
