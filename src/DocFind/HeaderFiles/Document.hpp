#ifndef Document_H
#define Document_H

#include <string>
#include "./DFFile.hpp"

namespace DocFind
{
    class Document : DFFile
    {
    private:
        /* data */
    public:
        Document(/* args */);
        ~Document();
    };    
} // namespace DocFind
#endif