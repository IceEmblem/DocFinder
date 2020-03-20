#ifndef FindCommand_H
#define FindCommand_H

#include <memory>
#include "../../DocFind/HeaderFiles/DocFinder.hpp"
#include "./Command.hpp"

using namespace DocFind;

class FindContextData {
public:
    FindContextData(
        std::shared_ptr<std::vector<FindDocResult>> results, 
        std::shared_ptr<std::vector<std::string>> keys,
        std::shared_ptr<std::string> newKey
    ): results(results), keys(keys), newKey(newKey)
    {
    }

    std::shared_ptr<std::vector<FindDocResult>> results;
    std::shared_ptr<std::vector<std::string>> keys;
    std::shared_ptr<std::string> newKey;
    std::shared_ptr<int> selectIndex;
};

class FindCommand : public Command
{
private:
    std::string _contentKey = "Find";

    // 查找文档
    std::string find(std::string paramStr);

    // 打开获读取文档
    // 返回值：显示文本
    std::string openDoc(std::string paramStr, std::string & nextCmd);

    // 添加关键字到文档
    std::string add(std::string & nextCmd);

public:
    FindCommand(){
        commandNames = { "find", "Find", "f", "F", "fo", "fadd" };
    }

    std::string exec(std::string commandName, std::string paramStr, std::string & nextCmd);
};

#endif