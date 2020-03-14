#include <vector>
#include "../../HeaderFiles/DocumentOpeners/TxtOpener.hpp"

namespace DocFind {

    bool TxtOpener::isCanOpen(std::string docPostfix) const{
        static std::vector<std::string> postfixs = {"txt"};
        for(auto posfix : postfixs){
            if(docPostfix == posfix){
                return true;
            }
        }

        return false;
    }

    void TxtOpener::open(std::string docPath, std::string execPath) const{
        std::string cmd = "\"\"" + execPath + "\"" + " " + "\"" + docPath + "\"\"";
        system(cmd.c_str());
    }
}