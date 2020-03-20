#include <regex>
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