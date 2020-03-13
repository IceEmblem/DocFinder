#include <iostream>
#include <string>
#include <regex>
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/CommandContext.hpp"
#include "../../DocFind/HeaderFiles/FileOperate.hpp"

int main(int argc, char * argv[]){
    std::cout << "欢迎使用文档查找器" << std::endl;
    std::cout << "该程序由 IceEmblem 所编写" << std::endl;
    std::cout << "输入 exit 退出程序" << std::endl << std::endl;

    std::string programPath;
    if(argc > 0){
        programPath = DocFind::FileOperate::getFileDirPath(argv[0]);
    }
    else{
        programPath = "./";
    }

    CommandContext::init(programPath);
    CommandManager::RegisterBuiltInCommands();
    CommandManager commandManager;

    while (true)
    {
        std::cout << "> ";
        std::string cmdLine;
        getline(std::cin, cmdLine);

        if(cmdLine == "exit"){
            return 0;
        }

        std::cout << "--------开始执行--------" << std::endl << std::endl;
        std::cout << commandManager.Exec(cmdLine) << std::endl;
        std::cout << std::endl << "--------结束执行--------" << std::endl;
    }

    return 0;
}