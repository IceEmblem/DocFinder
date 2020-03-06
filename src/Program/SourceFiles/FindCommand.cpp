#include <regex>
#include <vector>
#include <memory>
#include "../HeaderFiles/Command.hpp"
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/CommandContext.hpp"

using namespace  DocFind;

class FindCommand : public Command {
private:
    std::string _contentKey = "Find";
public:
    std::vector<std::string> commandNames = { "find", "Find", "f", "F", "fo", "fr" };

    // 查找文档
    std::string find(std::string paramStr){
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

        auto results =CommandContext::Instances()->docFinder->find(keys);
        if(results.size() == 0){
            return "未找到匹配的文档";
        }

        // 将结果保存到上下文中
        CommandContext::Instances()->setData(_contentKey, std::make_shared<std::vector<FindResult>>(results));

        std::stringstream outputText;

        outputText << "找到入下文档" << std::endl;
        outputText << "输入\"fo+空格+编号\"打开文档，输入\"fr+空格+编号\"显示文档" << std::endl;
        int no = 1;
        for(auto doc : results){
            outputText << no << ". " << doc.document->relativePath << std::endl;
        }

        return outputText.str();
    }

    // 打开获读取文档
    // 返回值：显示文本
    std::string openOrReadDoc(std::string commandName, std::string paramStr, std::string & nextCmd){
        int inputNo = 0;
        try{
            inputNo = std::stoi(paramStr);
        }
        catch(std::exception){
            return "无效的编号";
        }

        // 从上下文中获取结果
        std::shared_ptr<std::vector<FindResult>> results = std::static_pointer_cast<std::vector<FindResult>>(CommandContext::Instances()->getData(_contentKey));
        if(results == nullptr){
            return "不存在查找结果，请先进行查找";
        }

        if(inputNo > results->size() || inputNo < 1) {
            return "无效的编号";
        }

        if(commandName == "fo"){
            nextCmd = std::string() + "open " + (*results)[inputNo-1].document->relativePath;
        }
        else{
            nextCmd = std::string() + "read " + (*results)[inputNo-1].document->relativePath;
        }

        return "";
    }

    std::string exec(std::string commandName, std::string paramStr, std::string & nextCmd) {
        if(commandName == "find"
            || commandName == "Find"
            || commandName == "f"
            || commandName == "F"
        ){
            return find(paramStr);
        }
        else {
            return openOrReadDoc(commandName, paramStr, nextCmd);
        }
    };
};

CommandManagerRegister(FindCommand);