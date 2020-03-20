#ifndef AddCommand_H
#define AddCommand_H

#include "./Command.hpp"

class AddCommand : public Command
{
private:
    /* data */
public:
public:
    AddCommand(){
        commandNames = { "add", "Add" };
    }

    std::string exec(std::string commandName, std::string paramStr, std::string & nextCmd);
};

#endif