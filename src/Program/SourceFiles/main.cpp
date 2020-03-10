#include <iostream>
#include <string>
#include <regex>
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/CommandContext.hpp"

int main(int argc, char * argv[]){
    // 设置控制台的编码为 utf-8
    system("chcp 65001");
    std::cout << "欢迎使用文档查找器" << std::endl;
    std::cout << "该程序由 IceEmblem 所编写" << std::endl;
    std::cout << "输入 exit 退出程序" << std::endl;

    std::string programPath;
    if(argc > 0){
        static std::regex pathRegex("^(.*?)(\\\\|/)([^\\\\/]*?)$");
        std::smatch result;

        std::string arg = std::string(argv[0]);
        if(!std::regex_search(arg, result, pathRegex)){
            std::cout << "错误：无法找到程序路径" << std::endl;
            return -1;
        }

        programPath = result.str(1);
    }
    else{
        programPath = "./";
    }

    CommandContext::init(programPath);
    CommandManager::RegisterBuiltInCommands();
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