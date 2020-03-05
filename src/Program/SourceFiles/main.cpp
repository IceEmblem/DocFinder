#include <iostream>
#include <string>
#include "../HeaderFiles/CommandManager.hpp"

int main(){
    std::cout << "欢迎使用文档查找器" << std::endl;
    std::cout << "该程序由 IceEmblem 所编写" << std::endl;
    std::cout << "输入 exit 退出程序" << std::endl;

    CommandManager commandManager;

    while (true)
    {
        std::string cmdLine;
        getline(std::cin, cmdLine);

        if(cmdLine == "exit"){
            return 0;
        }

        std::cout << commandManager.Exec(cmdLine) << std::endl;
    }

    return 0;
}