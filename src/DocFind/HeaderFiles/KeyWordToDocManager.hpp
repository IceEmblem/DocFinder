#ifndef KeyWordToDocManager_H
#define KeyWordToDocManager_H

#include "./KeyWordToDoc.hpp"

namespace DocFind
{
    class KeyWordToDocManager
    {
    private:
        /* data */
    public:
        KeyWordToDocManager(/* args */);
        ~KeyWordToDocManager();

        void addKeyWordToDoc(KeyWordToDoc &keyWordToDoc) const;
    };
} // namespace DocFind
#endif