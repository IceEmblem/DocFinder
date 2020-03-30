#ifndef OpenCommand_H
#define OpenCommand_H

#include "./Command.hpp"

class OpenCommand : public Command
{
private:
    std::string open(std::string paramStr);

    std::string rgt(std::string paramStr, std::string & nextCmd);
public:
    OpenCommand(){
        commandNames = {"Open", "open", "rgt"};
    }

    std::string exec(std::string command, std::string paramStr, std::string & nextCmd);
    std::string help();
};

#endif