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

        DocumentOpener* getDocumentOpener(std::string docPostfix) const;
    };    
} // namespace DocFind
#endif