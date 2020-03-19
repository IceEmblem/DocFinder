#include <stdio.h>
#include <string.h>
#include <regex>
#include "../HeaderFiles/DirectoriesOperate.hpp"
#include "../HeaderFiles/EncodedTransform.hpp"

#ifdef _WIN32
// windows
#include <WINDOWS.H>
namespace Infrastructure
{
    std::map<std::string, bool> DirectoriesOperate::getFiles(std::string dirPath)
    {
        std::string szPath = dirPath + "/*.*";
        WIN32_FIND_DATA wfd;
        std::map<std::string, bool> files;

        szPath = EncodedTransform::UT8ToSystemEncoded(szPath);
        HANDLE hFind = FindFirstFile(szPath.c_str(), &wfd) ;
        do
        {
            std::string fileName = std::string(wfd.cFileName);
            fileName = EncodedTransform::SystemEncodedToUT8(fileName);
            if(fileName == "." || fileName == ".."){
                continue;
            }
            files[fileName] = wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        } while (FindNextFile(hFind, &wfd));
        FindClose(hFind);

        return files;
    }
}
#else
// linux
#include <dirent.h>
namespace Infrastructure
{
    std::map<std::string, bool> DirectoriesOperate::getFiles(std::string dirPath)
    {
        std::map<std::string, bool> files;

        DIR *pDir = nullptr;
        struct dirent* ptr;

        dirPath = EncodedTransform::UT8ToSystemEncoded(dirPath);
        if(!(pDir = opendir(dirPath.c_str())))
            return files;
        
        while((ptr = readdir(pDir))!=0) {
            std::string fileName = ptr->d_name;
            fileName = EncodedTransform::SystemEncodedToUT8(fileName);
            if (strcmp(fileName.c_str(), ".") != 0 && strcmp(fileName.c_str(), "..") != 0)
                files[fileName.c_str()] = ptr->d_type == DT_DIR;
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

namespace Infrastructure
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
        system(EncodedTransform::UT8ToSystemEncoded(command).c_str());
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