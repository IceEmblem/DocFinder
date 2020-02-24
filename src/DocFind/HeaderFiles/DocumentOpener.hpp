#ifndef DocumentOpener_H
#define DocumentOpener_H

#include <string>

namespace DocFind
{
    class DocumentOpener
    {
    private:
        /* data */
    public:
        virtual bool isCanOpen(std::string docPostfix) const = 0;
        virtual void open(std::string docPath) const = 0;
    }; 
} // namespace DocFind
#endif