#include <fstream>
#include <regex>
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

    std::string FileOperate::getFileName(std::string path){
        static std::regex nameRegex("(\\\\|/)([^\\\\/]*?)$");
        std::smatch sresult;
        if (!std::regex_search(path, sresult, nameRegex))
        {
            throw std::logic_error("无效的文件路径");
        }
        
        return sresult.str(2);
    }

    std::string FileOperate::getFileDirPath(std::string path){
        static std::regex pathRegex("^(.*?)(\\\\|/)([^\\\\/]*?)$");
        std::smatch result;

        std::string arg = std::string(path);
        if(!std::regex_search(arg, result, pathRegex)){
            throw std::logic_error("无效的文件路径");
        }

        return result.str(1);
    }

    std::string FileOperate::getPostfix(std::string path){
        static std::regex postfix("\\.([^\\.]+)$");
        std::smatch sresult;
        if (!std::regex_search(path, sresult, postfix))
        {
            return "";
        }

        return sresult.str(1);
    }
}