#ifndef RegisterCommand_H
#define RegisterCommand_H

#include "./Command.hpp"

class RegisterCommand : public Command
{
private:
    /* data */
public:
    RegisterCommand(){
        commandNames = {"Register", "register"};
    }

    std::string exec(std::string command, std::string paramStr, std::string & nextCmd);
};

#endif