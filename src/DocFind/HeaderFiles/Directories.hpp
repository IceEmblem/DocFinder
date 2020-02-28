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

                if(childFile.second == true){
                    childs.push_back(std::make_shared<Directories>(Directories(relativePath + "/" + childFile.first, childKeys)));
                }
                else{
                    childs.push_back(std::make_shared<Document>(Document(relativePath + "/" + childFile.first, childKeys)));
                }
            }

            // 对子文件进行排序
            std::sort(childs.begin(), childs.end(), [](std::shared_ptr<DFFile>  left, std::shared_ptr<DFFile>  right){
                return right->relativePath.compare(left->relativePath) > 0 ? true : false;
            });
        }
        
        std::vector<std::shared_ptr<DFFile>> childs;
    };
} // namespace DicFind

#endif