#include <vector>
#include <regex>
#include <sstream>
#include "../../HeaderFiles/DocumentReaders/TxtReader.hpp"
#include "../../../Infrastructure/HeaderFiles/FileOperate.hpp"

using namespace Infrastructure;

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
        return FileOperate::getFileText(docPath);
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