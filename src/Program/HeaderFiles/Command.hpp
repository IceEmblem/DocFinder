#ifndef Command_H
#define Command_H

#include <vector>
#include <string>

class Command
{
private:
    /* data */
public:
    bool isDefault = false;
    std::vector<std::string> commandNames;

    // 执行命令
    // paramStr 为执行命令的参数
    // nextCmd 为执行完当前命令之后当前exce函数想要要执行的下一条命令，该参数为输出参数，由exec填充
    virtual std::string exec(std::string paramStr, std::string & nextCmd) = 0;
};

#endif