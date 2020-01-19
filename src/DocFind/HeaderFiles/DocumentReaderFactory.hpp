#ifndef DocumentReaderFactory_H
#define DocumentReaderFactory_H

#include "./DocumentReader.hpp"
#include "./Document.hpp"

namespace DocFind
{
    class DocumentReaderFactory
    {
    private:
        /* data */
    public:
        DocumentReaderFactory(/* args */);
        ~DocumentReaderFactory();

        DocumentReader getDocumentReader(Document doc);
    };    
} // namespace DocFind
#endif