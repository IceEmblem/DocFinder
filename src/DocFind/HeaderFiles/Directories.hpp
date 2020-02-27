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
        Directories(std::string relativePath, std::vector<std::string> keys):DFFile(relativePath, true, keys)
        {
            auto childFiles = DirectoriesOperate::getFiles(fullPath);

            for(auto childFile : childFiles){
                std::vector<std::string> childKeys = keys;
                childKeys.push_back(childFile.first);

                std::shared_ptr<DFFile> childPtr = childFile.second == true ?
                    std::make_shared<DFFile>(Directories(relativePath + "/" + childFile.first, childKeys)):
                    std::make_shared<DFFile>(Document(relativePath + "/" + childFile.first, childKeys));
                    
                childs.push_back(childPtr);
            }

            // 对子文件进行排序
            std::sort(childs.begin(), childs.end(), [](std::shared_ptr<DFFile>  left, std::shared_ptr<DFFile>  right){
                return left->relativePath.compare(right->relativePath);
            });
        }
        
        std::vector<std::shared_ptr<DFFile>> childs;
    };
} // namespace DicFind

#endif