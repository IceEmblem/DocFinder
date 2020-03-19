#include <vector>
#include "../../HeaderFiles/DocumentOpeners/WordDocOpener.hpp"
#include "../../../Infrastructure/HeaderFiles/EncodedTransform.hpp"

using namespace Infrastructure;

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
        system(EncodedTransform::UT8ToSystemEncoded(createCommandCmd(docPath, execPath)).c_str());
    }
}