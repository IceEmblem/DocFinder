#include <fstream>
#include "../HeaderFiles/FileOperate.hpp"

namespace DocFind {
    bool FileOperate::isExistFile(std::string path){
        std::ifstream f(path);
        return f.good();
    }

    void FileOperate::createFile(std::string path){
        std::ofstream file;
        file.open(path, std::fstream::out);
        file.close();
    }
}