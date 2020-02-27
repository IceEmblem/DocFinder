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
        KeyWordToDoc(std::string relativePath, std::vector<std::string> keys): relativePath(relativePath), keys(keys) { }

        std::string relativePath;
        std::vector<std::string> keys;
    };    
} // namespace DocFind
#endif