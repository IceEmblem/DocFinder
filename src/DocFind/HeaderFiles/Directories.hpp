#ifndef Directories_H
#define Directories_H

#include <vector>
#include "./DFFile.hpp"

namespace DocFind
{
    class Directories
    {
    private:
        /* data */
    public:
        Directories(/* args */);
        ~Directories();
        
        std::vector<DFFile> childs;
    };
} // namespace DicFind

#endif