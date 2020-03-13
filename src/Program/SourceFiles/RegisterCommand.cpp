#include <sstream>
#include "../HeaderFiles/RegisterCommand.hpp"
#include "../HeaderFiles/CommandContext.hpp"

std::string RegisterCommand::exec(std::string command, std::string paramStr, std::string & nextCmd){
    std::stringstream ss;
    ss.str(paramStr);

    std::string execName;
    ss >> execName;
    if(execName == ""){
        return "参数输入错误，请输入可执行程序名";
    }

    std::string execPath;
    ss >> execPath;

    if(execPath == ""){
        return "参数输入错误，请输入可执行程序路径";
    }

    CommandContext::Instances()->docFinder->registerExecPath(execName, execPath);
    return "以注册程序路径：" + execPath;
}