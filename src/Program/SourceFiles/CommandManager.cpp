#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/FindCommand.hpp"
#include "../HeaderFiles/OpenCommand.hpp"
#include "../HeaderFiles/RegisterCommand.hpp"

// 初始化私有静态变量
std::vector<std::shared_ptr<Command>> CommandManager::_commands = std::vector<std::shared_ptr<Command>>();

void CommandManager::Register(std::shared_ptr<Command> command) {
    _commands.push_back(command);
}

void CommandManager::RegisterBuiltInCommands(){
    static bool isRegistered = false;
    if(isRegistered == true){
        return;
    }

    Register(std::make_shared<FindCommand>());
    Register(std::make_shared<OpenCommand>());
    Register(std::make_shared<RegisterCommand>());

    isRegistered = true;
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

    return nullptr;
}

std::string CommandManager::Exec(std::string cmdLine){
    static std::regex cmdRegex("^([^\\s]*)(\\s(.*))?");
    std::smatch sresult;

    std::string name;
    std::string param;
    if (std::regex_search(cmdLine, sresult, cmdRegex))
    {
        name = sresult.str(1);
        param = sresult.str(3);
    }
    else {
        return "无效的命令行";
    }

    auto command = GetCommand(name);
    if(command == nullptr){
        return std::string("不存在命令命令 ") + name;
    }
    std::string nextCmdLine;
    std::string result;

    try{
        result = command->exec(name, param, nextCmdLine);
    }
    catch(std::exception ex){
        return ex.what();
    }

    if(nextCmdLine == ""){
        return result;
    }

    return Exec(nextCmdLine);
}