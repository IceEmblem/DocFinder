#ifndef KeyWordToDoc_H
#define KeyWordToDoc_H

#include <string>
#include <vector>
#include "./Document.hpp"

namespace DocFind
{
    class KeyWordToDoc
    {
    private:
        /* data */
    public:
        KeyWordToDoc(std::string fullPath, std::vector<std::string> keys): fullPath(fullPath), keys(keys) { }

        std::string fullPath;
        std::vector<std::string> keys;
    };    
} // namespace DocFind
#endif