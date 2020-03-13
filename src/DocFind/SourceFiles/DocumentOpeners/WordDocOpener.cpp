#include <vector>
#include "../../HeaderFiles/DocumentOpeners/WordDocOpener.hpp"

namespace DocFind {
    static std::vector<std::string> wordPostfixs = {"doc", "docx"};
    bool WordDocOpener::isCanOpen(std::string docPostfix) const{
        for(auto wordPostfix : wordPostfixs){
            if(wordPostfix == docPostfix){
                return true;
            }
        }

        return false;
    }

    void WordDocOpener::open(std::string docPath, std::string execPath) const{
        std::string cmd = "\"" + execPath + "\"" + " " + "\"" + docPath + "\"";
        system(cmd.c_str());
    }
}