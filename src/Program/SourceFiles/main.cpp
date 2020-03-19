#include <iostream>
#include <string>
#include <regex>
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/CommandContext.hpp"
#include "../../Infrastructure/HeaderFiles/FileOperate.hpp"
#include "../../Infrastructure/HeaderFiles/EncodedTransform.hpp"

using namespace Infrastructure;

int main(int argc, char * argv[]){
    std::cout << EncodedTransform::UT8ToSystemEncoded("欢迎使用文档查找器") << std::endl;
    std::cout << EncodedTransform::UT8ToSystemEncoded("该程序由 IceEmblem 所编写") << std::endl;
    std::cout << EncodedTransform::UT8ToSystemEncoded("输入 exit 退出程序") << std::endl << std::endl;

    std::string programPath;
    if(argc > 0){
        programPath = FileOperate::getFileDirPath(argv[0]);
        programPath = EncodedTransform::SystemEncodedToUT8(programPath);
    }
    else{
        programPath = "./";
    }

    CommandContext::init(programPath);
    CommandManager::RegisterBuiltInCommands();
    CommandManager commandManager;

    while (true)
    {
        std::cout << EncodedTransform::UT8ToSystemEncoded("> ");
        std::string cmdLine;
        getline(std::cin, cmdLine);
        cmdLine = EncodedTransform::SystemEncodedToUT8(cmdLine);

        if(cmdLine == "exit"){
            return 0;
        }

        std::cout << EncodedTransform::UT8ToSystemEncoded("--------开始执行--------") << std::endl << std::endl;
        std::cout << EncodedTransform::UT8ToSystemEncoded(commandManager.Exec(cmdLine)) << std::endl;
        std::cout << std::endl << EncodedTransform::UT8ToSystemEncoded("--------结束执行--------") << std::endl;
    }

    return 0;
}