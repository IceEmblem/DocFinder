#include "../HeaderFiles/CommandContext.hpp"

std::shared_ptr<CommandContext> CommandContext::Instances(){
    static std::shared_ptr<CommandContext> commandContext = nullptr;

    if(commandContext == nullptr){
        commandContext = std::make_shared<CommandContext>(CommandContext());
    }

    return commandContext;
}

std::shared_ptr<void> CommandContext::getData(std::string key){
    return _datas[key];
}

void CommandContext::setData(std::string key, std::shared_ptr<void> data){
    _datas[key] = data;
}