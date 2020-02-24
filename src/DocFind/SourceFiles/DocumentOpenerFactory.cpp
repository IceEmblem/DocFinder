#include <memory>
#include <vector>
#include "../HeaderFiles/DocumentOpenerFactory.hpp"

namespace DocFind
{
    class DocumentOpenerFactory
    {
    private:
        static std::vector<std::shared_ptr<DocumentOpener>> openers;
    public:
        DocumentOpenerFactory(/* args */);
        ~DocumentOpenerFactory();

        static void Register(DocumentOpener opener){
            openers.push_back(std::make_shared<DocumentOpener>(opener));
        }

        std::shared_ptr<DocumentOpener> getDocumentOpener(std::string docPostfix) const{
            for(auto opener : openers){
                if(opener->isCanOpen(docPostfix)){
                    return opener;
                }
            }

            return nullptr;
        }
    };
} // namespace DocFind
