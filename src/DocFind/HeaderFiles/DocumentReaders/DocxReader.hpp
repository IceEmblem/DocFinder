#ifndef DocxReader_H
#define DocxReader_H

#include "../DocumentReader.hpp"

namespace DocFind
{
    class DocxReader: public DocumentReader
    {
    private:
        /* data */
    public:
        bool isCanReader(std::string docPostfix);
        std::string getDocText(std::string docPath);
        std::vector<std::string> getDocTitle(std::string docPath);
    };
    
} // namespace DocFind

#endif