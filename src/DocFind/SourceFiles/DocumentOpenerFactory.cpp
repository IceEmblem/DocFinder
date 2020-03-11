#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "../HeaderFiles/DocumentOpenerFactory.hpp"
#include "../HeaderFiles/DirectoriesOperate.hpp"
#include "../HeaderFiles/DocumentOpeners/WordDocOpener.hpp"

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

        isRegistered = true;
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

    OpenResult DocumentOpenerFactory::open(std::string docPath){
        static std::regex postfix("\\.([^\\.]+)$");
        std::smatch sresult;
        if (!std::regex_search(docPath, sresult, postfix))
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

        docOpener->open(docPath, execPath);
        return OpenResult(OpenResultEnum::success, docOpener->getExecName());
    }
} // namespace DocFind
