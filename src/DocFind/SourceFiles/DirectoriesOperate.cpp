#include <stdio.h>
#include <string.h>
#include <regex>
#include "../HeaderFiles/DirectoriesOperate.hpp"

#ifdef _WIN32
// windows
#include <WINDOWS.H>
namespace DocFind
{
    std::map<std::string, bool> DirectoriesOperate::getFiles(std::string dirPath)
    {
        std::string szPath = dirPath + "/*.*";
        WIN32_FIND_DATA wfd;
        std::map<std::string, bool> files;

        HANDLE hFind = FindFirstFile(szPath.c_str(), &wfd) ;
        do
        {
            if(std::string(wfd.cFileName) == "." || std::string(wfd.cFileName) == ".."){
                continue;
            }
            files[wfd.cFileName] = wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        } while (FindNextFile(hFind, &wfd));
        FindClose(hFind);

        return files;
    }
}
#else
// linux
#include <dirent.h>
namespace DocFind
{
    std::map<std::string, bool> DirectoriesOperate::getFiles(std::string dirPath)
    {
        std::map<std::string, bool> files;

        DIR *pDir = nullptr;
        struct dirent* ptr;
        if(!(pDir = opendir(dirPath.c_str())))
            return files;
        while((ptr = readdir(pDir))!=0) {
            if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
                files[ptr->d_name] = ptr->d_type == DT_DIR;
        }
        closedir(pDir);

        return files;
    }


}
#endif

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace DocFind
{
    bool DirectoriesOperate::isExitDir(std::string dirPath){
        return access(dirPath.c_str(), F_OK) == 0;
    }

    void DirectoriesOperate::createDir(std::string dirPath)
    {
        if(isExitDir(dirPath)){
            return;
        }
        
        #ifdef _WIN32
            // 替换字符串中的 "/" 为 "\"
            int pos;
            pos = dirPath.find("/");
            while(pos != -1){
                dirPath.replace(pos, 1, "\\");
                pos = dirPath.find("/");
            }
        #endif

        std::string command = "mkdir \"" + dirPath + "\"";  
        system(command.c_str());
    }

    std::string DirectoriesOperate::getDirPath(std::string filePath)
    {
        std::string path;
        static std::regex nameRegex("(.*?)(\\\\|/)[^\\\\/]*?$");
        std::smatch sresult;
        if (std::regex_search(filePath, sresult, nameRegex))
        {
            path = sresult.str(1);
        }

        return path;
    }
}


// #ifdef linux
// #endif