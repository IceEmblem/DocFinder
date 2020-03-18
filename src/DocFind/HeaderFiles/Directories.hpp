#ifndef Directories_H
#define Directories_H

#include <vector>
#include <string>
#include <memory>
#include "./DFFile.hpp"
#include "./Document.hpp"
#include "./DirectoriesOperate.hpp"

namespace DocFind
{
    class Directories : public DFFile
    {
    private:
        /* data */
    public:
        Directories(std::string relativePath, time_t lastModifiedTime,  std::vector<std::string> keys, std::vector<std::shared_ptr<DFFile>> childs):DFFile(relativePath, true, lastModifiedTime, keys), childs(childs)
        {
        }
        
        std::vector<std::shared_ptr<DFFile>> childs;
    };
} // namespace DicFind

#endif