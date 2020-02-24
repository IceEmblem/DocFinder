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
        std::vector<std::string> getDocTitle(std::string docPath);
    };    
} // namespace DocFind
#endif