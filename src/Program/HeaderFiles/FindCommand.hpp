#ifndef FindCommand_H
#define FindCommand_H

#include "./Command.hpp"

class FindCommand : public Command
{
private:
    std::string _contentKey = "Find";

    // 查找文档
    std::string find(std::string paramStr);

    // 打开获读取文档
    // 返回值：显示文本
    std::string openOrReadDoc(std::string commandName, std::string paramStr, std::string & nextCmd);

public:
    std::vector<std::string> commandNames = { "find", "Find", "f", "F", "fo", "fr" };

    std::string exec(std::string commandName, std::string paramStr, std::string & nextCmd);
};

#endif