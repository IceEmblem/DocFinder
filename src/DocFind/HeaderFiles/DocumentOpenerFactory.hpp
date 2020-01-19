#ifndef DocumentOpenerFactory_H
#define DocumentOpenerFactory_H

#include "./DocumentOpener.hpp"
#include "./Document.hpp"

namespace DocFind
{
    class DocumentOpenerFactory
    {
    private:
        /* data */
    public:
        DocumentOpenerFactory(/* args */);
        ~DocumentOpenerFactory();

        DocumentOpener getDocumentOpener(Document doc);
    };    
} // namespace DocFind
#endif