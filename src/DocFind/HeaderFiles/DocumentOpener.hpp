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

        void open(std::string docPath);
    }; 
} // namespace DocFind
#endif