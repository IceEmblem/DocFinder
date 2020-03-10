#ifndef OpenCommand_H
#define OpenCommand_H

#include "./Command.hpp"

class OpenCommand : public Command
{
private:
public:
    OpenCommand(){
        commandNames = {"Open", "open"};
    }

    std::string exec(std::string command, std::string paramStr, std::string & nextCmd);
};

#endif