#include <string>
#include <memory>
#include <fstream>
#include "../HeaderFiles/DocumentManager.hpp"
#include "../HeaderFiles/Directories.hpp"

namespace DocFind
{
    // 关键字到文档文件 的相对路径
    static std::string keyWordToDocFileRelativePath("/DocFinder/KeyWordToDocs.txt");

    // 获取 关键字到文档文件 的路径
    static std::string getKeyWordToDocFilePath(){
        return Directories::docFindDirPath +  keyWordToDocFileRelativePath;
    }

    // 根据路径查找文档，使用折中算法
    static int getDocIndexForPath(std::vector<std::shared_ptr<Document>> &docs, std::string path)
    {
        int minIndex = 0;
        int maxIndex = docs.size();
        int middleIndex = (minIndex + maxIndex) / 2;
        if((minIndex + maxIndex) % 2 > 0){
            middleIndex++;
        }

        while (true)
        {
            int result = docs[middleIndex]->relativePath.compare(path);
            if(result == 0){
                return middleIndex;
            }

            // 如果最大路径和最小路径相等则没有匹配
           if(minIndex == maxIndex){
                return -1;
            }

            // 如果 中间路径 > 比较的路径
            if(result > 0){
                maxIndex = middleIndex;
                // 这里生成的中间索引取较小的（如：(1+2)/2 等于 1.5，我们取 1 而不是2，因为 2 是原先的中间索引，而中间索引我们刚比较过）
                middleIndex = (minIndex + maxIndex) / 2;
                continue;
            }

            // 如果 中间路径 < 比较路径
            if(result < 0){
                minIndex = middleIndex;
                // 这里生成的中间索引取较大的（如：(1+2)/2 等于 1.5，我们取 2 而不是 1，因为 1 是原先的中间索引，而中间索引我们刚比较过）
                middleIndex = (minIndex + maxIndex) / 2;
                if((minIndex + maxIndex) % 2 > 0){
                    middleIndex++;
                }
                continue;
            }
        }
        
    }

    // 获取目录的所有文件
    static std::vector<std::shared_ptr<Document>> getDocuments(std::shared_ptr<DFFile> file)
    {
        std::vector<std::shared_ptr<Document>> files;

        if(!file->isDir){
            return files;
        }

        std::shared_ptr<Directories> dir = std::static_pointer_cast<Directories>(file);
        for(auto file : dir->childs) {
            if(file->isDir){
                auto childFiles = getDocuments(file);
                for(auto childFile : childFiles){
                    files.push_back(childFile);
                }
                continue;
            }

            files.push_back(std::static_pointer_cast<Document>(file));
        }

        return files;
    }

    // 从文件读取KeyWordToDoc
    void DocumentManager::readKeyWordToDocFromFile(std::string keyWordToDocFilePath)
    {
        // 实例 keyWordToDocs 列表
        keyWordToDocs = std::make_shared<std::vector<KeyWordToDoc>>(std::vector<KeyWordToDoc>());

        std::ifstream keyWordToDocFile;
        keyWordToDocFile.open(keyWordToDocFilePath);

        // 如果文件不存在，则创建文件
        if(!keyWordToDocFile){
            keyWordToDocFile.close();

            std::string path = DirectoriesOperate::getDirPath(keyWordToDocFilePath);
            DirectoriesOperate::createDir(path);

            std::ofstream keyWordToDocFileOutput;
            keyWordToDocFileOutput.open(keyWordToDocFilePath, std::fstream::out);
            keyWordToDocFileOutput.close();
            return;
        }

        std::string line;
        while (std::getline(keyWordToDocFile, line))
        {
            std::istringstream lineStringStram;
            lineStringStram.str(line);

            // 第一个为路径
            std::string path;
            lineStringStram >> path;

            // 其余为关键字
            std::vector<std::string> keys;
            std::string key;
            while (lineStringStram >> key)
            {
                keys.push_back(key);
            }
            
            KeyWordToDoc keyWordToDoc(path,  keys);
            keyWordToDocs->push_back(keyWordToDoc);
        }

        keyWordToDocFile.close();
    }

    DocumentManager::DocumentManager(std::string dirPath)
    {
        Directories::docFindDirPath = dirPath;
        _dir = std::make_shared<Directories>(Directories("", std::vector<std::string>()));
        readKeyWordToDocFromFile(getKeyWordToDocFilePath());
    }

    // 将KeyWordToDoc写入到文件
    void DocumentManager::writeKeyWordToDocToFile()
    {
        std::ofstream file(getKeyWordToDocFilePath());

        for(auto keyWordToDoc : *keyWordToDocs){
            file << keyWordToDoc.relativePath + " ";
            for(auto key : keyWordToDoc.keys)
            {
                file << key + " ";
            }
            file << std::endl;
        }

        file.close();
    }
    
    // 将关键字关联到文档
    void DocumentManager::addKeyWordToDoc(std::string key, std::shared_ptr<Document> doc)
    {
        KeyWordToDoc *oldKeyWordToDoc = nullptr;
        
        for(auto keyWordToDoc = keyWordToDocs->begin(); keyWordToDoc != keyWordToDocs->end(); keyWordToDoc++)
        {
            if(keyWordToDoc->relativePath == doc->relativePath){
                oldKeyWordToDoc = &*keyWordToDoc;
            }
        }

        if(oldKeyWordToDoc){
            // 判断旧的 oldKeyWordToDoc 是否包含该关键字
            bool isHadKey = false;
            for(auto oldKey : oldKeyWordToDoc->keys){
                if(oldKey.find(key) != oldKey.npos) {
                    isHadKey = true;
                    break;
                }
            }

            if(!isHadKey)
                oldKeyWordToDoc->keys.push_back(key);
        }
        else{
            KeyWordToDoc newKeyWordToDoc(doc->relativePath, { key });
            keyWordToDocs->push_back(newKeyWordToDoc);
        }

        doc->keys.push_back(key);

        writeKeyWordToDocToFile();
    }

    void DocumentManager::addKeyWordToDoc(std::string key, std::string docPath){
        int index = getDocIndexForPath(*keyDocument, docPath);
        if(index < 0){
            return;
        }

        addKeyWordToDoc(key, (*keyDocument)[index]);
    }

    // 将关键字添加到文档对象中
    void DocumentManager::addKeysToDocObject(std::vector<std::shared_ptr<Document>> &docs)
    {
        for(auto keyWordToDoc : *keyWordToDocs){
            int index = getDocIndexForPath(docs, keyWordToDoc.relativePath);
            if(index < 0){
                continue;
            }

            for(auto key : keyWordToDoc.keys){
                docs[index]->keys.push_back(key);
            }
        }
    }

    // 获取文档
    std::vector<std::shared_ptr<Document>> DocumentManager::getDocuments()
    {
        if(keyDocument){
            return *keyDocument;
        }
        std::vector<std::shared_ptr<Document>> docs = DocFind::getDocuments(_dir);
        addKeysToDocObject(docs);
        keyDocument = std::make_shared<std::vector<std::shared_ptr<Document>>>(docs);

        return *keyDocument;
    }
} // namespace DocFind
