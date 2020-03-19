#ifndef PathOperate_H
#define PathOperate_H

#include <string>

namespace Infrastructure{
    class PathOperate
    {
    private:
        /* data */
    public:
        static std::string convertToWindowPath(std::string path);
        static std::string convertToLinuxPath(std::string path);
        static std::string pathConvertHandle(std::string path);
    };
}

#endif