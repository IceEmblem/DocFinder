#ifndef TxtOpener_H
#define TxtOpener_H

#include "../DocumentOpener.hpp"

namespace DocFind {
    class TxtOpener : public DocumentOpener
    {
    private:
        /* data */
    public:
        std::string getExecName() const{
            static std::string execName = "Txt";
            return execName;
        }
        bool isCanOpen(std::string docPostfix) const;
        void open(std::string docPath, std::string execPath) const;
    };
    
}

#endif