#include <iostream>
#include <string>
#include "../../DocFind/HeaderFiles/DocFinder.hpp"

int main(){
    std::cout << "欢迎使用文档查找器" << std::endl;
    std::cout << "该程序由 IceEmblem 所编写" << std::endl;

    DocFind::DocFinder docFinder("./");
    auto results = docFinder.find({"test"});
    
    for(auto findResult : results){
        std::cout << findResult.document->name << std::endl;
    }

    return 0;
}