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
        Document(std::string relativePath, std::vector<std::string> parentKeys):DFFile(relativePath, false, parentKeys)
        {
        }
    };    
} // namespace DocFind
#endif