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

    // 移除空格
    ss.get();

    std::string execPath;
    std::getline(ss, execPath);

    if(execPath == ""){
        return "参数输入错误，请输入可执行程序路径";
    }

    CommandContext::Instances()->docFinder->registerExecPath(execName, execPath);
    return "已注册程序路径：" + execPath;
}

std::string RegisterCommand::help(){
    std::stringstream text;
    text << "名称：register" << std::endl;
    text << "描述：注册文档打开程序路径" << std::endl;
    text << "格式：register + 空格 + 打开器名称 + 空格 + 程序路径" << std::endl;
    text << "示例：register WordDoc c:\\wps.exe" << std::endl;

    return text.str();
}