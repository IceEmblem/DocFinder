#include <memory>
#include <vector>
#include <sstream>
#include <regex>
#include "../HeaderFiles/DocumentOpenerFactory.hpp"
#include "../HeaderFiles/DocumentOpeners/WordDocOpener.hpp"
#include "../HeaderFiles/DocumentOpeners/TxtOpener.hpp"
#include "../HeaderFiles/AppConfiguration.hpp"
#include "../../Infrastructure/HeaderFiles/FileOperate.hpp"
#include "../../Infrastructure/HeaderFiles/DirectoriesOperate.hpp"

using namespace Infrastructure;

namespace DocFind
{
    static std::vector<std::shared_ptr<DocumentOpener>> openers;

    void DocumentOpenerFactory::readExecPathFromFile(){
        // 如果文件不存在，则创建文件
        if(!FileOperate::isExistFile(AppConfiguration::getExecPath(_currentPath))){
            std::string path = DirectoriesOperate::getDirPath(AppConfiguration::getExecPath(_currentPath));
            DirectoriesOperate::createDir(path);

            FileOperate::createFile(AppConfiguration::getExecPath(_currentPath));
            return;
        }

        std::string text = FileOperate::getFileText(AppConfiguration::getExecPath(_currentPath));
        std::stringstream file(text);
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream lineStringStram;
            lineStringStram.str(line);

            // 程序名
            std::string execName;
            lineStringStram >> execName;
            // 移除空格
            lineStringStram.get();

            std::string execPath;
            std::getline(lineStringStram, execPath);

            _execPaths[execName].push_back(ExecPath(execPath, FileOperate::isExistExecFile(execPath)));
        }
    }

    void DocumentOpenerFactory::writeFileFromExecPath(){
        std::stringstream file;

        for(auto execPath:_execPaths){
            for(auto path : execPath.second){
                file << execPath.first << " " << path.path << std::endl;
            }
        }
        
        FileOperate::writeFileText(AppConfiguration::getExecPath(_currentPath), file.str());
    }

    DocumentOpenerFactory::DocumentOpenerFactory(std::string current):_currentPath(current){
        readExecPathFromFile();
    }

    void DocumentOpenerFactory::Register(std::shared_ptr<DocumentOpener> opener){
        for(auto oldOpener : openers){
            if(oldOpener->getExecName() == opener->getExecName()){
                throw std::logic_error("试图注册2个相同名称的打开器");
            }
        }
        openers.push_back(opener);
    }

    // 注册内置的文档打开器
    void DocumentOpenerFactory::RegisterBuiltInOpener(){
        static bool isRegistered = false;
        if(isRegistered == true){
            return;
        }
        
        Register(std::make_shared<WordDocOpener>());
        Register(std::make_shared<TxtOpener>());
        isRegistered = true;
    }

    void DocumentOpenerFactory::registerExecPath(std::string execName, std::string execPath){
        bool isExist = false;
        for(auto oldExecPath : _execPaths[execName]){
            if(oldExecPath.path == execPath){
                isExist = true;
                break;
            }
        }

        if(!isExist){
            _execPaths[execName].push_back(ExecPath(execPath, FileOperate::isExistExecFile(execPath)));
            writeFileFromExecPath();
        }
    }

    std::shared_ptr<DocumentOpener> DocumentOpenerFactory::getDocumentOpener(std::string docPostfix) const{
        for(auto opener : openers){
            if(opener->isCanOpen(docPostfix)){
                return opener;
            }
        }

        return nullptr;
    }

    OpenResult DocumentOpenerFactory::open(std::string docPath){
        std::string postfix = FileOperate::getPostfix(docPath);
        if(postfix == "")
        {
            throw std::logic_error("文档不存在后缀，无法找到合适的程序用于打开文档");
        }

        std::shared_ptr<DocumentOpener> docOpener = getDocumentOpener(postfix);
        if(!docOpener){
            return OpenResult(OpenResultEnum::nonExistOpener, "");
        }

        auto execPaths = _execPaths[docOpener->getExecName()];
        std::string inputExecPath;
        for(auto execPath : execPaths){
            if(execPath.isExist == true){
                inputExecPath = execPath.path;
                break;
            }
        }

        if(inputExecPath == ""){
            return OpenResult(OpenResultEnum::unregisteredExecPath, docOpener->getExecName());
        }

        docOpener->open(docPath, inputExecPath);
        return OpenResult(OpenResultEnum::success, docOpener->getExecName());
    }
} // namespace DocFind
