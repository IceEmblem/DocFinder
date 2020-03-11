#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "../HeaderFiles/DocumentOpenerFactory.hpp"
#include "../HeaderFiles/DirectoriesOperate.hpp"

namespace DocFind
{
    static std::vector<std::shared_ptr<DocumentOpener>> openers;

    // 可执行程序路径文件相对路径
    static std::string execPathFileRelativePath = "/DocFinder/ExecPath.txt";

    void DocumentOpenerFactory::readExecPathFromFile(){
        std::string execPathFilePath = _currentPath + execPathFileRelativePath;
        std::ifstream file;
        file.open(execPathFilePath);

        // 如果文件不存在，则创建文件
        if(!file){
            file.close();

            std::string path = DirectoriesOperate::getDirPath(execPathFilePath);
            DirectoriesOperate::createDir(path);

            std::ofstream ofile;
            ofile.open(execPathFilePath, std::fstream::out);
            ofile.close();
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream lineStringStram;
            lineStringStram.str(line);

            // 程序名
            std::string execName;
            lineStringStram >> execName;

            std::string execPath;
            lineStringStram >> execPath;

            _execPaths[execName] = execPath;
        }

        file.close();
    }

    void DocumentOpenerFactory::writeFileFromExecPath(){
        std::string execPathFilePath = _currentPath + execPathFileRelativePath;
        std::ofstream file;
        file.open(execPathFilePath);

        for(auto execPath:_execPaths){
            file << execPath.first << " " << execPath.second << std::endl;
        }
    }

    DocumentOpenerFactory::DocumentOpenerFactory(std::string current):_currentPath(current){
        readExecPathFromFile();
    }

    template<typename TDocumentOpener>
    void DocumentOpenerFactory::Register(TDocumentOpener* opener){
        openers.push_back(std::make_shared<DocumentOpener>(*opener));
    }

    void DocumentOpenerFactory::registerExecPath(std::string execName, std::string execPath){
        _execPaths[execName] = execPath;
        writeFileFromExecPath();
    }

    std::shared_ptr<DocumentOpener> DocumentOpenerFactory::getDocumentOpener(std::string docPostfix) const{
        for(auto opener : openers){
            if(opener->isCanOpen(docPostfix)){
                return opener;
            }
        }

        return nullptr;
    }

    OpenResult DocumentOpenerFactory::open(std::string execPath){
        static std::regex postfix("\\.(.+)$");
        std::smatch sresult;
        if (std::regex_search(execPath, sresult, postfix))
        {
            throw std::logic_error("文档不存在后缀，无法找到合适的程序用于打开文档");
        }

        std::shared_ptr<DocumentOpener> docOpener = getDocumentOpener(sresult.str(1));
        if(!docOpener){
            throw std::logic_error("无法找到合适的程序用于打开文档");
        }

        std::string execPath = _execPaths[docOpener->getExecName()];
        if(execPath == ""){
            return OpenResult(OpenResultEnum::unregisteredExecPath, docOpener->getExecName());
        }

        docOpener->open(execPath, execPath);
        return OpenResult(OpenResultEnum::success, docOpener->getExecName());
    }
} // namespace DocFind
