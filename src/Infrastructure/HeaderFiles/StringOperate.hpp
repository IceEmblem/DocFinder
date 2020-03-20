#ifndef StringOperate_H
#define StringOperate_H

#include <string>

namespace Infrastructure{
    class StringOperate
    {
    private:
        /* data */
    public:
        static std::string replace(std::string src, std::string findStr, std::string replaceStr);
    };
}

#endif