#include <regex>
#include <vector>
#include <memory>
#include "../HeaderFiles/FindCommand.hpp"
#include "../HeaderFiles/CommandManager.hpp"
#include "../HeaderFiles/CommandContext.hpp"

using namespace  DocFind;

// 查找文档
std::string FindCommand::find (std::string paramStr) {
    static std::regex paramRegex ("(\".*?\"|[^ ]+)\\s*");
    std::smatch sresult;

    std::vector<std::string> keys;
    std::string suffixStr = paramStr;
    while (std::regex_search(suffixStr, sresult, paramRegex))
    {
        keys.push_back(sresult.str(1));
        suffixStr = sresult.suffix().str();
    }

    if (keys.size () == 0) {
        return "输入关键字有误，请重新输入";
    }

    auto result = CommandContext::Instances () -> docFinder -> find (keys);
    if (result.docResults.size () == 0) {
        return "未找到匹配的文档";
    }

    std::shared_ptr<FindContextData> findContextData;
    findContextData.reset(new FindContextData(
            std::make_shared<std::vector<FindDocResult>>(result.docResults),
            std::make_shared<std::vector<std::string>>(keys),
            std::make_shared<std::string>(result.newKey)
        )
    );
    
    // 将结果保存到上下文中
    CommandContext::Instances ()-> setData (_contentKey, findContextData);

    std::stringstream outputText;

    outputText << "找到入下文档" << std::endl;
    outputText << "输入\"fo+空格+编号\"打开文档" << std::endl;
    int no = 1;
    for (auto doc : result.docResults) {
        outputText << no << ". " << doc.document -> relativePath << "            -----匹配文本：" << doc.matchText << std::endl;
        no++;
    }

    return outputText.str ();
}

// 打开获读取文档
// 返回值：显示文本
std::string FindCommand::openDoc (std::string paramStr, std::string & nextCmd) {
    int inputNo = 0;
    try {
        inputNo = std::stoi (paramStr);
    } catch (std::exception& ex) {
        return "无效的编号";
    }

    // 从上下文中获取结果
    std::shared_ptr<FindContextData> findContextData = std::static_pointer_cast<FindContextData> (CommandContext::Instances () -> getData (_contentKey));
    if (findContextData == nullptr) {
        return "不存在查找结果，请先进行查找";
    }

    if (inputNo > findContextData->results->size() || inputNo < 1) {
        return "无效的编号";
    }

    int selectIndex = inputNo - 1;
    findContextData->selectIndex = std::make_shared<int>(selectIndex);
    nextCmd = std::string () + "open " + (*findContextData->results)[selectIndex].document -> relativePath;
    
    if(*findContextData->newKey != ""){
        return "具有新关键字：" + *findContextData->newKey + "，输入 fadd 可关联到文档";
    }

    return "";
}

std::string FindCommand::add(std::string & nextCmd){
    // 从上下文中获取结果
    std::shared_ptr<FindContextData> findContextData = std::static_pointer_cast<FindContextData>(CommandContext::Instances () -> getData (_contentKey));

    if(findContextData == nullptr){
        return "不存在查找结果，请先进行查找";
    }

    if(*findContextData->newKey == ""){
        return "不存在新关键字，如法进行添加";
    }

    if(findContextData->selectIndex == nullptr){
        return "找不到要关联的文档，请先执行 fo 命令打开文档";
    }

    auto findDoc = (*findContextData->results)[*findContextData->selectIndex];
    nextCmd = "add \"" + findDoc.document->relativePath + "\" \"" + *findContextData->newKey + "\"";

    return "";
}

std::string FindCommand::exec (std::string commandName, std::string paramStr, std::string & nextCmd) {
    if (commandName == "find" ||
        commandName == "Find" ||
        commandName == "f" ||
        commandName == "F"
    ) 
    {
        return find (paramStr);
    } 
    else if(commandName == "fo") 
    {
        return openDoc(paramStr, nextCmd);
    }
    else
    {
        return add(nextCmd);
    }
};