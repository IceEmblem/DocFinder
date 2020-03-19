#include <vector>
#include "../../HeaderFiles/DocumentOpeners/TxtOpener.hpp"
#include "../../../Infrastructure/HeaderFiles/EncodedTransform.hpp"

using namespace Infrastructure;

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
        system(EncodedTransform::UT8ToSystemEncoded(createCommandCmd(docPath, execPath)).c_str());
    }
}