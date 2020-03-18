#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
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

        std::stringstream ss;
        ss.str(text);

        std::string preLine;
        std::string line;
        while (std::getline(ss, line))
        {
            if(preLine == "" && line != "" && line.size() < 30){
                titles.push_back(line);
            }

            preLine = line;
        }

        return titles;
    }

    std::vector<std::string> TxtReader::getDocTitle(std::string docPath){
        return getDocTitleForText(getDocText(docPath));
    }
}