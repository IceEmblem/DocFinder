#ifndef DocumentOpenerFactory_H
#define DocumentOpenerFactory_H

#include <string>
#include "./DocumentOpener.hpp"

namespace DocFind
{
    class DocumentOpenerFactory
    {
    private:
        /* data */
    public:
        DocumentOpenerFactory(/* args */);
        ~DocumentOpenerFactory();

        static void Register(DocumentOpener opener);
        std::shared_ptr<DocumentOpener> getDocumentOpener(std::string docPostfix) const;
    };    
} // namespace DocFind
#endif