#include "../HeaderFiles/PathOperate.hpp"
#include "../HeaderFiles/StringOperate.hpp"

namespace Infrastructure{
    std::string PathOperate::convertToWindowPath(std::string path){
        // 替换字符串中的 "/" 为 "\"
        return StringOperate::replace(path, "/", "\\");
    }

    std::string PathOperate::convertToLinuxPath(std::string path){
        // 替换字符串中的 "\" 为 "/"
        return StringOperate::replace(path, "\\", "/");
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