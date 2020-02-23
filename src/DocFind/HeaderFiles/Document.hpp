#ifndef Document_H
#define Document_H

#include <string>
#include <vector>
#include "./DFFile.hpp"

namespace DocFind
{
    class Document : public DFFile
    {
    private:
        /* data */
    public:
        Document(std::string fullPath, std::vector<std::string> parentKeys):DFFile(fullPath, false, parentKeys)
        {
        }
    };    
} // namespace DocFind
#endif