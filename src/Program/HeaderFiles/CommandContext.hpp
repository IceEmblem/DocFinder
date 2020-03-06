#ifndef CommandContext_H
#define CommandContext_H

#include <map>
#include <string>
#include <memory>
#include "../../DocFind/HeaderFiles/DocFinder.hpp"

class CommandContext
{
private:
    std::map<std::string, std::shared_ptr<void>> _datas;

    CommandContext() = default;
public:
    static void init(std::string dirPath);
    static std::shared_ptr<CommandContext> Instances();

    std::shared_ptr<DocFind::DocFinder> docFinder = nullptr;

    std::shared_ptr<void> getData(std::string key);

    void setData(std::string key, std::shared_ptr<void> data);
};

#endif