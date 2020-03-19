#include "../HeaderFiles/PathOperate.hpp"

namespace Infrastructure{
    std::string PathOperate::convertToWindowPath(std::string path){
        // 替换字符串中的 "/" 为 "\"
        int pos;
        pos = path.find("/");
        while(pos != -1){
            path.replace(pos, 1, "\\");
            pos = path.find("/");
        }

        return path;
    }

    std::string PathOperate::convertToLinuxPath(std::string path){
        // 替换字符串中的 "\" 为 "/"
        int pos;
        pos = path.find("\\");
        while(pos != -1){
            path.replace(pos, 1, "/");
            pos = path.find("\\");
        }

        return path;
    }

    // 路径转换处理
    std::string PathOperate::pathConvertHandle(std::string path){
        #ifdef _WIN32
            return convertToWindowPath(path);
        #else
            return convertToLinuxPath(path);
        #endif
    }
}