#ifndef DocumentOpener_H
#define DocumentOpener_H

#include <string>

namespace DocFind
{
    class DocumentOpener
    {
    private:

    public:
        virtual std::string getExecName() const = 0;
        virtual bool isCanOpen(std::string docPostfix) const = 0;
        virtual void open(std::string docPath, std::string execPath) const = 0;
    }; 
} // namespace DocFind
#endif