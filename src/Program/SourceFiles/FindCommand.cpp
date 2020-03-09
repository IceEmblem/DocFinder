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

    auto results = CommandContext::Instances () -> docFinder -> find (keys);
    if (results.size () == 0) {
        return "未找到匹配的文档";
    }

    // 将结果保存到上下文中
    CommandContext::Instances () -> setData (_contentKey, std::make_shared<std::vector<FindResult>> (results));

    std::stringstream outputText;

    outputText << "找到入下文档" << std::endl;
    outputText << "输入\"fo+空格+编号\"打开文档，输入\"fr+空格+编号\"显示文档" << std::endl;
    int no = 1;
    for (auto doc : results) {
        outputText << no << ". " << doc.document -> relativePath << std::endl;
    }

    return outputText.str ();
}

// 打开获读取文档
// 返回值：显示文本
std::string FindCommand::openOrReadDoc (std::string commandName, std::string paramStr, std::string & nextCmd) {
    int inputNo = 0;
    try {
        inputNo = std::stoi (paramStr);
    } catch (std::exception) {
        return "无效的编号";
    }

    // 从上下文中获取结果
    std::shared_ptr<std::vector<FindResult>> results = std::static_pointer_cast<std::vector<FindResult>> (CommandContext::Instances () -> getData (_contentKey));
    if (results == nullptr) {
        return "不存在查找结果，请先进行查找";
    }

    if (inputNo > results -> size () || inputNo < 1) {
        return "无效的编号";
    }

    if (commandName == "fo") {
        nextCmd = std::string () + "open " + ( * results) [inputNo - 1].document -> relativePath;
    } else {
        nextCmd = std::string () + "read " + ( * results) [inputNo - 1].document -> relativePath;
    }

    return "";
}

std::string FindCommand::exec (std::string commandName, std::string paramStr, std::string & nextCmd) {
    if (commandName == "find" ||
        commandName == "Find" ||
        commandName == "f" ||
        commandName == "F"
    ) {
        return find (paramStr);
    } else {
        return openOrReadDoc (commandName, paramStr, nextCmd);
    }
};

CommandManagerRegister(FindCommand);