#ifndef TxtReader_H
#define TxtReader_H

#include "../DocumentReader.hpp"

namespace DocFind {
    class TxtReader : public DocumentReader
    {
    private:
        /* data */
    public:
        bool isCanReader(std::string docPostfix);

        std::string getDocText(std::string docPath);
        std::vector<std::string> getDocTitleForText(std::string text);
        std::vector<std::string> getDocTitle(std::string docPath);
    };
}

#endif