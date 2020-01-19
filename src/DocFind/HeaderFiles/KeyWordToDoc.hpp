#ifndef KeyWordToDoc_H
#define KeyWordToDoc_H

#include <string>
#include "./Document.hpp"

namespace DocFind
{
    class KeyWordToDoc
    {
    private:
        /* data */
    public:
        KeyWordToDoc(std::string key, Document doc): key(key), doc(doc) { }

        std::string key;
        Document doc;
    };    
} // namespace DocFind
#endif