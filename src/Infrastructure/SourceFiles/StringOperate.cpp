#include "../HeaderFiles/StringOperate.hpp"

namespace Infrastructure{
    std::string StringOperate::replace(std::string src, std::string findStr, std::string replaceStr){
        int pos;
        pos = src.find(findStr);
        while(pos != -1){
            src.replace(pos, findStr.size(), replaceStr);
            pos = src.find(findStr);
        }

        return src;
    }
}