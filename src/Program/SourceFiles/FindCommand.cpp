#include <regex>
#include <vector>
#include <iostream>
#include <memory>
#include "../../DocFind/HeaderFiles/DocFinder.hpp"
#include "../HeaderFiles/Command.hpp"
#include "../HeaderFiles/CommandManager.hpp"

using namespace  DocFind;

class FindCommand : public Command {
private:

public:
    bool isDefault = true;
    std::vector<std::string> commandNames = { "find", "Find", "f", "F" };

    std::string exec(std::string paramStr, std::string & nextCmd) {
        std::regex paramRegex("\\w+\\:(?:\\w+|\"[^\"]*\")+?");
        std::smatch sresult;

        std::vector<std::string> keys;

        if (std::regex_search(paramStr, sresult, paramRegex)){
            for(auto key : sresult){
                keys.push_back(key.str());
            }
        }

        if(keys.size() == 0){
            return "输入关键字有误，请重新输入";
        }

        auto results =DocFinder::Instances()->find(keys);
        if(results.size() == 0){
            return "未找到匹配的文档";
        }

        std::cout << "找到入下文档" << std::endl;
        std::cout << "输入\"编号+空格+open\"打开文档，输入\"编号+空格+read\"显示文档，什么多不做则直接回车" << std::endl;
        int no = 1;
        for(auto doc : results){
            std::cout << no << doc.document->relativePath << std::endl;
        }

        int inputNo = 0;
        std::string inputCmd;
        if(!(std::cin >> inputNo) || inputNo > results.size()){
            return "无效的编号，结束查找";
        }
        
        if(!(std::cin >> inputCmd) || (inputCmd != "open" && inputCmd != "read")){
            return "无效的命令，结束查找";
        }

        if(inputCmd == "open"){
            nextCmd = std::string() + "open " + results[inputNo-1].document->relativePath;
        }
        else{
            nextCmd = std::string() + "read " + results[inputNo-1].document->relativePath;
        }

        return "结束查找";
    };
};

CommandManagerRegister(FindCommand);