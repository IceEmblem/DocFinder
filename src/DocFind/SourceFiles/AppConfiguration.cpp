#include "../HeaderFiles/AppConfiguration.hpp"

namespace DocFind
{
    std::string AppConfiguration::DataFileDirPath = "/DocFinder";
    std::string AppConfiguration::DocumentTitlesPath = DataFileDirPath + "/DocumentTitles.txt";
    std::string AppConfiguration::ExecPath = DataFileDirPath + "/ExecPath.txt";
    std::string AppConfiguration::KeyWordToDocsPath = DataFileDirPath + "/KeyWordToDocs.txt";
} // namespace DocFind
