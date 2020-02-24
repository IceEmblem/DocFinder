#ifndef DocumentReaderFactory_H
#define DocumentReaderFactory_H

#include <string>
#include "./DocumentReader.hpp"

namespace DocFind
{
    class DocumentReaderFactory
    {
    private:
        /* data */
    public:
        DocumentReaderFactory(/* args */);
        ~DocumentReaderFactory();

        DocumentReader* getDocumentReader(std::string docPostfix) const;
    };    
} // namespace DocFind
#endif