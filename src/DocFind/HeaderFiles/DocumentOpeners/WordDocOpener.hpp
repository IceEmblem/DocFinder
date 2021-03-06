#ifndef WordDocOpener_H
#define WordDocOpener_H

#include "../DocumentOpener.hpp"

namespace DocFind
{
    // word文档打开器
    class WordDocOpener : public DocumentOpener
    {
    private:
        /* data */
    public:
        std::string getExecName() const{
            static std::string execName = "WordDoc";
            return execName;
        }
        bool isCanOpen(std::string docPostfix) const;
        void open(std::string docPath, std::string execPath) const;
    };
}

#endif