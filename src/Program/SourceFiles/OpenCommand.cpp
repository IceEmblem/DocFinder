#include "../HeaderFiles/OpenCommand.hpp"
#include "../HeaderFiles/CommandContext.hpp"

std::string OpenCommand::exec(std::string command, std::string paramStr, std::string & nextCmd){
    CommandContext::Instances()->docFinder->open(paramStr);
}