#include <stdio.h>
#include <string.h>
#include "../HeaderFiles/DirectoriesOperate.hpp"

#ifdef WIN32
// windows
#include <WINDOWS.H>
namespace DocFind
{
    std::map<std::string, bool> DirectoriesOperate::getFiles(std::string dirPath)
    {
        string szPath = dirPath + "/*.*";
        WIN32_FIND_DATA wfd;
        std::map<std::string, bool> files;

        HANDLE hFind = FindFirstFile(szPath.c_str(), &wfd) ;
        do
        {
            files[wfd.cFileName] = false;
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

        DIR *pDir;
        struct dirent* ptr;
        if(!(pDir = opendir(dirPath.c_str())))
            return;
        while((ptr = readdir(pDir))!=0) {
            if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
                files[ptr->d_name] = ptr->d_type == DT_DIR;
        }
        closedir(pDir);

        return files;
    }
}
#endif

// #ifdef linux
// #endif