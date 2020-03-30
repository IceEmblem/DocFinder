#include <sstream>
#include "../HeaderFiles/OpenCommand.hpp"
#include "../HeaderFiles/CommandContext.hpp"

static std::string commandContextDataKey = "open";

std::string OpenCommand::open(std::string paramStr){
    auto result = CommandContext::Instances()->docFinder->open(paramStr);
    if(result.result == DocFind::OpenResultEnum::success){
        return "";
    }

    if(result.result == DocFind::OpenResultEnum::unregisteredExecPath){
        std::stringstream output;
        output << "无法打开文档：" << paramStr << "，请注册打开该类型文档的程序路径" << std::endl;
        output << "输入 rgt+空格+\"+程序路径+\" 注册该程序路径" << std::endl;

        // 将程序名保存到命令上下文中
        CommandContext::Instances()->setData(commandContextDataKey, std::make_shared<std::string>(result.execName));

        return output.str();
    }

    if(result.result == DocFind::OpenResultEnum::nonExistOpener){
        return "暂不支持打开该类型文档";
    }

    return "";
}

std::string OpenCommand::rgt(std::string paramStr, std::string & nextCmd){
    auto execName = std::static_pointer_cast<std::string>(CommandContext::Instances()->getData(commandContextDataKey));
    nextCmd = "register " + *execName + " " + paramStr;
    return "";
}

std::string OpenCommand::exec(std::string command, std::string paramStr, std::string & nextCmd){
    if(command == "open" || command == "Open"){
        return open(paramStr);
    }
    else{
        return rgt(paramStr, nextCmd);
    }
}

std::string OpenCommand::help(){
    std::stringstream text;
    text << "名称：open" << std::endl;
    text << "描述：打开文档" << std::endl;
    text << "格式：open + 空格 + 文档相对路径" << std::endl;
    text << "示例：open /text.txt" << std::endl;

    return text.str();
}