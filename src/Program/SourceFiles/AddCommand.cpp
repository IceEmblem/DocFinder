#include <regex>
#include <sstream>
#include "../HeaderFiles/AddCommand.hpp"
#include "../../Infrastructure/HeaderFiles/StringOperate.hpp"
#include "../HeaderFiles/CommandContext.hpp"

using namespace Infrastructure;

std::string AddCommand::exec(std::string commandName, std::string paramStr, std::string & nextCmd){
    static std::regex paramRegex("^(\".*?\"|[^\\s]*?)\\s+(\".*?\"|[^\\s]*)$");
    std::smatch smatchResult;
    if(!std::regex_search(paramStr, smatchResult, paramRegex)){
        return "无效的命令格式";
    }

    std::string path = StringOperate::replace(smatchResult.str(1), "\"", "");
    std::string key = StringOperate::replace(smatchResult.str(2), "\"", "");

    CommandContext::Instances()->docFinder->addKeyWordToDoc({key}, path);
    return "";
}

std::string AddCommand::help(){
    std::stringstream text;
    text << "名称：add" << std::endl;
    text << "描述：添加关键字到文档" << std::endl;
    text << "格式：add + 空格 + 文档相对路径 + 【空格 + 关键字】n" << std::endl;
    text << "示例：add /File.txt key1 key2" << std::endl;

    return text.str();
}