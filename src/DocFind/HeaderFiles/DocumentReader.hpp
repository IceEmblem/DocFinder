#ifndef DocumentReader_H
#define DocumentReader_H

#include <vector>
#include <string>
#include "./Document.hpp"

namespace DocFind
{
    class DocumentReader
    {
    private:
    public:
        virtual bool isCanReader(std::string docPostfix) = 0;
        virtual std::vector<std::string> getDocTitle(std::string docPath) = 0;
    };    
} // namespace DocFind
#endif