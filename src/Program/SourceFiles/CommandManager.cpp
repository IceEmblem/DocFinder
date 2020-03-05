#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include "../HeaderFiles/CommandManager.hpp"

void CommandManager::Register(std::shared_ptr<Command> command) {
    _commands.push_back(command);
}

std::shared_ptr<Command> CommandManager::GetCommand(std::string commandName){
    for(auto command : _commands){
        if(std::find(
                command->commandNames.begin(), 
                command->commandNames.end(), 
                commandName) 
            != command->commandNames.end()
        ){
            return command;
        }
    }

    // 返回默认命令
    for(auto command : _commands){
        if(command->isDefault){
            return command;
        }
    }

    return nullptr;
}

std::string CommandManager::Exec(std::string cmdLine){
    static std::regex cmdRegex("^([^\\s]*?)\\s(.*?)");
    std::smatch sresult;

    std::string name;
    std::string param;
    if (std::regex_search(cmdLine, sresult, cmdRegex))
    {
        name = sresult.str(1);
        param = sresult.str(2);
    }
    else {
        throw std::logic_error("无效的命令");
    }

    auto command = GetCommand(name);
    std::string nextCmdLine;
    std::string result;

    try{
        result = command->exec(param, nextCmdLine);
    }
    catch(std::exception ex){
        return ex.what();
    }

    if(nextCmdLine == ""){
        return result;
    }

    return Exec(nextCmdLine);
}