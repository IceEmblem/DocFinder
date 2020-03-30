#ifndef CommandManager_H
#define CommandManager_H

#include <memory>
#include <string>
#include <vector>
#include "./Command.hpp"

class CommandManager
{
private:
    static std::vector<std::shared_ptr<Command>> _commands;
public:
    // 注册命令
    static void Register(std::shared_ptr<Command> command);
    // 注册内置命令，查找器的命令的注册写在这里
    static void RegisterBuiltInCommands();
    
    // 执行命令
    std::string Exec(std::string cmdLine);

    // 获取帮助文档
    std::string help();

    // 获取命令
    std::shared_ptr<Command> GetCommand(std::string commandName);
};

// template<typename T>
// class CommandManagerRegisterAction
// {
// public:
//     CommandManagerRegisterAction(T* (*registerActionLambda)())
//     {
//         std::shared_ptr<Command> command;
//         command.reset(registerActionLambda());
//         CommandManager::Register(command);
//     }
// };

// #define CommandManagerRegister(CLASS_NAME) \
// CommandManagerRegisterAction<CLASS_NAME> g_register_action_##CLASS_NAME([]()\
// {\
//     return new CLASS_NAME(); \
// });

#endif