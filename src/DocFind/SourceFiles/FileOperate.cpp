#include <fstream>
#include <regex>
#include <cstdlib>
#include <memory>
#include "../HeaderFiles/FileOperate.hpp"

namespace DocFind {
    bool FileOperate::isExistFile(std::string path){
        std::ifstream f(path);
        return f.good();
    }

    // 获取环境路径
    static std::vector<std::string> getEnvPaths(){
        static std::shared_ptr<std::vector<std::string>> envPaths = nullptr;
        if(envPaths == nullptr){
            envPaths = std::make_shared<std::vector<std::string>>();

            std::string envPathString = std::getenv("PATH");
            // 分割符
            std::string separation;
            #ifdef _WIN32
                separation = ";";
            #else
                separation = ":";
            #endif

            
            int pos = 0;
            int index = envPathString.find(separation, pos);
            while (index != envPathString.npos)
            {
                std::string envPath = envPathString.substr(pos, index - pos);
                envPaths->push_back(envPath);
                pos = index + 1;
                index = envPathString.find(separation, pos);
            }
        }

        return *envPaths;
    }

    bool FileOperate::isExistExecFile(std::string path) {
        // 如果路径存在"/"或在"\"，则不在环境路径中
        if(path.find("/") != path.npos || path.find("\\") != path.npos)
        {
            return isExistFile(path);
        }

        auto envPaths = getEnvPaths();
        for(auto envPath : envPaths){
            std::string fullPath;
            // 如果环境路径最后一个字符是"\"或"/"
            if(envPath[envPath.size()-1] == '\\'
            || envPath[envPath.size()-1] == '/'
            )
            {
                fullPath = envPath + path;
            }
            else{
                std::string pathChar;
                #ifdef _WIN32
                    pathChar = "\\";
                #else
                    pathChar = "/";
                #endif
                fullPath = envPath + pathChar + path;
            }

            if(isExistFile(fullPath)){
                return true;
            }
        }

        return false;
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