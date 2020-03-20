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
        Document(std::string relativePath, time_t lastModifiedTime, std::vector<std::string> parentKeys):DFFile(relativePath, false, parentKeys), lastModifiedTime(lastModifiedTime)
        {
        }

        time_t lastModifiedTime;
    };    
} // namespace DocFind
#endif