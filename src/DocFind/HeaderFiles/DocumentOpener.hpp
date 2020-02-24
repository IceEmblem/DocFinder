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
        DocumentOpener(/* args */);
        ~DocumentOpener();

        bool isCanOpen(std::string docPostfix) const;
        void open(std::string docPath) const;
    }; 
} // namespace DocFind
#endif