#include <vector>
#include <regex>
#include <fstream>
#include "../../HeaderFiles/DocumentReaders/TxtReader.hpp"

namespace DocFind{
    bool TxtReader::isCanReader(std::string docPostfix){
        static std::vector<std::string> postfixs = { "txt" };

        for(auto postfix : postfixs){
            if(postfix == docPostfix){
                return true;
            }
        }

        return false;
    }

    std::string TxtReader::getDocText(std::string docPath){
        std::ifstream file;
        file.open(docPath);
        if(!file){
            throw std::logic_error("无法打开文档：" + docPath);
        }

        // 读取文件
        file.seekg(0, std::ios::end);
        int len = file.tellg();
        char *buffer = new char[len];
        file.seekg(0,std::ios::beg);
        file.read(buffer,len);
        file.close();

        return buffer;
    }

    std::vector<std::string> TxtReader::getDocTitleForText(std::string text)
    {
        std::vector<std::string> titles;

        // 文本开始
        static std::regex startRegex("^(([a-zA-Z]+|.){1,15})(\r?\n)");
        std::smatch startMatch;
        std::string suffixStr = text;
        if(std::regex_search(suffixStr, startMatch, startRegex)){
            titles.push_back(startMatch.str(1));
            // 获取未匹配的文本
            suffixStr = startMatch.suffix().str();
        }


        // 匹配 换行符+换行符+小于10的字符串+换行符
        static std::regex titleRegex("(\r?\n){2}(([a-zA-Z]+|.){1,15})(\r?\n)");
        std::smatch titleMatch;

        while (std::regex_search(suffixStr, titleMatch, titleRegex))
        {
            titles.push_back(titleMatch.str(2));
            suffixStr = titleMatch.suffix().str();
        }

        return titles;
    }

    std::vector<std::string> TxtReader::getDocTitle(std::string docPath){
        return getDocTitleForText(getDocText(docPath));
    }
}