#include "../HeaderFiles/CommandContext.hpp"

static std::shared_ptr<CommandContext> commandContext = nullptr;

void CommandContext::init(std::string dirPath){
    commandContext = std::make_shared<CommandContext>(CommandContext());
    commandContext->docFinder = std::make_shared<DocFind::DocFinder>(DocFind::DocFinder(dirPath));
}

std::shared_ptr<CommandContext> CommandContext::Instances(){
    return commandContext;
}

std::shared_ptr<void> CommandContext::getData(std::string key){
    return _datas[key];
}

void CommandContext::setData(std::string key, std::shared_ptr<void> data){
    _datas[key] = data;
}